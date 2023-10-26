#include <iostream>
#include "matrix.h"
#include "interior_point.h"

using namespace std;

int main() {
  cout << "Enter the number of variables and the number of constraints:"
       << endl;
  int variables;   // number of variables
  int constraints; // number of constraints
  cin >> variables;
  cin >> constraints;

  cout << "Enter the C matrix:" << endl;
  Matrix C(1, variables);
  cin >> C;

  cout << "Enter the A vector (objective function):" << endl;
  Matrix A(constraints, variables);
  cin >> A;

  cout << "Enter the b vector (right-hand side):" << endl;
  Matrix b(constraints, 1);
  cin >> b;

  cout << "Enter the approximation accuracy (as in std::setprecision):" << endl;
  int approximation;
  cin >> approximation;

  // simplex(C, A, b, approximation, variables, constraints);
  interior_point(C, A, b, approximation, variables, constraints, 0.5);
  interior_point(C, A, b, approximation, variables, constraints, 0.5);

  return 0;
}
