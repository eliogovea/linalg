#pragma once

#include <linalg/matrix.hpp>
#include <linalg/util.hpp>

namespace linear_algebra {

template <typename T, std::size_t N>
using vector = matrix<T, N, 1>;

}  // namespace linear_algebra