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
        double cathode_offset;                       //!< [cm] Distance from the cathode.
        //int64_t crthit_id;                         //!< CRT hit ID for the matched CRT hit.
        //uint8_t crthit_matched;                    //!< Whether the CRT hit is matched to the interaction (0 or 1).
        //int64_t crthit_matched_particle_id;        //!< Particle ID corresponding to the matched CRT hit.
        double flash_hypo_pe;                        //!< [p.e.] Total PE of the hypothesized flash.
        int64_t flash_id;                            //!< [p.e.] Flash ID for the matched flash.
        double flash_time;                           //!< [us] Time of the matched flash.
        double flash_total_pe;                       //!< [p.e.] Total PE of the matched flash.
        bool is_flash_matched;                       //!< Whether the flash is matched to the interaction.
        int64_t id;                                  //!< Interaction ID.
        BufferView<int64_t> index;                   //!< (???)
        bool is_cathode_crosser;                     //!< Whether the interaction is a cathode-crosser.
        bool is_contained;                           //!< Whether the interaction is contained.
        bool is_fiducial;                            //!< Whether the interaction has an interaction in the fiducial volume.
        //bool is_neutrino;                          //!< Whether the interaction is a neutrino interaction.
        //bool is_principal_match;                   //!< (???) Whether the interaction is the principal match.
        BufferView<int64_t> match_ids;               //!< Interaction IDs of the considered matches (correspond to true interactions).
        BufferView<float> match_overlaps;            //!< Intersection over union (IoU) of the considered matches.
        bool is_matched;                             //!< Whether the interaction is matched to a true interaction.
        double bjorken_x;                            //!< Bjorken x of the neutrino interaction.
        char * creation_process;                     //!< Creation process of the neutrino.
        CurrentType nu_current_type;                 //!< Current type of the neutrino.
        //double nu_distance_travel;                 //!< [cm] Distance traveled by the neutrino.
        //double nu_energy_deposit;                  //!< [GeV] Energy deposited by the neutrino.
        double nu_energy_init;                       //!< [GeV] Initial energy of the neutrino.
        double nu_hadronic_invariant_mass;           //!< [GeV] Hadronic invariant mass of the neutrino.
        int64_t nu_id;                               //!< Neutrino ID (-1 = not a neutrino, 0 = first neutrino, 1 = second neutrino, etc.).
        double inelasticity;                         //!< Inelasticity of the neutrino interaction.
        InteractionMode interaction_mode;            //!< Interaction mode of the neutrino.
        InteractionType interaction_type;            //!< Interaction type of the neutrino.
        int64_t lepton_track_id;                     //!< Track ID of the lepton in the neutrino interaction.
        //int64_t nu_mcst_index;                     //!< MCST index of the neutrino interaction.
        int64_t nu_mct_index;                        //!< Index of the neutrino in the original MCTruth array.
        double q2;                                   //!< [GeV] Momentum transfer (Q^2) of the neutrino interaction.
        double q0;                                   //!< [GeV] Energy transfer (Q0) of the neutrino interaction.
        int64_t nu_nucleon;                          //!< Nucleon in the neutrino interaction.
        //int64_t nu_num_voxels;                     //!< Number of voxels in the neutrino interaction.
        std::array<float, 3> nu_p;                   //!< [GeV] Momentum (vector) of the neutrino.
        int64_t nu_pdg_code;                         //!< PDG code of the neutrino.
        std::array<float, 3> position;               //!< [cm] Position of the neutrino interaction.
        int64_t nu_quark;                            //!< Quark in the neutrino interaction.
        //double nu_t;                               //!< (???)
        int64_t nu_target;                           //!< Target in the neutrino interaction.
        double nu_theta;                             //!< [rad] Angle of the neutrino interaction.
        int64_t nu_track_id;                         //!< Track ID of the neutrino interaction.
        //int64_t nu_truth_id;                       //!< Truth ID of the neutrino interaction.
        //int64_t num_particles;                     //!< Number of particles in the interaction.
        //int64_t num_primaries;                     //!< Number of primary particles in the interaction.
        //std::array<int64_t, 7> particle_counts;    //!< Number of particles of each type in the interaction.
        BufferView<int64_t> particle_ids;            //!< Particle IDs in the interaction.
        //std::array<int64_t, 7> primary_counts;     //!< Number of primary particles of each type in the interaction.
        //int64_t size;                              //!< [voxels] Size of the interaction.
        char * topology;                             //!< Topology of the interaction (e.g. "0g0e1mu0pi2p") considering only primaries.
        int64_t orig_id;                             //!< Original ID of the interaction.
        //BufferView<int64_t> truth_particle_counts; //!< Number of particles of each type in the interaction.
        //BufferView<int64_t> truth_primary_counts;  //!< Number of primary particles of each type in the interaction.
        //char * truth_topology;                     //!< Topology of the interaction (e.g. "0g0e1mu0pi2p") considering only primaries.
        std::array<float, 3> truth_vertex;           //!< [cm] Vertex of the interaction in detector coordinates (truth).
        char * units;                                //!< Units in which the position coordinates are expressed.
        std::array<float, 3> reco_vertex;            //!< [cm] Vertex of the interaction in detector coordinates (reco).
        //char * vertex_mode;                          //!< (???)
        //int64_t volume_id;                           //!< Volume ID of the interaction (0 = East Cryo/SBND, 1 = West Cryo)

        // NEW
        BufferView<int32_t> module_ids;              //!< Module IDs of the interaction.
        bool is_truth;                               //!< Whether the interaction is a truth interaction.
        BufferView<int64_t> index_adapt;             //!< (???)
        BufferView<int64_t> index_g4;                //!< (???)
        int64_t lepton_pdg_code;                     //!< PDG code of the lepton in the interaction.
        double q3;                                   //!< [GeV/c] Momentum transfer (Q3) of the neutrino interaction.
        double lepton_p;                             //!< [GeV/c] Momentum of the lepton in the interaction.
        double lepton_theta;                         //!< [rad] Angle between incoming and outgoing leptons.
        std::array<float, 3> nu_momentum;            //!< [GeV/c] Momentum of the neutrino.
        int64_t interaction_id;                      //!< (???) Interaction ID.
        double energy_transfer;                      //!< [GeV] Energy transfer of the neutrino interaction.

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

        hvl_t index_handle;
        hvl_t match_ids_handle;
        hvl_t match_overlaps_handle;
        hvl_t particle_ids_handle;
        hvl_t module_ids_handle;
        hvl_t index_adapt_handle;
        hvl_t index_g4_handle;
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