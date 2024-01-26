#include <iostream>
#include <vector>
#include <ctype.h>
#include "H5Cpp.h"
#include "sbn_h5_classes.h"
#include "record_fillers.h"
#include "hdf5_utilities.h"
#include "sbnanaobj/StandardRecord/StandardRecord.h"
#include "sbnanaobj/StandardRecord/SRInteractionDLP.h"
#include "sbnanaobj/StandardRecord/SRInteractionTruthDLP.h"
#include "sbnanaobj/StandardRecord/SRParticleDLP.h"
#include "sbnanaobj/StandardRecord/SRParticleTruthDLP.h"
#include "TFile.h"
#include "TDirectoryFile.h"
#include "TTree.h"
#include "TH1D.h"

typedef std::pair<size_t, size_t> index_t;

int main(int argc, char const * argv[])
{
    /**
     * Check that the required arguments are present. The first argument is the
     * name and path of the output CAF file. The second argument is the name
     * and path of the input CAF which contains the reconstruction outputs from
     * the standard reconstruction pathway. The third argument is the input
     * HDF5 file with the ML reconstruction outputs for the same set of events.
    */
    if(argc < 3)
    {
        std::cerr << "Usage: ./merge_sources <output_file> <input_caf_file> <input_h5_file>" << std::endl;
        return 0;
    }

    /**
     * Configure the input HDF5 file. The merging code will need to access the
     * event records in the file once it has been matched to an event from the
     * input CAF file. This is done by building a map between (Run, Event No.)
     * and the dlp::types::Event object. This class contains only references to
     * the actual ML data products, so it is not overly heavy.
    */
    H5::H5File input_h5(argv[3], H5F_ACC_RDONLY);
    std::map<index_t, size_t> event_map;
    std::vector<dlp::types::Event> events(get_all_events(input_h5));
    for(size_t e(0); e < events.size(); ++e)
    {
        try
        {
            /**
             * For each event in the input HDF5 file, the run info is retrieved
             * and emplaced in a map that will allow for efficient lookup later
             * when copying data into the output CAF file.
            */
            std::vector<dlp::types::RunInfo> run_info(get_product<dlp::types::RunInfo>(input_h5, events.at(e)));
            index_t index(std::make_pair(run_info.back().run, run_info.back().event));
            event_map.insert(std::make_pair(index, e));
        }
        catch(const H5::ReferenceException & e)
        {
            std::cerr << "Found incomplete entry for event." << std::endl;
        }
    }

    /**
     * Configure the input CAF file. The merging code will need to attach to
     * the "recTree.rec" branch (StandardRecord) in order to copy them over
     * to a new file and simultaneously copy in the ML reconstruction outputs.
    */
    TFile input_caf(argv[2], "read");
    TTree *input_tree = (TTree*)input_caf.Get("recTree");
    caf::StandardRecord *rec = new caf::StandardRecord;
    input_tree->SetBranchAddress("rec", &rec);

    TFile output_caf(argv[1], "recreate");
    TTree *output_tree = new TTree("recTree", "records");
    output_tree->Branch("rec", &rec);

    /**
     * Begin main loop over records within the input CAF file. At each step,
     * check that there is a matching event in the HDF5 input file.
    */
    for(size_t n(0); n < input_tree->GetEntries(); ++n)
    {
        input_tree->GetEntry(n);

        /**
         * It is safest to reset the ML reconstruction output branches to
         * prevent old products from remaining in the case where no matching
         * data products are found in the H5 file.
        */ 
        rec->dlp.clear();
        rec->ndlp = 0;
        rec->dlp_true.clear();
        rec->ndlp_true = 0;

        index_t index(std::make_pair(rec->hdr.run, rec->hdr.evt));
        if(event_map.find(index) != event_map.end())
        {
            std::cout << "Matched Event " << index.second << " in Run " << index.first << " of CAF input to HDF5 event." << std::endl;
            try
            {
                package_event(rec, input_h5, events[event_map[index]]);
            }
            catch(const H5::ReferenceException & e)
            {
                std::cerr << "Found incomplete entry for event." << std::endl;
            }
        }
        output_tree->Fill();
    }

    /**
     * Write the data into the output CAF file. In addition to the TTree
     * containing the StandardRecord entries, there are also histograms for
     * storing the total POT and the total number of events and some other
     * TTrees storing environment stuff and metadata. The order probably
     * doesn't matter, but this maintains the same exact order as in the input
     * CAF file.
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
     * Finally, close both the input and output files. 
    */
    input_caf.Close();
    output_caf.Close();

    return 0;
}