#include "matrix.h"
#include <math.h>

#ifndef STRUCTURES_FUNCTION_MATRIX_H
#define STRUCTURES_FUNCTION_MATRIX_H

//Задание 1
void swapRowsWithMaxAndMinElements(matrix m);

//Задание 2
int getMax(int *a, int n);

//Задание 2
void sortRowsByMaxElement(matrix m);

//Задание 3
int getMin(int *a, int n);

//Задание 3
void sortColsByMinElement(matrix m);

//Задание 4
matrix mulMatrices(matrix m1, matrix m2);

//Задание 4
void getSquareOfMatrixIfSymmetric(matrix *m);

#endif //STRUCTURES_FUNCTION_MATRIX_H
