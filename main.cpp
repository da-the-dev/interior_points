#include "interior_point.h"
#include "matrix.h"
#include <iostream>

using namespace std;

int main() {
  cout << "Enter the number of variables and the number of constraints:"
       << endl;
  int variables;   // number of variables
  int constraints; // number of constraints
  cin >> variables;
  cin >> constraints;

  cout << "Enter the C matrix:" << endl;
  Matrix C(constraints, variables);
  cin >> C;

  cout << "Enter the A vector (objective function):" << endl;
  Matrix A(variables, 1);
  cin >> A;

  cout << "Enter the b vector (right-hand side):" << endl;
  Matrix b(constraints, 1);
  cin >> b;

  cout << "Enter the approximation accuracy (as in std::setprecision):" << endl;
  int approximation;
  cin >> approximation;

  cout << "Enter the initial trial solutions (a point within the constraints):"
       << endl;
  Matrix X_0(variables, 1);
  cin >> X_0;

  Matrix result =
      interior_point(C, A, b, approximation, variables, constraints, X_0, 0.5);

  cout << result << endl;
  return 0;
}
