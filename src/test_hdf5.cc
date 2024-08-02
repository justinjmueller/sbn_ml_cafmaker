/**
 * @file test_hdf5.cc
 * @brief Simple test program for reading in H5 files.
 * @author mueller@fnal.gov
*/
#include <iostream>
#include <vector>
#include "H5Cpp.h"
//#include "/exp/icarus/app/users/mueller/sbn_ml_cafmaker_spineworkshop2024/sbn_ml_cafmaker/test_classes.h"
//#include "/exp/icarus/app/users/mueller/sbn_ml_cafmaker_spineworkshop2024/sbn_ml_cafmaker/hdf5_utilities.h"
#include "products.h"
#include "event.h"
//#include "runinfo.h"

int main(int argc, char const * argv[])
{
    size_t event_number(0);
    if(argc < 2)
    {
        std::cerr << "Usage: ./test_hdf5 <input file>" << std::endl;
        return 0;
    }
    else if(argc == 3) event_number = std::stoi(argv[2]);

    // Open the test input file
    std::string input_file(argv[1]);
    std::cout << "Reading in test file: " << input_file << std::endl;
    H5::H5File file(input_file, H5F_ACC_RDONLY);
    std::cout << "Opened test file: " << input_file << std::endl;
    
    // Get the number of events in the file.
    std::vector<dlp::types::Event> events(get_all_events(file));
    std::vector<dlp::types::RunInfo> run_info(get_product<dlp::types::RunInfo>(file, events[event_number]));
    std::cout << "Number of events in file: " << events.size() << std::endl;
    
    //std::cout << events[0].index << std::endl;
    //std::cout << events[14].index << std::endl;
    std::cout << "Run: " << run_info[0].run << std::endl;
    std::cout << "Subrun: " << run_info[0].subrun << std::endl;
    std::cout << "Event: " << run_info[0].event << std::endl;

    std::vector<dlp::types::RecoInteraction> reco_interactions(get_product<dlp::types::RecoInteraction>(file, events[event_number]));
    std::cout << "Number of reco interactions: " << reco_interactions.size() << std::endl;

    std::vector<dlp::types::RecoParticle> reco_particles(get_product<dlp::types::RecoParticle>(file, events[event_number]));
    std::cout << "Number of reco particles: " << reco_particles.size() << std::endl;

    std::vector<dlp::types::TruthInteraction> truth_interactions(get_product<dlp::types::TruthInteraction>(file, events[event_number]));
    std::cout << "Number of truth interactions: " << truth_interactions.size() << std::endl;

    std::vector<dlp::types::TruthParticle> truth_particles(get_product<dlp::types::TruthParticle>(file, events[event_number]));
    std::cout << "Number of truth particles: " << truth_particles.size() << std::endl;

    file.close();

    return 0;
}