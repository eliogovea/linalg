#pragma once

#include <array>
#include <cassert>
#include <linalg/matrix_view.hpp>
#include <linalg/util.hpp>

namespace linear_algebra {

/**
 * generic matrix class
 * supported operations: +, -, *, ...
 */
template <typename T, std::size_t N, std::size_t M>
class matrix {
 public:
  using _T = T;
  static const std::size_t _N = N;
  static const std::size_t _M = M;

  explicit matrix() noexcept : values_{} {
    for (auto& x : values_) {
      x = T{0};
    }
  }

  matrix(std::initializer_list<T> list) {
    // TODO check list.size() !!!
    std::copy(list.begin(), list.end(), values_.begin());
  }

  explicit matrix(std::array<T, N * M> values) : values_{values} {}

  matrix(const matrix& other) {
    for (std::size_t r = 0; r < N; r++) {
      for (std::size_t c = 0; c < M; c++) {
        at(r, c) = static_cast<T>(other.at(r, c));
      }
    }
  }

  matrix(const matrix&& other) noexcept : values_{std::move(other.values_)} {}

  matrix& operator=(const matrix& other) {
    if (&other == this) {
      return *this;
    }
    for (std::size_t i = 0; i < N * M; i++) {
      values_[i] = static_cast<T>(other.values_[i]);
    }
  }

  matrix& operator=(matrix&& other) noexcept {
    if (&other == this) {
      return *this;
    }
    values_ = std::move(other.values_);
  }

  ~matrix() = default;

  /**
   * friend class for creating special matrices
   */
  template <typename T_, std::size_t N_, std::size_t M_>
  friend class matrix_factory;

  /**
   * data access methods and operators
   */

  internal::row_view<T, M> row(std::size_t idx) {
    if (!(idx < N)) {
      throw std::out_of_range("index out of range");
    }
    return internal::row_view<T, M>(values_.data() + idx * M);
  }

  internal::matrix_view<T, N, M> column(std::size_t idx) {
    if (!(idx < N)) {
      throw std::out_of_range("index out of range");
    }
    return internal::matrix_view<T, N, M>(values_.data() + idx);
  }

  internal::row_view<T, M> operator[](std::size_t r) { return row(r); }

  internal::row_view<T, M> operator[](std::size_t r) const { return row(r); }

  T& at(std::size_t r, std::size_t c) {
    if (!(r < N) && !(c < M)) {
      throw std::out_of_range("index out of range");
    }
    return values_[r * M + c];
  }

  const T& at(std::size_t r, std::size_t c) const {
    if (!(r < N) && !(c < M)) {
      throw std::out_of_range("index out of range");
    }
    return values_[r * M + c];
  }

  /**
   * matrix cast
   */

  template <typename T_>
  operator matrix<T_, N, M>() const {
    auto result = matrix<T_, N, M>{};
    for (std::size_t r = 0; r < N; r++) {
      for (std::size_t c = 0; c < M; c++) {
        result.at(r, c) = static_cast<T_>(at(r, c));
      }
    }
    return result;
  }

  /**
   * arithmetic operators
   */

  template <typename T_>
  auto operator+(const matrix<T_, N, M>& rhs) {
    auto result = matrix<internal::result_of_add_t<T, T_>, N, M>{};
    for (std::size_t r = 0; r < N; r++) {
      for (std::size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) + rhs.at(r, c);
      }
    }
    return result;
  }

  template <typename T_>
  auto operator-(const matrix<T_, N, M>& rhs) {
    auto result = matrix<internal::result_of_add_t<T, T_>, N, M>{};
    for (std::size_t r = 0; r < N; r++) {
      for (std::size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) - rhs.at(r, c);
      }
    }
    return result;
  }

  template <typename T_>
  std::enable_if_t<std::is_arithmetic_v<T_>,
                   matrix<internal::result_of_mul_t<T, T_>, N, M>>
  operator*(const T_& rhs) const {
    auto result = matrix<internal::result_of_mul_t<T, T_>, N, M>{};
    for (std::size_t r = 0; r < N; r++) {
      for (std::size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) * rhs;
      }
    }
    return result;
  }

  template <typename T_, std::size_t M_>
  auto operator*(const matrix<T_, M, M_>& rhs) const {
    auto result = matrix<internal::result_of_add_mul_t<T, T_>, N, M_>{};
    for (std::size_t r = 0; r < N; r++) {
      for (std::size_t c = 0; c < M_; c++) {
        for (std::size_t i = 0; i < M; i++) {
          result.at(r, c) = result.at(r, c) + at(r, i) * rhs.at(i, c);
        }
      }
    }
    return result;
  }

 private:
  std::array<T, N * M> values_;
};

/**
 * cte * matrix
 */

template <typename K, typename T, std::size_t N, std::size_t M>
typename std::enable_if<std::is_arithmetic<K>::value,
                        matrix<internal::result_of_mul_t<K, T>, N, M>>::type
operator*(const K& lhs, const matrix<T, N, M>& rhs) {
  return rhs * lhs;
}

/**
 * ouput operator
 */

template <typename T, std::size_t N, std::size_t M>
std::ostream& operator<<(std::ostream& out, const matrix<T, N, M>& A) {
  for (std::size_t r = 0; r < N; r++) {
    for (std::size_t c = 0; c < M; c++) {
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

}  // namespace linear_algebra