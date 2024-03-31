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

//Задание 10
int cmp_int(const void *pa, const void *pb);

//Задание 10
int countNUnique(const int *a, int n);

//Задание 10
int countEqClassesByRowsSum(matrix m);

//Задание 11
int getNSpecialElement(matrix m);

//Задание 12
position getLeftMin(matrix m);

//Задание 12
void swapPenultimateRow(matrix m, int n);

//Задание 13
bool isNonDescendingSorted(int *a, int n);

//Задание 13
bool hasAllNonDescendingRows(matrix m);

//Задание 13
int countNonDescendingRowsMatrices(matrix *ms, int nMatrix);

//Задание 14
int countValues(const int *a, int n, int value);

//Задание 14
int countZeroRows(matrix m);

//Задание 14
void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix);

//Задание 15
int getMaxAbsoluteValue(matrix m);

//Задание 15
void printMatrixWithMinStandard(matrix *ms, int nMatrix);

//Задание 16
int min2(int a, int b);

//Задание 16
int getNSpecialElement2(matrix m);

//Задание 17
double getScalarProduct(int *a, int *b, int n);

//Задание 17
double getVectorLength(int *a, int n);

//Задание 17
double getCosine(int *a, int *b, int n);

//Задание 17
int getVectorIndexWithMaxAngle(matrix m, int *b);


#endif //STRUCTURES_FUNCTION_MATRIX_H
