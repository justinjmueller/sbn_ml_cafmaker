/**
 * @file products.h
 * @brief Declaration of various functions for interacting with and retrieving
 * data from H5 files.
 * @author mueller@fnal.gov
*/
#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <vector>
#include "H5Cpp.h"
#include "event.h"

/**
 * @brief Checks the dimensions of the H5 DataSpace and calculates the number
 * of events present.
 * @param dsp the H5 DataSpace.
 * @return the number of events in the DataSpace.
*/
size_t get_nevents(H5::DataSpace & dsp);

/**
 * @brief Retrieves the specified dlp::types::Event object from the H5 file.
 * @param file the input H5 file.
 * @param index of the event to retrieve.
 * @return the specified dlp::types::Event object.
*/
dlp::types::Event get_single_event(H5::H5File & file, int64_t index);

/**
 * @brief Retrieves all objects of class dlp::types::Event from the H5 file.
 * @param file the input H5 file.
 * @return a vector of all dlp::types::Event objects in the file.
*/
std::vector<dlp::types::Event> get_all_events(H5::H5File & file);

/**
 * @brief Retrieves all products of a certain type from the H5 file.
 * @tparam T the type of product to retrieve.
 * @param file the input H5 file.
 * @param evt the dlp::types::Event object containing the references to the
 * requested products.
*/
template <class T>
std::vector<T> get_product(H5::H5File & file, dlp::types::Event & evt);

#endif // PRODUCTS_H