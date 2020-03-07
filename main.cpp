#include <iostream>

#include <string>

#include "matrix.hpp"
#include "vector.hpp"

namespace LA = linear_algebra;

int main() {
  auto A = LA::matrix_factory<int, 2, 2>::eye();

  std::cout << "ostream operator <<\n";
  std::cout << A << "\n\n";

  std::cout << "access with at\n";
  std::cout << "A.at(0, 0) = " << A.at(0, 0) << "\n\n";

  std::cout << "modify element with at, add 15\n";
  std::cout << "before: A.at(0, 1) = " << A.at(0, 1) << "\n";
  A.at(0, 1) = A.at(0, 1) + 15;
  std::cout << "after: A.at(0, 1) = " << A.at(0, 1) << "\n\n";

  std::cout << "access with [][]\n";
  std::cout << "A[0][0] = " << A[0][0] << "\n\n";

  std::cout << "modify element with [][], add 15\n";
  std::cout << "before: A[0][1] = " << A[0][1] << "\n";
  A[0][1] = A[0][1] + 15;
  std::cout << "after: A[0][1] = " << A[0][1] << "\n\n";

  std::cout << "addition, substracion:\n";
  auto B = LA::matrix_factory<int, 2, 2>::eye();

  std::cout << "B = \n" << B << "\n\n";

  auto C = LA::matrix_factory<int, 2, 3>::zero();

  // auto D = A + C; // compilation error
  // auto E = C - A; // compilation error

  std::cout << "A + A - B = \n" << A + B - B << "\n\n";

  std::cout << "scale:\n";

  std::cout << "2.5 * A = \n" << 2.5 * A << "\n\n";
  std::cout << "A * 2.5 = \n" << A * 2.5 << "\n\n";

  // std::string k = "2";
  // std::cout << A * k << "\n"; // compilation error, k must be arithmetic 

  std::cout << "matrix multiplication:\n";
  C[0][0] = 1; C[0][1] = 2; C[0][2] = 3;
  C[1][0] = 1; C[1][1] = 3; C[1][2] = 4;

  std::cout << "A * C = \n" << A * C << "\n";
  // std::cout << "C * A = \n" << C * A << "\n"; // complation error
}