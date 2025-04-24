/**
 * @file record_fillers.h
 * @brief Declaration of various functions for filling the SPINE reconstruction
 * output objects for use within the CAF files.
 * @details This file contains the declaration of the functions that are
 * responsible for copying the SPINE reconstruction output data products from
 * the HDF5 files into the CAF objects. The functions are designed to be called
 * from either the standalone CAF generator or the merged CAF generator.
 * @author mueller@fnal.gov
 */
#ifndef RECORD_FILLERS_H
#define RECORD_FILLERS_H
#include <vector>
#include <ctype.h>

#include "event.h"
#include "reco_interaction.h"
#include "reco_particle.h"
#include "true_interaction.h"
#include "true_particle.h"

#include "sbnanaobj/StandardRecord/StandardRecord.h"

#define COPY(x,y) std::copy(y.begin(), y.end(), x)

// Forward declare.
template <class T>
std::vector<T> get_product(H5::H5File & file, dlp::types::Event & evt);

/**
 * @brief Constructs an instance of the caf::SRParticleTruthDLP class from the
 * data in the dlp::types::TruthParticle data product.
 * @param p the input dlp::types::TruthParticle data product containing the
 * information to be copied.
 * @param offset to add to the image_id of the particle (default = 0).
 * @return an instance of the caf::SRParticleTruthDLP class that contains the
 * data copied from the input dlp::types::TruthParticle object.
 */
caf::SRParticleTruthDLP fill_truth_particle(dlp::types::TruthParticle &p, uint64_t offset=0);

/**
 * @brief Constructs an instance of the caf::SRParticleDLP class from the data
 * in the dlp::types::TruthParticle data product.
 * @param p the input dlp::types::Particle data product containing the
 * information to be copied.
 * @param offset to add to the image_id of the particle (default = 0).
 * @return an instance of the caf::SRParticleDLP class that contains the data
 * copied from the input dlp::types::Particle object.
 */
caf::SRParticleDLP fill_particle(dlp::types::RecoParticle &p, uint64_t offset=0);

/**
 * @brief Constructs an instance of the caf::SRInteractionTruthDLP class from
 * the data in the dlp::types::TruthInteraction data product and the input
 * vector of caf::SRParticleTruthDLP objects.
 * @param in the input dlp::types::TruthInteraction data product containing the
 * information to be copied.
 * @param particles the vector of caf::SRParticleTruthDLP objects to copy to
 * the SRTruthInteractionDLP object.
 * @param offset to add to the image_id of the interaction (default = 0).
 * @return an instance of the caf::SRInteractionTruthDLP class that contains
 * the data copied from the input dlp::types::TruthInteraction object and the
 * vector of caf::SRParticleTruthDLP.
 */
caf::SRInteractionTruthDLP fill_truth_interaction(dlp::types::TruthInteraction &in, std::vector<caf::SRParticleTruthDLP> &particles, uint64_t offset=0);

/**
 * @brief Constructs an instance of the caf::SRInteractionDLP class from the
 * data in the dlp::types::Interaction data product and the input vector of
 * caf::SRParticleDLP objects.
 * @param in the input dlp::types::Interaction data product containing the
 * information to be copied.
 * @param particles the vector of caf::SRParticleDLP objects to copy to the
 * SRInteractionDLP object.
 * @param offset to add to the image_id of the interaction (default = 0).
 * @return an instance of the caf::SRInteractionDLP class that contains the
 * data copied from the input dlp::types::Interaction object and the vector
 * of caf::SRParticleDLP.
 */
caf::SRInteractionDLP fill_interaction(dlp::types::RecoInteraction &in, std::vector<caf::SRParticleDLP> &particles, uint64_t offset=0);

/**
 * @brief Populates the StandardRecord object with the ML reconstruction
 * outputs contained in the input dlp::types::Event object of the H5 file. If
 * the StandardRecord already contains ML products, they will be replaced. This
 * guarantees that the ML products will not be mix across different versions or
 * duplicated, and additionally adds functionality to replace the ML
 * reconstruction outputs when they have been regenerated after updates.
 * @param rec a pointer to the StandardRecord object to modify.
 * @param file the H5 file containing the event.
 * @param evt the dlp::types::Event that contains references to the ML data.
 * products within the H5 file.
 * @param offset to add to each image_id in the ML data products (default = 0).
 */
void package_event(caf::StandardRecord * rec, H5::H5File & file, dlp::types::Event & evt, uint64_t offset=0);

#endif
