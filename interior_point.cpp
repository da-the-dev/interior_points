#include "matrix.h"

#define EPSILON 0.00001


Matrix projection_matrix(Matrix *Atilda) {
  Matrix Atilda_T = Atilda->transpose();
  Matrix Atilda_Atilda_T = *Atilda * Atilda_T;
  Matrix AATinverse = Atilda_Atilda_T.inverse();
  Matrix Atilda_T_times_inverse = Atilda_T * AATinverse;
  Matrix finalA = Atilda_T_times_inverse * *Atilda;

  Matrix I = Matrix(finalA.height, finalA.width);

  Matrix P = I - finalA;
  return P;
}

/**
 * Matrix C is the constraint matrix
 * Matrix A is the objective vector (represented as a matrix)
 * Matrix b is the right-hand side vector (represented as a matrix)
 *
 * In the example solution 
 * C is A
 * A is C
 * b is not used 
 *
 * In this implementation the notation defined by the task is used, 
 * i.e. the one defined in the paragraph before
 */
Matrix interior_point(Matrix C, Matrix A, Matrix b, int approximation,
                    int variables, int constraints, Matrix X_0, double alpha) {
  // // TODO DEBUG
  // cout << "DEB: Matrix C" << endl;
  // cout << C;
  // cout << "DEB: Matrix A" << endl;
  // cout << A;
  // cout << "DEB: Matrix b" << endl;
  // cout << b;
  // cout << "DEB: Matrix X_0" << endl;
  // cout << X_0;

  // Diagonal matrix D
  Matrix D = Matrix(X_0.height, X_0.height);
  for (int i = 0; i < X_0.height; i++) {
    D(i, i) = X_0(i, 0);
  }

  Matrix Ctilda = C * D; // + computes correctly
  Matrix Atilda = D * A; // + computes correctly

  Matrix P = projection_matrix(&Ctilda); 

  Matrix A_p = P * Atilda;

  /* Find the largest absolute component in C_p
   * and assign in to v   */
  double v;
  for (int i = 0; i < A_p.height; i++)
    v = max(v, abs(A_p(i, 0)));


  Matrix alphad = (alpha / v) * A_p;
  Matrix xtilda = Matrix(A_p.height, 1, 1) + alphad;
  Matrix X = D * xtilda;
  Matrix diff = X_0 - X;

  if (diff.length() > EPSILON)
    interior_point(C, A, b, approximation, variables, constraints, X, alpha);
  return X;
}
