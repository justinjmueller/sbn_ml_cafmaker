#include <vector>
#include <ctype.h>
#include "sbn_h5_classes.h"
#include "sbnanaobj/StandardRecord/StandardRecord.h"
#include "sbnanaobj/StandardRecord/SRInteractionDLP.h"
//#include "sbnanaobj/StandardRecord/SRInteractionTruthDLP.h"
//#include "sbnanaobj/StandardRecord/SRIMatchDLP.h"
//#include "sbnanaobj/StandardRecord/SRPMatchDLP.h"

#ifndef RECORD_FILLERS_H
#define RECORD_FILLERS_H

#define COPY(x,y) std::copy(y.begin(), y.end(), x)

caf::SRParticleTruthDLP fill_truth_particle(dlp::types::TruthParticle &p)
{
  p.children_counts.reset(&p.children_counts_handle);
  p.first_step.reset(&p.first_step_handle);
  p.fragment_ids.reset(&p.fragment_ids_handle);
  p.index.reset(&p.index_handle);
  p.last_step.reset(&p.last_step_handle);
  p.match.reset(&p.match_handle);
  p.match_overlap.reset(&p.match_overlap_handle);
  p.parent_position.reset(&p.parent_position_handle);
  p.position.reset(&p.position_handle);
  p.sed_index.reset(&p.sed_index_handle);
  p.truth_index.reset(&p.truth_index_handle);

  caf::SRParticleTruthDLP part;
  part.ancestor_creation_process = p.ancestor_creation_process;
  part.ancestor_pdg_code = p.ancestor_pdg_code;
  part.ancestor_t = p.ancestor_t;
  part.ancestor_track_id = p.ancestor_track_id;
  part.calo_ke = p.calo_ke;
  part.calo_ke_tng = p.calo_ke_tng;
  part.children_counts = std::vector<int64_t>(p.children_counts.begin(), p.children_counts.end());
  part.coffset = p.coffset;
  part.creation_process = p.creation_process;
  part.csda_ke = p.csda_ke;
  part.csda_ke_tng = p.csda_ke_tng;
  part.depositions_sum = p.depositions_sum;
  part.distance_travel = p.distance_travel;
  COPY(part.end_dir,p.end_dir);
  COPY(part.end_point,p.end_point);
  COPY(part.end_position,p.end_position);
  part.energy_deposit = p.energy_deposit;
  part.energy_init = p.energy_init;
  part.first_step = std::vector<float>(p.first_step.begin(), p.first_step.end());
  part.fragment_ids = std::vector<int64_t>(p.fragment_ids.begin(), p.fragment_ids.end());
  part.group_id = p.group_id;
  part.id = p.id;
  part.image_id = p.image_id;
  part.index = std::vector<int64_t>(p.index.begin(), p.index.end());
  part.interaction_id = p.interaction_id;
  part.is_ccrosser = p.is_ccrosser;
  part.is_contained = p.is_contained;
  part.is_primary = p.is_primary;
  part.is_principal_match = p.is_principal_match;
  part.is_valid = p.is_valid;
  part.ke = p.ke;
  part.last_step = std::vector<float>(p.last_step.begin(), p.last_step.end());
  part.length = p.length;
  part.length_tng = p.length_tng;
  part.match = std::vector<int64_t>(p.match.begin(), p.match.end());
  part.match_overlap = std::vector<float>(p.match_overlap.begin(), p.match_overlap.end());
  part.matched = p.matched;
  part.mcs_ke = p.mcs_ke;
  part.mcs_ke_tng = p.mcs_ke_tng;
  part.mcst_index = p.mcst_index;
  COPY(part.momentum,p.momentum);
  part.nu_id = p.nu_id;
  part.num_fragments = p.num_fragments;
  part.num_voxels = p.num_voxels;
  part.p = p.p;
  part.parent_creation_process = p.parent_creation_process;
  part.parent_id = p.parent_id;
  part.parent_pdg_code = p.parent_pdg_code;
  part.parent_position = std::vector<float>(p.parent_position.begin(), p.parent_position.end());
  part.parent_t = p.parent_t;
  part.parent_track_id = p.parent_track_id;
  part.pdg_code = p.pdg_code;
  part.pid = (int64_t)p.pid;
  part.position = std::vector<float>(p.position.begin(), p.position.end());
  part.sed_depositions_MeV_sum = p.sed_depositions_MeV_sum;
  part.sed_index = std::vector<int64_t>(p.sed_index.begin(), p.sed_index.end());
  part.sed_size = p.sed_size;
  part.semantic_type = (int64_t)p.semantic_type;
  part.shape = p.shape;
  part.size = p.size;
  COPY(part.start_dir,p.start_dir);
  COPY(part.start_point,p.start_point);
  part.t = p.t;
  part.track_id = p.track_id;
  part.truth_depositions_MeV_sum = p.truth_depositions_MeV_sum;
  part.truth_depositions_sum = p.truth_depositions_sum;
  part.truth_index = std::vector<int64_t>(p.truth_index.begin(), p.truth_index.end());
  COPY(part.truth_momentum,p.truth_momentum);
  part.truth_size = p.truth_size;
  COPY(part.truth_start_dir,p.truth_start_dir);
  part.units = p.units;
  part.volume_id = p.volume_id;
  
  return part;
}

caf::SRParticleDLP fill_particle(dlp::types::Particle &p)
{
  p.fragment_ids.reset(&p.fragment_ids_handle);
  p.index.reset(&p.index_handle);
  p.match.reset(&p.match_handle);
  p.match_overlap.reset(&p.match_overlap_handle);

  caf::SRParticleDLP part;
  part.calo_ke = p.calo_ke;
  part.coffset = p.coffset;
  part.csda_ke = p.csda_ke;
  part.depositions_sum = p.depositions_sum;
  COPY(part.end_dir, p.end_dir);
  COPY(part.end_point, p.end_point);
  part.fragment_ids = std::vector<int64_t>(p.fragment_ids.begin(), p.fragment_ids.end());
  part.id = p.id;
  part.image_id = p.image_id;
  part.index = std::vector<int64_t>(p.index.begin(), p.index.end());
  part.interaction_id = p.interaction_id;
  part.is_ccrosser = p.is_ccrosser;
  part.is_contained = p.is_contained;
  part.is_primary = p.is_primary;
  part.is_principal_match = p.is_principal_match;
  part.is_valid = p.is_valid;
  part.ke = p.ke;
  part.length = p.length;
  part.match = std::vector<int64_t>(p.match.begin(), p.match.end());
  part.match_overlap = std::vector<float>(p.match_overlap.begin(), p.match_overlap.end());
  part.matched = p.matched;
  part.mcs_ke = p.mcs_ke;
  COPY(part.momentum, p.momentum);
  part.nu_id = p.nu_id;
  part.num_fragments = p.num_fragments;
  part.pdg_code = p.pdg_code;
  part.pid = (int64_t)p.pid;
  COPY(part.pid_scores, p.pid_scores);
  COPY(part.primary_scores, p.primary_scores);
  part.semantic_type = (int64_t)p.semantic_type;
  part.size = p.size;
  COPY(part.start_dir, p.start_dir);
  COPY(part.start_point, p.start_point);
  part.units = p.units;
  part.volume_id = p.volume_id;

  return part;
}

caf::SRInteractionTruthDLP fill_truth_interaction(dlp::types::TruthInteraction &in, std::vector<caf::SRParticleTruthDLP> &particles)
{
  in.match.reset(&in.match_handle);
  in.match_overlap.reset(&in.match_overlap_handle);
  in.nu_position.reset(&in.nu_position_handle);
  in.particle_ids.reset(&in.particle_ids_handle);
  in.truth_particle_counts.reset(&in.truth_particle_counts_handle);
  in.truth_primary_counts.reset(&in.truth_primary_counts_handle);

  caf::SRInteractionTruthDLP ret;
  ret.coffset = in.coffset;
  ret.crthit_id = in.crthit_id;
  ret.crthit_matched = in.crthit_matched;
  ret.crthit_matched_particle_id = in.crthit_matched_particle_id;
  ret.flash_hypothesis = in.flash_hypothesis;
  ret.flash_id = in.flash_id;
  ret.flash_time = in.flash_time;
  ret.flash_total_pe = in.flash_total_pE;
  ret.fmatched = in.fmatched;
  ret.id = in.id;
  ret.image_id = in.image_id;
  ret.is_ccrosser = in.is_ccrosser;
  ret.is_contained = in.is_contained;
  ret.is_fiducial = in.is_fiducial;
  ret.is_neutrino = in.is_neutrino;
  ret.is_principal_match = in.is_principal_match;
  ret.match = std::vector<int64_t>(in.match.begin(), in.match.end());
  ret.match_overlap = std::vector<float>(in.match_overlap.begin(), in.match_overlap.end());
  ret.matched = in.matched;
  ret.nu_bjorken_x = in.nu_bjorken_x;
  ret.nu_creation_process = in.nu_creation_process;
  ret.nu_current_type = (int64_t)in.nu_current_type;
  ret.nu_distance_travel = in.nu_distance_travel;
  ret.nu_energy_deposit = in.nu_energy_deposit;
  ret.nu_energy_init = in.nu_energy_init;
  ret.nu_hadronic_invariant_mass = in.nu_hadronic_invariant_mass;
  ret.nu_id = in.nu_id;
  ret.nu_inelasticity = in.nu_inelasticity;
  ret.nu_interaction_mode = (int64_t)in.nu_interaction_mode;
  ret.nu_interaction_type = (int64_t)in.nu_interaction_type;
  ret.nu_lepton_track_id = in.nu_lepton_track_id;
  ret.nu_mcst_index = in.nu_mcst_index;
  ret.nu_mct_index = in.nu_mct_index;
  ret.nu_momentum_transfer = in.nu_momentum_transfer;
  ret.nu_nucleon = in.nu_nucleon;
  ret.nu_num_voxels = in.nu_num_voxels;
  ret.nu_p = in.nu_p;
  ret.nu_pdg_code = in.nu_pdg_code;
  ret.nu_position = std::vector<double>(in.nu_position.begin(), in.nu_position.end());
  ret.nu_quark = in.nu_quark;
  ret.nu_t = in.nu_t;
  ret.nu_target = in.nu_target;
  ret.nu_theta = in.nu_theta;
  ret.nu_track_id = in.nu_track_id;
  ret.nu_truth_id = in.nu_truth_id;
  ret.num_particles = in.num_particles;
  ret.num_primaries = in.num_primaries;
  COPY(ret.particle_counts,in.particle_counts);
  ret.particle_ids = std::vector<int64_t>(in.particle_ids.begin(), in.particle_ids.end());
  COPY(ret.primary_counts,in.primary_counts);
  ret.size = in.size;
  ret.topology = in.topology;
  ret.truth_id = in.truth_id;
  ret.truth_particle_counts = std::vector<int64_t>(in.truth_particle_counts.begin(), in.truth_particle_counts.end());
  ret.truth_primary_counts = std::vector<int64_t>(in.truth_primary_counts.begin(), in.truth_primary_counts.end());
  ret.truth_topology = in.truth_topology;
  COPY(ret.truth_vertex,in.truth_vertex);
  ret.units = in.units;
  COPY(ret.vertex,in.vertex);
  ret.vertex_mode = in.vertex_mode;
  ret.volume_id = in.volume_id;
  for(int64_t id : ret.particle_ids)
    ret.particles.push_back(particles.at(id));

  return ret;
}

caf::SRInteractionDLP fill_interaction(dlp::types::Interaction &in, std::vector<caf::SRParticleDLP> &particles)
{
  in.match.reset(&in.match_handle);
  in.match_overlap.reset(&in.match_overlap_handle);
  in.particle_ids.reset(&in.particle_ids_handle);

  caf::SRInteractionDLP ret;
  ret.coffset = in.coffset;
  ret.crthit_id = in.crthit_id;
  ret.crthit_matched = in.crthit_matched;
  ret.crthit_matched_particle_id = in.crthit_matched_particle_id;
  ret.flash_hypothesis = in.flash_hypothesis;
  ret.flash_id = in.flash_id;
  ret.flash_time = in.flash_time;
  ret.flash_total_pe = in.flash_total_pE;
  ret.fmatched = in.fmatched;
  ret.id = in.id;
  ret.image_id = in.image_id;
  ret.is_ccrosser = in.is_ccrosser;
  ret.is_contained = in.is_contained;
  ret.is_fiducial = in.is_fiducial;
  ret.is_neutrino = in.is_neutrino;
  ret.is_principal_match = in.is_principal_match;
  ret.match = std::vector<int64_t>(in.match.begin(), in.match.end());
  ret.match_overlap = std::vector<float>(in.match_overlap.begin(), in.match_overlap.end());
  ret.matched = in.matched;
  ret.nu_id = in.nu_id;
  ret.num_particles = in.num_particles;
  ret.num_primaries = in.num_primaries;
  COPY(ret.particle_counts, in.particle_counts);
  ret.particle_ids = std::vector<int64_t>(in.particle_ids.begin(), in.particle_ids.end());
  COPY(ret.primary_counts, in.primary_counts);
  ret.size = in.size;
  ret.topology = in.topology;
  ret.units = in.units;
  COPY(ret.vertex, in.vertex);
  ret.vertex_mode = in.vertex_mode;
  ret.volume_id = in.volume_id;
  for(int64_t id : ret.particle_ids)
    ret.particles.push_back(particles.at(id));

  return ret;
}
#endif
