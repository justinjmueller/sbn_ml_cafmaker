/**
 * @file composites.h
 * @brief Header file defining the templated composite types used in
 * sbn_ml_cafmaker.
 * @author mueller@fnal.gov
*/
#ifndef COMPOSITES_H
#define COMPOSITES_H

#include "H5Cpp.h"

namespace dlp::types
{
    // Generic template for building a compound type that will be overloaded
    // for each type that we create below.
    template <typename T>
    H5::CompType BuildCompType();
}

#endif