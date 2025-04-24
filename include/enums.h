/**
 * @file enums.h
 * @brief Definition of the enums used in the sbn_ml_cafmaker package.
 * @author mueller@fnal.gov
*/
#ifndef ENUMS_H
#define ENUMS_H

#include "H5Cpp.h"

namespace dlp::types
{
    /**
     * @brief Enumeration for the current type of the neutrino.
    */
    enum class CurrentType : int64_t
    {
        kCC = 0,
        kNC = 1,
        kUnknownCurrent = -1,
    };

    /**
     * @brief Enumeration for the interaction mode of the neutrino.
    */
    enum class InteractionMode : int64_t
    {
        kAMNuGamma = 9,
        kCCCOH = 1097,
        kCCDIS = 1091,
        kCCQE = 1001,
        kCCQEHyperon = 1095,
        kCoh = 3,
        kCohElastic = 4,
        kDIS = 2,
        kDiffractive = 11,
        kEM = 12,
        kElectronScattering = 5,
        kGlashowResonance = 8,
        kIMDAnnihilation = 6,
        kInverseBetaDecay = 7,
        kInverseMuDecay = 1099,
        kMEC = 10,
        kMEC2p2h = 1100,
        kNCCOH = 1096,
        kNCDIS = 1092,
        kNCQE = 1002,
        kNuElectronElastic = 1098,
        kNuanceOffset = 1000,
        kQE = 1,
        kResCCNuBarDelta0PiMinus = 1028,
        kResCCNuBarDeltaMinusPiPlus = 1032,
        kResCCNuBarKaon0Lambda0 = 1076,
        kResCCNuBarNeutronEta = 1070,
        kResCCNuBarNeutronPi0Pi0 = 1086,
        kResCCNuBarNeutronPiMinus = 1010,
        kResCCNuBarNeutronPiPlusPiMinus = 1085,
        kResCCNuBarNeutronRho0 = 1048,
        kResCCNuBarNeutronRhoMinus = 1046,
        kResCCNuBarProtonPi0 = 1011,
        kResCCNuBarProtonPi0Pi0 = 1090,
        kResCCNuBarProtonPiMinus = 1012,
        kResCCNuBarSigma0Kaon0 = 1062,
        kResCCNuBarSigmaMinusKaon0 = 1060,
        kResCCNuDelta2PlusPiMinus = 1021,
        kResCCNuDeltaPlusPiPlus = 1017,
        kResCCNuKaonPlusLambda0 = 1073,
        kResCCNuNeutronPi0 = 1004,
        kResCCNuNeutronPiPlus = 1005,
        kResCCNuNeutronRhoPlus = 1041,
        kResCCNuProtonEta = 1067,
        kResCCNuProtonPi0Pi0 = 1080,
        kResCCNuProtonPiPlus = 1003,
        kResCCNuProtonPiPlusPiMinus = 1079,
        kResCCNuProtonRhoPlus = 1039,
        kResCCNuSigmaPlusKaon0 = 1055,
        kResCCNuSigmaPlusKaonPlus = 1053,
        kResNCNuBarNeutronPi0 = 1015,
        kResNCNuBarNeutronPiMinus = 1016,
        kResNCNuBarProtonPi0 = 1013,
        kResNCNuBarProtonPiPlus = 1014,
        kResNCNuNeutronPi0 = 1008,
        kResNCNuNeutronPiMinus = 1009,
        kResNCNuProtonPi0 = 1006,
        kResNCNuProtonPiPlus = 1007,
        kUnUsed1 = 1093,
        kUnUsed2 = 1094,
        kUnknownInteraction = -1,
        kWeakMix = 13,
    };

    /**
     * @brief Enumeration for the interaction type of the neutrino.
    */
    enum class InteractionType : int64_t
    {
        kAMNuGamma = 9,
        kCCCOH = 1097,
        kCCDIS = 1091,
        kCCQE = 1001,
        kCCQEHyperon = 1095,
        kCoh = 3,
        kCohElastic = 4,
        kDIS = 2,
        kDiffractive = 11,
        kEM = 12,
        kElectronScattering = 5,
        kGlashowResonance = 8,
        kIMDAnnihilation = 6,
        kInverseBetaDecay = 7,
        kInverseMuDecay = 1099,
        kMEC = 10,
        kMEC2p2h = 1100,
        kNCCOH = 1096,
        kNCDIS = 1092,
        kNCQE = 1002,
        kNuElectronElastic = 1098,
        kNuanceOffset = 1000,
        kQE = 1,
        kResCCNuBarDelta0PiMinus = 1028,
        kResCCNuBarDeltaMinusPiPlus = 1032,
        kResCCNuBarKaon0Lambda0 = 1076,
        kResCCNuBarNeutronEta = 1070,
        kResCCNuBarNeutronPi0Pi0 = 1086,
        kResCCNuBarNeutronPiMinus = 1010,
        kResCCNuBarNeutronPiPlusPiMinus = 1085,
        kResCCNuBarNeutronRho0 = 1048,
        kResCCNuBarNeutronRhoMinus = 1046,
        kResCCNuBarProtonPi0 = 1011,
        kResCCNuBarProtonPi0Pi0 = 1090,
        kResCCNuBarProtonPiMinus = 1012,
        kResCCNuBarSigma0Kaon0 = 1062,
        kResCCNuBarSigmaMinusKaon0 = 1060,
        kResCCNuDelta2PlusPiMinus = 1021,
        kResCCNuDeltaPlusPiPlus = 1017,
        kResCCNuKaonPlusLambda0 = 1073,
        kResCCNuNeutronPi0 = 1004,
        kResCCNuNeutronPiPlus = 1005,
        kResCCNuNeutronRhoPlus = 1041,
        kResCCNuProtonEta = 1067,
        kResCCNuProtonPi0Pi0 = 1080,
        kResCCNuProtonPiPlus = 1003,
        kResCCNuProtonPiPlusPiMinus = 1079,
        kResCCNuProtonRhoPlus = 1039,
        kResCCNuSigmaPlusKaon0 = 1055,
        kResCCNuSigmaPlusKaonPlus = 1053,
        kResNCNuBarNeutronPi0 = 1015,
        kResNCNuBarNeutronPiMinus = 1016,
        kResNCNuBarProtonPi0 = 1013,
        kResNCNuBarProtonPiPlus = 1014,
        kResNCNuNeutronPi0 = 1008,
        kResNCNuNeutronPiMinus = 1009,
        kResNCNuProtonPi0 = 1006,
        kResNCNuProtonPiPlus = 1007,
        kUnUsed1 = 1093,
        kUnUsed2 = 1094,
        kUnknownInteraction = -1,
        kWeakMix = 13,
    };

    /**
     * @brief Enumeration for the particle ID.
    */
    enum class Pid : int64_t
    {
        kElectron = 1,
        kKaon = 5,
        kMuon = 2,
        kPhoton = 0,
        kPion = 3,
        kProton = 4,
        kUnknown = -1,
    };

    /**
     * @brief Enumeration for the semantic type of the particle.
    */
    enum class Shape : int64_t
    {
        kDelta = 3,
        kGhost = 5,
        kLowEnergy = 4,
        kMichel = 2,
        kShower = 0,
        kTrack = 1,
        kUnknown = -1,
    };

    /**
     * @brief Configure the HDF5 enum type for NuCurrentType.
     * @return The H5::EnumType for the NuCurrentType enum.
    */
    H5::EnumType create_current_type_enumtype();

    /**
     * @brief Configure the HDF5 enum type for NuInteractionMode.
     * @return The H5::EnumType for the NuInteractionMode enum.
    */
    H5::EnumType create_interaction_mode_enumtype();

    /**
     * @brief Configure the HDF5 enum type for NuInteractionType.
     * @return The H5::EnumType for the NuInteractionType enum.
    */
    H5::EnumType create_interaction_type_enumtype();

    /**
     * @brief Configure the HDF5 enum type for Pid.
     * @return The H5::EnumType for the Pid enum.
    */
    H5::EnumType create_pid_enumtype();

    /**
     * @brief Configure the HDF5 enum type for SemanticType.
     * @return The H5::EnumType for the SemanticType enum.
    */
    H5::EnumType create_shape_enumtype();

} // namespace dlp::types
#endif // ENUMS_H