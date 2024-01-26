/**
 * @file hdf5_utlities.h
 * @brief Implementation of various functions for interacting with and
 * retrieving data from H5 files.
 * @author justin.mueller@colostate.edu
*/

#ifndef HDF5_UTILITIES_H
#define HDF5_UTILITIES_H

#include "H5Cpp.h"
#include "sbn_h5_classes.h"
#include "record_fillers.h"

/**
 * Some preliminary notes about the dataset structure: The top-level object
 * is the dlp::types::Event class. The Event class does not itself contain all
 * data, but rather it contains references to the locations in memory where
 * each other product (particles, interactions, etc) is stored.
*/

/**
 * Checks the dimensions of the H5 DataSpace and calculates the number of
 * events present.
 * @param dsp the H5 DataSpace.
 * @return the number of events in the DataSpace.
*/
size_t get_nevents(H5::DataSpace & dsp)
{
  hsize_t dims_max = dsp.getSimpleExtentNdims();
  auto dims = new hsize_t[dims_max];
  dsp.getSimpleExtentDims(dims);
  size_t nevents(dims[dims_max - 1]);
  delete[] dims;
  return nevents;
}

/**
 * Retrieves the specified dlp::types::Event object from the H5 file.
 * @param file the input H5 file.
 * @param index of the event to retrieve.
 * @return the specified dlp::types::Event object.
*/
dlp::types::Event get_single_event(H5::H5File & file, int64_t index)
{
  H5::DataSet dataset(file.openDataSet("events"));
  H5::DataSpace dsp(dataset.getSpace());

  std::vector<dlp::types::Event> evt(1);
  std::vector<hsize_t> start(1, index);
  std::vector<hsize_t> count(1, 1);
  dsp.selectHyperslab(H5S_SELECT_SET, count.data(), start.data());

  H5::DataSpace memspace(H5S_SIMPLE);
  std::vector<hsize_t> dims(dsp.getSimpleExtentNdims());
  std::vector<hsize_t> dimsMax(dsp.getSimpleExtentNdims(), H5S_UNLIMITED);
  dsp.getSimpleExtentDims(dims.data());
  memspace.setExtentSimple(dsp.getSimpleExtentNdims(), dims.data(), dimsMax.data());
  start[0] = 0;
  count[0] = 1;
  memspace.selectHyperslab(H5S_SELECT_SET, count.data(), start.data());

  H5::CompType ctype(dlp::types::BuildCompType<dlp::types::Event>());
  dataset.read(evt.data(), ctype, memspace, dsp);

  return evt[0];
}

/**
 * Retrieves all objects of class dlp::types::Event from the H5 file.
 * @param file the input H5 file.
 * @return a vector of all dlp::types::Event objects in the file.
*/
std::vector<dlp::types::Event> get_all_events(H5::H5File & file)
{
  H5::DataSet dataset(file.openDataSet("events"));
  H5::DataSpace dsp(dataset.getSpace());

  std::vector<dlp::types::Event> evt;
  evt.resize(get_nevents(dsp));
  H5::CompType ctype(dlp::types::BuildCompType<dlp::types::Event>());
  dataset.read(evt.data(), ctype, H5::DataSpace::ALL, H5::DataSpace::ALL);
  return evt;
}

/**
 * Retrieves all products of a certain type from the H5 file.
 * @tparam T the type of product to retrieve.
 * @param file the input H5 file.
 * @param evt the dlp::types::Event object containing the references to the
 * requested products.
*/
template <class T>
std::vector<T> get_product(H5::H5File & file, dlp::types::Event & evt)
{
  H5::DataSet ds_ref(file.openDataSet("events"));
  
  const void *buff_ref_const(&(evt.GetRef<T>()));
  ds_ref.dereference(file, buff_ref_const, H5R_DATASET_REGION);
  void *buff_ref(&(const_cast<hdset_reg_ref_t&>(evt.GetRef<T>())));
  H5::DataSpace ref_region = file.getRegion(buff_ref);

  H5::DataSpace memspace(H5S_SIMPLE);
  std::vector<hsize_t> dims(ref_region.getSimpleExtentNdims());
  std::vector<hsize_t> dims_max(ref_region.getSimpleExtentNdims(), H5S_UNLIMITED);
  ref_region.getSimpleExtentDims(dims.data());
  memspace.setExtentSimple(1, dims.data(), dims_max.data());
  std::vector<hsize_t> start(1, 0);
  std::vector<hsize_t> count(1, static_cast<hsize_t>(ref_region.getSelectNpoints()));
  memspace.selectHyperslab(H5S_SELECT_SET, count.data(), start.data());

  std::vector<T> data_product(static_cast<hsize_t>(ref_region.getSelectNpoints()));
  H5::CompType ctype(dlp::types::BuildCompType<T>());
  ds_ref.read(data_product.data(), ctype, memspace, ref_region);
  return data_product;
}

#endif