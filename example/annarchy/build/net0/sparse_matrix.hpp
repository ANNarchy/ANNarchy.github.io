#pragma once
#ifdef __AVX__
#include <immintrin.h>  // AVX instructions
#endif

// ANNarchy specific global definitions
#include "helper_functions.hpp"
#include "ANNarchy.h"

// Coordinate 
#include "COOMatrix.hpp"

// List of List
#include "LILMatrix.hpp"
#include "LILInvMatrix.hpp"

// compressed sparse row
#include "CSRMatrix.hpp"
#include "CSRCMatrix.hpp"
#include "CSRCMatrixT.hpp"

// ELLPACK/ITPACK
#include "ELLMatrix.hpp"

// ELLPACK with row-length array
#include "ELLRMatrix.hpp"

// Hybrid (ELLPACK+Coordinate)
#include "HYBMatrix.hpp"

// Matrix is split into parts across rows
#include "PartitionedMatrix.hpp"

// allow the user defined definition aka
// "old-style" connectivity definition
#include "Specific.hpp"
