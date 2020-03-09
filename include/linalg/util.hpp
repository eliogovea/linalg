#pragma once

namespace linear_algebra::util {

template <typename Ta, typename Tb>
using result_of_add_t = decltype(std::declval<Ta>() + std::declval<Tb>());

template <typename Ta, typename Tb>
using result_of_mul_t = decltype(std::declval<Ta>() * std::declval<Tb>());

template <typename Ta, typename Tb>
using result_of_add_mul_t =
    result_of_add_t<result_of_mul_t<Ta, Tb>, result_of_mul_t<Ta, Tb>>;

/**
 * lightweight view of some range of the matrix
 * e.g. matrix_view<T, S, 1> could represent a row
 * or you can change D to be equal to the number of columns of
 * the matrix so you have access to a column
 */
template <typename T, std::size_t S, std::size_t D>
class matrix_view {
 public:
  matrix_view(T* values) : values_{values} {}

  template <typename T_, std::size_t S_ = S,
            typename = std::enable_if_t<S_ == 1>>
  matrix_view(T_ value) {
    values_ = new T[1];
    values_[0] = static_cast<T>(value);
  }

  T& operator[](std::size_t idx) {
    if (!(idx < S)) {
      throw std::out_of_range("out of range");
    }
    return values_[D * idx];
  }

  const T& operator[](std::size_t idx) const {
    if (!(idx < S)) {
      throw std::out_of_range("out of range");
    }
    return values_[D * idx];
  }

  template <std::size_t S_ = S, typename = std::enable_if_t<S_ == 1>>
  operator T() const {
    return values_[0];
  }

 private:
  T* values_;
};

template <typename T, std::size_t S>
using row_view = matrix_view<T, S, 1>;

template <std::size_t S, typename Tlhs, std::size_t Dlhs, typename Trhs,
          std::size_t Drhs>
result_of_add_mul_t<Tlhs, Trhs> dot_product(
    const matrix_view<Tlhs, S, Dlhs>& lhs,
    const matrix_view<Trhs, S, Drhs>& rhs) {
  result_of_add_mul_t<Tlhs, Trhs> result{0};
  for (std::size_t i = 0; i < S; i++) {
    result = result + lhs[i] * rhs[i];
  }
}

}  // namespace linear_algebra::util