/**
 * @file test_caf.cc
 * @brief Simple test program for reading in CAF files.
 * @author mueller@fnal.gov
*/
#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "sbnanaobj/StandardRecord/StandardRecord.h"

/**
 * @brief A basic test program for reading in the CAF files produced by the
 * standard CAFMaker code/sbn_ml_cafmaker
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
        std::cerr << "Usage: ./test_caf <input file>" << std::endl;
        return 0;
    }
    else if(argc == 3) event_number = std::stoi(argv[2]);

    /**
     * @brief Open the input file and check if it is valid.
    */
    TFile * f = new TFile(argv[1], "READ");
    if(f->IsZombie())
    {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    /**
     * @brief Create a StandardRecord object to hold the data from the CAF
     * file.
    */
    caf::StandardRecord * sr = new caf::StandardRecord();

    /**
     * @brief Create a TTree object to hold the data from the CAF file and
     * connect the StandardRecord object to it.
    */
    TTree * tree = (TTree*)f->Get("recTree");
    tree->SetBranchAddress("rec", &sr);

    /**
     * @brief Read in the event from the CAF file and print out some basic
     * information.
    */
    tree->GetEntry(event_number);
    std::cout << "Run: " << sr->hdr.run << std::endl;
    std::cout << "Subrun: " << sr->hdr.subrun << std::endl;
    std::cout << "Event: " << sr->hdr.evt << std::endl;

    /**
     * @brief Clean up the memory and close the input file.
    */
    delete sr;
    f->Close();

    return 0;
}