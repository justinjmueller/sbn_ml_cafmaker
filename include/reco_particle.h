/**
 * @file reco_particle.h
 * @brief Definition of the RecoParticle class.
 * @author mueller@fnal.gov
*/
#ifndef RECO_PARTICLE_H
#define RECO_PARTICLE_H

#include <array>
#include "buffer.h"
#include "composites.h"
#include "enums.h"

namespace dlp::types
{
    /**
     * @brief A class representing the reconstructed particle in the HDF5 file.
     * 
     * This class represents the reconstructed particle in the HDF5 file. It
     * contains information about the reconstructed particle that was stored by
     * SPINE.
    */
    struct RecoParticle
    {
        float axial_spread;                                 //!< Axial spread of the particle.
        float calo_ke;                                      //!< Calorimetric kinetic energy.
        double cathode_offset;                              //!< Distance from the cathode.
        float chi2_per_pid[6];                              //!< Chi2 score per PID hypothesis.
        int64_t chi2_pid;                                   //!< PID from the chi2-based PID.
        double csda_ke;                                     //!< Continuous-slowing-down-approximation kinetic energy.
        float csda_ke_per_pid[6];                           //!< CSDA kinetic energy per PID.
        float depositions_sum;                              //!< Total tagged (true non-ghost) energy deposited [MeV].
        float directional_spread;                           //!< Directional spread of the particle.
        float end_dir[3];                                   //!< Unit direction vector calculated at the particle end point.
        float end_point[3];                                 //!< End point (vector) of the particle.
        BufferView<int32_t> fragment_ids;                   //!< Fragment IDs comprising the particle.
        int64_t id;                                         //!< Particle ID.
        int64_t interaction_id;                             //!< Parent interaction ID.
        bool is_cathode_crosser;                            //!< Whether the particle is a cathode-crosser.
        bool is_contained;                                  //!< Whether the particle is contained.
        bool is_matched;                                    //!< Whether the particle is matched.
        bool is_primary;                                    //!< Whether the particle is a primary particle.
        bool is_truth;                                      //!< Whether the particle is a truth particle.
        bool is_valid;                                      //!< Whether the particle passes thresholds and counts towards topology.
        float ke;                                           //!< Kinetic energy from best energy estimator (CSDA, calorimetric, or MCS).
        double length;                                      //!< Length of the particle.
        double mass;                                        //!< Mass of the particle (according to assigned PID).
        BufferView<int64_t> match_ids;                      //!< Match ID.
        BufferView<float> match_overlaps;                   //!< Match overlap.
        double mcs_ke;                                      //!< Multiple Coulomb scattering kinetic energy.
        float mcs_ke_per_pid[6];                            //!< MCS kinetic energy per PID.
        BufferView<int64_t> module_ids;                     //!< Module IDs of the particle.
        float momentum[3];                                  //!< Momentum (vector) of the particle.
        int64_t num_fragments;                              //!< Number of fragments comprising the particle.
        float p;                                            //!< Momentum magnitude.
        int64_t pdg_code;                                   //!< PDG code of the particle.
        Pid pid;                                            //!< Particle ID (see Pid enumeration).
        float pid_scores[6];                                //!< PID softmax scores.
        BufferView<int32_t> ppn_ids;                        //!< PPN IDs of the particle.
        float primary_scores[2];                            //!< Primary softmax scores.
        Shape shape;                                        //!< Semantic type of the particle (see Shape enumeration).
        int64_t size;                                       //!< Number of voxels comprising the particle.
        double start_dedx;                                  //!< dE/dx at the start of the particle.
        float start_dir[3];                                 //!< Unit direction vector calculated at the particle start point.
        float start_point[3];                               //!< Start point (vector) of the particle.
        float start_straightness;                           //!< Straightness at the start of the particle.
        std::string units;                                  //!< Units in which the position coordinates are expressed.
        float vertex_distance;                              //!< Distance from the vertex.
    
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

        hvl_t fragment_ids_handle;
        hvl_t index_handle;
        hvl_t match_ids_handle;
        hvl_t match_overlaps_handle;
        hvl_t module_ids_handle;
        hvl_t ppn_ids_handle;
    };
    /**
     * @brief Build the HDF5 compound type for the RecoParticle class.
     * The composite type for the RecoParticle class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the RecoParticle class.
    */
    template <>
    H5::CompType BuildCompType<RecoParticle>();
} // namespace dlp::types

#endif // RECO_PARTICLE_H
