/**
 * @file make_standalone.cc
 * @brief This file contains the main function for the standalone CAF generator.
 * @details The standalone CAF generator reads in a list of HDF5 files
 * containing SPINE reconstruction output and converts the data into the CAF
 * format. The output CAF file will contain the same data products as the input
 * HDF5 files, but in a format that is compatible with the CAFAna analysis
 * framework.
 * @note The standalone CAF generator is intended to be used for testing and
 * development purposes only. It is not intended for use in production analysis
 * workflows.
 * @author mueller@fnal.gov
 */
#include <iostream>
#include <vector>
#include <ctype.h>
#include "H5Cpp.h"

#include "include/record_fillers.h"
#include "include/products.h"
#include "include/event.h"
#include "include/reco_interaction.h"
#include "include/reco_particle.h"
#include "include/true_interaction.h"
#include "include/true_particle.h"

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
     * @brief Check that the required arguments are present.
     * @details The first argument is the name and path of the output CAF file.
     * The second argument is the offset to add to each image_id, which may be
     * useful in the case where each file has a separate indexing of images (from
     * batch processing). The final argument(s) is/are a list of input H5 files.
     */
    if(argc < 4)
    {
        std::cerr << "Usage: ./make_standalone <output file> <event offset> <input file(s)>" << std::endl;
        return 0;
    }

    /**
     * @brief Configure the output CAF file.
     * @details There must be a TTree with a specific name for holding the
     * StandardRecord entries. The "rec" object is used as the connection
     * between a locally-populated StandardRecord and the entries populating
     * the TTree.
     */
    TFile caf(argv[1], "recreate");
    TTree rec_tree("recTree", "Event tree for ML reconstruction");
    caf::StandardRecord *rec = new caf::StandardRecord;
    rec_tree.Branch("rec", &rec);

    /**
     * @brief Create total POT and total event histograms.
     * @details These are used internally within CAFAna for exposure/POT
     * accounting. Since this is a standalone CAF generator with no actual POT
     * information stored from the ML data products, only dummy values will be
     * used.
     */
    TH1F * pot = new TH1F("TotalPOT", "TotalPOT", 1, 0, 1);
    TH1F * nevt = new TH1F("TotalEvents", "TotalEvents", 1, 0, 1);

    /**
     * @brief Begin the main loop over input files.
     * @details Each HDF5 file will be opened and copied into the same output
     * CAF file.
     */
    for(size_t n(3); n < argc; ++n)
    {
        /**
         * @brief Open the input HDF5 file.
         * @details Configure the input HDF5 file and retrieve the list of all
         * events. The dlp::types::Event class contains only references to the
         * actual ML data products, so it is not overly heavy.
         */
        H5::H5File file(argv[n], H5F_ACC_RDONLY);
        std::cout << "Opened file: " << argv[n] << std::endl;    
        std::vector<dlp::types::Event> events(get_all_events(file));

        /**
         * @brief Loop over all events in the current HDF5 file.
        */
        for(dlp::types::Event &evt : events)
        {
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
            try
            {
                /**
                 * @brief Package the event data products.
                 * @details The @ref package_event() function is responsible
                 * for copying the data products from the event into the proper
                 * CAF class within the StandardRecord.
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
     * @brief Write the output CAF file.
     * @details Write the "rec" TTree, the POT, and the number events
     * histograms to the output CAF file.
    */
    pot->Write();
    nevt->Write();
    rec_tree.Write();

    /**
     * @brief Close the output file.
    */
    caf.Close();

    return 0;
}