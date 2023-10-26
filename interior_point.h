#ifndef INTERIOR_H
#define INTERIOR_H

#include "matrix.h"

void interior_point(Matrix C, Matrix A, Matrix b, int approximation, int variables, int constraints, double alpha);

#endif
