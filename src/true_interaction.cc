/**
 * @file true_interactions.cc
 * @brief Implementation of the TruthInteraction class.
 * @author mueller@fnal.gov
*/
#include <array>
#include "H5Cpp.h"
#include "true_interaction.h"
#include "enums.h"
#include <iostream>

namespace dlp::types
{
    /**
     * @brief Synchronize the BufferView objects with the current memory
     * locations.
    */
    void TruthInteraction::SyncVectors()
    {
        index.reset(&index_handle);
        match_ids.reset(&match_ids_handle);
        match_overlaps.reset(&match_overlaps_handle);
        particle_ids.reset(&particle_ids_handle);
        module_ids.reset(&module_ids_handle);
        index_adapt.reset(&index_adapt_handle);
        index_g4.reset(&index_g4_handle);
    }

    /**
     * @brief Build the HDF5 compound type for the TruthInteraction class.
     * 
     * The composite type for the TruthInteraction class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the TruthInteraction class.
    */
    template <>
    H5::CompType BuildCompType<TruthInteraction>()
    {
        // Set the size of the compound type to the size of the TruthInteraction.
        H5::CompType ctype(sizeof(TruthInteraction));
        std::cout << "Refactored TruthInteraction loaded." << std::endl;

        // Create a string type for the string fields in the TruthInteraction.
        H5::StrType string_type(H5::PredType::C_S1, H5T_VARIABLE);
        string_type.setCset(H5T_CSET_UTF8);

        // Create the H5::EnumType objects for the enums used in the TruthInteraction.
        H5::EnumType nu_current_type_enumtype(create_current_type_enumtype());
        H5::EnumType nu_interaction_mode_enumtype(create_interaction_mode_enumtype());
        H5::EnumType nu_interaction_type_enumtype(create_interaction_type_enumtype());

        ctype.insertMember("cathode_offset", HOFFSET(TruthInteraction, cathode_offset), H5::PredType::IEEE_F64LE);
        //ctype.insertMember("crthit_id", HOFFSET(TruthInteraction, crthit_id), H5::PredType::STD_I64LE);
        //ctype.insertMember("crthit_matched", HOFFSET(TruthInteraction, crthit_matched), H5::PredType::STD_U8LE);
        //ctype.insertMember("crthit_matched_particle_id", HOFFSET(TruthInteraction, crthit_matched_particle_id), H5::PredType::STD_I64LE);
        ctype.insertMember("flash_hypo_pe", HOFFSET(TruthInteraction, flash_hypo_pe), H5::PredType::IEEE_F64LE);
        ctype.insertMember("flash_id", HOFFSET(TruthInteraction, flash_id), H5::PredType::STD_I64LE);
        ctype.insertMember("flash_time", HOFFSET(TruthInteraction, flash_time), H5::PredType::IEEE_F64LE);
        ctype.insertMember("flash_total_pe", HOFFSET(TruthInteraction, flash_total_pe), H5::PredType::IEEE_F64LE);
        ctype.insertMember("is_flash_matched", HOFFSET(TruthInteraction, is_flash_matched), H5::PredType::STD_U8LE);
        ctype.insertMember("id", HOFFSET(TruthInteraction, id), H5::PredType::STD_I64LE);
        ctype.insertMember("index", HOFFSET(TruthInteraction, index_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("is_cathode_crosser", HOFFSET(TruthInteraction, is_cathode_crosser), H5::PredType::STD_U8LE);
        ctype.insertMember("is_contained", HOFFSET(TruthInteraction, is_contained), H5::PredType::STD_U8LE);
        ctype.insertMember("is_fiducial", HOFFSET(TruthInteraction, is_fiducial), H5::PredType::STD_U8LE);
        //ctype.insertMember("is_neutrino", HOFFSET(TruthInteraction, is_neutrino), H5::PredType::STD_U8LE);
        //ctype.insertMember("is_principal_match", HOFFSET(TruthInteraction, is_principal_match), H5::PredType::STD_U8LE);
        ctype.insertMember("match_ids", HOFFSET(TruthInteraction, match_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("match_overlaps", HOFFSET(TruthInteraction, match_overlaps_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
        ctype.insertMember("is_matched", HOFFSET(TruthInteraction, is_matched), H5::PredType::STD_U8LE);
        ctype.insertMember("bjorken_x", HOFFSET(TruthInteraction, bjorken_x), H5::PredType::IEEE_F64LE);
        ctype.insertMember("creation_process", HOFFSET(TruthInteraction, creation_process), string_type);
        ctype.insertMember("current_type", HOFFSET(TruthInteraction, nu_current_type), nu_current_type_enumtype);        
        //ctype.insertMember("nu_distance_travel", HOFFSET(TruthInteraction, nu_distance_travel), H5::PredType::IEEE_F64LE);
        //ctype.insertMember("energy_deposit", HOFFSET(TruthInteraction, nu_energy_deposit), H5::PredType::IEEE_F64LE);
        ctype.insertMember("energy_init", HOFFSET(TruthInteraction, nu_energy_init), H5::PredType::IEEE_F64LE);
        ctype.insertMember("hadronic_invariant_mass", HOFFSET(TruthInteraction, nu_hadronic_invariant_mass), H5::PredType::IEEE_F64LE);
        ctype.insertMember("nu_id", HOFFSET(TruthInteraction, nu_id), H5::PredType::STD_I64LE);
        ctype.insertMember("inelasticity", HOFFSET(TruthInteraction, inelasticity), H5::PredType::IEEE_F64LE);
        ctype.insertMember("interaction_mode", HOFFSET(TruthInteraction, interaction_mode), nu_interaction_mode_enumtype);
        ctype.insertMember("interaction_type", HOFFSET(TruthInteraction, interaction_type), nu_interaction_type_enumtype);
        ctype.insertMember("lepton_track_id", HOFFSET(TruthInteraction, lepton_track_id), H5::PredType::STD_I64LE);
        //ctype.insertMember("nu_mcst_index", HOFFSET(TruthInteraction, nu_mcst_index), H5::PredType::STD_I64LE);
        ctype.insertMember("mct_index", HOFFSET(TruthInteraction, nu_mct_index), H5::PredType::STD_I64LE);
        ctype.insertMember("momentum_transfer", HOFFSET(TruthInteraction, q2), H5::PredType::IEEE_F64LE);
        ctype.insertMember("nucleon", HOFFSET(TruthInteraction, nu_nucleon), H5::PredType::STD_I64LE);
        //ctype.insertMember("nu_num_voxels", HOFFSET(TruthInteraction, nu_num_voxels), H5::PredType::STD_I64LE);
        ctype.insertMember("momentum", HOFFSET(TruthInteraction, nu_p), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("pdg_code", HOFFSET(TruthInteraction, nu_pdg_code), H5::PredType::STD_I64LE);
        ctype.insertMember("position", HOFFSET(TruthInteraction, position), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("quark", HOFFSET(TruthInteraction, nu_quark), H5::PredType::STD_I64LE);
        //ctype.insertMember("nu_t", HOFFSET(TruthInteraction, nu_t), H5::PredType::IEEE_F64LE);
        ctype.insertMember("target", HOFFSET(TruthInteraction, nu_target), H5::PredType::STD_I64LE);
        ctype.insertMember("theta", HOFFSET(TruthInteraction, nu_theta), H5::PredType::IEEE_F64LE);
        ctype.insertMember("track_id", HOFFSET(TruthInteraction, nu_track_id), H5::PredType::STD_I64LE);
        //ctype.insertMember("nu_truth_id", HOFFSET(TruthInteraction, nu_truth_id), H5::PredType::STD_I64LE);
        //ctype.insertMember("num_particles", HOFFSET(TruthInteraction, num_particles), H5::PredType::STD_I64LE);
        //ctype.insertMember("num_primaries", HOFFSET(TruthInteraction, num_primaries), H5::PredType::STD_I64LE);
        //ctype.insertMember("particle_counts", HOFFSET(TruthInteraction, particle_counts), H5::ArrayType(H5::PredType::STD_I64LE, 1, &std::array<hsize_t, 1>{7}[0]));
        ctype.insertMember("particle_ids", HOFFSET(TruthInteraction, particle_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        //ctype.insertMember("primary_counts", HOFFSET(TruthInteraction, primary_counts), H5::ArrayType(H5::PredType::STD_I64LE, 1, &std::array<hsize_t, 1>{7}[0]));
        //ctype.insertMember("size", HOFFSET(TruthInteraction, size), H5::PredType::STD_I64LE);
        ctype.insertMember("topology", HOFFSET(TruthInteraction, topology), string_type);
        ctype.insertMember("orig_id", HOFFSET(TruthInteraction, orig_id), H5::PredType::STD_I64LE);
        //ctype.insertMember("truth_particle_counts", HOFFSET(TruthInteraction, truth_particle_counts_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        //ctype.insertMember("truth_primary_counts", HOFFSET(TruthInteraction, truth_primary_counts_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        //ctype.insertMember("truth_topology", HOFFSET(TruthInteraction, truth_topology), string_type);
        ctype.insertMember("vertex", HOFFSET(TruthInteraction, truth_vertex), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("units", HOFFSET(TruthInteraction, units), string_type);
        ctype.insertMember("reco_vertex", HOFFSET(TruthInteraction, reco_vertex), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
        //ctype.insertMember("vertex_mode", HOFFSET(TruthInteraction, vertex_mode), string_type);
        //ctype.insertMember("volume_id", HOFFSET(TruthInteraction, volume_id), H5::PredType::STD_I64LE);
        ctype.insertMember("module_ids", HOFFSET(TruthInteraction, module_ids_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
        ctype.insertMember("is_truth", HOFFSET(TruthInteraction, is_truth), H5::PredType::STD_U8LE);
        ctype.insertMember("index_adapt", HOFFSET(TruthInteraction, index_adapt_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("index_g4", HOFFSET(TruthInteraction, index_g4_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("lepton_pdg_code", HOFFSET(TruthInteraction, lepton_pdg_code), H5::PredType::STD_I64LE);
        ctype.insertMember("momentum_transfer_mag", HOFFSET(TruthInteraction, q3), H5::PredType::IEEE_F64LE);
        ctype.insertMember("interaction_id", HOFFSET(TruthInteraction, interaction_id), H5::PredType::STD_I64LE);
        ctype.insertMember("energy_transfer", HOFFSET(TruthInteraction, q0), H5::PredType::IEEE_F64LE);
        ctype.insertMember("lepton_p", HOFFSET(TruthInteraction, lepton_p), H5::PredType::STD_I64LE);
    
        return ctype;
    }
} // namespace dlp::types