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
        double calo_ke;                              //!< [MeV] Calorimetric kinetic energy.
        double cathode_offset;                       //!< [cm] Distance from the cathode.
        double csda_ke;                              //!< [MeV] Continuous-slowing-down-approximation kinetic energy.
        //double depositions_sum;                    //!< [MeV] Sum of energy depositions.
        std::array<float, 3> end_dir;                //!< Unit direction vector calculated at the particle end point.
        std::array<float, 3> end_point;              //!< [cm] End point (vector) of the particle.
        BufferView<int32_t> fragment_ids;            //!< Fragment IDs comprising the particle.
        int64_t id;                                  //!< Particle ID.
        BufferView<int64_t> index;                   //!< (???)
        int64_t interaction_id;                      //!< Parent interaction ID.
        bool is_cathode_crosser;                     //!< Whether the particle is a cathode-crosser.
        bool is_contained;                           //!< Whether the particle is contained.
        bool is_primary;                             //!< Whether the particle is a primary particle.
        //bool is_principal_match;                   //!< Whether the particle is the principal match.
        bool is_valid;                               //!< (???) Whether the particle is valid.
        double ke;                                   //!< (???) [MeV] Kinetic energy.
        double length;                               //!< [cm] Length of the particle.
        BufferView<int64_t> match_ids;               //!< Match ID.
        BufferView<float> match_overlaps;            //!< Match overlap.
        bool is_matched;                             //!< Whether the particle is matched.
        double mcs_ke;                               //!< [MeV] Multiple Coulomb scattering kinetic energy.
        std::array<float, 3> momentum;               //!< [MeV/c] Momentum (vector) of the particle.
        //int64_t nu_id;                             //!< Neutrino ID (-1 = not a neutrino, 0 = first neutrino, 1 = second neutrino, etc.).
        //int64_t num_fragments;                     //!< Number of fragments comprising the particle.
        int64_t pdg_code;                            //!< PDG code of the particle.
        Pid pid;                                     //!< Particle ID (see Pid enumeration).
        std::array<float, 5> pid_scores;             //!< PID softmax scores.
        std::array<float, 2> primary_scores;         //!< Primary softmax scores.
        Shape shape;                                 //!< Semantic type of the particle (see SemanticType enumeration).
        //int64_t size;                              //!< [voxels] Size of the particle.
        std::array<float, 3> start_dir;              //!< Unit direction vector calculated at the particle start point.
        std::array<float, 3> start_point;            //!< [cm] Start point (vector) of the particle.
        char * units;                                //!< Units in which the position coordinates are expressed.
        //int64_t volume_id;                         //!< Volume ID of the particle (0 = East Cryo/SBND, 1 = West Cryo)

        // NEW
        BufferView<float> module_ids;                //!< Module IDs of the particle.
        bool is_truth;                               //!< Whether the particle is a truth particle.
        float p;                                     //!< [MeV/c] Momentum magnitude.
        BufferView<int32_t> ppn_ids;                 //!< PPN IDs of the particle.
    
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