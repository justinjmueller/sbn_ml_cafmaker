/**
 * @file merge_sources.cc
 * @brief This file contains the main function for merging the outputs of the
 * standard reconstruction pathway with the SPINE reconstruction.
 * @details The merging code acts on a pair of input files: one CAF file with
 * the standard reconstruction outputs and one HDF5 file with the SPINE (ML)
 * reconstruction outputs. The code will copy-merge the data products from each
 * file into a new CAF file which contains both sets of data products.
 * @note The merging code is intended to be used for anything from testing to
 * full-scale production analysis workflows.
 */
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <memory>
#include <optional>
#include <ctype.h>
#include <spine/error.hpp>
#include <spine/reader.hpp>

#include "record_fillers.h"

#include "sbnanaobj/StandardRecord/StandardRecord.h"
#include "sbnanaobj/StandardRecord/SRInteractionDLP.h"
#include "sbnanaobj/StandardRecord/SRInteractionTruthDLP.h"
#include "sbnanaobj/StandardRecord/SRParticleDLP.h"
#include "sbnanaobj/StandardRecord/SRParticleTruthDLP.h"

#include "TFile.h"
#include "TDirectoryFile.h"
#include "TTree.h"
#include "TH1D.h"

typedef std::tuple<size_t, size_t, size_t> index_t;

/**
 * @brief Copy the key/val products from an event in the CAF file to the output
 * CAF file.
 * @details This function is used to copy the key/val products from the
 * input TDirectory to the output TDirectory. Specifically, this represents
 * metadata and environment variables that are stored in the input CAF file.
 * @param output The output TDirectory to copy to.
 * @param input The input TDirectory to copy from.
 * @param name The name of the TTree to copy.
 */
void copy_keyval_tree(TDirectory * output, TDirectory * input, const char * name)
{
    output->cd();
    if(input)
    {
        TDirectory * dir = output->mkdir(input->GetName());
        dir->cd();
        TTree * tree = static_cast<TTree *>(input->Get(name));
        TTree * new_tree = new TTree(name, tree->GetTitle());
        
        std::string key, value;
        std::string * pkey = &key;
        std::string * pvalue = &value;
        new_tree->Branch("key", &pkey);
        new_tree->Branch("value", &pvalue);
        tree->SetBranchAddress("key", &pkey);
        tree->SetBranchAddress("value", &pvalue);
        for(Long64_t i(0); i < tree->GetEntries(); ++i)
        {
            tree->GetEntry(i);
            new_tree->Fill();
        }
        new_tree->Write();
        output->cd();
    }
}
int main(int argc, char const * argv[])
{
    /**
     * @brief Check that the required arguments are present.
     * @details The first argument is the name and path of the output CAF file.
     * The second argument is the name and path of the input CAF which contains
     * the reconstruction outputs from the standard reconstruction pathway. The
     * third argument is the input HDF5 file with the SPINE reconstruction
     * outputs for the same set of events.
     * @note The two input files are assumed to correspond to the same parent
     * set of events. The merging code will match the events in the input CAF
     * file to the events in the input HDF5 file by (Run, Subrun, Event No.).
     */
    if(argc < 3)
    {
        std::cerr << "Usage: ./merge_sources <output_file> <input_caf_file> <input_h5_file(s)>" << std::endl;
        return 0;
    }

    if(argc > 28)
    {
        std::cerr << "You passed more than 25 input HDF5 files! Absolutely not!" << std::endl;
        return 0;
    }

    /**
     * @brief Configure the input HDF5 file(s).
     * @details The merging code will need to access the event records in the
     * files once they have been matched to an event from the input CAF file.
     * One spine-reader Reader serves all the input files: it counts their
     * events as one sequence, in the order given, and indexes them by
     * (Run, Subrun, Event No.) from the run_info products. If a (Run, Subrun,
     * Event No.) occurs more than once, the first one (in file order, then in
     * event order) is used. Only the products that this tool uses are
     * requested (the truth products only in MC mode).
     */
    spine::ReaderOptions options;
    options.products = {"run_info", "reco_particles", "reco_interactions"};
    #ifdef MC_NOT_DATA
    options.products.insert(options.products.end(), {"truth_particles", "truth_interactions"});
    #endif
    std::unique_ptr<spine::Reader> input_h5;
    try
    {
        input_h5 = std::make_unique<spine::Reader>(std::vector<std::string>(argv + 3, argv + argc), options);
    }
    catch(const spine::Error & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    /**
     * @brief Configure the output CAF file.
     * @details The merging code will need to attach to the "recTree.rec"
     * branch (StandardRecord) in order to copy them over to a new file and
     * simultaneously copy in the SPINE reconstruction outputs.
     */
    TFile input_caf(argv[2], "read");
    TTree *input_tree = (TTree*)input_caf.Get("recTree");
    caf::StandardRecord *rec = new caf::StandardRecord;
    input_tree->SetBranchAddress("rec", &rec);

    /**
     * @brief Configure the output CAF file.
     * @details There must be a TTree with a specific name for holding the 
     * StandardRecord entries. Since the code is modifying in-place the "rec"
     * object, the output TTree is set to track this same object. This means
     * that calling TTree::GetEntry() and TTree::Fill() with no intermediate
     * changes will effectively copy the StandardRecord entry.
     */
    TFile output_caf(argv[1], "recreate");
    TTree *output_tree = new TTree("recTree", "records");
    output_tree->Branch("rec", &rec);

    /**
     * @brief Begin main loop over records within the input CAF file.
     * @details At each step, check that there is a matching event in the HDF5
     * input file.
     */
    size_t matched(0), unmatched(0);
    for(size_t n(0); n < input_tree->GetEntries(); ++n)
    {
        input_tree->GetEntry(n);
        /**
         * @brief Reset the ML reconstruction output branches.
         * @details It is safest to reset the ML reconstruction output
         * branches to prevent old products from remaining in the case
         * where something unexpected happens.
         */  
        rec->dlp.clear();
        rec->ndlp = 0;
        rec->dlp_true.clear();
        rec->ndlp_true = 0;

        index_t index(rec->hdr.run, rec->hdr.subrun, rec->hdr.evt);
        std::optional<uint64_t> entry;
        try
        {
            entry = input_h5->find(std::get<0>(index), std::get<1>(index), std::get<2>(index));
        }
        catch(const spine::Error & e)
        {
            std::cerr << "Found incomplete entry for event: " << e.what() << std::endl;
        }
        if(entry)
        {
            ++matched;
            /**
             * @brief Package the event data products.
             * @details The @ref package_event() function is responsible
             * for copying the data products from the event into the proper
             * CAF class within the StandardRecord.
             * @throw spine::Error if the event cannot be read.
             */
            try
            {
                const spine::Event evt = input_h5->event(*entry);
                std::cout << "Matched Event " << std::get<2>(index) << " in (Run, Subrun) = (" << std::get<0>(index) << ", " << std::get<1>(index) << ") of CAF input to HDF5 event."
                          << " Found in file " << 3 + evt.file_index() << " at index " << evt.entry()
                          << " (" << argv[3 + evt.file_index()] << ")"
                          << "."
                          << std::endl;
                package_event(rec, evt);
            }
            catch(const spine::Error & e)
            {
                std::cerr << "Found incomplete entry for event: " << e.what() << std::endl;
            }
            output_tree->Fill();
        }
        else
        {
            ++unmatched;
            std::cerr << "No matching event found for (Run, Subrun, Event No.) = (" << rec->hdr.run << ", " << rec->hdr.subrun << ", " << rec->hdr.evt << ")." << std::endl;
        }
    }

    /**
     * @brief Write the data into the output CAF file.
     * @details In addition to the TTree containing the StandardRecord entries,
     * there are also histograms for storing the total POT and the total number
     * of events and some other TTrees storing environment stuff and metadata.
     * The order probably doesn't matter, but this maintains the same exact
     * order as in the input CAF file.
     */
    TDirectoryFile *env = (TDirectoryFile*)input_caf.Get("env");
    copy_keyval_tree(&output_caf, env, "envtree");
    TH1D *total_pot = (TH1D*)input_caf.Get("TotalPOT");
    total_pot->Write();
    TH1D *total_events = (TH1D*)input_caf.Get("TotalEvents");
    total_events->Write();
    output_tree->Write();
    TDirectoryFile * metadata = (TDirectoryFile*)input_caf.Get("metadata");
    copy_keyval_tree(&output_caf, metadata, "metatree");
    
    #ifdef MC_NOT_DATA
    /**
     * @brief Copy the globalTree and the GenieEvtRecTree
     */
    TTree * global_tree = (TTree*)input_caf.Get("globalTree");
    if(global_tree)
    {
        output_caf.cd();
        TTree * clone = global_tree->CloneTree(-1, "fast");
        clone->Write();
        delete clone;
    }
    TTree * genie_tree = (TTree*)input_caf.Get("GenieEvtRecTree");
    if(genie_tree)
    {
        output_caf.cd();
        TTree * clone = genie_tree->CloneTree(-1, "fast");
        clone->Write();
        delete clone;
    }
    #endif

    /**
     * @brief Close the input and output files. 
     */
    input_caf.Close();
    output_caf.Close();

    std::cout << "Merged " << matched << " / " << matched+unmatched << " events from the input HDF5 file(s) into the output CAF file." << std::endl;

    return 0;
}
