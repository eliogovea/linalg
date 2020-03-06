#pragma once

namespace linear_algebra {


template<typename T, size_t N, size_t M>
class matrix;

template<typename T, size_t N, size_t M>
struct matrix_factory {
  static constexpr matrix<T, N, M> zero() {
    matrix<T, N, M> result{};
    for (auto& x: result.values_) {
      x = T{0};
    }
    return result; // move ???
  }
  static constexpr matrix<T, N, M> eye() {
    static_assert(N == M, "dimensions must match");
    auto result = zero();
    for (size_t r = 0; r < N; r++) {
      result.at(r, r) = T{1};
    }
    return result; // move ???
  }
};

} // namespace linear_algebra