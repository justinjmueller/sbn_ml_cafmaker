#include <iostream>
#include <vector>
#include <ctype.h>
#include "H5Cpp.h"
#include "sbn_h5_classes.h"
#include "record_fillers.h"
#include "hdf5_utilities.h"
#include "sbnanaobj/StandardRecord/StandardRecord.h"
#include "sbnanaobj/StandardRecord/SRInteractionDLP.h"
#include "sbnanaobj/StandardRecord/SRInteractionTruthDLP.h"
#include "sbnanaobj/StandardRecord/SRParticleDLP.h"
#include "sbnanaobj/StandardRecord/SRParticleTruthDLP.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

int main(int argc, char const *argv[])
{
  if(argc < 2)
  {
    std::cerr << "Please provide at least one input file!" << std::endl;
    return 0;
  }

  TFile caf("bnb_nucosmics.caf.root", "recreate");
  TTree rec_tree("recTree", "Event tree for ML reconstruction");
  caf::StandardRecord *rec;
  rec_tree.Branch("rec", &rec);

  TH1F * pot = new TH1F("TotalPOT", "TotalPOT", 1, 0, 1);
  TH1F * nevt = new TH1F("TotalEvents", "TotalEvents", 1, 0, 1);
  for(size_t n(1); n < argc; ++n)
  {
    H5::H5File file(argv[n], H5F_ACC_RDONLY);
    std::cout << "Opened file: " << argv[n] << std::endl;
  
    std::vector<dlp::types::Event> events(get_events(file, -1));
    for(dlp::types::Event &evt : events)
    {
      std::vector<dlp::types::Particle> reco_particles(get_product<dlp::types::Particle>(file, evt));
      std::vector<dlp::types::TruthParticle> true_particles(get_product<dlp::types::TruthParticle>(file, evt));

      std::vector<caf::SRParticleDLP> caf_reco_particles;
      for(dlp::types::Particle &p : reco_particles)
	caf_reco_particles.push_back(fill_particle(p));

      std::vector<caf::SRParticleTruthDLP> caf_true_particles;
      for(dlp::types::TruthParticle &p : true_particles)
        caf_true_particles.push_back(fill_truth_particle(p));
      
      std::vector<dlp::types::Interaction> reco_interactions(get_product<dlp::types::Interaction>(file, evt));
      std::vector<dlp::types::TruthInteraction> true_interactions(get_product<dlp::types::TruthInteraction>(file, evt));

      std::vector<caf::SRInteractionDLP> caf_reco_interactions;
      for(dlp::types::Interaction &i : reco_interactions)
	caf_reco_interactions.push_back(fill_interaction(i, caf_reco_particles));

      std::vector<caf::SRInteractionTruthDLP> caf_true_interactions;
      for(dlp::types::TruthInteraction &i : true_interactions)
        caf_true_interactions.push_back(fill_truth_interaction(i, caf_true_particles));

      caf::StandardRecord sr;
      sr.dlp = caf_reco_interactions;
      sr.ndlp = caf_reco_interactions.size();
      sr.dlp_true = caf_true_interactions;
      sr.ndlp_true = caf_true_interactions.size();
      sr.hdr.pot = 1;
      sr.hdr.first_in_subrun = true;
      pot->Fill(1);
      nevt->Fill(1);
  
      rec = &sr;
      rec_tree.Fill();
    }
    file.close();
  }
  rec_tree.Write();
  pot->Write();
  nevt->Write();
  caf.Close();

  return 0;
}

