#pragma once

#include <array>
#include <cassert>

#include "factory.hpp"

namespace linear_algebra {

template <typename T, size_t N, size_t M>
class matrix {
public:

  matrix() noexcept : values_{} {}

  template<typename To, size_t No, size_t Mo>
  friend class matrix_factory;

  // utilities
  T& at(size_t r, size_t c) {
    if (r < 0 || N < r || c < 0 || M < c) {
      throw std::out_of_range("blablala...");
    }
    return values_[r * N + c];
  }

  const T& at(size_t r, size_t c) const {
    if (r < 0 || N < r || c < 0 || M < c) {
      throw std::out_of_range("blablabla...");
    }
    return values_[r * N + c];
  }

private:

  std::array<T, N * M> values_;
};

template <typename T, size_t N, size_t M>
std::ostream& operator << (std::ostream& out, const matrix<T, N, M>& A) {
  for (size_t r = 0; r < N; r++) {
    for (size_t c = 0; c < M; c++) {
      out << A.at(r, c);
      if (c + 1 < M) {
        out << " ";
      }
    }
    if (r + 1 < N) {
      out << "\n";
    }
  }
  return out;
}

template<class T, size_t N>
using vector = matrix<T, N, 1>;

} // namespace linear_algebra