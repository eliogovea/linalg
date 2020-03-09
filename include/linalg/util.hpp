#pragma once

namespace linear_algebra::internal {

/**
 * Some utilities for declaring types resulting
 * common arithmetic operations performed over
 * the elements of a matrix
 */

template <typename Ta, typename Tb>
using result_of_add_t = decltype(std::declval<Ta>() + std::declval<Tb>());

template <typename Ta, typename Tb>
using result_of_mul_t = decltype(std::declval<Ta>() * std::declval<Tb>());

template <typename Ta, typename Tb>
using result_of_add_mul_t =
    result_of_add_t<result_of_mul_t<Ta, Tb>, result_of_mul_t<Ta, Tb>>;

}  // namespace linear_algebra::internal