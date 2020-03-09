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
template <typename T, size_t S, size_t D>
class matrix_view {
public:
  explicit matrix_view(T* values) : values_{values} {}
  T& operator [] (size_t idx) {
    if (!(idx < S)) {
      throw std::out_of_range("out of range"); 
    }
    return values_[D * idx];
  }
  const T& operator [] (size_t idx) const {
    if (!(idx < S)) {
      throw std::out_of_range("out of range"); 
    }
    return values_[D * idx];
  }
private:
  T* values_;
};

template <typename T, size_t S>
using row_view = matrix_view<T, S, 1>;

template <size_t S, typename Tlhs, size_t Dlhs, typename Trhs, size_t Drhs>
result_of_add_mul_t<Tlhs, Trhs> dot_product(const matrix_view<Tlhs, S, Dlhs>& lhs, const matrix_view<Trhs, S, Drhs>& rhs) {
  result_of_add_mul_t<Tlhs, Trhs> result{0};
  for (size_t i = 0; i < S; i++) {
    result = result + lhs[i] * rhs[i];
  }
}

}  // namespace linear_algebra::util