#pragma once

#include <array>
#include <cassert>

#include <linalg/util.hpp>

namespace linear_algebra {

/**
 * generic matrix class
 * supported operations: +, -, *, ...
 */
template <typename T, size_t N, size_t M>
class matrix {
 public:
  using _T = T;
  static const size_t _N = N;
  static const size_t _M = M;

  explicit matrix() noexcept : values_{} {
    for (auto& x : values_) {
      x = T{0};
    }
  }

  matrix(std::initializer_list<T> list) {
    // TODO check list.size() !!!
    std::copy(list.begin(), list.end(), values_.begin());
  }

  matrix(std::array<T, N * M> values) : values_{values} {}

  template <typename T_>
  matrix(const matrix<T_, N, M>& other) {
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
        at(r, c) = static_cast<T>(other.at(r, c));
      }
    }
  }

  template <typename T_, typename = std::enable_if_t<std::is_same_v<T, T_>>>
  matrix(const matrix<T_, N, M>&& other)
      : values_{std::move(other.values_)} {}

  template <typename T_>
  matrix& operator=(const matrix<T_, N, M>& other) {
    for (size_t i = 0; i < N * M; i++) {
      values_[i] = static_cast<T>(other.values_[i]);
    }
  }

  template <typename T_, typename = std::enable_if_t<std::is_same_v<T, T_>>>
  matrix& operator=(const matrix<T_, N, M>&& other) {
    if (&other == this) {
      return *this;
    }
    values_ = std::move(other.values_);
  }

  ~matrix<T, N, M>() {}  //

  /**
   * friend class for creating special matrices
   */
  template <typename T_, size_t N_, size_t M_>
  friend class matrix_factory;

  /**
   * data access methods and operators
   */

  util::row_view<T, M> row(size_t idx) {
    if (!(idx < N)) {
      throw std::out_of_range("index out of range");
    }
    return util::row_view<T, M>(values_.data() + idx * M);
  }

  util::matrix_view<T, N, M> column(size_t idx) {
    if (!(idx < N)) {
      throw std::out_of_range("index out of range");
    }
    return util::matrix_view<T, N, M>(values_.data() + idx);
  }

  util::row_view<T, M> operator[](size_t r) {
    return row(r);
  }

  util::row_view<T, M> operator[](size_t r) const {
    return row(r);
  }

  T& at(size_t r, size_t c) {
    if (!(r < N) && !(c < M)) {
      throw std::out_of_range("index out of range");
    }
    return values_[r * M + c];
  }

  const T& at(size_t r, size_t c) const {
    if (!(r < N) && !(c < M)) {
      throw std::out_of_range("index out of range");
    }
    return values_[r * M + c];
  }

  /**
   * explicit matrix cast
   */

  template <typename T_>
  explicit operator matrix<T_, N, M>() const {
    auto result = matrix<T_, N, M>{};
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
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
    auto result = matrix<util::result_of_add_t<T, T_>, N, M>{};
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) + rhs.at(r, c);
      }
    }
    return result;
  }

  template <typename T_>
  auto operator-(const matrix<T_, N, M>& rhs) {
    auto result = matrix<util::result_of_add_t<T, T_>, N, M>{};
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) - rhs.at(r, c);
      }
    }
    return result;
  }

  template <typename T_>
  std::enable_if_t<std::is_arithmetic_v<T_>,
                   matrix<util::result_of_mul_t<T, T_>, N, M>>
  operator*(const T_& rhs) const {
    auto result = matrix<util::result_of_mul_t<T, T_>, N, M>{};
    for (size_t r = 0; r < N; r++) {
      for (size_t c = 0; c < M; c++) {
        result.at(r, c) = at(r, c) * rhs;
      }
    }
    return result;
  }

  template <typename T_, size_t M_>
  auto operator*(const matrix<T_, M, M_>& rhs) const {
    auto result =
        matrix<util::result_of_add_mul_t<T, T_>, N, M_>{};
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

/**
 * cte * matrix
 */

template <typename K, typename T, size_t N, size_t M>
typename std::enable_if<std::is_arithmetic<K>::value,
                        matrix<util::result_of_mul_t<K, T>, N, M>>::type
operator*(const K& lhs, const matrix<T, N, M>& rhs) {
  return rhs * lhs;
}

/**
 * ouput operator
 */

template <typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& out, const matrix<T, N, M>& A) {
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

}  // namespace linear_algebra