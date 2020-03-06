#include <iostream>

#include "matrix.hpp"

namespace LA = linear_algebra;

int main() {
  auto A = LA::matrix_factory<int, 2, 2>::eye();
  auto B = LA::matrix_factory<int, 2, 3>::zero();

  std::cout << A << "\n\n";
  std::cout << B << "\n\n";
}