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

//Задание 5
long long getSum1(int *a, int n);

//Задание 5
bool isUnique(long long *a, int n);

//Задание 5
void transposeIfMatrixHasNotEqualSumOfRows(matrix m);

//Задание 6
bool isMutuallyInverseMatrices(matrix m1, matrix m2);

//Задание 7
int max(int a, int b);

//Задание 7
long long findSumOfMaxesOfPseudoDiagonal(matrix m);

//Задание 8
int getMinInArea(matrix m);

//Задание 9
float getDistance(int *a, int n);

//Задание 9
void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int));

//Задание 9
void sortByDistances(matrix m);

#endif //STRUCTURES_FUNCTION_MATRIX_H
