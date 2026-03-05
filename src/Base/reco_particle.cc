/**
 * @file reco_particle.cc
 * @brief Implementation of the RecoParticle class.
 * @author mueller@fnal.gov
*/
#include <array>
#include "H5Cpp.h"
#include "reco_particle.h"
#include "enums.h"
#include <iostream>

struct enum_ptr
{
    int64_t value;
    operator int64_t *() { return &value; }
};

namespace dlp::types
{
    /**
     * @brief Synchronize the BufferView objects with the current memory
     * locations.
    */
    void RecoParticle::SyncVectors()
    {
        fragment_ids.reset(&fragment_ids_handle);
        match_ids.reset(&match_ids_handle);
        match_overlaps.reset(&match_overlaps_handle);
        module_ids.reset(&module_ids_handle);
        ppn_ids.reset(&ppn_ids_handle);
    }

    /**
     * @brief Build the HDF5 compound type for the RecoParticle class.
     * 
     * The composite type for the RecoParticle class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the RecoParticle class.
    */
    template <>
    H5::CompType BuildCompType<RecoParticle>()
    {
        // Set the size of the compound type to the size of the RecoParticle.
        H5::CompType ctype(sizeof(RecoParticle));
	
        // Create a string type for the string fields in the RecoParticle.
        H5::StrType string_type(H5::PredType::C_S1, H5T_VARIABLE);
        string_type.setCset(H5T_CSET_UTF8);

        // Create the H5::EnumType objects for the enums used in the RecoParticle.
        H5::EnumType pid_enumtype(create_pid_enumtype());
        H5::EnumType semantic_type_enumtype(create_shape_enumtype());


        // Add the members of the RecoParticle to the compound type.
        ctype.insertMember("axial_spread", HOFFSET(RecoParticle, axial_spread), H5::PredType::IEEE_F32LE);
        ctype.insertMember("calo_ke", HOFFSET(RecoParticle, calo_ke), H5::PredType::IEEE_F32LE);
        ctype.insertMember("cathode_offset", HOFFSET(RecoParticle, cathode_offset), H5::PredType::IEEE_F64LE);
        ctype.insertMember("chi2_per_pid", HOFFSET(RecoParticle, chi2_per_pid), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{6}[0]));
        ctype.insertMember("chi2_pid", HOFFSET(RecoParticle, chi2_pid), H5::PredType::STD_I64LE);
        ctype.insertMember("csda_ke", HOFFSET(RecoParticle, csda_ke), H5::PredType::IEEE_F64LE);
        ctype.insertMember("csda_ke_per_pid", HOFFSET(RecoParticle, csda_ke_per_pid), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{6}[0]));
	    ctype.insertMember("depositions_sum", HOFFSET(RecoParticle, depositions_sum), H5::PredType::IEEE_F32LE);
        ctype.insertMember("directional_spread", HOFFSET(RecoParticle, directional_spread), H5::PredType::IEEE_F32LE);
        ctype.insertMember("end_dir", HOFFSET(RecoParticle, end_dir), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("end_point", HOFFSET(RecoParticle, end_point), H5::ArrayType(H5::PredType::IEEE_F32LE,  1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("fragment_ids", HOFFSET(RecoParticle, fragment_ids_handle), H5::VarLenType(H5::PredType::STD_I32LE));
        ctype.insertMember("id", HOFFSET(RecoParticle, id), H5::PredType::STD_I64LE);
        ctype.insertMember("index", HOFFSET(RecoParticle, index_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("interaction_id", HOFFSET(RecoParticle, interaction_id), H5::PredType::STD_I64LE);
        ctype.insertMember("is_cathode_crosser", HOFFSET(RecoParticle, is_cathode_crosser), H5::PredType::STD_U8LE);
        ctype.insertMember("is_contained", HOFFSET(RecoParticle, is_contained), H5::PredType::STD_U8LE);
        ctype.insertMember("is_matched", HOFFSET(RecoParticle, is_matched), H5::PredType::STD_U8LE);
        ctype.insertMember("is_primary", HOFFSET(RecoParticle, is_primary), H5::PredType::STD_U8LE);
        ctype.insertMember("is_time_contained", HOFFSET(RecoParticle, is_time_contained), H5::PredType::STD_U8LE);
        ctype.insertMember("is_truth", HOFFSET(RecoParticle, is_truth), H5::PredType::STD_U8LE);
        ctype.insertMember("is_valid", HOFFSET(RecoParticle, is_valid), H5::PredType::STD_U8LE);
        ctype.insertMember("ke", HOFFSET(RecoParticle, ke), H5::PredType::IEEE_F32LE);
        ctype.insertMember("length", HOFFSET(RecoParticle, length), H5::PredType::IEEE_F64LE);  
        ctype.insertMember("match_ids", HOFFSET(RecoParticle, match_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
	    ctype.insertMember("mass", HOFFSET(RecoParticle, mass), H5::PredType::IEEE_F64LE);
        ctype.insertMember("match_overlaps", HOFFSET(RecoParticle, match_overlaps_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
        ctype.insertMember("mcs_ke", HOFFSET(RecoParticle, mcs_ke), H5::PredType::IEEE_F64LE);
        ctype.insertMember("mcs_ke_per_pid", HOFFSET(RecoParticle, mcs_ke_per_pid), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{6}[0]));
        ctype.insertMember("module_ids", HOFFSET(RecoParticle, module_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
        ctype.insertMember("momentum", HOFFSET(RecoParticle, momentum), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
	    ctype.insertMember("num_fragments", HOFFSET(RecoParticle, num_fragments), H5::PredType::STD_I64LE);
        ctype.insertMember("p", HOFFSET(RecoParticle, p), H5::PredType::IEEE_F32LE);
        ctype.insertMember("pdg_code", HOFFSET(RecoParticle, pdg_code), H5::PredType::STD_I64LE);
        ctype.insertMember("pid", HOFFSET(RecoParticle, pid), pid_enumtype);
        ctype.insertMember("pid_scores", HOFFSET(RecoParticle, pid_scores), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{6}[0]));
        ctype.insertMember("ppn_ids", HOFFSET(RecoParticle, ppn_ids_handle), H5::VarLenType(H5::PredType::STD_I32LE));
        ctype.insertMember("primary_scores", HOFFSET(RecoParticle, primary_scores), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{2}[0]));
        ctype.insertMember("shape", HOFFSET(RecoParticle, shape), semantic_type_enumtype);
	    ctype.insertMember("size", HOFFSET(RecoParticle, size), H5::PredType::STD_I64LE);
        ctype.insertMember("start_dedx", HOFFSET(RecoParticle, start_dedx), H5::PredType::IEEE_F64LE);
        ctype.insertMember("start_dir", HOFFSET(RecoParticle, start_dir), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("start_point", HOFFSET(RecoParticle, start_point), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
        ctype.insertMember("start_straightness", HOFFSET(RecoParticle, start_straightness), H5::PredType::IEEE_F32LE);
        ctype.insertMember("units", HOFFSET(RecoParticle, units), string_type);
        ctype.insertMember("vertex_distance", HOFFSET(RecoParticle, vertex_distance), H5::PredType::IEEE_F32LE);

        return ctype;
    }
} // namespace dlp::types
