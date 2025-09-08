/**
 * @file record_fillers.cc
 * @brief Implementation of various functions for filling the SPINE
 * reconstruction output objects for use within the CAF files.
 * @details This file contains the implementation of the functions that are
 * responsible for copying the SPINE reconstruction output data products from
 * the HDF5 files into the CAF objects. The functions are designed to be
 * called from either the standalone CAF generator or the merged CAF generator.
 * @author mueller@fnal.gov
 */
#include <vector>
#include <ctype.h>
#include "H5Cpp.h"

#include "record_fillers.h"
#include "event.h"
#include "reco_interaction.h"
#include "reco_particle.h"
#include "true_interaction.h"
#include "true_particle.h"

#include "sbnanaobj/StandardRecord/StandardRecord.h"

caf::SRParticleTruthDLP fill_truth_particle(dlp::types::TruthParticle &p, uint64_t offset)
{
    p.children_counts.reset(&p.children_counts_handle);
    p.children_id.reset(&p.children_id_handle);
    p.fragment_ids.reset(&p.fragment_ids_handle);
    p.match_ids.reset(&p.match_ids_handle);
    p.match_overlaps.reset(&p.match_overlaps_handle);
    p.module_ids.reset(&p.module_ids_handle);
    p.orig_children_id.reset(&p.orig_children_id_handle);

    caf::SRParticleTruthDLP part;
    part.ancestor_creation_process = p.ancestor_creation_process;
    part.ancestor_pdg_code = p.ancestor_pdg_code;
    std::copy(std::begin(p.ancestor_position), std::end(p.ancestor_position), std::begin(part.ancestor_position));
    part.ancestor_t = p.ancestor_t;
    part.ancestor_track_id = p.ancestor_track_id;
    part.calo_ke = p.calo_ke;
    part.cathode_offset = p.cathode_offset;
    part.children_counts = std::vector<int64_t>(p.children_counts.begin(), p.children_counts.end());
    part.children_id = std::vector<int64_t>(p.children_id.begin(), p.children_id.end());
    part.creation_process = p.creation_process;
    part.csda_ke = p.csda_ke;
    std::copy(std::begin(p.csda_ke_per_pid), std::end(p.csda_ke_per_pid), std::begin(part.csda_ke_per_pid));
    part.depositions_adapt_q_sum = p.depositions_adapt_q_sum;
    part.depositions_adapt_sum = p.depositions_adapt_sum;
    part.depositions_g4_sum = p.depositions_g4_sum;
    part.depositions_q_sum = p.depositions_q_sum;
    part.depositions_sum = p.depositions_sum;
    part.distance_travel = p.distance_travel;
    std::copy(std::begin(p.end_dir), std::end(p.end_dir), std::begin(part.end_dir));
    std::copy(std::begin(p.end_momentum), std::end(p.end_momentum), std::begin(part.end_momentum));
    part.end_p = p.end_p;
    std::copy(std::begin(p.end_point), std::end(p.end_point), std::begin(part.end_point));
    std::copy(std::begin(p.end_position), std::end(p.end_position), std::begin(part.end_position));
    part.end_t = p.end_t;
    part.energy_deposit = p.energy_deposit;
    part.energy_init = p.energy_init;
    std::copy(std::begin(p.first_step), std::end(p.first_step), std::begin(part.first_step));
    part.fragment_ids = std::vector<int32_t>(p.fragment_ids.begin(), p.fragment_ids.end());
    part.group_id = p.group_id;
    part.group_primary = p.group_primary;
    part.id = p.id;
    part.interaction_id = p.interaction_id;
    part.interaction_primary = p.interaction_primary;
    part.is_cathode_crosser = p.is_cathode_crosser;
    part.is_contained = p.is_contained;
    part.is_matched = p.is_matched;
    part.is_primary = p.is_primary;
    part.is_time_contained = p.is_time_contained;
    part.is_truth = p.is_truth;
    part.is_valid = p.is_valid;
    part.ke = p.ke;
    std::copy(std::begin(p.last_step), std::end(p.last_step), std::begin(part.last_step));
    part.length = p.length;
    part.mass = p.mass;
    part.match_ids = std::vector<int64_t>(p.match_ids.begin(), p.match_ids.end());
    part.match_overlaps = std::vector<float>(p.match_overlaps.begin(), p.match_overlaps.end());
    part.mcs_ke = p.mcs_ke;
    std::copy(std::begin(p.mcs_ke_per_pid), std::end(p.mcs_ke_per_pid), std::begin(part.mcs_ke_per_pid));
    part.mcst_index = p.mcst_index;
    part.mct_index = p.mct_index;
    part.module_ids = std::vector<int64_t>(p.module_ids.begin(), p.module_ids.end());
    std::copy(std::begin(p.momentum), std::end(p.momentum), std::begin(part.momentum));
    part.nu_id = p.nu_id;
    part.num_fragments = p.num_fragments;
    part.num_voxels = p.num_voxels;
    part.orig_children_id = std::vector<int64_t>(p.orig_children_id.begin(), p.orig_children_id.end());
    part.orig_group_id = p.orig_group_id;
    part.orig_id = p.orig_id;
    part.orig_interaction_id = p.orig_interaction_id;
    part.orig_parent_id = p.orig_parent_id;
    part.p = p.p;
    part.parent_creation_process = p.parent_creation_process;
    part.parent_id = p.parent_id;
    part.parent_pdg_code = p.parent_pdg_code;
    std::copy(std::begin(p.parent_position), std::end(p.parent_position), std::begin(part.parent_position));
    part.parent_t = p.parent_t;
    part.parent_track_id = p.parent_track_id;
    part.pdg_code = p.pdg_code;
    part.pid = (int64_t)p.pid;
    std::copy(std::begin(p.position), std::end(p.position), std::begin(part.position));
    std::copy(std::begin(p.reco_end_dir), std::end(p.reco_end_dir), std::begin(part.reco_end_dir));
    part.reco_ke = p.reco_ke;
    part.reco_length = p.reco_length;
    std::copy(std::begin(p.reco_momentum), std::end(p.reco_momentum), std::begin(part.reco_momentum));
    std::copy(std::begin(p.reco_start_dir), std::end(p.reco_start_dir), std::begin(part.reco_start_dir));
    part.shape = (int64_t)p.shape;
    part.size = p.size;
    part.size_adapt = p.size_adapt;
    part.size_g4 = p.size_g4;
    std::copy(std::begin(p.start_dir), std::end(p.start_dir), std::begin(part.start_dir));
    std::copy(std::begin(p.start_point), std::end(p.start_point), std::begin(part.start_point));
    part.t = p.t;
    part.track_id = p.track_id;

    return part;
}

caf::SRParticleDLP fill_particle(dlp::types::RecoParticle &p, uint64_t offset)
{
    p.fragment_ids.reset(&p.fragment_ids_handle);
    p.match_ids.reset(&p.match_ids_handle);
    p.match_overlaps.reset(&p.match_overlaps_handle);
    p.module_ids.reset(&p.module_ids_handle);
    p.ppn_ids.reset(&p.ppn_ids_handle);

    caf::SRParticleDLP part;
    part.axial_spread = p.axial_spread;
    part.calo_ke = p.calo_ke;
    part.cathode_offset = p.cathode_offset;
    std::copy(std::begin(p.chi2_per_pid), std::end(p.chi2_per_pid), std::begin(part.chi2_per_pid));
    part.chi2_pid = (int64_t)p.chi2_pid;
    part.csda_ke = p.csda_ke;
    std::copy(std::begin(p.csda_ke_per_pid), std::end(p.csda_ke_per_pid), std::begin(part.csda_ke_per_pid));
    part.depositions_sum = p.depositions_sum;
    part.directional_spread = p.directional_spread;
    std::copy(std::begin(p.end_dir), std::end(p.end_dir), std::begin(part.end_dir));
    std::copy(std::begin(p.end_point), std::end(p.end_point), std::begin(part.end_point));
    part.fragment_ids = std::vector<int32_t>(p.fragment_ids.begin(), p.fragment_ids.end());  
    part.id = p.id;
    part.interaction_id = p.interaction_id;
    part.is_cathode_crosser = p.is_cathode_crosser;
    part.is_contained = p.is_contained;
    part.is_matched = p.is_matched;
    part.is_primary = p.is_primary;
    part.is_time_contained = p.is_time_contained;
    part.is_truth = p.is_truth;
    part.is_valid = p.is_valid;
    part.ke = p.ke;
    part.length = p.length;
    part.mass = p.mass;
    part.match_ids = std::vector<int64_t>(p.match_ids.begin(), p.match_ids.end());
    part.match_overlaps = std::vector<float>(p.match_overlaps.begin(), p.match_overlaps.end());
    part.mcs_ke = p.mcs_ke;
    std::copy(std::begin(p.mcs_ke_per_pid), std::end(p.mcs_ke_per_pid), std::begin(part.mcs_ke_per_pid));
    part.module_ids = std::vector<int64_t>(p.module_ids.begin(), p.module_ids.end());
    std::copy(std::begin(p.momentum), std::end(p.momentum), std::begin(part.momentum));
    part.num_fragments = p.num_fragments;
    part.p = p.p;
    part.pdg_code = p.pdg_code;
    part.pid = (int64_t)p.pid;
    std::copy(std::begin(p.pid_scores), std::end(p.pid_scores), std::begin(part.pid_scores));
    part.ppn_ids = std::vector<int32_t>(p.ppn_ids.begin(), p.ppn_ids.end());
    std::copy(std::begin(p.primary_scores), std::end(p.primary_scores), std::begin(part.primary_scores));
    part.shape = (int64_t)p.shape;
    part.size = p.size;
    part.start_dedx = p.start_dedx;
    std::copy(std::begin(p.start_dir), std::end(p.start_dir), std::begin(part.start_dir));
    std::copy(std::begin(p.start_point), std::end(p.start_point), std::begin(part.start_point));
    part.start_straightness = p.start_straightness;
    part.vertex_distance = p.vertex_distance;

    return part;
}

caf::SRInteractionTruthDLP fill_truth_interaction(dlp::types::TruthInteraction &in, std::vector<caf::SRParticleTruthDLP> &particles, uint64_t offset)
{
    in.flash_ids.reset(&in.flash_ids_handle);
    in.flash_scores.reset(&in.flash_scores_handle);
    in.flash_times.reset(&in.flash_times_handle);
    in.flash_volume_ids.reset(&in.flash_volume_ids_handle);
    in.match_ids.reset(&in.match_ids_handle);
    in.match_overlaps.reset(&in.match_overlaps_handle);
    in.module_ids.reset(&in.module_ids_handle);
    in.particle_ids.reset(&in.particle_ids_handle);
    in.primary_particle_ids.reset(&in.primary_particle_ids_handle);

    caf::SRInteractionTruthDLP ret;
    ret.bjorken_x = in.bjorken_x;
    ret.cathode_offset = in.cathode_offset;
    ret.creation_process = in.creation_process;
    ret.current_type = (int64_t)in.current_type;
    ret.depositions_adapt_q_sum = in.depositions_adapt_q_sum;
    ret.depositions_adapt_sum = in.depositions_adapt_sum;
    ret.depositions_g4_sum = in.depositions_g4_sum;
    ret.depositions_q_sum = in.depositions_q_sum;
    ret.depositions_sum = in.depositions_sum;
    ret.distance_travel = in.distance_travel;
    ret.energy_init = in.energy_init;
    ret.energy_transfer = in.energy_transfer;
    ret.flash_hypo_pe = in.flash_hypo_pe;
    ret.flash_ids = std::vector<int64_t>(in.flash_ids.begin(), in.flash_ids.end());
    ret.flash_scores = std::vector<float>(in.flash_scores.begin(), in.flash_scores.end());
    ret.flash_times = std::vector<float>(in.flash_times.begin(), in.flash_times.end());
    ret.flash_total_pe = in.flash_total_pe;
    ret.flash_volume_ids = std::vector<int64_t>(in.flash_volume_ids.begin(), in.flash_volume_ids.end());
    ret.hadronic_invariant_mass = in.hadronic_invariant_mass;
    ret.id = in.id;
    ret.inelasticity = in.inelasticity;
    ret.interaction_mode = (int64_t)in.interaction_mode;
    ret.interaction_type = (int64_t)in.interaction_type;
    ret.is_cathode_crosser = in.is_cathode_crosser;
    ret.is_contained = in.is_contained;
    ret.is_fiducial = in.is_fiducial;
    ret.is_flash_matched = in.is_flash_matched;
    ret.is_matched = in.is_matched;
    ret.is_time_contained = in.is_time_contained;
    ret.is_truth = in.is_truth;
    ret.lepton_p = in.lepton_p;
    ret.lepton_pdg_code = in.lepton_pdg_code;
    ret.lepton_track_id = in.lepton_track_id;
    ret.match_ids = std::vector<int64_t>(in.match_ids.begin(), in.match_ids.end());
    ret.match_overlaps = std::vector<float>(in.match_overlaps.begin(), in.match_overlaps.end());
    ret.mct_index = in.mct_index;
    ret.module_ids = std::vector<int64_t>(in.module_ids.begin(), in.module_ids.end());
    std::copy(std::begin(in.momentum), std::end(in.momentum), std::begin(ret.momentum));
    ret.momentum_transfer = in.momentum_transfer;
    ret.momentum_transfer_mag = in.momentum_transfer_mag;
    ret.nu_id = in.nu_id;
    ret.nucleon = in.nucleon;
    ret.num_particles = in.num_particles;
    ret.num_primary_particles = in.num_primary_particles;
    ret.orig_id = in.orig_id;
    std::copy(std::begin(in.particle_counts), std::end(in.particle_counts), std::begin(ret.particle_counts));
    ret.particle_ids = std::vector<int64_t>(in.particle_ids.begin(), in.particle_ids.end());
    ret.pdg_code = in.pdg_code;
    std::copy(std::begin(in.position), std::end(in.position), std::begin(ret.position));
    std::copy(std::begin(in.primary_particle_counts), std::end(in.primary_particle_counts), std::begin(ret.primary_particle_counts));
    ret.primary_particle_ids = std::vector<int64_t>(in.primary_particle_ids.begin(), in.primary_particle_ids.end());
    ret.quark = in.quark;
    std::copy(std::begin(in.reco_vertex), std::end(in.reco_vertex), std::begin(ret.reco_vertex));
    ret.size = in.size;
    ret.size_adapt = in.size_adapt;
    ret.size_g4 = in.size_g4;
    ret.target = in.target;
    ret.theta = in.theta;
    ret.topology = in.topology;
    ret.track_id = in.track_id;
    std::copy(std::begin(in.vertex), std::end(in.vertex), std::begin(ret.vertex));
    for(int64_t id : ret.particle_ids)
        ret.particles.push_back(particles.at(id));

    return ret;
}

caf::SRInteractionDLP fill_interaction(dlp::types::RecoInteraction &in, std::vector<caf::SRParticleDLP> &particles, uint64_t offset)
{
    in.flash_ids.reset(&in.flash_ids_handle);
    in.flash_scores.reset(&in.flash_scores_handle);
    in.flash_times.reset(&in.flash_times_handle);
    in.flash_volume_ids.reset(&in.flash_volume_ids_handle);
    in.match_ids.reset(&in.match_ids_handle);
    in.match_overlaps.reset(&in.match_overlaps_handle);
    in.module_ids.reset(&in.module_ids_handle);
    in.particle_ids.reset(&in.particle_ids_handle);
    in.primary_particle_ids.reset(&in.primary_particle_ids_handle);

    caf::SRInteractionDLP ret;
    ret.cathode_offset = in.cathode_offset;
    ret.depositions_sum = in.depositions_sum;
    ret.flash_hypo_pe = in.flash_hypo_pe;
    ret.flash_ids = std::vector<int64_t>(in.flash_ids.begin(), in.flash_ids.end());
    ret.flash_scores = std::vector<float>(in.flash_scores.begin(), in.flash_scores.end());
    ret.flash_times = std::vector<float>(in.flash_times.begin(), in.flash_times.end());
    ret.flash_total_pe = in.flash_total_pe;
    ret.flash_volume_ids = std::vector<int64_t>(in.flash_volume_ids.begin(), in.flash_volume_ids.end());
    ret.id = in.id;
    ret.is_cathode_crosser = in.is_cathode_crosser;
    ret.is_contained = in.is_contained;
    ret.is_fiducial = in.is_fiducial;
    ret.is_flash_matched = in.is_flash_matched;
    ret.is_matched = in.is_matched;
    ret.is_time_contained = in.is_time_contained;
    ret.is_truth = in.is_truth;
    ret.match_ids = std::vector<int64_t>(in.match_ids.begin(), in.match_ids.end());
    ret.match_overlaps = std::vector<float>(in.match_overlaps.begin(), in.match_overlaps.end());
    ret.module_ids = std::vector<int64_t>(in.module_ids.begin(), in.module_ids.end());
    ret.num_particles = in.num_particles;
    ret.num_primary_particles = in.num_primary_particles;
    std::copy(std::begin(in.particle_counts), std::end(in.particle_counts), std::begin(ret.particle_counts));
    ret.particle_ids = std::vector<int64_t>(in.particle_ids.begin(), in.particle_ids.end());
    std::copy(std::begin(in.primary_particle_counts), std::end(in.primary_particle_counts), std::begin(ret.primary_particle_counts));
    ret.primary_particle_ids = std::vector<int64_t>(in.primary_particle_ids.begin(), in.primary_particle_ids.end());
    ret.size = in.size;
    ret.topology = in.topology;
    std::copy(std::begin(in.vertex), std::end(in.vertex), std::begin(ret.vertex));
    for(int64_t id : ret.particle_ids)
        ret.particles.push_back(particles.at(id));

    return ret;
}

void package_event(caf::StandardRecord * rec, H5::H5File & file, dlp::types::Event & evt, uint64_t offset)
{
    /**
     * @brief Retrieve and copy the reconstructed particle products.
     * @details Retrieve the reconstructed particle data products from the H5
     * file for the specified event. The data in each particle is copied into
     * an instance of the SRParticleDLP class, which will later be added to its
     * parent interaction.
     */
    std::vector<dlp::types::RecoParticle> reco_particles(get_product<dlp::types::RecoParticle>(file, evt));
    std::vector<caf::SRParticleDLP> caf_reco_particles;
    for(dlp::types::RecoParticle &p : reco_particles)
        caf_reco_particles.push_back(fill_particle(p, offset));

    /**
     * @brief Retrieve and copy the true particle products.
     * @details Retrieve the true particle data products from the H5 file for
     * the specified event. The data in each particle is copied into an
     * instance of the SRParticleTruthDLP class, which will later be added to
     * its parent interaction.
     * @note This block is only included if run in MC mode.
     */
    #ifdef MC_NOT_DATA
    std::vector<dlp::types::TruthParticle> true_particles(get_product<dlp::types::TruthParticle>(file, evt));
    std::vector<caf::SRParticleTruthDLP> caf_true_particles;
    for(dlp::types::TruthParticle &p : true_particles)
        caf_true_particles.push_back(fill_truth_particle(p, offset));
    #endif

    /**
     * @brief Retrieve the reconstructed interaction data products.
     * @details Retrieve the reconstructed interaction data products from the
     * H5 file for the specified event. The data in each interaction is copied
     * into an instance of the SRInteractionDLP class, along with the subset of
     * particles in the event that belong to it.
     */
    std::vector<dlp::types::RecoInteraction> reco_interactions(get_product<dlp::types::RecoInteraction>(file, evt));
    std::vector<caf::SRInteractionDLP> caf_reco_interactions;
    for(dlp::types::RecoInteraction &i : reco_interactions)
        caf_reco_interactions.push_back(fill_interaction(i, caf_reco_particles, offset));

    /**
     * @brief Retrieve the true interaction data products.
     * @details Retrieve the true interaction data products from the H5 file
     * for the specified event. The data in each interaction is copied into an
     * instance of the SRInteractionTruthDLP class, along with the subset of
     * particles in the event that belong to it.
     * @note This block is only included if run in MC mode.
     */
    #ifdef MC_NOT_DATA
    std::vector<dlp::types::TruthInteraction> true_interactions(get_product<dlp::types::TruthInteraction>(file, evt));
    std::vector<caf::SRInteractionTruthDLP> caf_true_interactions;
    for(dlp::types::TruthInteraction &i : true_interactions)
        caf_true_interactions.push_back(fill_truth_interaction(i, caf_true_particles, offset));
    #endif

    /**
     * @brief Populate the StandardRecord object.
     * @details Populate the StandardRecord object with the reconstructed and
     * true interaction data products. The number of interactions in each
     * category is also stored.
     * @note True data products are only included if run in MC mode.
     */
    rec->dlp = caf_reco_interactions;
    rec->ndlp = caf_reco_interactions.size();
    #ifdef MC_NOT_DATA
    rec->dlp_true = caf_true_interactions;
    rec->ndlp_true = caf_true_interactions.size();
    #endif
}