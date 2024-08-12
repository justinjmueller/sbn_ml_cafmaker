# Introduction
CAF (Common Analysis Framework) files are used in SBN analyses either through the CAFAna framework or through various standalone projects. In either case, they are a common starting point for many analyzers. The standard pathway for making CAFs only includes reconstruction outputs which are available in the artROOT files after the final step of the reconstruction chain.

The `SPINE` (Scalable Particle Imaging with Neural Embeddings) package ([Github](https://github.com/DeepLearnPhysics/spine)) implements an end-to-end reconstruction chain with a machine learning algorithms at the heart of point classification, clustering, and particle identification. The reconstruction chain uses LArCV files as input and produces HDF5 files with the outputs of the reconstruction. This necessarily takes place outside of the LArSoft ecosystem, so to make these reconstruction outputs available for analyzers requires a little extra work.

# Overview of `sbn_ml_cafmaker`
The `sbn_ml_cafmaker` package provides code for merging the ML reconstruction outputs into existing CAF files (enforcing event-by-event matching) and for producing standalone CAF files with only ML reconstruction outputs. 

## Dependencies
The package has two main requirements:
* HDF5 C++ library (instructions below)
* `sbnanaobj` (must have ML variables implemented in `StandardRecord`)

### Installing the HDF5 C++ API
The most recent versions of `hdf5` available on UPS do not come packaged with the C++ API. The latest version which works as a viable dependency is `v1.10.5` with qualifier `e20`, which is absolutely ancient. Moreover, `hdf5` will not be supported in the future as a UPS product. The switch to qualifier `e26` means that the UPS product is essentially a non-workable solution for the foreseable future. The unfortunate solution is to clone and build the `hdf5` repository. 

CMake is required to be setup before beginning installation:

    cd /path/to/hdf5 (hereafter $HDF5_HOME)
    git clone https://github.com/HDFGroup/hdf5.git $HDF5_HOME/hdf5_src
    mkdir $HDF5_HOME/hdf5_build
    mkdir $HDF5_HOME/hdf5_install
    cd $HDF5_HOME/hdf5_src
    git checkout hdf5-1_10_5
    cd $HDF5_HOME/hdf5_build
    cmake $HDF5_HOME/hdf5_src/ -DCMAKE_CXX_COMPILER="g++" -DCMAKE_CXX_STANDARD=17 -DCMAKE_INSTALL_PREFIX=$HDF5_HOME/hdf5_install/
    make install

This should build an install of `hdf5` that is compatible with qualifier `e26` and that can be used for building `sbn_ml_cafmaker`.

### Building `sbnanaobj`
The machine-learning reconstruction outputs are implemented as two additional branches within the `StandardRecord` tree. It is recommended to clone the latest version of `sbnanaobj` to be compatible with existing CAF files (or backwards compatible) and then `git cherry-pick` the singular commit on feature branch `feature/mueller_mlcafs` implementing these new variables. This will result in the most up-to-date version of `StandardRecord` after building for use in `sbn_ml_cafmaker`.

## Installation
The repository can be easily built using CMake:

    git clone https://github.com/justinjmueller/sbn_ml_cafmaker.git
    cd sbn_ml_cafmaker
    mkdir build
    cmake /path/to/sbn_ml_cafmaker -DHDF5_INSTALL="/path/to/hdf5/install"
    make

## Merging
The executable that handles the merging of the ML reconstruction outputs into an existing CAF (with the same events) is `merge_sources`. The executable takes as input a standard CAF file (not flattened) and the HDF5 with the reconstruction outputs of the same set of events. It uses the run number and event number to build a look-up table for events in the HDF5 file, then copies them into the `StandardRecord` during the main loop over entries in the CAF file. Finally, the output CAF file is written. There exists a separate executable for data (only contains reconstructed objects) and simulation (additionally has truth objects). The executable can be used as:

    ./merge_sources_simulation <output_caf_file> <input_caf_file> <input_hdf5_file>

or

    ./merge_sources_data <output_caf_file> <input_caf_file> <input_hdf5_file>

In the case where no ML reconstruction outputs exist for an event, none are written. If the ML classes within the `StandardRecord` are already filled, they are erased and replaced with the new inputs. This serves to allow efficient updating of reconstruction outputs in the future.

## Standalone
The executable that handles the creation of standalone CAFs with only ML reconstruction outputs is `make_standalone`. The executable takes as input a list of input HDF5 files and places them in a single CAF output file. There exists a separate executable for data (only contains reconstructed objects) and simulation (additionally has truth objects). The executable can be used as:

    ./make_standalone_simulation <output_caf_file> <event_offset> <input_hdf5_file(s)>

or

    ./make_standalone_data <output_caf_file> <event_offset> <input_hdf5_file(s)>

The `event_offset` is used to introduce a offset to the `image_id` attribute of interactions and particles. This may be useful in some cases for breaking the degeneracy of `image_id`s in multiple input files. The list of HDF5 input files may be one or longer - the code will loop over the remaining arguments and produce a single output file.

# Variables

<!--
| Variable Name | Variable Type | Units | Access Path | Description | Link to further Documentation |
| ------------- | ------------- | ----- | ----------- | ----------- | ----------------------------- |
-->
## RecoInteraction
|         Variable Name          |       Variable Type       | Units |                                        Description                                         |
| ------------------------------ | ------------------------- | ----- | ------------------------------------------------------------------------------------------ |
| cathode_offset                 | double                    | cm    | Distance from the cathode.                                                                 |
| flash_hypo_pe                  | double                    | p.e.  | Total PE of the hypothesized flash.                                                        |
| flash_id                       | int64_t                   | p.e.  | Flash ID for the matched flash.                                                            |
| flash_time                     | double                    | us    | Time of the matched flash.                                                                 |
| flash_total_pe                 | double                    | p.e.  | Total PE of the matched flash.                                                             |
| id                             | int64_t                   | None  | Interaction ID.                                                                            |
| index                          | std::vector<int64_t>      | None  | List of coordinate indices that comprise the interaction.                                  |
| is_cathode_crosser             | bool                      | None  | Whether the interaction is a cathode-crosser.                                              |
| is_contained                   | bool                      | None  | Whether the interaction is contained.                                                      |
| is_fiducial                    | bool                      | None  | Whether the interaction has an interaction in the fiducial volume.                         |
| is_flash_matched               | bool                      | None  | Whether the flash is matched to the interaction.                                           |
| is_matched                     | bool                      | None  | Whether the interaction is matched to a true interaction.                                  |
| is_truth                       | bool                      | None  | Whether the interaction is a truth interaction.                                            |
| match_ids                      | std::vector<int64_t>      | None  | Interaction IDs of the considered matches (correspond to true interactions).               |
| match_overlaps                 | std::vector<float>        | None  | Intersection over union (IoU) of the considered matches.                                   |
| module_ids                     | std::vector<float>        | None  | Module IDs of the interaction.                                                             |
| particle_ids                   | std::vector<int64_t>      | None  | Particle IDs in the interaction.                                                           |
| topology                       | char *                    | None  | Topology of the interaction (e.g. "0g0e1mu0pi2p") considering only primaries.              |
| units                          | char *                    | None  | Units in which the position coordinates are expressed.                                     |
| vertex                         | std::array<float, 3>      | cm    | Vertex of the interaction in detector coordinates.                                         |

## RecoParticle
|         Variable Name          |       Variable Type       | Units |                                        Description                                         |
| ------------------------------ | ------------------------- | ----- | ------------------------------------------------------------------------------------------ |
| calo_ke                        | double                    | MeV   | Calorimetric kinetic energy.                                                               |
| cathode_offset                 | double                    | cm    | Distance from the cathode.                                                                 |
| csda_ke                        | double                    | MeV   | Continuous-slowing-down-approximation kinetic energy.                                      |
| end_dir                        | std::array<float, 3>      | None  | Unit direction vector calculated at the particle end point.                                |
| end_point                      | std::array<float, 3>      | cm    | End point (vector) of the particle.                                                        |
| fragment_ids                   | std::vector<int32_t>      | None  | Fragment IDs comprising the particle.                                                      |
| id                             | int64_t                   | None  | Particle ID.                                                                               |
| index                          | std::vector<int64_t>      | None  | List of coordinate indices that comprise the particle.                                     |
| interaction_id                 | int64_t                   | None  | Parent interaction ID.                                                                     |
| is_cathode_crosser             | bool                      | None  | Whether the particle is a cathode-crosser.                                                 |
| is_contained                   | bool                      | None  | Whether the particle is contained.                                                         |
| is_matched                     | bool                      | None  | Whether the particle is matched.                                                           |
| is_primary                     | bool                      | None  | Whether the particle is a primary particle.                                                |
| is_truth                       | bool                      | None  | Whether the particle is a truth particle.                                                  |
| is_valid                       | bool                      | None  | Whether the particle passes thresholds and counts towards topology.                        |
| ke                             | double                    | MeV   | Kinetic energy according to assumed best energy estimator (CSDA, calorimetric, or MCS).    |
| length                         | double                    | cm    | Length of the particle.                                                                    |
| match_ids                      | std::vector<int64_t>      | None  | Match ID.                                                                                  |
| match_overlaps                 | std::vector<float>        | None  | Match overlap.                                                                             |
| mcs_ke                         | double                    | MeV   | Multiple Coulomb scattering kinetic energy.                                                |
| module_ids                     | std::vector<float>        | None  | Module IDs of the particle.                                                                |
| momentum                       | std::array<float, 3>      | MeV/c | Momentum (vector) of the particle.                                                         |
| p                              | float                     | MeV/c | Momentum magnitude.                                                                        |
| pdg_code                       | int64_t                   | None  | PDG code of the particle.                                                                  |
| pid                            | Pid                       | None  | Particle ID (see Pid enumeration).                                                         |
| pid_scores                     | std::array<float, 5>      | None  | PID softmax scores.                                                                        |
| ppn_ids                        | std::vector<int32_t>      | None  | PPN IDs of the particle.                                                                   |
| primary_scores                 | std::array<float, 2>      | None  | Primary softmax scores.                                                                    |
| shape                          | Shape                     | None  | Semantic type of the particle (see SemanticType enumeration).                              |
| start_dir                      | std::array<float, 3>      | None  | Unit direction vector calculated at the particle start point.                              |
| start_point                    | std::array<float, 3>      | cm    | Start point (vector) of the particle.                                                      |
| units                          | char *                    | None  | Units in which the position coordinates are expressed.                                     |

## TrueInteraction
|         Variable Name          |       Variable Type       | Units |                                        Description                                         |
| ------------------------------ | ------------------------- | ----- | ------------------------------------------------------------------------------------------ |
| bjorken_x                      | double                    | None  | Bjorken x of the neutrino interaction.                                                     |
| cathode_offset                 | double                    | cm    | Distance from the cathode.                                                                 |
| creation_process               | char *                    | None  | Creation process of the neutrino.                                                          |
| energy_transfer                | double                    | GeV   | Energy transfer of the neutrino interaction.                                               |
| flash_hypo_pe                  | double                    | p.e.  | Total PE of the hypothesized flash.                                                        |
| flash_id                       | int64_t                   | p.e.  | Flash ID for the matched flash.                                                            |
| flash_time                     | double                    | us    | Time of the matched flash.                                                                 |
| flash_total_pe                 | double                    | p.e.  | Total PE of the matched flash.                                                             |
| id                             | int64_t                   | None  | Interaction ID.                                                                            |
| index                          | std::vector<int64_t>      | None  | List of coordinate indices that comprise the interaction.                                  |
| index_adapt                    | std::vector<int64_t>      | None  | Index corresponding to the true interaction in the adapted cluster label points.           |
| index_g4                       | std::vector<int64_t>      | None  | Index corresponding to the true interaction in the G4 points (effectively SED).            |
| inelasticity                   | double                    | None  | Inelasticity of the neutrino interaction.                                                  |
| interaction_id                 | int64_t                   | None  | Deprecated.                                                                                |
| interaction_mode               | InteractionMode           | None  | Interaction mode of the neutrino.                                                          |
| interaction_type               | InteractionType           | None  | Interaction type of the neutrino.                                                          |
| is_cathode_crosser             | bool                      | None  | Whether the interaction is a cathode-crosser.                                              |
| is_contained                   | bool                      | None  | Whether the interaction is contained.                                                      |
| is_fiducial                    | bool                      | None  | Whether the interaction has an interaction in the fiducial volume.                         |
| is_flash_matched               | bool                      | None  | Whether the flash is matched to the interaction.                                           |
| is_matched                     | bool                      | None  | Whether the interaction is matched to a true interaction.                                  |
| is_truth                       | bool                      | None  | Whether the interaction is a truth interaction.                                            |
| lepton_p                       | double                    | GeV/c | Momentum of the lepton in the interaction.                                                 |
| lepton_pdg_code                | int64_t                   | None  | PDG code of the lepton in the interaction.                                                 |
| lepton_theta                   | double                    | rad   | Angle between incoming and outgoing leptons.                                               |
| lepton_track_id                | int64_t                   | None  | Track ID of the lepton in the neutrino interaction.                                        |
| match_ids                      | std::vector<int64_t>      | None  | Interaction IDs of the considered matches (correspond to true interactions).               |
| match_overlaps                 | std::vector<float>        | None  | Intersection over union (IoU) of the considered matches.                                   |
| module_ids                     | std::vector<int32_t>      | None  | Module IDs of the interaction.                                                             |
| nu_current_type                | CurrentType               | None  | Current type of the neutrino.                                                              |
| nu_energy_init                 | double                    | GeV   | Initial energy of the neutrino.                                                            |
| nu_hadronic_invariant_mass     | double                    | GeV   | Hadronic invariant mass of the neutrino.                                                   |
| nu_id                          | int64_t                   | None  | Neutrino ID (-1 = not a neutrino, 0 = first neutrino, 1 = second neutrino, etc.).          |
| nu_mct_index                   | int64_t                   | None  | Index of the neutrino in the original MCTruth array.                                       |
| nu_momentum                    | std::array<float, 3>      | GeV/c | Momentum of the neutrino.                                                                  |
| nu_nucleon                     | int64_t                   | None  | Nucleon in the neutrino interaction.                                                       |
| nu_p                           | std::array<float, 3>      | GeV   | Momentum (vector) of the neutrino.                                                         |
| nu_pdg_code                    | int64_t                   | None  | PDG code of the neutrino.                                                                  |
| nu_quark                       | int64_t                   | None  | Quark in the neutrino interaction.                                                         |
| nu_target                      | int64_t                   | None  | Target in the neutrino interaction.                                                        |
| nu_theta                       | double                    | rad   | Angle of the neutrino interaction.                                                         |
| nu_track_id                    | int64_t                   | None  | Track ID of the neutrino interaction.                                                      |
| orig_id                        | int64_t                   | None  | Original ID of the interaction.                                                            |
| particle_ids                   | std::vector<int64_t>      | None  | Particle IDs in the interaction.                                                           |
| position                       | std::array<float, 3>      | cm    | Position of the neutrino interaction.                                                      |
| q0                             | double                    | GeV   | Energy transfer (Q0) of the neutrino interaction.                                          |
| q2                             | double                    | GeV   | Momentum transfer (Q^2) of the neutrino interaction.                                       |
| q3                             | double                    | GeV/c | Momentum transfer (Q3) of the neutrino interaction.                                        |
| reco_vertex                    | std::array<float, 3>      | cm    | Vertex of the interaction in detector coordinates (reco).                                  |
| topology                       | char *                    | None  | Topology of the interaction (e.g. "0g0e1mu0pi2p") considering only primaries.              |
| truth_vertex                   | std::array<float, 3>      | cm    | Vertex of the interaction in detector coordinates (truth).                                 |
| units                          | char *                    | None  | Units in which the position coordinates are expressed.                                     |

## TrueParticle
|         Variable Name          |       Variable Type       | Units |                                        Description                                         |
| ------------------------------ | ------------------------- | ----- | ------------------------------------------------------------------------------------------ |
| ancestor_creation_process      | char *                    | None  | Geant4 creation process of the ancestor particle.                                          |
| ancestor_pdg_code              | int64_t                   | None  | PDG code of the ancestor particle.                                                         |
| ancestor_position              | std::array<float, 3>      | cm    | Position of the ancestor particle.                                                         |
| ancestor_t                     | double                    | ns    | Time of the ancestor particle.                                                             |
| ancestor_track_id              | int64_t                   | None  | Track ID of the ancestor particle.                                                         |
| calo_ke                        | double                    | MeV   | Calorimetric kinetic energy.                                                               |
| cathode_offset                 | double                    | cm    | Distance from the cathode.                                                                 |
| children_counts                | std::vector<int64_t>      | None  | Number of children of the particle.                                                        |
| children_id                    | std::vector<int64_t>      | None  | List of particle ID of children particles.                                                 |
| creation_process               | char *                    | None  | Geant4 creation process of the particle.                                                   |
| csda_ke                        | double                    | MeV   | Continuous-slowing-down-approximation kinetic energy.                                      |
| end_dir                        | std::array<float, 3>      | None  | Unit direction vector calculated at the particle end point.                                |
| end_momentum                   | std::array<float, 3>      | MeV/c | Momentum (vector) of the particle at the end.                                              |
| end_p                          | float                     | MeV/c | Momentum magnitude of the particle at the end.                                             |
| end_point                      | std::array<float, 3>      | cm    | End point (vector) of the particle.                                                        |
| end_position                   | std::array<float, 3>      | cm    | End position (vector) of the particle.                                                     |
| energy_deposit                 | double                    | MeV   | Energy deposited by the particle.                                                          |
| energy_init                    | double                    | MeV   | Initial energy of the particle.                                                            |
| first_step                     | std::array<float, 3>      | cm    | Coordinates of the first step of the particle.                                             |
| fragment_ids                   | std::vector<int64_t>      | None  | Fragment IDs comprising the particle.                                                      |
| gen_id                         | int64_t                   | None  | Generator ID of the particle (may differ from Geant4 or Supera ID).                        |
| group_id                       | int64_t                   | None  | Group ID of the particle.                                                                  |
| group_primary                  | int64_t                   | None  | Whether the particle is a primary within its group.                                        |
| id                             | int64_t                   | None  | Particle ID.                                                                               |
| index                          | std::vector<int64_t>      | None  | List of coordinate indices that comprise the particle.                                     |
| index_adapt                    | std::vector<int64_t>      | None  | Index corresponding to the true particle in the adapted cluster label points.              |
| index_g4                       | std::vector<int64_t>      | None  | Index corresponding to the true particle in the G4 points (effectively SED).               |
| interaction_id                 | int64_t                   | None  | Parent interaction ID.                                                                     |
| interaction_primary            | int64_t                   | None  | Whether the particle is a primary within its interaction (equivalent to is_primary).       |
| is_cathode_crosser             | bool                      | None  | Whether the particle is a cathode-crosser.                                                 |
| is_contained                   | bool                      | None  | Whether the particle is contained.                                                         |
| is_matched                     | bool                      | None  | Whether the particle is matched.                                                           |
| is_primary                     | bool                      | None  | Whether the particle is a primary particle.                                                |
| is_truth                       | bool                      | None  | Whether the particle is a truth particle.                                                  |
| is_valid                       | bool                      | None  | (Whether the particle passes thresholds and counts towards topology.                       |
| ke                             | double                    | MeV   | Kinetic energy according to assumed best energy estimator (CSDA, calorimetric, or MCS).    |
| last_step                      | std::array<float, 3>      | cm    | Coordinates of the last step of the particle.                                              |
| length                         | double                    | cm    | Length of the particle.                                                                    |
| match_ids                      | std::vector<int64_t>      | None  | Match ID.                                                                                  |
| match_overlaps                 | std::vector<float>        | None  | Match overlap.                                                                             |
| mcs_ke                         | double                    | MeV   | Multiple Coulomb scattering kinetic energy.                                                |
| mcst_index                     | int64_t                   | None  | MCST index.                                                                                |
| mct_index                      | int64_t                   | None  | Index of the particle in the original MCTruth array..                                      |
| module_ids                     | std::vector<float>        | None  | Module IDs of the particle.                                                                |
| momentum                       | std::array<float, 3>      | MeV/c | Momentum (vector) of the particle.                                                         |
| nu_id                          | int64_t                   | None  | Neutrino ID (-1 = not a neutrino, 0 = first neutrino, 1 = second neutrino, etc.).          |
| num_voxels                     | int64_t                   | None  | Number of voxels comprising the particle.                                                  |
| orig_id                        | int64_t                   | None  | Original ID of the particle.                                                               |
| orig_interaction_id            | int64_t                   | None  | Interaction ID as it was stored in the parent LArCV file under the interaction_id attribute. |
| p                              | float                     | MeV/c | Momentum magnitude.                                                                        |
| parent_creation_process        | char *                    | None  | Geant4 creation process of the parent particle.                                            |
| parent_id                      | int64_t                   | None  | Parent particle ID.                                                                        |
| parent_pdg_code                | int64_t                   | None  | PDG code of the parent particle.                                                           |
| parent_position                | std::array<float, 3>      | cm    | Position of the parent particle.                                                           |
| parent_t                       | double                    | ns    | Time of the parent particle.                                                               |
| parent_track_id                | int64_t                   | None  | Track ID of the parent particle.                                                           |
| pdg_code                       | int64_t                   | None  | PDG code of the particle.                                                                  |
| pid                            | Pid                       | None  | Particle ID (see Pid enumeration).                                                         |
| position                       | std::array<float, 3>      | cm    | Position of the particle.                                                                  |
| shape                          | Shape                     | None  | Semantic type of the particle (see SemanticType enumeration).                              |
| start_dir                      | std::array<float, 3>      | None  | Unit direction vector calculated at the particle start point.                              |
| start_point                    | std::array<float, 3>      | cm    | Start point (vector) of the particle.                                                      |
| t                              | double                    | ns    | Time of the particle.                                                                      |
| track_id                       | int64_t                   | None  | Track ID of the particle.                                                                  |
| truth_end_dir                  | std::array<double, 3>     | None  | Unit direction vector calculated at the truth particle end point.                          |
| truth_start_dir                | std::array<double, 3>     | None  | Unit direction vector calculated at the truth particle start point.                        |
| units                          | char *                    | None  | Units in which the position coordinates are expressed.                                     |