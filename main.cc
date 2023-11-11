#include <iostream>
#include <vector>
#include "H5Cpp.h"
#include "sbn_h5_classes.h"

std::vector<cafmaker::types::Event> get_event(H5::H5File &file, size_t index);

template <class T>
std::vector<T> get_product(H5::H5File &file, cafmaker::types::Event &evt);

std::ostream& operator<<(std::ostream& os, const cafmaker::types::Particle& p);

int main(int argc, char const *argv[])
{
  if(argc != 2)
  {
    std::cerr << "Please provide exactly one input file." << std::endl;
    return 0;
  }

  H5::H5File file(argv[1], H5F_ACC_RDONLY);
  std::cout << "Opened file: " << argv[1] << "\n" << std::endl;
  
  std::vector<cafmaker::types::Event> events(get_event(file, 0));
  std::cerr << "Successfully loaded event.\n" << std::endl;
  
  std::vector<cafmaker::types::Particle> p(get_product<cafmaker::types::Particle>(file, events.at(0)));
  std::cout << p[0];
  
  file.close();
    
  return 0;
}

std::vector<cafmaker::types::Event> get_event(H5::H5File &file, size_t index)
{
  H5::DataSet dataset(file.openDataSet("events"));
  H5::DataSpace dsp(dataset.getSpace());

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

  std::vector<cafmaker::types::Event> evt(1);
  H5::CompType ctype(cafmaker::types::BuildCompType<cafmaker::types::Event>());
  dataset.read(evt.data(), ctype, memspace, dsp);

  return evt;
}

template <class T>
std::vector<T> get_product(H5::H5File &file, cafmaker::types::Event &evt)
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
  H5::CompType ctype(cafmaker::types::BuildCompType<T>());
  ds_ref.read(data_product.data(), ctype, memspace, ref_region);
  return data_product;
}

std::ostream& operator<<(std::ostream& os, const cafmaker::types::Particle& p)
{
  os << "Particle [image_id=" << p.image_id 
     << ", interaction_id=" << p.interaction_id
     << ", id=" << p.id << "]\n"
     << "\tpid: " << int(p.pid) << "\n"
     << "\tprimary: " << p.is_primary << "\n"
     << "\tcontained: " << p.is_contained << "\n"
     << std::endl;
  
  return os;
}
