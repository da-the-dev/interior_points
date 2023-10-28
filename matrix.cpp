#include "matrix.h"
#include <cmath>
#include <iostream>
#include <istream>

using namespace std;

Matrix::Matrix(int height, int width) : height(height), width(width) {
  matrix.resize(height);
  for (int i = 0; i < height; i++)
    matrix[i].resize(width);
}

Matrix::Matrix(int height, int width, double filler)
    : height(height), width(width) {
  matrix.resize(height);
  for (int i = 0; i < height; i++)
    matrix[i].resize(width);

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      (*this)(i, j) = filler;
}

double &Matrix::operator()(int row, int col) { return matrix[row][col]; }

void Matrix::setIdentity() {
  if (height != width) {
    printf("Attempted to setIdentity on a rectangular matrix\n");
    exit(0);
  }

  for (int i = 0; i < height; i++)
    for (int j = 0; j < height; j++) {
      if (i == j)
        (*this)(i, j) = 0;
      else
        (*this)(i, j) = 1;
    }
}

Matrix Matrix::transpose() {
  Matrix result(width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      result(j, i) = matrix[i][j];
    }
  }
  return result;
}

const double &Matrix::operator()(int row, int col) const {
  return matrix[row][col];
}

ostream &operator<<(ostream &out, const Matrix &m) {
  for (int i = 0; i < m.height; i++) {
    for (int j = 0; j < m.width; j++) {
      out << m(i, j);
      if (j != m.width - 1)
        out << " ";
    }
    out << endl;
  }
  return out;
}

istream &operator>>(istream &in, Matrix &m) {
  for (int i = 0; i < m.height; i++)
    for (int j = 0; j < m.width; j++)
      in >> m(i, j);

  return in;
}

Matrix Matrix::operator+(const Matrix &matrixEntity) const {
  if ((matrixEntity.height == height) && (matrixEntity.width == width)) {
    Matrix newMatrix(height, width);
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        newMatrix.matrix[i][j] = matrix[i][j] + matrixEntity.matrix[i][j];
      }
    }
    return newMatrix;
  } else {
    cout << "Error: the dimensional problem occurred in addition" << endl;
    return {0, 0};
  }
}

Matrix Matrix::operator-(const Matrix &matrixEntity) const {
  if ((matrixEntity.height == height) && (matrixEntity.width == width)) {
    Matrix newMatrix(height, width);
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        newMatrix.matrix[i][j] = matrix[i][j] - matrixEntity.matrix[i][j];
      }
    }
    return newMatrix;
  } else {
    cout << "Error: the dimensional problem occurred in subtraction" << endl;
    return {0, 0};
  }
}

Matrix Matrix::operator*(const Matrix &matrixEntity) const {
  if (width == matrixEntity.height) {
    Matrix newMatrix(height, matrixEntity.width);
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < matrixEntity.width; j++) {
        double temp = 0;
        for (int k = 0; k < width; k++) {
          abs(temp + matrix[i][k] * matrixEntity.matrix[k][j]) >= 1e-10
              ? temp += matrix[i][k] * matrixEntity.matrix[k][j]
              : temp = 0;
        }
        newMatrix.matrix[i][j] = temp;
      }
    }
    return newMatrix;
  } else {
    cout << "Error: the dimensional problem occurred in multiplication" << endl;
    return {0, 0};
  }
}

Matrix operator*(double scalar, const Matrix &matrix) {
  Matrix result(matrix.height, matrix.width);
  for (int i = 0; i < matrix.height; i++) {
    for (int j = 0; j < matrix.width; j++) {
      result(i, j) = scalar * matrix(i, j);
    }
  }
  return result;
}

void Matrix::operator=(const Matrix &matrixEntity) {
  if (matrixEntity.height == height && matrixEntity.width == 1 ||
      height == 0 && width == 0) {
    this->height = matrixEntity.height;
    this->width = matrixEntity.width;
    this->matrix = matrixEntity.matrix;
  }
}

// void Matrix::permute(int first, int second) {
//   if (first < height && second < height) {
//   }
//   double *temp = matrix[first];
//   matrix[first] = matrix[second];
//   matrix[second] = temp;
// }
//
void Matrix::rowSubtract(int first, int second, double coef) {
  for (int i = 0; i < width; i++) {
    matrix[second][i] -= matrix[first][i] * coef;
    abs(matrix[second][i]) < 1e-10 ? matrix[second][i] = 0
                                   : matrix[second][i] = matrix[second][i];
  }
}

double Matrix::getValue(int i, int j) {
  double a = matrix[i][j];
  return (a);
}

Matrix Matrix::inverse() {
  if (height != width) {
    cout << "Error: Matrix is not square." << endl;
    return Matrix(0, 0);
  }

  int n = height;
  Matrix augmentedMatrix(n, 2 * n);

  // Create an augmented matrix [A | I]
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      augmentedMatrix(i, j) = matrix[i][j];
    }
    augmentedMatrix(i, i + n) = 1.0;
  }

  // Apply Gauss-Jordan elimination
  for (int i = 0; i < n; i++) {
    // Find pivot row
    int pivotRow = i;
    for (int j = i + 1; j < n; j++) {
      if (abs(augmentedMatrix(j, i)) > abs(augmentedMatrix(pivotRow, i))) {
        pivotRow = j;
      }
    }

    // Swap rows
    if (pivotRow != i) {
      for (int k = 0; k < 2 * n; k++) {
        swap(augmentedMatrix(i, k), augmentedMatrix(pivotRow, k));
      }
    }

    // Scale pivot row
    double pivot = augmentedMatrix(i, i);
    for (int k = 0; k < 2 * n; k++) {
      augmentedMatrix(i, k) /= pivot;
    }

    // Eliminate other rows
    for (int j = 0; j < n; j++) {
      if (j != i) {
        double factor = augmentedMatrix(j, i);
        for (int k = 0; k < 2 * n; k++) {
          augmentedMatrix(j, k) -= factor * augmentedMatrix(i, k);
        }
      }
    }
  }

  // Extract the inverse matrix
  Matrix inverseMatrix(n, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      inverseMatrix(i, j) = augmentedMatrix(i, j + n);
    }
  }

  return inverseMatrix;
}

double Matrix::length() {
  // Check if the matrix has height n and width 1
  // if (width != 1) {
  //     throw std::invalid_argument("Matrix dimensions do not match for length
  //     calculation.");
  // }

  double sumOfSquares = 0.0;
  for (int i = 0; i < height; i++) {
    sumOfSquares += matrix[i][0] * matrix[i][0];
  }

  return sqrt(sumOfSquares);
}
