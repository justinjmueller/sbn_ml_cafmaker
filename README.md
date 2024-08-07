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