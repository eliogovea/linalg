#include <iostream>

#include <vector>

#include "matrix.hpp"

namespace LA = linear_algebra;

int main() {
  auto A = LA::matrix_factory<int, 2, 2>::eye();
  auto B = LA::matrix_factory<int, 2, 3>::zero();

  std::cout << A << "\n\n";
  std::cout << B << "\n\n";

  // std::cout << A + B << "\n\n"; // compilation error

  auto C = LA::matrix_factory<double, 2, 2>::eye();

  std::cout.precision(10);
  std::cout << std::fixed;
  std::cout << C << "\n\n";

  C.at(0, 1) = 5;

  auto D = A + C;
  std::cout << D << "\n\n";

  std::cout << D - A - A - A << "\n\n";

  std::cout << A * 2.0 << "\n\n";

  std::cout << 2 * A << "\n\n";
}