#pragma once

#include <linalg/util.hpp>

namespace linear_algebra {

template <typename T, size_t N, size_t M>
class matrix;

template <typename T, size_t N>
class vector {
 public:
  vector() {}

  vector(std::initializer_list<T> list) {
    std::copy(list.begin(), list.end(), values_.begin());
  }

  vector(std::array<T, N> values) {
    std::copy(values.begin(), values.end(), values_.begin());
  }

  vector(const matrix<T, N, 1>& A) {
    for (size_t i = 0; i < N; i++) {
      values_[i] = A.at(i, 0);
    }
  }

  template <typename T_>
  vector(const vector<T_, N>& other) {
    for (size_t i = 0; i < N; i++) {
      values_[i] = other[i];
    }
  }

  template <typename T_, typename = std::enable_if_t<std::is_same_v<T, T_>>>
  vector<T, N>(const vector<T_, N>&& other)
      : values_{std::move(other.values_)} {}

  template <typename T_>
  vector<T, N>& operator=(const vector<T_, N>& other) {
    for (size_t i = 0; i < N; i++) {
      values_[i] = static_cast<T>(other.values_[i]);
    }
  }

  template <typename T_, typename = std::enable_if_t<std::is_same_v<T, T_>>>
  vector<T, N>& operator=(const vector<T_, N>&& other) {
    if (&other == this) {
      return *this;
    }
    values_ = std::move(other.values_);
  }

  T& operator[](size_t idx) { return values_[idx]; }

  const T& operator[](size_t idx) const { return values_[idx]; }

  explicit operator matrix<T, N, 1>() const { return matrix<T, N, 1>(values_); }

  template <typename T_>
  explicit operator vector<T_, N>() const {
    auto result = vector<T_, N>{};
    for (size_t i = 0; i < N; i++) {
      result[i] = static_cast<T_>(values_[i]);
    }
    return std::move(result);
  }

 private:
  std::array<T, N> values_;
};

template <typename Tm, size_t N, size_t M, typename Tv>
vector<util::result_of_add_mul_t<Tm, Tv>, N> operator*(
    const matrix<Tm, N, M>& lhs, const vector<Tv, M>& rhs) {
  return lhs * static_cast<matrix<Tv, N, 1>>(rhs);
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const vector<T, N>& v) {
  out << static_cast<matrix<T, N, 1>>(v);
  return out;
}

}  // namespace linear_algebra