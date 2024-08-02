/**
 * @file runinfo.h
 * @brief Definition of the RunInfo class.
 * @author mueller@fnal.gov
*/
#ifndef RUNINFO_H
#define RUNINFO_H

#include <cstdint>
#include "H5Cpp.h"
#include "composites.h"

namespace dlp::types
{
    /**
     * @brief A class representing the run information in the HDF5 file.
     * 
     * This class represents the run information in the HDF5 file. It contains
     * information about the run that was stored by SPINE (run number, subrun,
     * event number).
    */
    struct RunInfo
    {
        int64_t run;                                 //!< Run number.
        int64_t subrun;                              //!< Subrun number.
        int64_t event;                               //!< Event number.

        /**
         * @brief Synchronize the BufferView objects.
         * 
         * For variable-length arrays, we need to keep track of memory in the
         * variable-length buffers. The SyncVectors() method is used to update
         * the BufferView<T> objects with the current memory locations. The
         * hvl_t objects are used to keep track of the memory locations for each
         * variable-length array.
        */
        void SyncVectors();
    };

    /**
     * @brief Build the HDF5 compound type for the RunInfo class.
     * The composite type for the RunInfo class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the RunInfo class.
    */
    template <>
    H5::CompType BuildCompType<RunInfo>();
} // namespace dlp::types
#endif // RUNINFO_H