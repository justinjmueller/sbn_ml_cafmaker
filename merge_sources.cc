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

int main(int argc, char const * argv[])
{
    if(argc < 3)
    {
        std::cerr << "Usage: ./merge_sources <output_file> <input_caf_file> <input_h5_file>" << std::endl;
        return 0;
    }

    TFile input_caf(argv[2], "read");
    TTree *input_tree = (TTree*)input_caf.Get("recTree");
    caf::StandardRecord *rec = new caf::StandardRecord;
    input_tree->SetBranchAddress("rec", &rec);

    std::cout << "Number of events in CAF tree: " << input_tree->GetEntries() << std::endl;

    H5::H5File input_h5(argv[3], H5F_ACC_RDONLY);
    std::map<std::pair<size_t, size_t>, size_t> event_map;
    std::vector<dlp::types::Event> events(get_all_events(input_h5));
    for(size_t e(0); e < events.size(); ++e)
    {
        try
        {
            std::vector<dlp::types::RunInfo> run_info(get_product<dlp::types::RunInfo>(input_h5, events.at(e)));
            std::pair<size_t, size_t> index(std::make_pair(run_info.back().run, run_info.back().event));
            event_map.insert(std::make_pair(index, e));
            std::cout << "(Run, Event) = (" << index.first << ", " << index.second << ")" << std::endl;
        }
        catch(const H5::ReferenceException & e)
        {
            std::cerr << "Found incomplete entry for event." << std::endl;
        }
    }


    for(size_t n(0); n < input_tree->GetEntries(); ++n)
    {
        input_tree->GetEntry(n);
        std::cout << "Number of slices: " << rec->nslc << std::endl;
    }

    return 0;
}