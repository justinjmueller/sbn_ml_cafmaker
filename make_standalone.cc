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
#include "TTree.h"
#include "TH1F.h"

int main(int argc, char const *argv[])
{
    /**
     * Check that the required arguments are present. The first argument is the
     * name and path of the output CAF file. The second argument is the offset to
     * add to each image_id, which may be useful in the case where each file has
     * a separate indexing of images (from batch processing). The final
     * argument(s) is/are a list of input H5 files.
    */
    if(argc < 4)
    {
        std::cerr << "Usage: ./ReadHDF5 <output file> <event offset> <input file(s)>" << std::endl;
        return 0;
    }

    /**
     * Configure the output CAF file. There must be a TTree with a specific
     * name for holding the StandardRecord entries. The "rec" object is used
     * as the connection between a locally-populated StandardRecord and the
     * entries populating the TTree.
    */
    TFile caf(argv[1], "recreate");
    TTree rec_tree("recTree", "Event tree for ML reconstruction");
    caf::StandardRecord *rec = new caf::StandardRecord;
    rec_tree.Branch("rec", &rec);

    /**
     * Create total POT and total event histograms. These are used internally
     * within CAFAna for exposure/POT accounting. Since this is a standalone
     * CAF generator with no actual POT information stored from the ML data
     * products, only dummy values will be used.
    */
    TH1F * pot = new TH1F("TotalPOT", "TotalPOT", 1, 0, 1);
    TH1F * nevt = new TH1F("TotalEvents", "TotalEvents", 1, 0, 1);

    /**
     * Begin main loop over input files. Each HDF5 file will be opened and
     * copied into the same output CAF file.
    */
    for(size_t n(3); n < argc; ++n)
    {
        /**
         * Configure the input HDF5 file and retrieve the list of all events.
         * The dlp::types::Event class contains only references to the actual
         * ML data products, so it is not overly heavy.
        */
        H5::H5File file(argv[n], H5F_ACC_RDONLY);
        std::cout << "Opened file: " << argv[n] << std::endl;    
        std::vector<dlp::types::Event> events(get_all_events(file));

        /**
         * Begin the main loop over events within the current HDF5 file.
        */
        for(dlp::types::Event &evt : events)
        {
            /**
             * It is safest to reset the ML reconstruction output branches to
             * prevent old products from remaining in the case where something
             * unexpected happens.
            */ 
            rec->dlp.clear();
            rec->ndlp = 0;
            rec->dlp_true.clear();
            rec->ndlp_true = 0;
            try
            {
                /**
                 * The package_event() function handles the copying of data
                 * products from the event into the proper CAF class within
                 * the StandardRecord.
                */
                package_event(rec, file, evt, std::atoi(argv[2]));
                std::vector<dlp::types::RunInfo> run_info(get_product<dlp::types::RunInfo>(file, evt));
                rec->hdr.run = run_info[0].run;
                rec->hdr.subrun = run_info[0].subrun;
                rec->hdr.evt = run_info[0].event;
                rec->hdr.pot = 1;
                rec->hdr.first_in_subrun = true;
                pot->Fill(1);
                nevt->Fill(1);
                rec_tree.Fill();
            }
            catch(const H5::ReferenceException & e)
            {
                std::cerr << "Found incomplete entry for event." << std::endl;
            }
        }
        file.close();
    }
    /**
     * Write the "rec" TTree, the POT, and the number events histograms to the
     * output CAF file.
    */
    pot->Write();
    nevt->Write();
    rec_tree.Write();

    /**
     * Finally, close the output file. 
    */
    caf.Close();

    return 0;
}

