#pragma once 

namespace util {

template <typename Ta, typename Tb>
using result_of_add_t = decltype(std::declval<Ta>() + std::declval<Tb>());

template <typename Ta, typename Tb>
using result_of_mul_t = decltype(std::declval<Ta>() * std::declval<Tb>());

template <typename Ta, typename Tb>
using result_of_add_mul_t = result_of_add_t<result_of_mul_t<Ta, Tb>, result_of_mul_t<Ta, Tb>>;

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


} // namespace util