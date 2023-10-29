#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
using namespace std;

class Matrix {
public:
  int width;
  int height;

  vector<vector<double>> matrix;
  Matrix(int height, int width);
  Matrix(int height, int width, double filler);

  double &operator()(int row, int col);
  const double &operator()(int row, int col) const; //
  friend ostream &operator<<(ostream &out, const Matrix &m);
  friend istream &operator>>(istream &in, Matrix &m);

  Matrix operator+(const Matrix &matrixEntity) const;
  Matrix operator-(const Matrix &matrixEntity) const;
  Matrix operator*(const Matrix &matrixEntity) const;
  friend Matrix operator*(const double scalar, const Matrix &matrixEntity) ;

  virtual void operator=(const Matrix &matrixEntity);

  void setIdentity();
  Matrix transpose();
  Matrix inverse();
  double length();
};

#endif // !MATRIX_H
