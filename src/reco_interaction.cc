/**
 * @file reco_interactions.cc
 * @brief Implementation of the RecoInteraction class.
 * @author mueller@fnal.gov
*/
#include <array>
#include "H5Cpp.h"
#include "reco_interaction.h"
#include <iostream>

namespace dlp::types
{
    /**
     * @brief Synchronize the BufferView objects with the current memory
     * locations.
    */
    void RecoInteraction::SyncVectors()
    {
        flash_ids.reset(&flash_ids_handle);
        flash_times.reset(&flash_times_handle);
        flash_volume_ids.reset(&flash_volume_ids_handle);
        index.reset(&index_handle);
        match_ids.reset(&match_ids_handle);
        match_overlaps.reset(&match_overlaps_handle);
        particle_ids.reset(&particle_ids_handle);
        module_ids.reset(&module_ids_handle);
    }

    /**
     * @brief Build the HDF5 compound type for the RecoInteraction class.
     * 
     * The composite type for the RecoInteraction class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the RecoInteraction class.
    */
    template <>
    H5::CompType BuildCompType<RecoInteraction>()
    {
        // Set the size of the compound type to the size of the RecoInteraction.
        H5::CompType ctype(sizeof(RecoInteraction));
        std::cout << "Refactored RecoInteraction loaded." << std::endl;

        // Create a string type for the string fields in the RecoInteraction.
        H5::StrType string_type(H5::PredType::C_S1, H5T_VARIABLE);
        string_type.setCset(H5T_CSET_UTF8);

        // Add the members of the RecoInteraction to the compound type.
        ctype.insertMember("cathode_offset", HOFFSET(RecoInteraction, cathode_offset), H5::PredType::IEEE_F64LE);
	    ctype.insertMember("depositions_sum", HOFFSET(RecoInteraction, depositions_sum), H5::PredType::IEEE_F32LE);
        ctype.insertMember("flash_hypo_pe", HOFFSET(RecoInteraction, flash_hypo_pe), H5::PredType::IEEE_F64LE);
        ctype.insertMember("flash_ids", HOFFSET(RecoInteraction, flash_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("flash_times", HOFFSET(RecoInteraction, flash_times_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
        ctype.insertMember("flash_total_pe", HOFFSET(RecoInteraction, flash_total_pe), H5::PredType::IEEE_F64LE);
        ctype.insertMember("flash_volume_ids", HOFFSET(RecoInteraction, flash_volume_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("id", HOFFSET(RecoInteraction, id), H5::PredType::STD_I64LE);
        ctype.insertMember("index", HOFFSET(RecoInteraction, index_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("is_cathode_crosser", HOFFSET(RecoInteraction, is_cathode_crosser), H5::PredType::STD_U8LE);
        ctype.insertMember("is_contained", HOFFSET(RecoInteraction, is_contained), H5::PredType::STD_U8LE);
        ctype.insertMember("is_fiducial", HOFFSET(RecoInteraction, is_fiducial), H5::PredType::STD_U8LE);
        ctype.insertMember("is_flash_matched", HOFFSET(RecoInteraction, is_flash_matched), H5::PredType::STD_U8LE);
        ctype.insertMember("is_matched", HOFFSET(RecoInteraction, is_matched), H5::PredType::STD_U8LE);
        ctype.insertMember("is_truth", HOFFSET(RecoInteraction, is_truth), H5::PredType::STD_U8LE);
        ctype.insertMember("match_ids", HOFFSET(RecoInteraction, match_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("match_overlaps", HOFFSET(RecoInteraction, match_overlaps_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
        ctype.insertMember("module_ids", HOFFSET(RecoInteraction, module_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
	    ctype.insertMember("num_particles", HOFFSET(RecoInteraction, num_particles), H5::PredType::STD_I64LE);
	    ctype.insertMember("particle_counts", HOFFSET(RecoInteraction, particle_counts), H5::ArrayType(H5::PredType::STD_I64LE, 1, &std::array<hsize_t, 1>{6}[0]));
        ctype.insertMember("particle_ids", HOFFSET(RecoInteraction, particle_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
	    ctype.insertMember("primary_particle_counts", HOFFSET(RecoInteraction, primary_particle_counts), H5::ArrayType(H5::PredType::STD_I64LE, 1, &std::array<hsize_t,1>{6}[0]));
	    ctype.insertMember("size", HOFFSET(RecoInteraction, size), H5::PredType::STD_I64LE);
        ctype.insertMember("topology", HOFFSET(RecoInteraction, topology), string_type);
        ctype.insertMember("units", HOFFSET(RecoInteraction, units), string_type);
        ctype.insertMember("vertex", HOFFSET(RecoInteraction, vertex), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));

        return ctype;
    }
} // namespace dlp::types
