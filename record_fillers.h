/**
 * @file record_fillers.h
 * @brief Implementation of various functions for filling the ML reconstruction
 * output objects for use within the CAF files.
 * @author justin.mueller@colostate.edu
 */

#include <vector>
#include <ctype.h>
#include "sbnanaobj/StandardRecord/StandardRecord.h"
#include "sbnanaobj/StandardRecord/SRInteractionDLP.h"
#include "include/event.h"
#include "include/reco_interaction.h"
#include "include/reco_particle.h"
#include "include/true_interaction.h"
#include "include/true_particle.h"

#ifndef RECORD_FILLERS_H
#define RECORD_FILLERS_H

#define COPY(x,y) std::copy(y.begin(), y.end(), x)

// Forward declaration.
template <class T>
std::vector<T> get_product(H5::H5File & file, dlp::types::Event & evt);

/**
 * Constructs an instance of the caf::SRParticleTruthDLP class from the data
 * in the dlp::types::TruthParticle data product.
 * @param p the input dlp::types::TruthParticle data product containing the
 * information to be copied.
 * @param offset to add to the image_id of the particle (default = 0).
 * @return an instance of the caf::SRParticleTruthDLP class that contains the
 * data copied from the input dlp::types::TruthParticle object.
 */
caf::SRParticleTruthDLP fill_truth_particle(dlp::types::TruthParticle &p, uint64_t offset=0)
{

  p.children_counts.reset(&p.children_counts_handle);
  p.children_id.reset(&p.children_id_handle);
  p.fragment_ids.reset(&p.fragment_ids_handle);
  p.index.reset(&p.index_handle);
  p.index_adapt.reset(&p.index_adapt_handle);
  p.index_g4.reset(&p.index_g4_handle);
  p.match_ids.reset(&p.match_ids_handle);
  p.match_overlaps.reset(&p.match_overlaps_handle);
  p.module_ids.reset(&p.module_ids_handle);

  caf::SRParticleTruthDLP part;
  part.ancestor_creation_process = p.ancestor_creation_process;
  part.ancestor_pdg_code = p.ancestor_pdg_code;
  //part.ancestor_position = p.ancestor_position;
  std::copy(std::begin(p.ancestor_position), std::end(p.ancestor_position), std::begin(part.ancestor_position));
  part.ancestor_t = p.ancestor_t;
  part.ancestor_track_id = p.ancestor_track_id;
  part.calo_ke = p.calo_ke;
  part.cathode_offset = p.cathode_offset;
  part.children_counts = std::vector<int64_t>(p.children_counts.begin(), p.children_counts.end());
  part.children_id = std::vector<int64_t>(p.children_id.begin(), p.children_id.end());
  part.creation_process = p.creation_process;
  part.csda_ke = p.csda_ke;
  part.depositions_adapt_sum = p.depositions_adapt_sum;
  part.depositions_adapt_q_sum = p.depositions_adapt_q_sum;
  part.depositions_g4_sum = p.depositions_g4_sum;
  part.depositions_sum = p.depositions_sum;
  part.depositions_q_sum = p.depositions_q_sum;
  part.distance_travel = p.distance_travel;
  //part.end_dir = p.end_dir;
  std::copy(std::begin(p.end_dir), std::end(p.end_dir), std::begin(part.end_dir));
  //part.end_momentum = p.end_momentum;
  std::copy(std::begin(p.end_momentum), std::end(p.end_momentum), std::begin(part.end_momentum));
  part.end_p = p.end_p;
  //part.end_point = p.end_dir;
  std::copy(std::begin(p.end_point), std::end(p.end_point), std::begin(part.end_point));
  //part.end_position = p.end_position;
  std::copy(std::begin(p.end_position), std::end(p.end_position), std::begin(part.end_position));
  part.end_t = p.end_t;
  part.energy_deposit = p.energy_deposit;
  part.energy_init = p.energy_init;
  //part.first_step = p.first_step;
  std::copy(std::begin(p.first_step), std::end(p.first_step), std::begin(part.first_step));
  part.fragment_ids = std::vector<int32_t>(p.fragment_ids.begin(), p.fragment_ids.end());
  part.gen_id = p.gen_id;
  part.group_id = p.group_id;
  part.group_primary = p.group_primary;
  part.id = p.id;
  part.index = std::vector<int64_t>(p.index.begin(), p.index.end());
  part.index_adapt = std::vector<int64_t>(p.index_adapt.begin(), p.index_adapt.end());
  part.index_g4 = std::vector<int64_t>(p.index_g4.begin(), p.index_g4.end());
  part.interaction_id = p.interaction_id;
  part.interaction_primary = p.interaction_primary;
  part.is_cathode_crosser = p.is_cathode_crosser;
  part.is_contained = p.is_contained;
  part.is_matched = p.is_matched;
  part.is_primary = p.is_primary;
  part.is_truth = p.is_truth;
  part.is_valid = p.is_valid;
  part.ke = p.ke;
  //part.last_step = p.last_step;
  std::copy(std::begin(p.last_step), std::end(p.last_step), std::begin(part.last_step));
  part.length = p.length;
  part.mass = p.mass;
  part.match_ids = std::vector<int64_t>(p.match_ids.begin(), p.match_ids.end());
  part.match_overlaps = std::vector<float>(p.match_overlaps.begin(), p.match_overlaps.end());
  part.mcs_ke = p.mcs_ke;
  part.mct_index = p.mct_index;
  part.mcst_index = p.mcst_index;
  part.module_ids = std::vector<int64_t>(p.module_ids.begin(), p.module_ids.end());
  //part.momentum = p.momentum;
  std::copy(std::begin(p.momentum), std::end(p.momentum), std::begin(part.momentum));
  part.nu_id = p.nu_id;
  part.num_fragments = p.num_fragments;
  part.num_voxels = p.num_voxels;
  part.orig_id = p.orig_id;
  part.orig_interaction_id = p.orig_interaction_id;
  part.p = p.p;
  part.parent_creation_process = p.parent_creation_process;
  part.parent_id = p.parent_id;
  part.parent_pdg_code = p.parent_pdg_code;
  //part.parent_position = p.parent_position;
  std::copy(std::begin(p.parent_position), std::end(p.parent_position), std::begin(part.parent_position));
  part.parent_t = p.parent_t;
  part.parent_track_id = p.parent_track_id;
  part.pdg_code = p.pdg_code;
  part.pid = (int64_t)p.pid;
  //part.position = p.position;
  std::copy(std::begin(p.position), std::end(p.position), std::begin(part.position));
  //part.reco_end_dir = p.reco_end_dir;
  std::copy(std::begin(p.reco_end_dir), std::end(p.reco_end_dir), std::begin(part.reco_end_dir));
  part.reco_length = p.reco_length;
  //part.reco_start_dir = p.reco_start_dir;
  std::copy(std::begin(p.reco_start_dir), std::end(p.reco_start_dir), std::begin(part.reco_start_dir));
  part.shape = (int64_t)p.shape;
  part.size = p.size;
  part.size_adapt = p.size_adapt;
  part.size_g4 = p.size_g4;
  //part.start_dir = p.start_dir;
  std::copy(std::begin(p.start_dir), std::end(p.start_dir), std::begin(part.start_dir));
  //part.start_point = p.start_point;
  std::copy(std::begin(p.start_point), std::end(p.start_point), std::begin(part.start_point));
  part.t = p.t;
  part.track_id = p.track_id;
  part.units = p.units;

  return part;
}

/**
 * Constructs an instance of the caf::SRParticleDLP class from the data in the
 * dlp::types::TruthParticle data product.
 * @param p the input dlp::types::Particle data product containing the
 * information to be copied.
 * @param offset to add to the image_id of the particle (default = 0).
 * @return an instance of the caf::SRParticleDLP class that contains the data
 * copied from the input dlp::types::Particle object.
 */
caf::SRParticleDLP fill_particle(dlp::types::RecoParticle &p, uint64_t offset=0)
{

  p.fragment_ids.reset(&p.fragment_ids_handle);
  p.index.reset(&p.index_handle);
  p.match_ids.reset(&p.match_ids_handle);
  p.match_overlaps.reset(&p.match_overlaps_handle);
  p.module_ids.reset(&p.module_ids_handle);
  p.ppn_ids.reset(&p.ppn_ids_handle);

  caf::SRParticleDLP part;
  part.calo_ke = p.calo_ke;
  part.cathode_offset = p.cathode_offset;
  part.csda_ke = p.csda_ke;
  part.depositions_sum = p.depositions_sum;
  //part.end_dir = p.end_dir;
  std::copy(std::begin(p.end_dir), std::end(p.end_dir), std::begin(part.end_dir));
  //part.end_point = p.end_point;
  std::copy(std::begin(p.end_point), std::end(p.end_point), std::begin(part.end_point));
  part.fragment_ids = std::vector<int32_t>(p.fragment_ids.begin(), p.fragment_ids.end());  
  part.id = p.id;
  part.index = std::vector<int64_t>(p.index.begin(), p.index.end());
  part.interaction_id = p.interaction_id;
  part.is_cathode_crosser = p.is_cathode_crosser;
  part.is_contained = p.is_contained;
  part.is_matched = p.is_matched;
  part.is_primary = p.is_primary;
  part.is_truth = p.is_truth;
  part.is_valid = p.is_valid;
  part.ke = p.ke;
  part.length = p.length;
  part.mass = p.mass;
  part.match_ids = std::vector<int64_t>(p.match_ids.begin(), p.match_ids.end());
  part.match_overlaps = std::vector<float>(p.match_overlaps.begin(), p.match_overlaps.end());
  part.module_ids = std::vector<int64_t>(p.module_ids.begin(), p.module_ids.end());
  part.mcs_ke = p.mcs_ke;
  //part.momentum = p.momentum;
  std::copy(std::begin(p.momentum), std::end(p.momentum), std::begin(part.momentum));
  part.num_fragments = p.num_fragments;
  part.p = p.p;
  part.pdg_code = p.pdg_code;
  part.pid = (int64_t)p.pid;
  //part.pid_scores = p.pid_scores;
  std::copy(std::begin(p.pid_scores), std::end(p.pid_scores), std::begin(part.pid_scores));
  part.ppn_ids = std::vector<int32_t>(p.ppn_ids.begin(), p.ppn_ids.end());
  //part.primary_scores = p.primary_scores;
  std::copy(std::begin(p.primary_scores), std::end(p.primary_scores), std::begin(part.primary_scores));
  part.shape = (int64_t)p.shape;
  part.size = p.size;
  //part.start_dir = p.start_dir;
  std::copy(std::begin(p.start_dir), std::end(p.start_dir), std::begin(part.start_dir));
  //part.start_point = p.start_point;
  std::copy(std::begin(p.start_point), std::end(p.start_point), std::begin(part.start_point));
  part.units = p.units;  
  

  return part;
}

/**
 * Constructs an instance of the caf::SRInteractionTruthDLP class from the data
 * in the dlp::types::TruthInteraction data product and the input vector of
 * caf::SRParticleTruthDLP objects.
 * @param in the input dlp::types::TruthInteraction data product containing the
 * information to be copied.
 * @param particles the vector of caf::SRParticleTruthDLP objects to copy to
 * the SRTruthInteractionDLP object.
 * @param offset to add to the image_id of the interaction (default = 0).
 * @return an instance of the caf::SRInteractionTruthDLP class that contains
 * the data copied from the input dlp::types::TruthInteraction object and the
 * vector of caf::SRParticleTruthDLP.
 */
caf::SRInteractionTruthDLP fill_truth_interaction(dlp::types::TruthInteraction &in, std::vector<caf::SRParticleTruthDLP> &particles, uint64_t offset=0)
{

  in.index.reset(&in.index_handle);
  in.index_adapt.reset(&in.index_adapt_handle);
  in.index_g4.reset(&in.index_g4_handle);
  in.match_ids.reset(&in.match_ids_handle);
  in.match_overlaps.reset(&in.match_overlaps_handle);
  in.module_ids.reset(&in.module_ids_handle);
  in.particle_ids.reset(&in.particle_ids_handle);
  
  caf::SRInteractionTruthDLP ret;
  ret.bjorken_x = in.bjorken_x;
  ret.cathode_offset = in.cathode_offset;
  ret.creation_process = in.creation_process;
  ret.current_type = (int64_t)in.current_type;
  ret.depositions_adapt_sum = in.depositions_adapt_sum;
  ret.depositions_adapt_q_sum = in.depositions_adapt_q_sum;
  ret.depositions_g4_sum = in.depositions_g4_sum;
  ret.depositions_sum = in.depositions_sum;
  ret.depositions_q_sum = in.depositions_q_sum;
  ret.energy_init = in.energy_init;
  ret.energy_transfer = in.energy_transfer;
  ret.flash_hypo_pe = in.flash_hypo_pe;
  ret.flash_id = in.flash_id;
  ret.flash_time = in.flash_time;
  ret.flash_total_pe = in.flash_total_pe;
  ret.hadronic_invariant_mass = in.hadronic_invariant_mass;
  ret.id = in.id;
  ret.index = std::vector<int64_t>(in.index.begin(), in.index.end());
  ret.index_adapt = std::vector<int64_t>(in.index_adapt.begin(), in.index_adapt.end());
  ret.index_g4 = std::vector<int64_t>(in.index_g4.begin(), in.index_g4.end());
  ret.inelasticity = in.inelasticity;
  ret.interaction_id = in.interaction_id;
  ret.interaction_mode = (int64_t)in.interaction_mode;
  ret.interaction_type = (int64_t)in.interaction_type;
  ret.is_cathode_crosser = in.is_cathode_crosser;
  ret.is_contained = in.is_contained;
  ret.is_fiducial = in.is_fiducial;
  ret.is_flash_matched = in.is_flash_matched;
  ret.is_matched = in.is_matched;
  ret.is_truth = in.is_truth;
  ret.lepton_p = in.lepton_p;
  ret.lepton_pdg_code = in.lepton_pdg_code;
  ret.lepton_track_id = in.lepton_track_id;
  ret.match_ids = std::vector<int64_t>(in.match_ids.begin(), in.match_ids.end());
  ret.match_overlaps = std::vector<float>(in.match_overlaps.begin(), in.match_overlaps.end());
  ret.module_ids = std::vector<int64_t>(in.module_ids.begin(), in.module_ids.end());
  //ret.momentum = in.momentum;
  std::copy(std::begin(in.momentum), std::end(in.momentum), std::begin(ret.momentum));
  ret.momentum_transfer = in.momentum_transfer;
  ret.momentum_transfer_mag = in.momentum_transfer_mag;
  ret.mct_index = in.mct_index;
  ret.num_particles = in.num_particles;
  ret.nucleon = in.nucleon;
  ret.nu_id = in.nu_id;
  ret.orig_id = in.orig_id;
  //ret.particle_counts = in.particle_counts;
  std::copy(std::begin(in.particle_counts), std::end(in.particle_counts), std::begin(ret.particle_counts));
  ret.particle_ids = std::vector<int64_t>(in.particle_ids.begin(), in.particle_ids.end());
  ret.pdg_code = in.pdg_code;
  //ret.position = in.position;
  std::copy(std::begin(in.position), std::end(in.position), std::begin(ret.position));
  //ret.primary_particle_counts = in.primary_particle_counts;
  std::copy(std::begin(in.primary_particle_counts), std::end(in.primary_particle_counts), std::begin(ret.primary_particle_counts));
  ret.quark = in.quark;
  //ret.reco_vertex = in.reco_vertex;
  std::copy(std::begin(in.reco_vertex), std::end(in.reco_vertex), std::begin(ret.reco_vertex));
  ret.size = in.size;
  ret.size_adapt = in.size_adapt;
  ret.size_g4 = in.size_g4;
  ret.target = in.target;
  ret.theta = in.theta;
  ret.track_id = in.track_id;
  ret.topology = in.topology;
  //ret.vertex = in.vertex;
  std::copy(std::begin(in.vertex), std::end(in.vertex), std::begin(ret.vertex));
  ret.units = in.units;
  for(int64_t id : ret.particle_ids)
    ret.particles.push_back(particles.at(id));

  return ret;
}

/**
 * Constructs an instance of the caf::SRInteractionDLP class from the data in
 * the dlp::types::Interaction data product and the input vector of
 * caf::SRParticleDLP objects.
 * @param in the input dlp::types::Interaction data product containing the
 * information to be copied.
 * @param particles the vector of caf::SRParticleDLP objects to copy to the
 * SRInteractionDLP object.
 * @param offset to add to the image_id of the interaction (default = 0).
 * @return an instance of the caf::SRInteractionDLP class that contains the
 * data copied from the input dlp::types::Interaction object and the vector
 * of caf::SRParticleDLP.
 */
caf::SRInteractionDLP fill_interaction(dlp::types::RecoInteraction &in, std::vector<caf::SRParticleDLP> &particles, uint64_t offset=0)
{

  in.index.reset(&in.index_handle);
  in.match_ids.reset(&in.match_ids_handle);
  in.match_overlaps.reset(&in.match_overlaps_handle);
  in.module_ids.reset(&in.module_ids_handle);
  in.particle_ids.reset(&in.particle_ids_handle);

  caf::SRInteractionDLP ret;
  ret.cathode_offset = in.cathode_offset;
  ret.depositions_sum = in.depositions_sum;
  ret.flash_hypo_pe = in.flash_hypo_pe;
  ret.flash_id = in.flash_id;
  ret.flash_time = in.flash_time;
  ret.flash_total_pe = in.flash_total_pe;
  ret.id = in.id;
  ret.index = std::vector<int64_t>(in.index.begin(), in.index.end());
  ret.is_cathode_crosser = in.is_cathode_crosser;
  ret.is_contained = in.is_contained;
  ret.is_fiducial = in.is_fiducial;
  ret.is_flash_matched = in.is_flash_matched;
  ret.is_matched = in.is_matched;
  ret.is_truth = in.is_truth;
  ret.match_ids = std::vector<int64_t>(in.match_ids.begin(), in.match_ids.end());
  ret.match_overlaps = std::vector<float>(in.match_overlaps.begin(), in.match_overlaps.end());
  ret.module_ids = std::vector<int64_t>(in.module_ids.begin(), in.module_ids.end());
  ret.num_particles = in.num_particles;
  ret.nu_id = in.nu_id;
  //ret.particle_counts = in.particle_counts;
  std::copy(std::begin(in.particle_counts), std::end(in.particle_counts), std::begin(ret.particle_counts));
  ret.particle_ids = std::vector<int64_t>(in.particle_ids.begin(), in.particle_ids.end());
  //ret.primary_particle_counts = in.primary_particle_counts;
  std::copy(std::begin(in.primary_particle_counts), std::end(in.primary_particle_counts), std::begin(ret.primary_particle_counts));
  ret.size = in.size;
  ret.topology = in.topology;
  ret.units = in.units;
  //ret.vertex = in.vertex;
  std::copy(std::begin(in.vertex), std::end(in.vertex), std::begin(ret.vertex));
  for(int64_t id : ret.particle_ids)
    ret.particles.push_back(particles.at(id));

  return ret;
}

/**
 * Populates the StandardRecord object with the ML reconstruction outputs
 * contained in the input dlp::types::Event object of the H5 file. If the
 * StandardRecord already contains ML products, they will be replaced. This
 * guarantees that the ML products will not be mixed across different versions
 * or duplicated, and additionally adds functionality to replace the ML
 * reconstruction outputs when they have been regenerated after updates.
 * @param rec a pointer to the StandardRecord object to modify.
 * @param file the H5 file containing the event.
 * @param evt the dlp::types::Event that contains references to the ML data.
 * products within the H5 file.
 * @param offset to add to each image_id in the ML data products (default = 0).
 */
void package_event(caf::StandardRecord * rec, H5::H5File & file, dlp::types::Event & evt, uint64_t offset=0)
{
  /**
   * Retrieve the reconstructed particle data products from the H5 file for
   * the specified event. The data in each particle is copied into an
   * instance of the SRParticleDLP class, which will later be added to its
   * parent interaction.
   */
  std::vector<dlp::types::RecoParticle> reco_particles(get_product<dlp::types::RecoParticle>(file, evt));
  std::vector<caf::SRParticleDLP> caf_reco_particles;
  for(dlp::types::RecoParticle &p : reco_particles)
    caf_reco_particles.push_back(fill_particle(p, offset));

  /**
   * Retrieve the true particle data products from the H5 file for the
   * specified event. The data in each particle is copied into an instance
   * of the SRParticleTruthDLP class, which will later be added to its parent
   * interaction.
   */
    #ifdef MC_NOT_DATA
  std::vector<dlp::types::TruthParticle> true_particles(get_product<dlp::types::TruthParticle>(file, evt));
  std::vector<caf::SRParticleTruthDLP> caf_true_particles;
  for(dlp::types::TruthParticle &p : true_particles)
    caf_true_particles.push_back(fill_truth_particle(p, offset));
    #endif
    
  /**
   * Retrieve the reconstructed interaction data products from the H5 file
   * for the specified event. The data in each interaction is copied into an
   * instance of the SRInteractionDLP class, along with the subset of
   * particles in the event that belong to it.
   */
  std::vector<dlp::types::RecoInteraction> reco_interactions(get_product<dlp::types::RecoInteraction>(file, evt));
  std::vector<caf::SRInteractionDLP> caf_reco_interactions;
  for(dlp::types::RecoInteraction &i : reco_interactions)
    caf_reco_interactions.push_back(fill_interaction(i, caf_reco_particles, offset));
    
  /**
   * Retrieve the true interaction data products from the H5 file for the
   * specified event. The data in each interaction is copied into an instance
   * of the SRInteractionTruthDLP class, along with the subset of particles
   * in the event that belong to it.
   */
    #ifdef MC_NOT_DATA
  std::vector<dlp::types::TruthInteraction> true_interactions(get_product<dlp::types::TruthInteraction>(file, evt));
  std::vector<caf::SRInteractionTruthDLP> caf_true_interactions;
  for(dlp::types::TruthInteraction &i : true_interactions)
    caf_true_interactions.push_back(fill_truth_interaction(i, caf_true_particles, offset));
    #endif

  rec->dlp = caf_reco_interactions;
  rec->ndlp = caf_reco_interactions.size();
    #ifdef MC_NOT_DATA
  rec->dlp_true = caf_true_interactions;
  rec->ndlp_true = caf_true_interactions.size();
    #endif
}

#endif
