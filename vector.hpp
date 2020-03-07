#pragma once

#include "matrix.hpp"
#include "factory.hpp"

namespace linear_algebra {

template <typename T, size_t N>
using vector = matrix<T, N, 1>;


} // namespace linear_algebra