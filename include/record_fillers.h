/**
 * @file record_fillers.h
 * @brief Declaration of various functions for filling the SPINE reconstruction
 * output objects for use within the CAF files.
 * @details This file contains the declaration of the functions that are
 * responsible for copying the SPINE reconstruction output data products, as
 * read by spine-reader, into the CAF objects. The functions are designed to be
 * called from either the standalone CAF generator or the merged CAF generator.
 * @author mueller@fnal.gov
 */
#ifndef RECORD_FILLERS_H
#define RECORD_FILLERS_H
#include <vector>
#include <ctype.h>

#include <spine/event.hpp>

#include "sbnanaobj/StandardRecord/StandardRecord.h"

#define COPY(x,y) std::copy(y.begin(), y.end(), x)

/**
 * @brief Constructs an instance of the caf::SRParticleTruthDLP class from the
 * data in the spine::TruthParticle data product.
 * @param p the input spine::TruthParticle data product containing the
 * information to be copied.
 * @param offset to add to the image_id of the particle (default = 0).
 * @return an instance of the caf::SRParticleTruthDLP class that contains the
 * data copied from the input spine::TruthParticle object.
 */
caf::SRParticleTruthDLP fill_truth_particle(const spine::TruthParticle &p, uint64_t offset=0);

/**
 * @brief Constructs an instance of the caf::SRParticleDLP class from the data
 * in the spine::RecoParticle data product.
 * @param p the input spine::RecoParticle data product containing the
 * information to be copied.
 * @param offset to add to the image_id of the particle (default = 0).
 * @return an instance of the caf::SRParticleDLP class that contains the data
 * copied from the input spine::RecoParticle object.
 */
caf::SRParticleDLP fill_particle(const spine::RecoParticle &p, uint64_t offset=0);

/**
 * @brief Constructs an instance of the caf::SRInteractionTruthDLP class from
 * the data in the spine::TruthInteraction data product and the input
 * vector of caf::SRParticleTruthDLP objects.
 * @param in the input spine::TruthInteraction data product containing the
 * information to be copied.
 * @param particles the vector of caf::SRParticleTruthDLP objects to copy to
 * the SRTruthInteractionDLP object.
 * @param offset to add to the image_id of the interaction (default = 0).
 * @return an instance of the caf::SRInteractionTruthDLP class that contains
 * the data copied from the input spine::TruthInteraction object and the
 * vector of caf::SRParticleTruthDLP.
 */
caf::SRInteractionTruthDLP fill_truth_interaction(const spine::TruthInteraction &in, std::vector<caf::SRParticleTruthDLP> &particles, uint64_t offset=0);

/**
 * @brief Constructs an instance of the caf::SRInteractionDLP class from the
 * data in the spine::RecoInteraction data product and the input vector of
 * caf::SRParticleDLP objects.
 * @param in the input spine::RecoInteraction data product containing the
 * information to be copied.
 * @param particles the vector of caf::SRParticleDLP objects to copy to the
 * SRInteractionDLP object.
 * @param offset to add to the image_id of the interaction (default = 0).
 * @return an instance of the caf::SRInteractionDLP class that contains the
 * data copied from the input spine::RecoInteraction object and the vector
 * of caf::SRParticleDLP.
 */
caf::SRInteractionDLP fill_interaction(const spine::RecoInteraction &in, std::vector<caf::SRParticleDLP> &particles, uint64_t offset=0);

/**
 * @brief Populates the StandardRecord object with the ML reconstruction
 * outputs contained in the input spine::Event. If the StandardRecord already
 * contains ML products, they will be replaced. This guarantees that the ML
 * products will not be mix across different versions or duplicated, and
 * additionally adds functionality to replace the ML reconstruction outputs
 * when they have been regenerated after updates.
 * @param rec a pointer to the StandardRecord object to modify.
 * @param evt the spine::Event that holds the ML data products of one event.
 * @param offset to add to each image_id in the ML data products (default = 0).
 */
void package_event(caf::StandardRecord * rec, const spine::Event & evt, uint64_t offset=0);

#endif
