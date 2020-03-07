#pragma once

#include <array>
#include <cassert>

#include "factory.hpp"
#include "util.hpp"

namespace linear_algebra {

/**
 * generic matrix class
 * supported operations: +, -, *
 */
template <typename T, size_t N, size_t M>
class matrix {
public:

  /**
   * default constructor
   */
  matrix() noexcept : values_{} {
    for (auto& x: values_) {
      x = T{0};
    }
  }

  /**
   * copy contructor
   */
  template <typename T_>
  matrix<T, N, M>(const matrix<T_, N, M>& other) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        at(i, j) = static_cast<T>(other.at(i, j));
      }
    }
  }

  /**
   * move contructor
   * TODO
   */
  template <typename T_, typename = std::enable_if_t<std::is_same_v<T, T_>>>
  matrix<T, N, M>(const matrix<T_, N, M>&& other);

  /**
   * copy assignment
   */
  template <typename T_>
  matrix<T, N, M>& operator = (const matrix<T_, N, M>& other) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        at(i, j) = static_cast<T>(other.at(i, j));
      }
    }
  }

  /**
   * move assignment
   * TODO
   */
  template <typename T_, typename = std::enable_if_t<std::is_same_v<T, T_>>>
  matrix<T, N, M>& operator = (const matrix<T_, N, M>&& other);

  /**
   * destructor
   */
  ~matrix() {} // 

  /**
   * friend class for creating special matrices
   */
  template<typename T_, size_t N_, size_t M_>
  friend class matrix_factory;

  ///~ utilities

  /**
   * data access
   */

  util::row_view<T, M> operator [] (size_t r) {
    if (!(r < N)) {
      throw std::out_of_range("index out of range");
    }
    return util::row_view<T, M>(values_.data() + r * N, M);
  }

  const util::row_view<T, M> operator [] (size_t r) const {
    if (!(r < N)) {
      throw std::out_of_range("index out of range");
    }
    return util::row_view<T, M>(values_.data() + r * N, M);
  }
  
  T& at(size_t r, size_t c) {
    if (!(r < N) && !(c < M)) {
      throw std::out_of_range("index out of range");
    }
    return values_[r * N + c];
  }

  const T& at(size_t r, size_t c) const {
    if (!(r < N) && !(c < M)) {
      throw std::out_of_range("index out of range");
    }
    return values_[r * N + c];
  }

  ///~ operators

  template <typename T_>
  auto operator + (const matrix<T_, N, M>& rhs) {
    auto result = matrix_factory<util::result_of_add_t<T, T_>, N, M>::zero();
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) + rhs.at(r, c);
      }
    }
    return result;
  }

  template <typename T_>
  auto operator - (const matrix<T_, N, M>& rhs) {
    auto result = matrix_factory<util::result_of_add_t<T, T_>, N, M>::zero();
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) - rhs.at(r, c);
      }
    }
    return result;
  }

  template <typename T_>
  std::enable_if_t<
    std::is_arithmetic_v<T_>, 
    matrix<util::result_of_mul_t<T, T_>, N, M>
  > operator * (const T_& rhs) const {
    auto result = matrix_factory<util::result_of_mul_t<T, T_>, N, M>::zero();
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) * rhs;
      }
    }
    return result;
  }

  template <typename T_, size_t M_>
  auto operator * (const matrix<T_, M, M_>& rhs) const {
    auto result = matrix_factory<util::result_of_add_mul_t<T, T_>, N, M_>::zero();
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M_; c++) {
        for (size_t i = 0; i < M; i++) {
          result.at(r, c) = result.at(r, c) + at(r, i) * rhs.at(i, c);
        }
      }
    }
    return result;
  }

private:

  std::array<T, N * M> values_;
};

///~ cte * matrix

template <typename K, typename T, size_t N, size_t M>
typename std::enable_if<
  std::is_arithmetic<K>::value,
  matrix<util::result_of_mul_t<K, T>, N, M>
>::type operator * (const K& lhs, const matrix<T, N, M>& rhs) {
  return rhs * lhs;
}

///~ output

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

} // namespace linear_algebra