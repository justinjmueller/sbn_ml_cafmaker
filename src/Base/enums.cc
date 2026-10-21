/**
 * @file enums.cc
 * @brief Definition of the enums used in the sbn_ml_cafmaker package.
 * @author mueller@fnal.gov
*/

#include "H5Cpp.h"
#include "enums.h"

/**
 * @brief A struct to allow for the insertion of enum values into an HDF5 enum
 * type. This is sort of a "hacky" way to allow for the insertion of enum
 * values into an HDF5 enum type in a single line. The H5::EnumType::insert()
 * method requires a pointer to the value to be inserted, so this struct
 * essentially acts as a wrapper that creates a short-lived pointer to the
 * value.
*/
struct enum_ptr
{
    int64_t value;
    operator int64_t *() { return &value; }
};

struct bool_enum_ptr
{
    int8_t value;
    operator int8_t *() { return &value; }
};

namespace dlp::types
{
    /**
     * @brief Configure the HDF5 enum type matching the FALSE/TRUE enum that
     * HDF5/h5py uses to represent bool fields on disk. HDF5's bool is an
     * H5T_ENUM over a single byte with members "FALSE"=0 and "TRUE"=1, not a
     * plain integer predtype, so it cannot be read directly into
     * H5::PredType::NATIVE_HBOOL.
     * @return The H5::EnumType for the on-disk bool representation.
    */
    H5::EnumType create_bool_enumtype()
    {
        H5::EnumType bool_enumtype(H5::PredType::STD_I8LE);
        bool_enumtype.insert("FALSE", bool_enum_ptr{0});
        bool_enumtype.insert("TRUE", bool_enum_ptr{1});
        return bool_enumtype;
    }

    /**
     * @brief Configure the HDF5 enum type for NuCurrentType.
     * @return The H5::EnumType for the NuCurrentType enum.
    */
    H5::EnumType create_current_type_enumtype()
    {
        H5::EnumType current_type_enumtype(H5::PredType::STD_I64LE);
        current_type_enumtype.insert("CC", enum_ptr{0});
        current_type_enumtype.insert("NC", enum_ptr{1});
        current_type_enumtype.insert("UNKNOWN", enum_ptr{-1});
        return current_type_enumtype;
    }

    /**
     * @brief Configure the HDF5 enum type for NuInteractionMode.
     * @return The H5::EnumType for the NuInteractionMode enum.
    */
    H5::EnumType create_interaction_mode_enumtype()
    {
        H5::EnumType interaction_mode_enumtype(H5::PredType::STD_I64LE);
        interaction_mode_enumtype.insert("AMNuGamma", enum_ptr{9});
        interaction_mode_enumtype.insert("CCCOH", enum_ptr{1097});
        interaction_mode_enumtype.insert("CCDIS", enum_ptr{1091});
        interaction_mode_enumtype.insert("CCQE", enum_ptr{1001});
        interaction_mode_enumtype.insert("CCQEHyperon", enum_ptr{1095});
        interaction_mode_enumtype.insert("Coh", enum_ptr{3});
        interaction_mode_enumtype.insert("CohElastic", enum_ptr{4});
        interaction_mode_enumtype.insert("DIS", enum_ptr{2});
        interaction_mode_enumtype.insert("Diffractive", enum_ptr{11});
        interaction_mode_enumtype.insert("EM", enum_ptr{12});
        interaction_mode_enumtype.insert("ElectronScattering", enum_ptr{5});
        interaction_mode_enumtype.insert("GlashowResonance", enum_ptr{8});
        interaction_mode_enumtype.insert("IMDAnnihilation", enum_ptr{6});
        interaction_mode_enumtype.insert("InverseBetaDecay", enum_ptr{7});
        interaction_mode_enumtype.insert("InverseMuDecay", enum_ptr{1099});
        interaction_mode_enumtype.insert("MEC", enum_ptr{10});
        interaction_mode_enumtype.insert("MEC2p2h", enum_ptr{1100});
        interaction_mode_enumtype.insert("NCCOH", enum_ptr{1096});
        interaction_mode_enumtype.insert("NCDIS", enum_ptr{1092});
        interaction_mode_enumtype.insert("NCQE", enum_ptr{1002});
        interaction_mode_enumtype.insert("NuElectronElastic", enum_ptr{1098});
        interaction_mode_enumtype.insert("NuanceOffset", enum_ptr{1000});
        interaction_mode_enumtype.insert("QE", enum_ptr{0});
	interaction_mode_enumtype.insert("Res", enum_ptr{1});
        interaction_mode_enumtype.insert("ResCCNuBarDelta0PiMinus", enum_ptr{1028});
        interaction_mode_enumtype.insert("ResCCNuBarDeltaMinusPiPlus", enum_ptr{1032});
        interaction_mode_enumtype.insert("ResCCNuBarKaon0Lambda0", enum_ptr{1076});
        interaction_mode_enumtype.insert("ResCCNuBarNeutronEta", enum_ptr{1070});
        interaction_mode_enumtype.insert("ResCCNuBarNeutronPi0Pi0", enum_ptr{1086});
        interaction_mode_enumtype.insert("ResCCNuBarNeutronPiMinus", enum_ptr{1010});
        interaction_mode_enumtype.insert("ResCCNuBarNeutronPiPlusPiMinus", enum_ptr{1085});
        interaction_mode_enumtype.insert("ResCCNuBarNeutronRho0", enum_ptr{1048});
        interaction_mode_enumtype.insert("ResCCNuBarNeutronRhoMinus", enum_ptr{1046});
        interaction_mode_enumtype.insert("ResCCNuBarProtonPi0", enum_ptr{1011});
        interaction_mode_enumtype.insert("ResCCNuBarProtonPi0Pi0", enum_ptr{1090});
        interaction_mode_enumtype.insert("ResCCNuBarProtonPiMinus", enum_ptr{1012});
        interaction_mode_enumtype.insert("ResCCNuBarSigma0Kaon0", enum_ptr{1062});
        interaction_mode_enumtype.insert("ResCCNuBarSigmaMinusKaon0", enum_ptr{1060});
        interaction_mode_enumtype.insert("ResCCNuDelta2PlusPiMinus", enum_ptr{1021});
        interaction_mode_enumtype.insert("ResCCNuDeltaPlusPiPlus", enum_ptr{1017});
        interaction_mode_enumtype.insert("ResCCNuKaonPlusLambda0", enum_ptr{1073});
        interaction_mode_enumtype.insert("ResCCNuNeutronPi0", enum_ptr{1004});
        interaction_mode_enumtype.insert("ResCCNuNeutronPiPlus", enum_ptr{1005});
        interaction_mode_enumtype.insert("ResCCNuNeutronRhoPlus", enum_ptr{1041});
        interaction_mode_enumtype.insert("ResCCNuProtonEta", enum_ptr{1067});
        interaction_mode_enumtype.insert("ResCCNuProtonPi0Pi0", enum_ptr{1080});
        interaction_mode_enumtype.insert("ResCCNuProtonPiPlus", enum_ptr{1003});
        interaction_mode_enumtype.insert("ResCCNuProtonPiPlusPiMinus", enum_ptr{1079});
        interaction_mode_enumtype.insert("ResCCNuProtonRhoPlus", enum_ptr{1039});
        interaction_mode_enumtype.insert("ResCCNuSigmaPlusKaon0", enum_ptr{1055});
        interaction_mode_enumtype.insert("ResCCNuSigmaPlusKaonPlus", enum_ptr{1053});
        interaction_mode_enumtype.insert("ResNCNuBarNeutronPi0", enum_ptr{1015});
        interaction_mode_enumtype.insert("ResNCNuBarNeutronPiMinus", enum_ptr{1016});
        interaction_mode_enumtype.insert("ResNCNuBarProtonPi0", enum_ptr{1013});
        interaction_mode_enumtype.insert("ResNCNuBarProtonPiPlus", enum_ptr{1014});
        interaction_mode_enumtype.insert("ResNCNuNeutronPi0", enum_ptr{1008});
        interaction_mode_enumtype.insert("ResNCNuNeutronPiMinus", enum_ptr{1009});
        interaction_mode_enumtype.insert("ResNCNuProtonPi0", enum_ptr{1006});
        interaction_mode_enumtype.insert("ResNCNuProtonPiPlus", enum_ptr{1007});
        interaction_mode_enumtype.insert("UnUsed1", enum_ptr{1093});
        interaction_mode_enumtype.insert("UnUsed2", enum_ptr{1094});
        interaction_mode_enumtype.insert("UnknownInteraction", enum_ptr{-1});
        interaction_mode_enumtype.insert("WeakMix", enum_ptr{13});
        return interaction_mode_enumtype;
    }

    /**
     * @brief Configure the HDF5 enum type for NuInteractionType.
     * @return The H5::EnumType for the NuInteractionType enum.
    */
    H5::EnumType create_interaction_type_enumtype()
    {
        H5::EnumType interaction_type_enumtype(H5::PredType::STD_I64LE);
        interaction_type_enumtype.insert("AMNuGamma", enum_ptr{9});
        interaction_type_enumtype.insert("CCCOH", enum_ptr{1097});
        interaction_type_enumtype.insert("CCDIS", enum_ptr{1091});
        interaction_type_enumtype.insert("CCQE", enum_ptr{1001});
        interaction_type_enumtype.insert("CCQEHyperon", enum_ptr{1095});
        interaction_type_enumtype.insert("Coh", enum_ptr{3});
        interaction_type_enumtype.insert("CohElastic", enum_ptr{4});
        interaction_type_enumtype.insert("DIS", enum_ptr{2});
        interaction_type_enumtype.insert("Diffractive", enum_ptr{11});
        interaction_type_enumtype.insert("EM", enum_ptr{12});
        interaction_type_enumtype.insert("ElectronScattering", enum_ptr{5});
        interaction_type_enumtype.insert("GlashowResonance", enum_ptr{8});
        interaction_type_enumtype.insert("IMDAnnihilation", enum_ptr{6});
        interaction_type_enumtype.insert("InverseBetaDecay", enum_ptr{7});
        interaction_type_enumtype.insert("InverseMuDecay", enum_ptr{1099});
        interaction_type_enumtype.insert("MEC", enum_ptr{10});
        interaction_type_enumtype.insert("MEC2p2h", enum_ptr{1100});
        interaction_type_enumtype.insert("NCCOH", enum_ptr{1096});
        interaction_type_enumtype.insert("NCDIS", enum_ptr{1092});
        interaction_type_enumtype.insert("NCQE", enum_ptr{1002});
        interaction_type_enumtype.insert("NuElectronElastic", enum_ptr{1098});
        interaction_type_enumtype.insert("NuanceOffset", enum_ptr{1000});
        interaction_type_enumtype.insert("QE", enum_ptr{0});
	interaction_type_enumtype.insert("Res", enum_ptr{1});
        interaction_type_enumtype.insert("ResCCNuBarDelta0PiMinus", enum_ptr{1028});
        interaction_type_enumtype.insert("ResCCNuBarDeltaMinusPiPlus", enum_ptr{1032});
        interaction_type_enumtype.insert("ResCCNuBarKaon0Lambda0", enum_ptr{1076});
        interaction_type_enumtype.insert("ResCCNuBarNeutronEta", enum_ptr{1070});
        interaction_type_enumtype.insert("ResCCNuBarNeutronPi0Pi0", enum_ptr{1086});
        interaction_type_enumtype.insert("ResCCNuBarNeutronPiMinus", enum_ptr{1010});
        interaction_type_enumtype.insert("ResCCNuBarNeutronPiPlusPiMinus", enum_ptr{1085});
        interaction_type_enumtype.insert("ResCCNuBarNeutronRho0", enum_ptr{1048});
        interaction_type_enumtype.insert("ResCCNuBarNeutronRhoMinus", enum_ptr{1046});
        interaction_type_enumtype.insert("ResCCNuBarProtonPi0", enum_ptr{1011});
        interaction_type_enumtype.insert("ResCCNuBarProtonPi0Pi0", enum_ptr{1090});
        interaction_type_enumtype.insert("ResCCNuBarProtonPiMinus", enum_ptr{1012});
        interaction_type_enumtype.insert("ResCCNuBarSigma0Kaon0", enum_ptr{1062});
        interaction_type_enumtype.insert("ResCCNuBarSigmaMinusKaon0", enum_ptr{1060});
        interaction_type_enumtype.insert("ResCCNuDelta2PlusPiMinus", enum_ptr{1021});
        interaction_type_enumtype.insert("ResCCNuDeltaPlusPiPlus", enum_ptr{1017});
        interaction_type_enumtype.insert("ResCCNuKaonPlusLambda0", enum_ptr{1073});
        interaction_type_enumtype.insert("ResCCNuNeutronPi0", enum_ptr{1004});
        interaction_type_enumtype.insert("ResCCNuNeutronPiPlus", enum_ptr{1005});
        interaction_type_enumtype.insert("ResCCNuNeutronRhoPlus", enum_ptr{1041});
        interaction_type_enumtype.insert("ResCCNuProtonEta", enum_ptr{1067});
        interaction_type_enumtype.insert("ResCCNuProtonPi0Pi0", enum_ptr{1080});
        interaction_type_enumtype.insert("ResCCNuProtonPiPlus", enum_ptr{1003});
        interaction_type_enumtype.insert("ResCCNuProtonPiPlusPiMinus", enum_ptr{1079});
        interaction_type_enumtype.insert("ResCCNuProtonRhoPlus", enum_ptr{1039});
        interaction_type_enumtype.insert("ResCCNuSigmaPlusKaon0", enum_ptr{1055});
        interaction_type_enumtype.insert("ResCCNuSigmaPlusKaonPlus", enum_ptr{1053});
        interaction_type_enumtype.insert("ResNCNuBarNeutronPi0", enum_ptr{1015});
        interaction_type_enumtype.insert("ResNCNuBarNeutronPiMinus", enum_ptr{1016});
        interaction_type_enumtype.insert("ResNCNuBarProtonPi0", enum_ptr{1013});
        interaction_type_enumtype.insert("ResNCNuBarProtonPiPlus", enum_ptr{1014});
        interaction_type_enumtype.insert("ResNCNuNeutronPi0", enum_ptr{1008});
        interaction_type_enumtype.insert("ResNCNuNeutronPiMinus", enum_ptr{1009});
        interaction_type_enumtype.insert("ResNCNuProtonPi0", enum_ptr{1006});
        interaction_type_enumtype.insert("ResNCNuProtonPiPlus", enum_ptr{1007});
        interaction_type_enumtype.insert("UnUsed1", enum_ptr{1093});
        interaction_type_enumtype.insert("UnUsed2", enum_ptr{1094});
        interaction_type_enumtype.insert("UnknownInteraction", enum_ptr{-1});
        interaction_type_enumtype.insert("WeakMix", enum_ptr{13});
        return interaction_type_enumtype;
    }    

    /**
     * @brief Configure the HDF5 enum type for Pid.
     * @return The H5::EnumType for the Pid enum.
    */
    H5::EnumType create_pid_enumtype()
    {
        H5::EnumType pid_enumtype(H5::PredType::STD_I64LE);
        pid_enumtype.insert("ELECTRON", enum_ptr{1});
        pid_enumtype.insert("KAON", enum_ptr{5});
        pid_enumtype.insert("MUON", enum_ptr{2});
        pid_enumtype.insert("PHOTON", enum_ptr{0});
        pid_enumtype.insert("PION", enum_ptr{3});
        pid_enumtype.insert("PROTON", enum_ptr{4});
        pid_enumtype.insert("UNKNOWN", enum_ptr{-1});
        return pid_enumtype;
    }

    /**
     * @brief Configure the HDF5 enum type for SemanticType.
     * @return The H5::EnumType for the SemanticType enum.
    */
    H5::EnumType create_shape_enumtype()
    {
        H5::EnumType semantic_type_enumtype(H5::PredType::STD_I64LE);
        semantic_type_enumtype.insert("DELTA", enum_ptr{3});
        semantic_type_enumtype.insert("GHOST", enum_ptr{5});
        semantic_type_enumtype.insert("LARCV_UNKNOWN", enum_ptr{6});
        semantic_type_enumtype.insert("LOWE", enum_ptr{4});
        semantic_type_enumtype.insert("MICHEL", enum_ptr{2});
        semantic_type_enumtype.insert("SHOWER", enum_ptr{0});
        semantic_type_enumtype.insert("TRACK", enum_ptr{1});
        semantic_type_enumtype.insert("UNKNOWN", enum_ptr{-1});
        return semantic_type_enumtype;
    }

    /**
     * @brief Configure the HDF5 enum type for InteractionScheme.
     * @return The H5::EnumType for the InteractionScheme enum.
    */
    H5::EnumType create_interaction_scheme_enumtype()
    {
        H5::EnumType interaction_scheme_enumtype(H5::PredType::STD_I64LE);
        interaction_scheme_enumtype.insert("GENIE", enum_ptr{1});
        interaction_scheme_enumtype.insert("LARSOFT", enum_ptr{0});
        interaction_scheme_enumtype.insert("UNKNOWN", enum_ptr{-1});
        return interaction_scheme_enumtype;
    }
}
