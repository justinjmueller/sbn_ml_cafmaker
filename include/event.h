/**
 * @file event.h
 * @brief Definition of the Event class.
 * @author mueller@fnal.gov
*/
#ifndef EVENT_H
#define EVENT_H

#include "H5Cpp.h"
#include "runinfo.h"
#include "reco_interaction.h"
#include "reco_particle.h"
#include "true_interaction.h"
#include "true_particle.h"

namespace dlp::types
{
    /**
     * @brief A class representing the event information in the HDF5 file.
     * 
     * This class represents the top-level event information in the HDF5 file.
     * It contains references to the other compound objects in the file which
     * comprise the event. "Data" events do not have references to the truth
     * objects, so the corresponding fields must not be present in the "data"
     * version of this class. The "MC" version of this class contains
     * references to the truth objects. The solution to this is to use the
     * preprocessor to conditionally compile the class based on the presence of
     * the truth objects into two distinct libraries that can then be linked to
     * the appropriate code.
    */
    struct Event
    {
        hdset_reg_ref_t index;
        hdset_reg_ref_t meta;
        hdset_reg_ref_t run_info;
        hdset_reg_ref_t reco_interactions;
        hdset_reg_ref_t reco_particles;
        #ifdef MC_NOT_DATA
        hdset_reg_ref_t truth_interactions;
        hdset_reg_ref_t truth_particles;
        #endif
        
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

        /**
         * @brief Get a reference to the appropriate object in the event.
         * 
         * This method returns a reference to the appropriate object in the event
         * based on the type of the object requested. Note: "data" events do not
         * have references to the truth objects, so the corresponding fields must
         * not be present in the "data" version of this class. The solution to this
         * is to use the preprocessor to conditionally compile the class based on
         * the presence of the truth objects into two distinct libraries that can
         * then be linked to the appropriate code.
         * @tparam T The type of the object to retrieve.
         * @return A reference to the object in the event.
        */
        template <typename T>
        const hdset_reg_ref_t& GetRef() const;
    };
    extern template const hdset_reg_ref_t& Event::GetRef<RunInfo>() const;
    extern template const hdset_reg_ref_t& Event::GetRef<RecoInteraction>() const;
    extern template const hdset_reg_ref_t& Event::GetRef<RecoParticle>() const;
    #ifdef MC_NOT_DATA
    extern template const hdset_reg_ref_t& Event::GetRef<TruthInteraction>() const;
    extern template const hdset_reg_ref_t& Event::GetRef<TruthParticle>() const;
    #endif
} // namespace dlp::types
#endif // EVENT_H
