/**
 * @file true_particle.h
 * @brief Definition of the TruthParticle class.
 * @author mueller@fnal.gov
*/
#ifndef TRUE_PARTICLE_H
#define TRUE_PARTICLE_H

#include <array>
#include "buffer.h"
#include "composites.h"
#include "enums.h"

namespace dlp::types
{
    /**
     * @brief A class representing the truth particle in the HDF5 file.
     * 
     * This class represents the true particle in the HDF5 file. It contains
     * information about the true particle that was stored by SPINE.
    */
    struct TruthParticle
    {
        std::string ancestor_creation_process;              //!< Geant4 creation process of the ancestor particle.
        int64_t ancestor_pdg_code;                          //!< PDG code of the ancestor particle.
        float ancestor_position[3];                         //!< Position of the ancestor particle.
        double ancestor_t;                                  //!< Time of the ancestor particle.
        int64_t ancestor_track_id;                          //!< Track ID of the ancestor particle.
        double calo_ke;                                     //!< Calorimetric kinetic energy.
        double cathode_offset;                              //!< Distance from the cathode.
        BufferView<int64_t> children_counts;                //!< Number of children of the particle.
        BufferView<int64_t> children_id;                    //!< List of particle ID of children particles.
        std::string creation_process;                       //!< Geant4 creation process of the particle.
        double csda_ke;                                     //!< Continuous-slowing-down-approximation kinetic energy.
        double csda_ke_per_pid[6];                          //!< CSDA kinetic energy per PID.
        float depositions_adapt_q_sum;                      //!< TO DO.
        float depositions_adapt_sum;                        //!< TO DO.
        int64_t depositions_g4_sum;                         //!< TO DO.
        float depositions_q_sum;                            //!< TO DO.
        float depositions_sum;                              //!< TO DO.
        double distance_travel;                             //!< TO DO.
        float end_dir[3];                                   //!< Unit direction vector calculated at the particle end point.
        float end_momentum[3];                              //!< Momentum (vector) of the particle at the end.
        float end_p;                                        //!< Momentum magnitude of the particle at the end.
        float end_point[3];                                 //!< End point (vector) of the particle.
        float end_position[3];                              //!< End position (vector) of the particle.
        double end_t;                                       //!< TO DO.
        double energy_deposit;                              //!< Energy deposited by the particle.
        double energy_init;                                 //!< Initial energy of the particle.
        float first_step[3];                                //!< Coordinates of the first step of the particle.
        BufferView<int32_t> fragment_ids;                   //!< Fragment IDs comprising the particle.
        int64_t gen_id;                                     //!< Generator ID of the particle (may differ from Geant4 or Supera ID).
        int64_t group_id;                                   //!< Group ID of the particle.
        int64_t group_primary;                              //!< Whether the particle is a primary within its group.
        int64_t id;                                         //!< Particle ID.
        int64_t interaction_id;                             //!< Parent interaction ID.
        int64_t interaction_primary;                        //!< Whether the particle is a primary within its interaction (equivalent to is_primary).
        bool is_cathode_crosser;                            //!< Whether the particle is a cathode-crosser.
        bool is_contained;                                  //!< Whether the particle is contained.
        bool is_matched;                                    //!< Whether the particle is matched.
        bool is_primary;                                    //!< Whether the particle is a primary particle.
        bool is_truth;                                      //!< Whether the particle is a truth particle.
        bool is_valid;                                      //!< (Whether the particle passes thresholds and counts towards topology.
        double ke;                                          //!< Kinetic energy according from best energy estimator (CSDA, calorimetric, or MCS).
        float last_step[3];                                 //!< Coordinates of the last step of the particle.
        double length;                                      //!< Length of the particle.
        double mass;                                        //!< TO DO.
        BufferView<int64_t> match_ids;                      //!< Match ID.
        BufferView<float> match_overlaps;                   //!< Match overlap.
        double mcs_ke;                                      //!< Multiple Coulomb scattering kinetic energy.
        double mcs_ke_per_pid[6];                           //!< MCS kinetic energy per PID.
        int64_t mcst_index;                                 //!< MCST index.
        int64_t mct_index;                                  //!< Index of the particle in the original MCTruth array..
        BufferView<int64_t> module_ids;                     //!< Module IDs of the particle.
        float momentum[3];                                  //!< Momentum (vector) of the particle.
        int64_t nu_id;                                      //!< Neutrino ID (-1 = not a neutrino, 0 = first neutrino, 1 = second neutrino, etc.).
        int64_t num_fragments;                              //!< TO DO.
        int64_t num_voxels;                                 //!< Number of voxels comprising the particle.
        int64_t orig_id;                                    //!< Original ID of the particle.
        int64_t orig_interaction_id;                        //!< Interaction ID as it was stored in the parent LArCV file under the interaction_id attribute.
        float p;                                            //!< Momentum magnitude.
        std::string parent_creation_process;                //!< Geant4 creation process of the parent particle.
        int64_t parent_id;                                  //!< Parent particle ID.
        int64_t parent_pdg_code;                            //!< PDG code of the parent particle.
        float parent_position[3];                           //!< Position of the parent particle.
        double parent_t;                                    //!< Time of the parent particle.
        int64_t parent_track_id;                            //!< Track ID of the parent particle.
        int64_t pdg_code;                                   //!< PDG code of the particle.
        Pid pid;                                            //!< Particle ID (see Pid enumeration).
        float position[3];                                  //!< Position of the particle.
        float reco_end_dir[3];                              //!< TO DO.
        double reco_ke;                                     //!< TO DO.
        double reco_length;                                 //!< TO DO.
        float reco_momentum[3];                             //!< TO DO.
        float reco_start_dir[3];                            //!< TO DO.
        Shape shape;                                        //!< Semantic type of the particle (see SemanticType enumeration).
        int64_t size;                                       //!< TO DO.
        int64_t size_adapt;                                 //!< TO DO.
        int64_t size_g4;                                    //!< TO DO.
        float start_dir[3];                                 //!< Unit direction vector calculated at the particle start point.
        float start_point[3];                               //!< Start point (vector) of the particle.
        double t;                                           //!< Time of the particle.
        int64_t track_id;                                   //!< Track ID of the particle.
        std::string units;                                  //!< Units in which the position coordinates are expressed.
        
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

        hvl_t children_counts_handle;
        hvl_t fragment_ids_handle;
        hvl_t match_ids_handle;
        hvl_t match_overlaps_handle;
        hvl_t module_ids_handle;
        hvl_t children_id_handle;
    };
    /**
     * @brief Build the HDF5 compound type for the TruthParticle class.
     * The composite type for the RecoParticle class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the TruthParticle class.
    */
    template <>
    H5::CompType BuildCompType<TruthParticle>();
} // namespace dlp::types

#endif // TRUE_PARTICLE_H
