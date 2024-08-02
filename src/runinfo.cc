/**
 * @file runinfo.cc
 * @brief Implementation of the RunInfo class.
 * @author mueller@fnal.gov
*/
#include <cstdint>
#include "H5Cpp.h"
#include "runinfo.h"
#include <iostream>

namespace dlp::types
{
    /**
     * @brief Synchronize the BufferView objects with the current memory
     * locations.
    */
    void RunInfo::SyncVectors()
    {
        // No variable-length arrays to synchronize.
    }

    /**
     * @brief Build the HDF5 compound type for the RunInfo class.
     * 
     * The composite type for the RunInfo class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the RunInfo class.
    */
    template <>
    H5::CompType BuildCompType<RunInfo>()
    {
        // Set the size of the compound type to the size of the RunInfo.
        H5::CompType ctype(sizeof(RunInfo));
        std::cout << "Refactored RunInfo loaded." << std::endl;

        // Add the members of the RunInfo to the compound type.
        ctype.insertMember("run", HOFFSET(RunInfo, run), H5::PredType::STD_I64LE);
        ctype.insertMember("subrun", HOFFSET(RunInfo, subrun), H5::PredType::STD_I64LE);
        ctype.insertMember("event", HOFFSET(RunInfo, event), H5::PredType::STD_I64LE);

        return ctype;
    }
} // namespace dlp::types