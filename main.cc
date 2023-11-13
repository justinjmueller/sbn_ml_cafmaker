#include <iostream>
#include <vector>
#include <ctype.h>
#include "H5Cpp.h"
#include "sbn_h5_classes.h"
#include "sbnanaobj/StandardRecord/StandardRecord.h"
#include "sbnanaobj/StandardRecord/SRInteractionDLP.h"
#include "TFile.h"
#include "TTree.h"

std::vector<dlp::types::Event> get_events(H5::H5File &file, int64_t index);

template <class T>
std::vector<T> get_product(H5::H5File &file, dlp::types::Event &evt);

std::ostream& operator<<(std::ostream& os, const dlp::types::Particle& p);

size_t get_nevents(H5::DataSpace &dsp)
{
  hsize_t dims_max = dsp.getSimpleExtentNdims();
  auto dims = new hsize_t[dims_max];
  dsp.getSimpleExtentDims(dims);
  size_t nevents(dims[dims_max - 1]);
  delete[] dims;
  return nevents;
}

caf::SRInteractionDLP fill_interaction(dlp::types::TruthInteraction &in)
{
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
  //ret.match = ;
  //ret.match_overlap = ;
  ret.matched = in.matched;
  ret.nu_id = in.nu_id;
  ret.num_particles = in.num_particles;
  ret.num_primaries = in.num_primaries;
  ret.particle_counts = in.particle_counts;
  //ret.particle_ids = in.particle_ids;
  ret.primary_counts = in.primary_counts;
  ret.size = in.size;
  ret.topology = in.topology;
  ret.units = in.units;
  ret.vertex = in.vertex;
  ret.vertex_mode = in.vertex_mode;
  ret.volume_id = in.volume_id;

  return ret;
}

int main(int argc, char const *argv[])
{
  if(argc != 2)
  {
    std::cerr << "Please provide exactly one input file." << std::endl;
    return 0;
  }

  H5::H5File file(argv[1], H5F_ACC_RDONLY);
  std::cout << "Opened file: " << argv[1] << "\n" << std::endl;

  TFile caf("dlp.caf.root", "recreate");
  TTree rec_tree("dlp", "Event tree for ML reconstruction");
  caf::StandardRecord *rec;
  rec_tree.Branch("rec", &rec);
  
  std::vector<dlp::types::Event> events(get_events(file, -1));
  for(dlp::types::Event &evt : events)
  {
    caf::StandardRecord sr;
    std::vector<dlp::types::TruthInteraction> interactions(get_product<dlp::types::TruthInteraction>(file, evt));
    for(dlp::types::TruthInteraction &i : interactions)
      sr.dlp_true_interaction.push_back(fill_interaction(i));
    sr.ndlp_true = sr.dlp_true_interaction.size();
  
    rec = &sr;
    rec_tree.Fill();
  }
  rec_tree.Write();
  caf.Close();

  file.close();
    
  return 0;
}

std::vector<dlp::types::Event> get_events(H5::H5File &file, int64_t index)
{
  H5::DataSet dataset(file.openDataSet("events"));
  H5::DataSpace dsp(dataset.getSpace());

  std::vector<dlp::types::Event> evt;
  if(index < 0)
  {
    evt.resize(get_nevents(dsp));
    H5::CompType ctype(dlp::types::BuildCompType<dlp::types::Event>());
    dataset.read(evt.data(), ctype, H5::DataSpace::ALL, H5::DataSpace::ALL);
  }
  else
  {
    evt.resize(1);
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
  }

  return evt;
}

template <class T>
std::vector<T> get_product(H5::H5File &file, dlp::types::Event &evt)
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

std::ostream& operator<<(std::ostream& os, const dlp::types::Particle& p)
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
