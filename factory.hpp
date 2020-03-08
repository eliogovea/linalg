#pragma once

namespace linear_algebra {

// forward declaration
template <typename T, size_t N, size_t M>
class matrix;

/**
 * matrix_factory contains methods to create matrices,
 * it is declared as friend inside the matrix so
 * it have access to private members
 */
template <typename T, size_t N, size_t M>
struct matrix_factory {
  /**
   * create an all-zeroes matrix
   */
  static constexpr matrix<T, N, M> zero() {
    static_assert(0 < N && 0 < M,
                  "positive size for every dimension is required");
    matrix<T, N, M> result{};
    for (auto& x : result.values_) {
      x = T{0};
    }
    return result;  // move ???
  }
  /**
   * create an identity matrix
   */
  static constexpr matrix<T, N, M> eye() {
    static_assert(0 < N && 0 < M,
                  "positive size for every dimension is required");
    static_assert(N == M, "dimensions must match to create an identity matrix");
    auto result = zero();
    for (size_t r = 0; r < N; r++) {
      result.at(r, r) = T{1};
    }
    return result;  // move ???
  }
};

}  // namespace linear_algebra