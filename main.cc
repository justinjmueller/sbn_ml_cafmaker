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
#include "sbnanaobj/StandardRecord/SRIMatchDLP.h"
#include "sbnanaobj/StandardRecord/SRPMatchDLP.h"
#include "TFile.h"
#include "TTree.h"

int main(int argc, char const *argv[])
{
  if(argc != 2)
  {
    std::cerr << "Please provide exactly one input file." << std::endl;
    return 0;
  }

  H5::H5File file(argv[1], H5F_ACC_RDONLY);
  std::cout << "Opened file: " << argv[1] << "\n" << std::endl;

  TFile caf("dlp_revised.caf.root", "recreate");
  TTree rec_tree("dlp", "Event tree for ML reconstruction");
  caf::StandardRecord *rec;
  rec_tree.Branch("rec", &rec);
  
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

    std::vector<caf::SRPMatchDLP> caf_pmatch_reco;
    for(caf::SRParticleDLP &p : caf_reco_particles)
    {
      caf::SRPMatchDLP pmatch;
      pmatch.x = p;
      if(p.match.size() > 0)
      {
	pmatch.y = caf_true_particles.at(p.match[0]);
	pmatch.iou = p.match_overlap[0];
      }
      caf_pmatch_reco.push_back(pmatch);
    }

    std::vector<caf::SRPMatchTruthDLP> caf_pmatch_true;
    for(caf::SRParticleTruthDLP &p : caf_true_particles)
    {
      caf::SRPMatchTruthDLP pmatch;
      pmatch.x = p;
      if(p.match.size() > 0)
      {
	pmatch.y = caf_reco_particles.at(p.match[0]);
	pmatch.iou = p.match_overlap[0];
      }
      caf_pmatch_true.push_back(pmatch);
    }

    std::vector<dlp::types::Interaction> reco_interactions(get_product<dlp::types::Interaction>(file, evt));
    std::vector<dlp::types::TruthInteraction> true_interactions(get_product<dlp::types::TruthInteraction>(file, evt));

    std::vector<caf::SRInteractionDLP> caf_reco_interactions;
    for(dlp::types::Interaction &i : reco_interactions)
      caf_reco_interactions.push_back(fill_interaction(i, caf_pmatch_reco));

    std::vector<caf::SRInteractionTruthDLP> caf_true_interactions;
    for(dlp::types::TruthInteraction &i : true_interactions)
      caf_true_interactions.push_back(fill_truth_interaction(i, caf_pmatch_true));

    caf::StandardRecord sr;

    for(caf::SRInteractionDLP &i : caf_reco_interactions)
    {
      caf::SRIMatchDLP imatch;
      imatch.x = i;
      if(i.match.size() > 0)
      {
	imatch.y = caf_true_interactions.at(i.match[0]);
	imatch.iou = i.match_overlap[0];
      }
      ++sr.ndlp;
      sr.dlp.push_back(imatch);
    }

    for(caf::SRInteractionTruthDLP &i : caf_true_interactions)
    {
      caf::SRIMatchTruthDLP imatch;
      imatch.x = i;
      if(i.match.size() > 0)
      {
	imatch.y = caf_reco_interactions.at(i.match[0]);
	imatch.iou = i.match_overlap[0];
      }
      ++sr.ndlp_true;
      sr.dlp_true.push_back(imatch);
    }
  
    rec = &sr;
    rec_tree.Fill();
  }
  rec_tree.Write();
  caf.Close();

  file.close();
    
  return 0;
}

