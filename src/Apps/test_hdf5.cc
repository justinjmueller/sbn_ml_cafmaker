/**
 * @file test_hdf5.cc
 * @brief Simple test program for reading in H5 files.
 * @author mueller@fnal.gov
*/
#include <iostream>
#include <vector>
#include "H5Cpp.h"
#include "products.h"
#include "event.h"

/**
 * @brief A basic test program for reading in the H5 files produced by the
 * SPINE reconstruction code.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments. The first argument should be the
 * name of the input file. The second argument is optional and specifies the
 * event number to read in.
 * @return 0 if the program completes successfully.
*/
int main(int argc, char const * argv[])
{
    /**
     * @brief Check the arguments, verify a file name is provided, and set a
     * default event number in case it is not specified.
    */
    size_t event_number(0);
    if(argc < 2)
    {
        std::cerr << "Usage: ./test_hdf5 <input file>" << std::endl;
        return 0;
    }
    else if(argc == 3) event_number = std::stoi(argv[2]);

    /**
     * @brief Open the test input file.
    */
    std::string input_file(argv[1]);
    std::cout << "Reading in test file: " << input_file << std::endl;
    H5::H5File file(input_file, H5F_ACC_RDONLY);
    std::cout << "Opened test file: " << input_file << std::endl;
    
    /**
     * @brief Get the events from the file and print out the number of events.
    */
    std::vector<dlp::types::Event> events(get_all_events(file));
    std::vector<dlp::types::RunInfo> run_info(get_product<dlp::types::RunInfo>(file, events[event_number]));
    std::cout << "Number of events in file: " << events.size() << std::endl;
    
    /**
     * @brief Print out the run, subrun, and event numbers for the specified
     * event. This validates that the RunInfo product is being read in
     * correctly.
    */
    std::cout << "Run: " << run_info[0].run << std::endl;
    std::cout << "Subrun: " << run_info[0].subrun << std::endl;
    std::cout << "Event: " << run_info[0].event << std::endl;

    /**
     * @brief Get the reco and truth products from the file and print out the
     * number of reco and truth interactions and particles.
    */
    std::vector<dlp::types::RecoInteraction> reco_interactions(get_product<dlp::types::RecoInteraction>(file, events[event_number]));
    std::cout << "Number of reco interactions: " << reco_interactions.size() << std::endl;
    std::vector<dlp::types::RecoParticle> reco_particles(get_product<dlp::types::RecoParticle>(file, events[event_number]));
    std::cout << "Number of reco particles: " << reco_particles.size() << std::endl;
    std::vector<dlp::types::TruthInteraction> truth_interactions(get_product<dlp::types::TruthInteraction>(file, events[event_number]));
    std::cout << "Number of truth interactions: " << truth_interactions.size() << std::endl;
    std::vector<dlp::types::TruthParticle> truth_particles(get_product<dlp::types::TruthParticle>(file, events[event_number]));
    std::cout << "Number of truth particles: " << truth_particles.size() << std::endl;

    /**
     * @brief Close the input file.
    */
    file.close();

    return 0;
}