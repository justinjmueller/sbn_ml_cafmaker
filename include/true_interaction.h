/**
 * @file true_interaction.h
 * @brief Definition of the TruthInteraction class.
 * @author mueller@fnal.gov
*/
#ifndef TRUE_INTERACTION_H
#define TRUE_INTERACTION_H

#include <array>
#include "buffer.h"
#include "composites.h"
#include "enums.h"

namespace dlp::types
{
    /**
     * @brief A class representing the truth interaction in the HDF5 file.
     * 
     * This class represents the truth interaction in the HDF5 file. It
     * contains truth information about the interaction that was stored by
     * SPINE. This includes information about the interaction itself and some
     * high-level information about the particles in the interaction.
     */
    struct TruthInteraction
    {
        double bjorken_x;                                   //!< Bjorken x of the neutrino interaction.
        double cathode_offset;                              //!< Distance from the cathode.
        std::string creation_process;                       //!< Creation process of the neutrino.
        CurrentType current_type;                           //!< Current type of the neutrino.
        float depositions_adapt_q_sum;                      //!< Total tagged (reco non-ghost) charge deposited [ADC].
        float depositions_adapt_sum;                        //!< Total tagged (reco non-ghost) energy deposited [MeV].
        float depositions_g4_sum;                           //!< Total energy deposited energy at the G4 level [MeV].
        float depositions_q_sum;                            //!< Total tagged (true non-ghost) charge deposited [ADC].
        float depositions_sum;                              //!< Total tagged (true non-ghost) energy deposited [MeV].
        double distance_travel;                             //!< Distance traveled by the neutrino from production to the interaction.
        double energy_init;                                 //!< Initial energy of the neutrino.
        double energy_transfer;                             //!< Energy transfer (Q0) of the neutrino interaction.
        double flash_hypo_pe;                               //!< Total PE of the hypothesized flash.
        BufferView<int32_t> flash_ids;                      //!< Flash ID for the matched flashes.
        BufferView<float> flash_scores;                     //!< Flash score for the matched flashes.
        BufferView<float> flash_times;                      //!< Time of the matched flashes.
        double flash_total_pe;                              //!< Total PE of the matched flash.
        BufferView<int32_t> flash_volume_ids;               //!< Volume IDs of the matched flashes.
        double hadronic_invariant_mass;                     //!< Hadronic invariant mass of the neutrino.
        int64_t id;                                         //!< Interaction ID.
        double inelasticity;                                //!< Inelasticity of the neutrino interaction.
        int64_t interaction_id;                             //!< Deprecated.
        InteractionMode interaction_mode;                   //!< Interaction mode of the neutrino.
        InteractionType interaction_type;                   //!< Interaction type of the neutrino.
        bool is_cathode_crosser;                            //!< Whether the interaction is a cathode-crosser.
        bool is_contained;                                  //!< Whether the interaction is contained.
        bool is_fiducial;                                   //!< Whether the interaction has an interaction in the fiducial volume.
        bool is_flash_matched;                              //!< Whether the flash is matched to the interaction.
        bool is_matched;                                    //!< Whether the interaction is matched to a true interaction.
        bool is_time_contained;                             //!< Whether the particle is time-contained (within the "in-time" region of the drift window).
        bool is_truth;                                      //!< Whether the interaction is a truth interaction.
        double lepton_p;                                    //!< Momentum of the lepton in the interaction.
        int64_t lepton_pdg_code;                            //!< PDG code of the lepton in the interaction.
        int64_t lepton_track_id;                            //!< Track ID of the lepton in the neutrino interaction.
        BufferView<int64_t> match_ids;                      //!< Interaction IDs of the considered matches (correspond to true interactions).
        BufferView<float> match_overlaps;                   //!< Intersection over union (IoU) of the considered matches.
        int64_t mct_index;                                  //!< Index of the neutrino in the original MCTruth array.
        BufferView<int64_t> module_ids;                     //!< Module IDs of the interaction.
        float momentum[3];                                  //!< Momentum (vector) of the neutrino.
        double momentum_transfer;                           //!< Momentum transfer (Q^2) of the neutrino interaction.
        double momentum_transfer_mag;                       //!< Momentum transfer (Q3) of the neutrino interaction.
        int64_t nu_id;                                      //!< Neutrino ID (-1 = not a neutrino, 0 = first neutrino, 1 = second neutrino, etc.).
        int64_t nucleon;                                    //!< Nucleon in the neutrino interaction.
        int64_t num_particles;                              //!< Number of particles in the interaction.
        int64_t num_primary_particles;                      //!< Number of primary particles in the interaction.
        int64_t orig_id;                                    //!< Original ID of the interaction.
        int64_t particle_counts[6];                         //!< Number of particles of each type in the interaction.
        BufferView<int64_t> particle_ids;                   //!< Particle IDs in the interaction.
        int64_t pdg_code;                                   //!< PDG code of the neutrino.
        float position[3];                                  //!< Position of the neutrino interaction.
        int64_t primary_particle_counts[6];                 //!< Number of primary particles of each type in the interaction.
        BufferView<int64_t> primary_particle_ids;           //!< Particle IDs of the primary particles in the interaction.
        int64_t quark;                                      //!< Quark in the neutrino interaction.
        float reco_vertex[3];                               //!< Vertex of the interaction in detector coordinates (reco).
        int64_t size;                                       //!< Number of true non-ghost true-tagged space points.
        int64_t size_adapt;                                 //!< Number of reco non-ghost true-tagged space points.
        int64_t size_g4;                                    //!< Number of (rasterized) g4 energy depositions (no detector effects).
        int64_t target;                                     //!< Target in the neutrino interaction.
        double theta;                                       //!< Angle of the neutrino interaction.
        std::string topology;                               //!< Topology of the interaction (e.g. "0g0e1mu0pi2p") considering only primaries.
        int64_t track_id;                                   //!< Track ID of the neutrino interaction.
        std::string units;                                  //!< Units in which the position coordinates are expressed.
        float vertex[3];                                    //!< Vertex of the interaction in detector coordinates (truth).

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
     * @brief Build the HDF5 compound type for the TruthInteraction class.
     * The composite type for the TruthInteraction class needs to be defined.
     * defined. This is handled using a template specialization of the
     * BuildCompType() function.
     * @return The HDF5 compound type for the TruthInteraction class.
    */
    template <>
    H5::CompType BuildCompType<TruthInteraction>();
} // namespace dlp::types
#endif // TRUE_INTERACTION_H
