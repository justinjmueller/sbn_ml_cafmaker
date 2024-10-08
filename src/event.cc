/**
 * @file event.cc
 * @brief Implementation of the Event class.
 * @author mueller@fnal.gov
*/
#include "H5Cpp.h"
#include "event.h"
#include <iostream>

namespace dlp::types
{
    /**
     * @brief Synchronize the BufferView objects.
    */
    void Event::SyncVectors()
    {
        // No variable-length arrays to synchronize.
    }

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
     * @tparam type The type of object to return.
     * @return A reference to the appropriate object in the event.
    */
    template <typename T>
    const hdset_reg_ref_t& Event::GetRef() const
    {
        if constexpr(std::is_same_v<T, RunInfo>) return run_info;   
        else if(std::is_same_v<T, RecoInteraction>) return reco_interactions;
        else if(std::is_same_v<T, RecoParticle>) return reco_particles;
        #ifdef MC_NOT_DATA
        else if(std::is_same_v<T, TruthInteraction>) return truth_interactions;
        else if(std::is_same_v<T, TruthParticle>) return truth_particles;
        #endif
    }

    template const hdset_reg_ref_t& Event::GetRef<RunInfo>() const;
    template const hdset_reg_ref_t& Event::GetRef<RecoInteraction>() const;
    template const hdset_reg_ref_t& Event::GetRef<RecoParticle>() const;
    #ifdef MC_NOT_DATA
    template const hdset_reg_ref_t& Event::GetRef<TruthInteraction>() const;
    template const hdset_reg_ref_t& Event::GetRef<TruthParticle>() const;
    #endif

    /**
     * @brief Build the HDF5 compound type for the Event class.
     * 
     * The composite type for the Event class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function. Note: "data" events do not have references to
     * the truth objects, so the corresponding fields must not be present in the
     * "data" version of this class. The solution to this is to use the
     * preprocessor to conditionally compile the class based on the presence of
     * the truth objects into two distinct libraries that can then be linked to
     * the appropriate code.
     * @return The HDF5 compound type for the Event class.
    */
    template <>
    H5::CompType BuildCompType<Event>()
    {
        // Set the size of the compound type to the size of the Event.
        H5::CompType ctype(sizeof(Event));
        std::cout << "Refactored Event loaded." << std::endl;

        // Add the members of the Event to the compound type.
        ctype.insertMember("index", HOFFSET(Event, index), H5::PredType::STD_REF_DSETREG);
        ctype.insertMember("meta", HOFFSET(Event, meta), H5::PredType::STD_REF_DSETREG);
        ctype.insertMember("run_info", HOFFSET(Event, run_info), H5::PredType::STD_REF_DSETREG);
        ctype.insertMember("reco_interactions", HOFFSET(Event, reco_interactions), H5::PredType::STD_REF_DSETREG);
        ctype.insertMember("reco_particles", HOFFSET(Event, reco_particles), H5::PredType::STD_REF_DSETREG);
        #ifdef MC_NOT_DATA
        ctype.insertMember("truth_interactions", HOFFSET(Event, truth_interactions), H5::PredType::STD_REF_DSETREG);
        ctype.insertMember("truth_particles", HOFFSET(Event, truth_particles), H5::PredType::STD_REF_DSETREG);
        #endif
        //ctype.insertMember("crthits", HOFFSET(Event, crthits), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("depositions", HOFFSET(Event, depositions), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("depositions_label", HOFFSET(Event, depositions_label), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("depositions_q_label", HOFFSET(Event, depositions_q_label), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("flash_cryoE", HOFFSET(Event, flash_cryoE), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("flash_cryoW", HOFFSET(Event, flash_cryoW), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("info", HOFFSET(Event, info), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("points", HOFFSET(Event, points), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("points_g4", HOFFSET(Event, points_g4), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("points_label", HOFFSET(Event, points_label), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("sources", HOFFSET(Event, sources), H5::PredType::STD_REF_DSETREG);
        //ctype.insertMember("sources_label", HOFFSET(Event, sources_label), H5::PredType::STD_REF_DSETREG);

        return ctype;
    }

} // namespace dlp::types
