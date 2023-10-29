#ifndef INTERIOR_H
#define INTERIOR_H

#include "matrix.h"

Matrix interior_point(Matrix C, Matrix A, Matrix b, int approximation,
                    int variables, int constraints, Matrix starting_X, double alpha);

#endif
