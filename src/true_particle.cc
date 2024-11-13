/**
 * @file true_particle.cc
 * @brief Implementation of the TruthParticle class.
 * @author mueller@fnal.gov
*/
#include <array>
#include "H5Cpp.h"
#include "true_particle.h"
#include <iostream>

namespace dlp::types
{
    /**
     * @brief Synchronize the BufferView objects with the current memory
     * locations.
    */
    void TruthParticle::SyncVectors()
    {
        children_counts.reset(&children_counts_handle);
        fragment_ids.reset(&fragment_ids_handle);
        index.reset(&index_handle);
        match_ids.reset(&match_ids_handle);
        match_overlaps.reset(&match_overlaps_handle);
        module_ids.reset(&module_ids_handle);
        index_adapt.reset(&index_adapt_handle);
        index_g4.reset(&index_g4_handle);
        children_id.reset(&children_id_handle);
    }

    /**
     * @brief Build the HDF5 compound type for the TruthParticle class.
     * 
     * The composite type for the TruthParticle class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the TruthParticle class.
    */
    template <>
    H5::CompType BuildCompType<TruthParticle>()
    {
        // Set the size of the compound type to the size of the TruthParticle.
        H5::CompType ctype(sizeof(TruthParticle));
        std::cout << "Refactored TruthParticle loaded." << std::endl;

        // Create a string type for the string fields in the TruthParticle.
        H5::StrType string_type(H5::PredType::C_S1, H5T_VARIABLE);
        string_type.setCset(H5T_CSET_UTF8);

        // Create the H5::EnumType objects for the enums used in the TruthParticle.
        H5::EnumType pid_enumtype(create_pid_enumtype());
        H5::EnumType semantic_type_enumtype(create_shape_enumtype());

        // Add the members of the TruthParticle to the compound type.
        ctype.insertMember("ancestor_creation_process", HOFFSET(TruthParticle, ancestor_creation_process), string_type);
        ctype.insertMember("ancestor_pdg_code", HOFFSET(TruthParticle, ancestor_pdg_code), H5::PredType::STD_I64LE);
        ctype.insertMember("ancestor_position", HOFFSET(TruthParticle, ancestor_position), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("ancestor_t", HOFFSET(TruthParticle, ancestor_t), H5::PredType::IEEE_F64LE);
        ctype.insertMember("ancestor_track_id", HOFFSET(TruthParticle, ancestor_track_id), H5::PredType::STD_I64LE);
        ctype.insertMember("calo_ke", HOFFSET(TruthParticle, calo_ke), H5::PredType::IEEE_F64LE);
        ctype.insertMember("cathode_offset", HOFFSET(TruthParticle, cathode_offset), H5::PredType::STD_I64LE);
        ctype.insertMember("children_counts", HOFFSET(TruthParticle, children_counts_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("children_id", HOFFSET(TruthParticle, children_id_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("creation_process", HOFFSET(TruthParticle, creation_process), string_type);
        ctype.insertMember("csda_ke", HOFFSET(TruthParticle, csda_ke), H5::PredType::IEEE_F64LE);
        ctype.insertMember("csda_ke_per_pid", HOFFSET(TruthParticle, csda_ke_per_pid), H5::ArrayType(H5::PredType::IEEE_F64LE,  1, &std::array<hsize_t, 1>{6}[0]));
	    ctype.insertMember("depositions_adapt_q_sum", HOFFSET(TruthParticle, depositions_adapt_q_sum), H5::PredType::IEEE_F32LE);
        ctype.insertMember("depositions_adapt_sum", HOFFSET(TruthParticle, depositions_adapt_sum), H5::PredType::IEEE_F32LE);
	    ctype.insertMember("depositions_g4_sum", HOFFSET(TruthParticle, depositions_g4_sum), H5::PredType::IEEE_F32LE);
	    ctype.insertMember("depositions_q_sum", HOFFSET(TruthParticle, depositions_q_sum), H5::PredType::IEEE_F32LE);
        ctype.insertMember("depositions_sum", HOFFSET(TruthParticle, depositions_sum), H5::PredType::IEEE_F32LE);
	    ctype.insertMember("distance_travel", HOFFSET(TruthParticle, distance_travel), H5::PredType::IEEE_F64LE);
        ctype.insertMember("end_dir", HOFFSET(TruthParticle, end_dir), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("end_momentum", HOFFSET(TruthParticle, end_momentum), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("end_p", HOFFSET(TruthParticle, end_p), H5::PredType::IEEE_F32LE);
        ctype.insertMember("end_point", HOFFSET(TruthParticle, end_point), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("end_position", HOFFSET(TruthParticle, end_position), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
	    ctype.insertMember("end_t", HOFFSET(TruthParticle, end_t), H5::PredType::IEEE_F64LE);
        ctype.insertMember("energy_deposit", HOFFSET(TruthParticle, energy_deposit), H5::PredType::IEEE_F64LE);
        ctype.insertMember("energy_init", HOFFSET(TruthParticle, energy_init), H5::PredType::IEEE_F64LE);
        ctype.insertMember("first_step", HOFFSET(TruthParticle, first_step), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));	
        ctype.insertMember("fragment_ids", HOFFSET(TruthParticle, fragment_ids_handle), H5::VarLenType(H5::PredType::STD_I32LE));
        ctype.insertMember("gen_id", HOFFSET(TruthParticle, gen_id), H5::PredType::STD_I64LE);
        ctype.insertMember("group_id", HOFFSET(TruthParticle, group_id), H5::PredType::STD_I64LE);
        ctype.insertMember("group_primary", HOFFSET(TruthParticle, group_primary), H5::PredType::STD_I64LE);
        ctype.insertMember("id", HOFFSET(TruthParticle, id), H5::PredType::STD_I64LE);
        ctype.insertMember("index", HOFFSET(TruthParticle, index_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("index_adapt", HOFFSET(TruthParticle, index_adapt_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("index_g4", HOFFSET(TruthParticle, index_g4_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("interaction_id", HOFFSET(TruthParticle, interaction_id), H5::PredType::STD_I64LE);
        ctype.insertMember("interaction_primary", HOFFSET(TruthParticle, interaction_primary), H5::PredType::STD_I64LE);
        ctype.insertMember("is_cathode_crosser", HOFFSET(TruthParticle, is_cathode_crosser), H5::PredType::STD_U8LE);
        ctype.insertMember("is_contained", HOFFSET(TruthParticle, is_contained), H5::PredType::STD_U8LE);
        ctype.insertMember("is_matched", HOFFSET(TruthParticle, is_matched), H5::PredType::STD_U8LE);
        ctype.insertMember("is_primary", HOFFSET(TruthParticle, is_primary), H5::PredType::STD_U8LE);
        ctype.insertMember("is_truth", HOFFSET(TruthParticle, is_truth), H5::PredType::STD_U8LE);
        ctype.insertMember("is_valid", HOFFSET(TruthParticle, is_valid), H5::PredType::STD_U8LE);
        ctype.insertMember("ke", HOFFSET(TruthParticle, ke), H5::PredType::IEEE_F64LE);
        ctype.insertMember("last_step", HOFFSET(TruthParticle, last_step), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("length", HOFFSET(TruthParticle, length), H5::PredType::IEEE_F64LE);
	    ctype.insertMember("mass", HOFFSET(TruthParticle, mass), H5::PredType::IEEE_F64LE);	
        ctype.insertMember("match_ids", HOFFSET(TruthParticle, match_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("match_overlaps", HOFFSET(TruthParticle, match_overlaps_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
        ctype.insertMember("mcs_ke", HOFFSET(TruthParticle, mcs_ke), H5::PredType::IEEE_F64LE);
        ctype.insertMember("mcs_ke_per_pid", HOFFSET(TruthParticle, mcs_ke_per_pid), H5::ArrayType(H5::PredType::IEEE_F64LE,  1, &std::array<hsize_t, 1>{6}[0]));
        ctype.insertMember("mcst_index", HOFFSET(TruthParticle, mcst_index), H5::PredType::STD_I64LE);
        ctype.insertMember("mct_index", HOFFSET(TruthParticle, mct_index), H5::PredType::STD_I64LE);
        ctype.insertMember("module_ids", HOFFSET(TruthParticle, module_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("momentum", HOFFSET(TruthParticle, momentum), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("nu_id", HOFFSET(TruthParticle, nu_id), H5::PredType::STD_I64LE);
	    ctype.insertMember("num_fragments", HOFFSET(TruthParticle, num_fragments), H5::PredType::STD_I64LE);
        ctype.insertMember("num_voxels", HOFFSET(TruthParticle, num_voxels), H5::PredType::STD_I64LE);
        ctype.insertMember("orig_id", HOFFSET(TruthParticle, orig_id), H5::PredType::STD_I64LE);
        ctype.insertMember("orig_interaction_id", HOFFSET(TruthParticle, orig_interaction_id), H5::PredType::STD_I64LE);
        ctype.insertMember("p", HOFFSET(TruthParticle, p), H5::PredType::IEEE_F32LE);
        ctype.insertMember("parent_creation_process", HOFFSET(TruthParticle, parent_creation_process), string_type);
        ctype.insertMember("parent_id", HOFFSET(TruthParticle, parent_id), H5::PredType::STD_I64LE);
        ctype.insertMember("parent_pdg_code", HOFFSET(TruthParticle, parent_pdg_code), H5::PredType::STD_I64LE);	
        ctype.insertMember("parent_position", HOFFSET(TruthParticle, parent_position), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("parent_t", HOFFSET(TruthParticle, parent_t), H5::PredType::IEEE_F64LE);
        ctype.insertMember("parent_track_id", HOFFSET(TruthParticle, parent_track_id), H5::PredType::STD_I64LE);
        ctype.insertMember("pdg_code", HOFFSET(TruthParticle, pdg_code), H5::PredType::STD_I64LE);
        ctype.insertMember("pid", HOFFSET(TruthParticle, pid), pid_enumtype);
        ctype.insertMember("position", HOFFSET(TruthParticle, position), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("reco_end_dir", HOFFSET(TruthParticle, reco_end_dir), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("reco_length", HOFFSET(TruthParticle, reco_length), H5::PredType::IEEE_F64LE);
        ctype.insertMember("reco_start_dir", HOFFSET(TruthParticle, reco_start_dir), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("shape", HOFFSET(TruthParticle, shape), semantic_type_enumtype);	
        ctype.insertMember("size", HOFFSET(TruthParticle, size), H5::PredType::STD_I64LE);
        ctype.insertMember("size_adapt", HOFFSET(TruthParticle, size_adapt), H5::PredType::STD_I64LE);
        ctype.insertMember("size_g4", HOFFSET(TruthParticle, size_g4), H5::PredType::STD_I64LE);
        ctype.insertMember("start_dir", HOFFSET(TruthParticle, start_dir), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("start_point", HOFFSET(TruthParticle, start_point), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("t", HOFFSET(TruthParticle, t), H5::PredType::IEEE_F64LE);
        ctype.insertMember("track_id", HOFFSET(TruthParticle, track_id), H5::PredType::STD_I64LE);
        ctype.insertMember("units", HOFFSET(TruthParticle, units), string_type);
        
        return ctype;
    }
} // namespace dlp::types
