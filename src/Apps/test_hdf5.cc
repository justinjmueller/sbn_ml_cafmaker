/**
 * @file test_hdf5.cc
 * @brief Simple test program for reading in H5 files.
 * @author mueller@fnal.gov
*/
#include <iostream>
#include <vector>
#include <spine/error.hpp>
#include <spine/reader.hpp>

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
    try
    {
        spine::Reader file(input_file);
        std::cout << "Opened test file: " << input_file << std::endl;

        /**
         * @brief Get the events from the file and print out the number of events.
        */
        std::cout << "Number of events in file: " << file.num_events() << std::endl;
        const spine::Event evt = file.event(event_number);

        /**
         * @brief Print out the run, subrun, and event numbers for the specified
         * event. This validates that the RunInfo product is being read in
         * correctly.
        */
        const spine::RunInfo * run_info = evt.run_info();
        if(!run_info)
        {
            std::cerr << "The file has no run_info." << std::endl;
            return 1;
        }
        std::cout << "Run: " << run_info->run << std::endl;
        std::cout << "Subrun: " << run_info->subrun << std::endl;
        std::cout << "Event: " << run_info->event << std::endl;

        /**
         * @brief Get the reco and truth products from the file and print out the
         * number of reco and truth interactions and particles.
        */
        std::cout << "Number of reco interactions: " << evt.reco_interactions().size() << std::endl;
        std::cout << "Number of reco particles: " << evt.reco_particles().size() << std::endl;
        std::cout << "Number of truth interactions: " << evt.truth_interactions().size() << std::endl;
        std::cout << "Number of truth particles: " << evt.truth_particles().size() << std::endl;
    }
    catch(const spine::Error & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
