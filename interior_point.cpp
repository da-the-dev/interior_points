#include "matrix.h"

#define EPSILON 0.00001

Matrix projection_matrix(Matrix Ct) {
  Matrix Ct_T = Ct.transpose();
  Matrix finalC = Ct_T * (Ct * Ct_T).inverse() * Ct;

  Matrix I = Matrix(finalC.height, finalC.width);
  I.setIdentity();

  Matrix P = I - finalC;

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
                      int variables, int constraints, Matrix starting_X,
                      double alpha) {
  Matrix X = Matrix(0, 0);
  Matrix X_0 = starting_X;
  while (true) {
    // Diagonal matrix D
    Matrix D = Matrix(X_0.height, X_0.height);
    for (int i = 0; i < X_0.height; i++) {
      D(i, i) = X_0(i, 0);
    }

    Matrix Ctilda = C * D;
    Matrix Atilda = D * A;

    Matrix P = projection_matrix(Ctilda);

    Matrix A_p = P * Atilda;

    /* Find the largest negative component in C_p
       and assign its absolute value to v */
    double v;
    for (int i = 0; i < A_p.height; i++)
      v = abs(min(-v, A_p(i, 0)));

    Matrix alphad = (alpha / v) * A_p;
    Matrix xtilda = Matrix(A_p.height, 1, 1) + alphad;
    X = D * xtilda;
    Matrix diff = X_0 - X;

    if (diff.length() <= EPSILON)
      return X;
    X_0 = X;
  }
}
