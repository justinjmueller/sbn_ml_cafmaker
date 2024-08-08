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
        char * ancestor_creation_process;            //!< Geant4 creation process of the ancestor particle.
        int64_t ancestor_pdg_code;                   //!< PDG code of the ancestor particle.
        std::array<float, 3> ancestor_position;      //!< [cm] Position of the ancestor particle.
        double ancestor_t;                           //!< [ns] Time of the ancestor particle.
        int64_t ancestor_track_id;                   //!< Track ID of the ancestor particle.
        double calo_ke;                              //!< [MeV] Calorimetric kinetic energy.
        //double calo_ke_tng;                        //!< [MeV] Calorimetric kinetic energy (true-nonghost).
        BufferView<int64_t> children_counts;         //!< Number of children of the particle.
        double cathode_offset;                       //!< [cm] Distance from the cathode.
        char * creation_process;                     //!< Geant4 creation process of the particle.
        double csda_ke;                              //!< [MeV] Continuous-slowing-down-approximation kinetic energy.
        //double csda_ke_tng;                        //!< [MeV] Continuous-slowing-down-approximation kinetic energy (true-nonghost).
        //double depositions_sum;                    //!< [MeV] Sum of energy depositions.
        //double distance_travel;                    //!< [cm] Distance traveled by the particle.
        std::array<float, 3> end_dir;                //!< Unit direction vector calculated at the particle end point.
        std::array<float, 3> end_point;              //!< [cm] End point (vector) of the particle.
        std::array<float, 3> end_position;           //!< [cm] End position (vector) of the particle.
        double energy_deposit;                       //!< [MeV] Energy deposited by the particle.
        double energy_init;                          //!< [MeV] Initial energy of the particle.
        std::array<float, 3> first_step;             //!< [cm] Coordinates of the first step of the particle.
        BufferView<int64_t> fragment_ids;            //!< Fragment IDs comprising the particle.
        int64_t group_id;                            //!< Group ID of the particle.
        int64_t id;                                  //!< Particle ID.
        //int64_t image_id;                          //!< Image ID.
        BufferView<int64_t> index;                   //!< List of coordinate indices that comprise the particle.
        int64_t interaction_id;                      //!< Parent interaction ID.
        bool is_cathode_crosser;                     //!< Whether the particle is a cathode-crosser.
        bool is_contained;                           //!< Whether the particle is contained.
        bool is_primary;                             //!< Whether the particle is a primary particle.
        //bool is_principal_match;                   //!< Whether the particle is the principal match.
        bool is_valid;                               //!< (Whether the particle passes thresholds and counts towards topology.
        double ke;                                   //!< [MeV] Kinetic energy according to assumed best energy estimator (CSDA, calorimetric, or MCS).
        std::array<float, 3> last_step;              //!< [cm] Coordinates of the last step of the particle.
        double length;                               //!< [cm] Length of the particle.
        //double length_tng;                         //!< [cm] Length of the particle (true-nonghost).
        BufferView<int64_t> match_ids;               //!< Match ID.
        BufferView<float> match_overlaps;            //!< Match overlap.
        bool is_matched;                             //!< Whether the particle is matched.
        double mcs_ke;                               //!< [MeV] Multiple Coulomb scattering kinetic energy.
        //double mcs_ke_tng;                         //!< [MeV] Multiple Coulomb scattering kinetic energy (true-nonghost).
        int64_t mcst_index;                          //!< MCST index.
        int64_t mct_index;                           //!< Index of the particle in the original MCTruth array..
        std::array<float, 3> momentum;               //!< [MeV/c] Momentum (vector) of the particle.
        int64_t nu_id;                               //!< Neutrino ID (-1 = not a neutrino, 0 = first neutrino, 1 = second neutrino, etc.).
        //int64_t num_fragments;                     //!< Number of fragments comprising the particle.
        int64_t num_voxels;                          //!< Number of voxels comprising the particle.
        float p;                                     //!< [MeV/c] Momentum magnitude.
        char * parent_creation_process;              //!< Geant4 creation process of the parent particle.
        int64_t parent_id;                           //!< Parent particle ID.
        int64_t parent_pdg_code;                     //!< PDG code of the parent particle.
        std::array<float, 3> parent_position;        //!< [cm] Position of the parent particle.
        double parent_t;                             //!< [ns] Time of the parent particle.
        int64_t parent_track_id;                     //!< Track ID of the parent particle.
        int64_t pdg_code;                            //!< PDG code of the particle.
        Pid pid;                                     //!< Particle ID (see Pid enumeration).
        std::array<float, 3> position;               //!< [cm] Position of the particle.
        //double sed_depositions_MeV_sum;            //!< [MeV] Sum of energy depositions in the single-electron drift.
        //BufferView<int64_t> sed_index;             //!< (???)
        //int64_t sed_size;                          //!< (???)
        Shape shape;                                 //!< Semantic type of the particle (see SemanticType enumeration).
        //int64_t size;                              //!< [voxels] Size of the particle.
        std::array<float, 3> start_dir;              //!< Unit direction vector calculated at the particle start point.
        std::array<float, 3> start_point;            //!< [cm] Start point (vector) of the particle.
        double t;                                    //!< [ns] Time of the particle.
        int64_t track_id;                            //!< Track ID of the particle.
        //double truth_depositions_MeV_sum;          //!< [MeV] Sum of energy depositions in the truth.
        //double truth_depositions_sum;              //!< [ADC] Sum of depositions in the truth.
        //BufferView<int64_t> truth_index;           //!< (???)
        //std::array<double, 3> truth_momentum;      //!< [MeV/c] Momentum (vector) of the truth particle.
        //int64_t truth_size;                        //!< (???)
        std::array<double, 3> truth_start_dir;       //!< Unit direction vector calculated at the truth particle start point.
        char * units;                                //!< Units in which the position coordinates are expressed.
        //int64_t volume_id;                         //!< Volume ID of the particle (0 = East Cryo/SBND, 1 = West Cryo)

        // NEW
        BufferView<float> module_ids;                //!< Module IDs of the particle.
        bool is_truth;                               //!< Whether the particle is a truth particle.
        int64_t orig_id;                             //!< Original ID of the particle.
        BufferView<int64_t> index_adapt;             //!< (???)
        BufferView<int64_t> index_g4;                //!< (???)
        int64_t gen_id;                              //!< (???) Generator ID of the particle.
        int64_t interaction_primary;                 //!< (???) 
        int64_t group_primary;                       //!< (???)
        BufferView<int64_t> children_id;             //!< (???) ID of the children.
        std::array<float, 3> end_momentum;           //!< [MeV/c] Momentum (vector) of the particle at the end.
        float end_p;                                 //!< [MeV/c] Momentum magnitude of the particle at the end.
        int64_t orig_interaction_id;                 //!< (???) Original interaction ID.
        std::array<double, 3> truth_end_dir;         //!< Unit direction vector calculated at the truth particle end point.
        
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
        hvl_t index_handle;
        hvl_t match_ids_handle;
        hvl_t match_overlaps_handle;
        hvl_t module_ids_handle;
        hvl_t index_adapt_handle;
        hvl_t index_g4_handle;
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