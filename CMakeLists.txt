cmake_minimum_required(VERSION 3.12)

# CMake colourised text! See https://stackoverflow.com/questions/18968979/
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(OUTNOCOL "${Esc}[m")
  set(OUTRED "${Esc}[31m")
  set(OUTYELLOW "${Esc}[33m")
  set(OUTGREEN "${Esc}[32m")
  set(OUTCYAN "${Esc}[36m")
endif()

project(sbn_ml_cafmaker VERSION 0.1)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

string(REPLACE "." "_" CMAKE_PROJECT_VERSION_UNDERSCORES "${CMAKE_PROJECT_VERSION}")
set(CMAKE_INSTALL_FQ_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE STRING "Path to fully-qualified install directory")
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_CURRENT_SOURCE_DIR}")
  set_property(CACHE CMAKE_INSTALL_FQ_PREFIX PROPERTY VALUE "${CMAKE_INSTALL_PREFIX}/v${CMAKE_PROJECT_VERSION_UNDERSCORES}")
endif()

set(CMAKE_INSTALL_BINDIR "${CMAKE_INSTALL_FQ_PREFIX}/bin")
set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_FQ_PREFIX}/lib")

# We'll be careful and set the rpath to include libraries at install location
message(STATUS "${OUTGREEN}Making install directory: ${OUTCYAN}${CMAKE_INSTALL_FQ_PREFIX}${OUTNOCOL}")
set(CMAKE_BUILD_RPATH "${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}")
#set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
message(STATUS "${OUTGREEN}Embdedding libraries in ${OUTCYAN}${CMAKE_INSTALL_RPATH}${OUTNOCOL}")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

file(MAKE_DIRECTORY ${CMAKE_INSTALL_FQ_PREFIX} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_LIBDIR})
set(SBN_ML_CAFMAKER_BINARIES)

# Small function to append binary to SBN_ML_CAFMAKER_BINARIES
function(add_sbnml_executable name source)
  add_executable(${name} ${source})
  set_property(GLOBAL APPEND PROPERTY SBN_ML_CAFMAKER_BINARIES ${name})
endfunction()
# And for SBN_ML_CAFMAKER_LIBRARIES
function(add_sbnml_library name)
  set_property(GLOBAL APPEND PROPERTY SBN_ML_CAFMAKER_LIBRARIES ${name})
endfunction()

find_package(ZLIB)
find_package(HDF5 REQUIRED COMPONENTS C CXX HL)
find_package(ROOT REQUIRED)
find_package(sbnanaobj)

# Until we get sbnanaobj to emit its own targets at CMake level, import.
add_library(SBNANAOBJ::SBNANAOBJ INTERFACE IMPORTED)
set(sbnanaobj_STANDARDRECORD_LIB "${sbnanaobj_LIBRARY_DIR}/libsbnanaobj_StandardRecord.so")
set_target_properties(SBNANAOBJ::SBNANAOBJ PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${sbnanaobj_INCLUDE_DIR}"
  INTERFACE_LINK_LIBRARIES "${sbnanaobj_STANDARDRECORD_LIB}")

set(SBN_ML_CAFMAKER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)

# The input HDF5 files for data do not have truth products in them, so the
# same top-level "dlp::types::Event" class should not contain references to
# them when handling events from data. This is accomplished by means of a
# preprocessor flag that checks if "MC_NOT_DATA" is defined and allows for
# truth products to be defined if it is. Two separate libraries are therefore
# built and linked against.
add_library(dlp_simulation SHARED ${SPINE_SOURCES_BASE})
add_sbnml_library(dlp_simulation)
target_link_libraries(dlp_simulation PRIVATE ZLIB::ZLIB HDF5::HDF5)
target_include_directories(dlp_simulation PRIVATE ${HDF5_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS} ${sbnanaobj_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})
target_compile_definitions(dlp_simulation PRIVATE MC_NOT_DATA)

add_library(dlp_data SHARED ${SPINE_SOURCES_BASE})
add_sbnml_library(dlp_data)
target_link_libraries(dlp_simulation PRIVATE ZLIB::ZLIB HDF5::HDF5)
target_include_directories(dlp_data PRIVATE ${HDF5_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS} ${sbnanaobj_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})

# This executable is meant for testing the HDF5 parsing capabilities of the
# library. It simply connects to the input file and attempts to read the
# contents of the first/passed event.
add_sbnml_executable(test_hdf5 ${SPINE_APP_DIR}/test_hdf5.cc)
target_link_libraries(test_hdf5 PRIVATE ZLIB::ZLIB HDF5::HDF5 ${ROOT_LIBRARIES} SBNANAOBJ::SBNANAOBJ dlp_simulation)
target_include_directories(test_hdf5 PRIVATE ${HDF5_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})
target_compile_definitions(test_hdf5 PRIVATE MC_NOT_DATA REMOVE_THIS)

# This executable is meant for testing the CAF reading capabilities of the
# library. It connects to the input file and attempts to read the contents of
# the first/passed event.
add_sbnml_executable(test_caf ${SPINE_APP_DIR}/test_caf.cc)
target_link_libraries(test_caf PRIVATE ${ROOT_LIBRARIES} SBNANAOBJ::SBNANAOBJ)
target_include_directories(test_caf PRIVATE ${ROOT_INCLUDE_DIRS} ${sbnanaobj_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})

# This executable is meant for cases where "ML-only" CAFs are desired. It will
# produce a CAF file with only the ML reconstruction outputs available. There
# are two versions: one for data and one for simulation
add_sbnml_executable(make_standalone_simulation ${SPINE_APP_DIR}/make_standalone.cc)
target_compile_definitions(make_standalone_simulation PRIVATE MC_NOT_DATA)
target_link_libraries(make_standalone_simulation PRIVATE ZLIB::ZLIB HDF5::HDF5 ${ROOT_LIBRARIES} SBNANAOBJ::SBNANAOBJ dlp_simulation)
target_include_directories(make_standalone_simulation PRIVATE ${HDF5_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS} ${sbnanaobj_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})

add_sbnml_executable(make_standalone_data ${SPINE_APP_DIR}/make_standalone.cc)
target_link_libraries(make_standalone_data PRIVATE ZLIB::ZLIB HDF5::HDF5  ${ROOT_LIBRARIES} SBNANAOBJ::SBNANAOBJ dlp_data)
target_include_directories(make_standalone_data PRIVATE ${HDF5_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS} ${sbnanaobj_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})

# This executable is meant for merging already existing CAFs (holding Pandora
# reconstruction outputs) with ML reconstructions outputs. There are two
# versions available: one for data and one for simulation.
add_sbnml_executable(merge_sources_simulation ${SPINE_APP_DIR}/merge_sources.cc)
target_compile_definitions(merge_sources_simulation PRIVATE MC_NOT_DATA)
target_link_libraries(merge_sources_simulation PRIVATE ZLIB::ZLIB HDF5::HDF5 ${ROOT_LIBRARIES} SBNANAOBJ::SBNANAOBJ dlp_simulation)
target_include_directories(merge_sources_simulation PRIVATE ${HDF5_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS} ${sbnanaobj_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})

add_sbnml_executable(merge_sources_data ${SPINE_APP_DIR}/merge_sources.cc)
target_link_libraries(merge_sources_data PRIVATE ZLIB::ZLIB HDF5::HDF5 ${ROOT_LIBRARIES} SBNANAOBJ::SBNANAOBJ dlp_data)
target_include_directories(merge_sources_data PRIVATE ${HDF5_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS} ${sbnanaobj_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})

# This executable is meant for merging already existing CAFs (holding Pandora
# reconstruction outputs) with ML reconstructions outputs. This is different
# from the previous one in that it is meant to be used with one-to-many merging
# of one CAF file with many HDF5 files. There are two versions available: one
# for data and one for simulation.
add_sbnml_executable(merge_sources_simulation_multi ${SPINE_APP_DIR}/merge_sources_multi.cc)
target_compile_definitions(merge_sources_simulation_multi PRIVATE MC_NOT_DATA)
target_link_libraries(merge_sources_simulation_multi PRIVATE ZLIB::ZLIB HDF5::HDF5 ${ROOT_LIBRARIES} SBNANAOBJ::SBNANAOBJ dlp_simulation)
target_include_directories(merge_sources_simulation_multi PRIVATE ${HDF5_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS} ${sbnanaobj_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})

add_sbnml_executable(merge_sources_data_multi ${SPINE_APP_DIR}/merge_sources_multi.cc)
target_link_libraries(merge_sources_data_multi PRIVATE ZLIB::ZLIB HDF5::HDF5 ${ROOT_LIBRARIES} SBNANAOBJ::SBNANAOBJ dlp_data)
target_include_directories(merge_sources_data_multi PRIVATE ${HDF5_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS} ${sbnanaobj_INCLUDE_DIR} ${SBN_ML_CAFMAKER_INCLUDE})

get_property(SBN_ML_CAFMAKER_LIBRARIES GLOBAL PROPERTY SBN_ML_CAFMAKER_LIBRARIES)
install(TARGETS ${SBN_ML_CAFMAKER_LIBRARIES} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
#install(TARGETS ${SBN_ML_CAFMAKER_LIBRARIES} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
get_property(SBN_ML_CAFMAKER_BINARIES GLOBAL PROPERTY SBN_ML_CAFMAKER_BINARIES)
install(TARGETS ${SBN_ML_CAFMAKER_BINARIES} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
