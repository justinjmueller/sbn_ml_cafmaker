cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

project(sbn_ml_cafmaker)

find_package(HDF5 REQUIRED COMPONENTS C CXX HL)
find_package(sbnanaobj)
find_package(ZLIB)
find_package(ROOT REQUIRED)
set(SBNANAOBJ_INCLUDE_DIRS "$ENV{MRB_SOURCE}/sbnanaobj/")

# The input HDF5 files for data do not have truth products in them, so the
# same top-level "dlp::types::Event" class should not contain references to
# them when handling events from data. This is accomplished by means of a
# preprocessor flag that checks if "MC_NOT_DATA" is defined and allows for
# truth products to be defined if it is. Two separate libraries are therefore
# built and linked against.
add_library(libDLP_simulation SHARED sbn_h5_classes.cc)
target_link_libraries(libDLP_simulation PRIVATE ${HDF5_LIBRARIES} ZLIB::ZLIB)
target_include_directories(libDLP_simulation PRIVATE ${HDF5_INCLUDE_DIR})
target_compile_definitions(libDLP_simulation PRIVATE MC_NOT_DATA)

add_library(libDLP_data SHARED sbn_h5_classes.cc)
target_link_libraries(libDLP_data PRIVATE ${HDF5_LIBRARIES} ZLIB::ZLIB)
target_include_directories(libDLP_data PRIVATE ${HDF5_INCLUDE_DIR})

# This executable is meant for cases where "ML-only" CAFs are desired. It will
# produce a CAF file with only the ML reconstruction outputs available. There
# are two versions: one for data and one for simulation
add_executable(make_standalone_simulation make_standalone.cc)
target_compile_definitions(make_standalone_simulation PRIVATE MC_NOT_DATA)
target_link_libraries(make_standalone_simulation PRIVATE ${HDF5_LIBRARIES} ZLIB::ZLIB libDLP_simulation ${sbnanaobj_LIBRARY_DIRS}/libsbnanaobj_StandardRecord.so ${ROOT_LIBRARIES})
target_include_directories(make_standalone_simulation PRIVATE ${HDF5_INCLUDE_DIR} ${SBNANAOBJ_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

add_executable(make_standalone_data make_standalone.cc)
target_link_libraries(make_standalone_data PRIVATE ${HDF5_LIBRARIES} ZLIB::ZLIB libDLP_data ${sbnanaobj_LIBRARY_DIRS}/libsbnanaobj_StandardRecord.so ${ROOT_LIBRARIES})
target_include_directories(make_standalone_data PRIVATE ${HDF5_INCLUDE_DIR} ${SBNANAOBJ_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

# This executable is meant for merging already existing CAFs (holding Pandora
# reconstruction outputs) with ML reconstructions outputs. There are two
# versions available: one for data and one for simulation.
add_executable(merge_sources_simulation merge_sources.cc)
target_compile_definitions(merge_sources_simulation PRIVATE MC_NOT_DATA)
target_link_libraries(merge_sources_simulation PRIVATE ${HDF5_LIBRARIES} ZLIB::ZLIB libDLP_simulation ${sbnanaobj_LIBRARY_DIRS}/libsbnanaobj_StandardRecord.so ${ROOT_LIBRARIES})
target_include_directories(merge_sources_simulation PRIVATE ${HDF5_INCLUDE_DIR} ${SBNANAOBJ_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

add_executable(merge_sources_data merge_sources.cc)
target_link_libraries(merge_sources_data PRIVATE ${HDF5_LIBRARIES} ZLIB::ZLIB libDLP_data ${sbnanaobj_LIBRARY_DIRS}/libsbnanaobj_StandardRecord.so ${ROOT_LIBRARIES})
target_include_directories(merge_sources_data PRIVATE ${HDF5_INCLUDE_DIR} ${SBNANAOBJ_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

message("${sbnanaobj_LIBRARY_DIRS}")
