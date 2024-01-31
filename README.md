# Introduction
CAF (Common Analysis Framework) files are used in SBN analyses either through the CAFAna framework or through various standalone projects. In either case, they are a common starting point for many analyzers. The standard pathway for making CAFs only includes reconstruction outputs which are available in the artROOT files after the final step of the reconstruction chain.

The `lartpc_mlreco3d` package ([Github](https://github.com/DeepLearnPhysics/lartpc_mlreco3d)) implements an end-to-end reconstruction chain with a machine learning algorithms at the heart of point classification, clustering, and particle identification. The reconstruction chain uses LArCV files as input and produces HDF5 files with the outputs of the reconstruction. This necessarily takes place outside of the LArSoft ecosystem, so to make these reconstruction outputs available for analyzers requires a little extra work.

# Overview of `sbn_ml_cafmaker`
The `sbn_ml_cafmaker` package provides code for merging the ML reconstruction outputs into existing CAF files (enforcing event-by-event matching) and for producing standalone CAF files with only ML reconstruction outputs. 

## Dependencies
The package has two main requirements:
* HDF5 C++ library (available as a ups product)
* `sbnanaobj` (must have ML variables implemented in `StandardRecord`)

## Installation
The repository can be easily built using CMake:

    git clone https://github.com/justinjmueller/sbn_ml_cafmaker.git
    cd sbn_ml_cafmaker
    mkdir build
    cmake /path/to/sbn_ml_cafmaker
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