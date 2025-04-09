/**
 * @file reco_interaction.h
 * @brief Definition of the RecoInteraction class.
 * @author mueller@fnal.gov
*/
#ifndef RECO_INTERACTION_H
#define RECO_INTERACTION_H

#include <array>
#include "buffer.h"
#include "composites.h"

namespace dlp::types
{
    /**
     * @brief A class representing the reconstructed interaction in the HDF5 file.
     * 
     * This class represents the reconstructed interaction in the HDF5 file. It
     * contains all of the information about the interaction that was reconstructed
     * by SPINE. This includes information about the interaction itself and some
     * high-level information about the particles in the interaction.
     */
    struct RecoInteraction
    {
        double cathode_offset;                              //!< Distance from the cathode.
        float depositions_sum;                              //!< Total tagged (true non-ghost) energy deposited [MeV].
        double flash_hypo_pe;                               //!< Total PE of the hypothesized flash.
        BufferView<int32_t> flash_ids;                      //!< Flash IDs for the matched flashes.
        BufferView<float> flash_scores;                     //!< Score of the matched flashes.
        BufferView<float> flash_times;                      //!< Time of the matched flashes
        double flash_total_pe;                              //!< Total PE of the matched flash.
        BufferView<int32_t> flash_volume_ids;               //!< Volume IDs of the matched flashes.
        int64_t id;                                         //!< Interaction ID.
        bool is_cathode_crosser;                            //!< Whether the interaction is a cathode-crosser.
        bool is_contained;                                  //!< Whether the interaction is contained.
        bool is_fiducial;                                   //!< Whether the interaction has an interaction in the fiducial volume.
        bool is_flash_matched;                              //!< Whether the flash is matched to the interaction.
        bool is_matched;                                    //!< Whether the interaction is matched to a true interaction.
        bool is_truth;                                      //!< Whether the interaction is a truth interaction.
        BufferView<int64_t> match_ids;                      //!< Interaction IDs of the considered matches (correspond to true interactions).
        BufferView<float> match_overlaps;                   //!< Intersection over union (IoU) of the considered matches.
        BufferView<int64_t> module_ids;                     //!< Module IDs of the interaction.
        int64_t num_particles;                              //!< The number of particles in the interaction.
        int64_t num_primary_particles;                      //!< The number of primary particles in the interaction.
        int64_t particle_counts[6];                         //!< The number of particles of each type in the interaction.
        BufferView<int64_t> particle_ids;                   //!< Particle IDs in the interaction.
        int64_t primary_particle_counts[6];                 //!< The number of primary particles of each type in the interaction.
        BufferView<int64_t> primary_particle_ids;           //!< Primary particle IDs in the interaction.
        int64_t size;                                       //!< The size of the interaction (number of voxels).
        std::string topology;                               //!< Topology of the interaction (e.g. "0g0e1mu0pi2p") considering only primaries.
        std::string units;                                  //!< Units in which the position coordinates are expressed.
        float vertex[3];                                    //!< Vertex of the interaction in detector coordinates.

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

        hvl_t flash_ids_handle;
        hvl_t flash_scores_handle;
        hvl_t flash_times_handle;
        hvl_t flash_volume_ids_handle;
        hvl_t match_ids_handle;
        hvl_t match_overlaps_handle;
        hvl_t module_ids_handle;
        hvl_t particle_ids_handle;
        hvl_t primary_particle_ids_handle;
    };

    /**
     * @brief Build the HDF5 compound type for the RecoInteraction class.
     * The composite type for the RecoInteraction class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the RecoInteraction class.
    */
    template <>
    H5::CompType BuildCompType<RecoInteraction>();
} // namespace dlp::types
#endif // RECO_INTERACTION_H
