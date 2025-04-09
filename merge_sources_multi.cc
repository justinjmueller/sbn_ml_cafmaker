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
#include <ctype.h>
#include "H5Cpp.h"

#include "include/products.h"
#include "include/event.h"
#include "include/reco_interaction.h"
#include "include/reco_particle.h"
#include "include/true_interaction.h"
#include "include/true_particle.h"
#include "include/record_fillers.h"

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
     * file once it has been matched to an event from the input CAF file. This
     * is done by building a map between (Run, Event No.) and the @ref 
     * dlp::types::Event object. This class contains only references to the
     * actual SPINE data products, so it is not overly heavy. Because the input
     * HDF5 dataset in general is a list of files, the code will maintain a map
     * of events for each file.
     */
    std::map<index_t, std::pair<size_t, size_t> > event_map;
    std::map<size_t, H5::H5File> input_files;
    std::map<size_t, std::vector<dlp::types::Event> > events;
    for(size_t f(3); f < argc; ++f)
    {
        input_files.insert(std::make_pair(f, H5::H5File(argv[f], H5F_ACC_RDONLY)));
        events.insert(std::make_pair(f, get_all_events(input_files[f])));
        for(size_t e(0); e < events[f].size(); ++e)
        {
            try
            {
                /**
                 * @brief Retrieve the run info for the event.
                 * @details For each event in the input HDF5 file, the run info is
                 * retrieved and emplaced in a map that will allow for efficient
                 * lookup later when copying data into the output CAF file.
                 * @note The index is a tuple of (Run, Subrun, Event No.).
                 */
                std::vector<dlp::types::RunInfo> run_info(get_product<dlp::types::RunInfo>(input_files[f], events[f][e]));
                index_t index(run_info.back().run, run_info.back().subrun, run_info.back().event);
                event_map.insert(std::make_pair(index, std::make_pair(f, e)));
            }
            catch(const H5::ReferenceException & e)
            {
                std::cerr << "Found incomplete entry for event." << std::endl;
            }
        }
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
    size_t current_file(3);
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
        if(event_map.find(index) != event_map.end())
        {
            ++matched;
	        std::cout << "Matched Event " << std::get<2>(index) << " in (Run, Subrun) = (" << std::get<0>(index) << ", " << std::get<1>(index) << ") of CAF input to HDF5 event."
                      << " Found in file " << std::get<0>(event_map[index]) << " at index " << std::get<1>(event_map[index])
                      << " (" << argv[std::get<0>(event_map[index])] << ")"
                      << "."
                      << std::endl;
            /**
             * @brief Package the event data products.
             * @details The @ref package_event() function is responsible
             * for copying the data products from the event into the proper
             * CAF class within the StandardRecord.
             * @throw H5::ReferenceException if the event is incom
             */
            try
            {
                package_event(rec, input_files[std::get<0>(event_map[index])], events[std::get<0>(event_map[index])][std::get<1>(event_map[index])]);
            }
            catch(const H5::ReferenceException & e)
            {
                std::cerr << "Found incomplete entry for event." << std::endl;
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
    env->Write();
    TH1D *total_pot = (TH1D*)input_caf.Get("TotalPOT");
    total_pot->Write();
    TH1D *total_events = (TH1D*)input_caf.Get("TotalEvents");
    total_events->Write();
    output_tree->Write();
    TDirectoryFile *metadata = (TDirectoryFile*)input_caf.Get("metadata");
    metadata->Write();
    
    /**
     * @brief Close the input and output files. 
     */
    for(auto &f : input_files)
        f.second.close();
    input_caf.Close();
    output_caf.Close();

    std::cout << "Merged " << matched << " / " << matched+unmatched << " events from the input HDF5 file(s) into the output CAF file." << std::endl;

    return 0;
}
