#pragma once

#include <array>
#include <cassert>

#include "factory.hpp"

namespace linear_algebra {

/**
 * lightweigth view of a row
 * (like std::span)
 */
template <typename T, size_t M>
class row_view {
public:

  row_view(T* values, size_t size) : values_{values}, size_{size} {}

  T& operator [] (size_t idx) {
    if (!(idx < size_)) {
      throw std::out_of_range("out of range");
    }
    return values_[idx];
  }

  const T& operator [] (size_t idx) const {
    if (!(idx < size_)) {
      throw std::out_of_range("out of range");
    }
    return values_[idx];
  }
  
  // TODO
  // better way to iterate

private:

  T* values_;
  size_t size_;
};

/**
 * generic matrix class
 * supported operations: +, -, *
 */
template <typename T, size_t N, size_t M>
class matrix {
public:

  matrix() noexcept : values_{} {
    for (auto& x: values_) {
      x = T(0);
    }
  }

  template<typename To, size_t No, size_t Mo>
  friend class matrix_factory;

  ///~ utilities

  row_view<T, M> operator [] (size_t r) {
    if (!(r < N)) {
      throw std::out_of_range("index out of range");
    }
    return row_view<T, M>(values_.data() + r * N, M);
  }

  const row_view<T, M> operator [] (size_t r) const {
    if (!(r < N)) {
      throw std::out_of_range("index out of range");
    }
    return row_view<T, M>(values_.data() + r * N, M);
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

  template <typename To>
  auto operator + (const matrix<To, N, M>& rhs) {
    auto result = matrix_factory<decltype(std::declval<T>() + std::declval<To>()), N, M>::zero();
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) + rhs.at(r, c);
      }
    }
    return result;
  }

  template <typename To>
  auto operator - (const matrix<To, N, M>& rhs) {
    auto result = matrix_factory<decltype(std::declval<T>() + std::declval<To>()), N, M>::zero();
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) - rhs.at(r, c);
      }
    }
    return result;
  }

  template <typename K>
  auto operator * (const K& rhs) const {
    static_assert(std::is_arithmetic<K>::value, "to scale the value must be arithmetic");
    auto result = matrix_factory<decltype(std::declval<T>() * rhs), N, M>::zero();
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < N; c++) {
        result.at(r, c) = at(r, c) * rhs;
      }
    }
    return result;
  }

  template <typename To, size_t Mo>
  auto operator * (const matrix<To, M, Mo>& rhs) const {
    auto result = matrix_factory<decltype(std::declval<T>() * std::declval<To>()), N, Mo>::zero();
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < Mo; c++) {
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
  matrix<decltype(std::declval<K>() * std::declval<T>()), N, M>
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