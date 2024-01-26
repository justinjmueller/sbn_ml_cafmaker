cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

project(ReadHDF5)

find_package(HDF5 REQUIRED COMPONENTS C CXX HL)
find_package(sbnanaobj)
find_package(ZLIB)
find_package(ROOT REQUIRED)
set(SBNANAOBJ_INCLUDE_DIRS "$ENV{MRB_SOURCE}/sbnanaobj/")

add_library(Objects SHARED sbn_h5_classes.cc)
target_link_libraries(Objects PRIVATE ${HDF5_LIBRARIES} ZLIB::ZLIB)
target_include_directories(Objects PRIVATE ${HDF5_INCLUDE_DIR})

add_executable(ReadHDF5 main.cc)
target_link_libraries(ReadHDF5 PRIVATE ${HDF5_LIBRARIES} ZLIB::ZLIB Objects ${sbnanaobj_LIBRARY_DIRS}/libsbnanaobj_StandardRecord.so ${ROOT_LIBRARIES})
target_include_directories(ReadHDF5 PRIVATE ${HDF5_INCLUDE_DIR} ${SBNANAOBJ_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

add_executable(merge_sources merge_sources.cc)
target_link_libraries(merge_sources PRIVATE ${HDF5_LIBRARIES} ZLIB::ZLIB Objects ${sbnanaobj_LIBRARY_DIRS}/libsbnanaobj_StandardRecord.so ${ROOT_LIBRARIES})
target_include_directories(merge_sources PRIVATE ${HDF5_INCLUDE_DIR} ${SBNANAOBJ_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

message("${sbnanaobj_LIBRARY_DIRS}")
