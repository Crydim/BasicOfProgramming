#include "vector.h"
#include "matrix.h"
#include "function_matrix.h"
#include <stdio.h>
#include "string_.h"

void test_pushBack_emptyVector(){
    vector v = createVector(0);
    pushBack(&v, 1);
    assert(v.data[0] == 1);
    deleteVector(&v);
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
    deleteVector(&v);
}

void test_atVector_notEmptyVector(){
    vector v = createVector(0);
    pushBack(&v, 9);
    assert(atVector(&v, 0) != NULL);
    deleteVector(&v);
}

void test_atVector_requestToLastElement(){
    vector v = createVector(0);
    pushBack(&v, 9);
    pushBack(&v, 8);
    assert(atVector(&v, v.size-1) != NULL);
    deleteVector(&v);
}

void test_back_oneElementInVector(){
    vector v = createVector(0);
    pushBack(&v, 9);
    pushBack(&v, 8);
    assert(back(&v) != NULL);
    deleteVector(&v);
}

void test_front_oneElementInVector(){
    vector v = createVector(0);
    pushBack(&v, 9);
    pushBack(&v, 8);
    assert(front(&v) != NULL);
    deleteVector(&v);
}

void test_pushBack_fullVector(){
    vector v = createVector(4);
    for (int i = 0; i < 5; i++){
        pushBack(&v, i);
    }
    assert(v.data[4] == 4);
    deleteVector(&v);
}

void test_vector() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();
}

void test_transposeSquareMatrix(){
    matrix A = createMatrixFromArray(
            (int []) {
                3, 6, 4,
                9, 8, 7,
                2 ,4, 5
            },
            3, 3
            );
    transposeSquareMatrix(&A);
    matrix expected = createMatrixFromArray(
            (int[]){
                3, 9, 2,
                6, 8, 4,
                4, 7, 5,
            },3, 3
            );
    assert(areTwoMatricesEqual(&A, &expected));
    freeMemMatrix(&A);
    freeMemMatrix(&expected);
}

void test_transposeMatrix1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 6, 4, 7, 6,
                    9, 8, 7, 7, 3,
                    2 ,4, 5, 1, 2,
            },
            3, 5
    );
    transposeMatrix(&A);
    matrix expected = createMatrixFromArray(
            (int[]){
                    3, 9, 2,
                    6, 8, 4,
                    4, 7, 5,
                    7, 7, 1,
                    6, 3, 2,
            },5, 3
    );
    assert(areTwoMatricesEqual(&A, &expected));
    freeMemMatrix(&A);
    freeMemMatrix(&expected);
}

void test_transposeMatrix2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 6, 4,
                    9, 8, 7,
                    2 ,4, 5,
                    15, 8, 4,
                    9, 7, 4,
            },
            5, 3
    );
    transposeMatrix(&A);
    matrix expected = createMatrixFromArray(
            (int[]){
                    3, 9, 2, 15, 9,
                    6, 8, 4, 8, 7,
                    4, 7, 5, 4, 4,
            },3, 5
    );
    assert(areTwoMatricesEqual(&A, &expected));
    freeMemMatrix(&A);
    freeMemMatrix(&expected);
}

int getSum(int *a, int n){
    int s = 0;
    for (int i = 0; i < n; i++){
        s += a[i];
    }
    return s;
}

void test_insertionSortRowsMatrixByRowCriteria(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 6, 4,
                    9, 8, 7,
                    2 ,4, 5
            },
            3, 3
    );
    insertionSortRowsMatrixByRowCriteria(A, getSum);
    matrix expected = createMatrixFromArray(
            (int []) {
                    2, 4, 5,
                    3, 6, 4,
                    9 ,8, 7
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &expected));
    freeMemMatrix(&A);
    freeMemMatrix(&expected);
}

void test_selectionSortColsMatrixByColCriteria(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 6, 4,
                    9, 8, 7,
                    2 ,4, 5
            },
            3, 3
    );
    selectionSortColsMatrixByColCriteria(A, getSum);
    matrix expected = createMatrixFromArray(
            (int []) {
                    3, 4, 6,
                    9, 7, 8,
                    2 ,5, 4
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &expected));
    freeMemMatrix(&A);
    freeMemMatrix(&expected);
}

void test_isEMatrix1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    1, 0, 0,
                    0, 1, 0,
                    0,0, 1
            },
            3, 3
    );
    assert(isEMatrix(&A));
    freeMemMatrix(&A);
}

void test_isEMatrix2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    1, 1, 0,
                    0, 1, 0,
                    1,0, 1
            },
            3, 3
    );
    assert(!isEMatrix(&A));
    freeMemMatrix(&A);
}

void test_isSymmetricMatrix1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 2, 4,
                    2, 1, 6,
                    4,6, 9
            },
            3, 3
    );
    assert(isSymmetricMatrix(&A));
    freeMemMatrix(&A);
}

void test_isSymmetricMatrix2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 5, 4,
                    2, 1, 6,
                    4,15, 9
            },
            3, 3
    );
    assert(!isSymmetricMatrix(&A));
    freeMemMatrix(&A);
}

void test_getMinValuePos(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 5, 4,
                    2, 1, 6,
                    4,15, 9
            },
            3, 3
    );
    position t = getMinValuePos(A);
    position expected = {1, 1};
    assert(t.colIndex == expected.colIndex && t.rowIndex == expected.rowIndex);
    freeMemMatrix(&A);
}

void test_transposeMatrix(){
    test_transposeSquareMatrix();
    test_transposeMatrix1();
    test_transposeMatrix2();
}

void test_isEMatrix() {
    test_isEMatrix1();
    test_isEMatrix2();
}

void test_isSymmetricMatrix() {
    test_isSymmetricMatrix1();
    test_isSymmetricMatrix2();
}

void test_matrix(){
    test_getMinValuePos();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_selectionSortColsMatrixByColCriteria();
    test_insertionSortRowsMatrixByRowCriteria();
    test_transposeMatrix();
}

void test_swapRowsWithMaxAndMinElements1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 5, 4,
                    2, 1, 6,
                    4,15, 9
            },
            3, 3
    );
    swapRowsWithMaxAndMinElements(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    3, 5, 4,
                    4, 15, 9,
                    2,1, 6
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_swapRowsWithMaxAndMinElements2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    7, 3, 2,
                    1, 48, 9,
                    8,15, 13
            },
            3, 3
    );
    swapRowsWithMaxAndMinElements(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    7, 3, 2,
                    1, 48, 9,
                    8,15, 13
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_swapRowsWithMaxAndMinElements(){
    test_swapRowsWithMaxAndMinElements1();
    test_swapRowsWithMaxAndMinElements2();
}

void test_sortRowsByMaxElement1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 5, 4,
                    2, 1, 6,
                    4,15, 9
            },
            3, 3
    );
    sortRowsByMaxElement(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    3, 5, 4,
                    2, 1, 6,
                    4,15, 9
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_sortRowsByMaxElement2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    20, 3, 2,
                    1, 48, 9,
                    8,15, 13
            },
            3, 3
    );
    sortRowsByMaxElement(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    8, 15, 13,
                    20, 3, 2,
                    1,48, 9
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_sortRowsByMaxElement(){
    test_sortRowsByMaxElement1();
    test_sortRowsByMaxElement2();
}

void test_sortColsByMinElement1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 5, 4, 9, 2,
                    2, 1, 6, 3, 45,
                    4,15, 9, 6, 12
            },
            3, 5
    );
    sortColsByMinElement(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    5, 3, 2, 9, 4,
                    1, 2, 45, 3, 6,
                    15,4,12, 6, 9
            },
            3, 5
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_sortColsByMinElement2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    5, 3, 2, 9, 4,
                    1, 2, 45, 3, 6,
                    15,4, 12, 6, 9
            },
            3, 5
    );
    sortColsByMinElement(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    5, 3, 2, 9, 4,
                    1, 2, 45, 3, 6,
                    15,4,12, 6, 9
            },
            3, 5
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_sortColsByMinElement3(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 5, 4,
                    2, 1, 6,
                    4,15, 9,
                    15, 42, 4,
                    5, 2, 12,
            },
            5, 3
    );
    sortColsByMinElement(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    5, 3, 4,
                    1, 2, 6,
                    15,4, 9,
                    42, 15, 4,
                    2, 5, 12,
            },
            5, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_sortColsByMinElement(){
    test_sortColsByMinElement1();
    test_sortColsByMinElement2();
    test_sortColsByMinElement3();
}

void test_getSquareOfMatrixIfSymmetric1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    9, 3, 2,
                    1, 5, 2,
                    8,3, 1
            },
            3, 3
    );
    getSquareOfMatrixIfSymmetric(&A);
    matrix res = createMatrixFromArray(
            (int []) {
                    9, 3, 2,
                    1, 5, 2,
                    8,3, 1
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_getSquareOfMatrixIfSymmetric2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    9, 4, 8,
                    4, 5, 3,
                    8,3, 1
            },
            3, 3
    );
    getSquareOfMatrixIfSymmetric(&A);
    matrix res = createMatrixFromArray(
            (int []) {
                    161, 80, 92,
                    80, 50, 50,
                    92,50, 74
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_getSquareOfMatrixIfSymmetric(){
    test_getSquareOfMatrixIfSymmetric1();
    test_getSquareOfMatrixIfSymmetric2();
}

void test_transposeIfMatrixHasNotEqualSumOfRows1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    10, 5, 9,
                    4, 9, 1,
                    19,15, 1
            },
            3, 3
    );
    transposeIfMatrixHasNotEqualSumOfRows(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    10, 4, 19,
                    5, 9, 15,
                    9,1, 1
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_transposeIfMatrixHasNotEqualSumOfRows2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    10, 15, 9,
                    4, 17, 1,
                    6,15, 1
            },
            3, 3
    );
    transposeIfMatrixHasNotEqualSumOfRows(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    10, 15, 9,
                    4, 17, 1,
                    6,15, 1
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_transposeIfMatrixHasNotEqualSumOfRows(){
    test_transposeIfMatrixHasNotEqualSumOfRows1();
    test_transposeIfMatrixHasNotEqualSumOfRows2();
}

void test_isMutuallyInverseMatrices1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, -4,
                    -5, 7,
            },
            2, 2
    );
    matrix B = createMatrixFromArray(
            (int []) {
                    7, 4,
                    5, 3,
            },
            2, 2
    );
    assert(isMutuallyInverseMatrices(A, B));
    freeMemMatrix(&A);
    freeMemMatrix(&B);
}

void test_isMutuallyInverseMatrices2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, -4,
                    -5, 7,
            },
            2, 2
    );
    matrix B = createMatrixFromArray(
            (int []) {
                    16, 4,
                    5, 17,
            },
            2, 2
    );
    assert(!isMutuallyInverseMatrices(A, B));
    freeMemMatrix(&A);
    freeMemMatrix(&B);
}

void test_isMutuallyInverseMatrices(){
    test_isMutuallyInverseMatrices1();
    test_isMutuallyInverseMatrices2();
}

void test_findSumOfMaxesOfPseudoDiagonal1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    5, 3, 2, 9, 4,
                    1, 2, 45, 3, 6,
                    15,4, 12, 6, 9
            },
            3, 5
    );
    long long res = findSumOfMaxesOfPseudoDiagonal(A);
    long long expected = 86;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_findSumOfMaxesOfPseudoDiagonal2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 5, 4,
                    2, 1, 6,
                    4,15, 9,
                    15, 42, 4,
                    5, 2, 12,
            },
            5, 3
    );
    long long res = findSumOfMaxesOfPseudoDiagonal(A);
    long long expected = 87;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_findSumOfMaxesOfPseudoDiagonal(){
    test_findSumOfMaxesOfPseudoDiagonal1();
    test_findSumOfMaxesOfPseudoDiagonal2();
}

void test_getMinInArea1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 5, 4,
                    15, 42, 6,
                    3,16, 7,
                    15, 12, 6,
                    5, 1, 15,
            },
            5, 3
    );
    int res = getMinInArea(A);
    int expected = 3;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getMinInArea2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 15, 4,
                    11, 2, 1,
                    3,13, 9,
                    14, 12, 6,
                    5, 1, 14,
            },
            5, 3
    );
    int res = getMinInArea(A);
    int expected = 15;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getMinInArea3(){
    matrix A = createMatrixFromArray(
            (int []) {
                    5, 3, 2, 9, 4,
                    1, 12, 7, 3, 6,
                    15,4, 45, 6, 9
            },
            3, 5
    );
    int res = getMinInArea(A);
    int expected = 2;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getMinInArea(){
    test_getMinInArea1();
    test_getMinInArea2();
    test_getMinInArea3();
}

void test_sortByDistances1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    6, 23, 3, 2, 4,
                    1, 12, 7, 13, 21,
                    13,0, 4, 6, 9
            },
            3, 5
    );
    sortByDistances(A);
    matrix expected = createMatrixFromArray(
            (int []) {
                    13, 0, 4, 6, 9,
                    6, 23, 3, 2, 4,
                    1,12, 7, 13, 21
            },
            3, 5
    );
    assert(areTwoMatricesEqual(&A, &expected));
    freeMemMatrix(&A);
    freeMemMatrix(&expected);
}

void test_sortByDistances2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    1, 5, 3, 2, 4,
                    1, 8, 7, 9, 5,
                    13,3, 4, 6, 11
            },
            3, 5
    );
    sortByDistances(A);
    matrix expected = createMatrixFromArray(
            (int []) {
                    1, 5, 3, 2, 4,
                    1, 8, 7, 9, 5,
                    13,3, 4, 6, 11
            },
            3, 5
    );
    assert(areTwoMatricesEqual(&A, &expected));
    freeMemMatrix(&A);
    freeMemMatrix(&expected);
}

void test_sortByDistances3(){
    matrix A = createMatrixFromArray(
            (int []) {
                    1, 5, 3,
                    1, 8, 7,
                    13,3, 4,
                    21, 4, 5,
                    12, 14, 1
            },
            5, 3
    );
    sortByDistances(A);
    matrix expected = createMatrixFromArray(
            (int []) {
                    1, 5, 3,
                    1, 8, 7,
                    13,3, 4,
                    12, 14, 1,
                    21, 4, 5
            },
            5, 3
    );
    assert(areTwoMatricesEqual(&A, &expected));
    freeMemMatrix(&A);
    freeMemMatrix(&expected);
}

void test_sortByDistances(){
    test_sortByDistances1();
    test_sortByDistances2();
    test_sortByDistances3();
}

void test_countEqClassesByRowsSum1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 15, 4,
                    11, 2, 1,
                    3,13, 9,
                    14, 12, 6,
                    5, 1, 14,
            },
            5, 3
    );
    int res = countEqClassesByRowsSum(A);
    int expected = 5;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_countEqClassesByRowsSum2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 7, 4,
                    4, 6, 5,
                    4,6, 1,
                    10, 3, 2,
                    5, 1, 14,
            },
            5, 3
    );
    int res = countEqClassesByRowsSum(A);
    int expected = 4;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_countEqClassesByRowsSum3(){
    matrix A = createMatrixFromArray(
            (int []) {
                    1, 15, 3, 2, 4,
                    1, 6, 7, 9, 2,
                    1,3, 12, 5, 4
            },
            3, 5
    );
    int res = countEqClassesByRowsSum(A);
    int expected = 1;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_countEqClassesByRowsSum(){
    test_countEqClassesByRowsSum1();
    test_countEqClassesByRowsSum2();
    test_countEqClassesByRowsSum3();
}

void test_getNSpecialElement1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 15, 4,
                    11, 2, 1,
                    3,34, 9,
                    25, 12, 6,
                    5, 1, 14,
            },
            5, 3
    );
    int res = getNSpecialElement(A);
    int expected = 2;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getNSpecialElement2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    3, 7, 4, 8, 7,
                    4, 6, 5, 9, 5,
                    4,6, 1,  6, 12
            },
            3, 5
    );
    int res = getNSpecialElement(A);
    int expected = 0;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getNSpecialElement3(){
    matrix A = createMatrixFromArray(
            (int []) {
                    1, 15, 3, 2, 4,
                    5, 6, 7, 9, 2,
                    9,3, 17, 5, 12
            },
            3, 5
    );
    int res = getNSpecialElement(A);
    int expected = 5;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getNSpecialElement(){
    test_getNSpecialElement1();
    test_getNSpecialElement2();
    test_getNSpecialElement3();
}

void test_swapPenultimateRow1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    10, 1, 9,
                    4, 17, 5,
                    6,15, 9
            },
            3, 3
    );
    swapPenultimateRow(A, getLeftMin(A).colIndex);
    matrix res = createMatrixFromArray(
            (int []) {
                    10, 1, 9,
                    1, 17, 15,
                    6,15, 9
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_swapPenultimateRow2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    10, 15, 1,
                    4, 17, 6,
                    1,15, 7
            },
            3, 3
    );
    swapPenultimateRow(A, getLeftMin(A).colIndex);
    matrix res = createMatrixFromArray(
            (int []) {
                    10, 15, 1,
                    10, 4, 1,
                    1,15, 7
            },
            3, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_swapPenultimateRow(){
    test_swapPenultimateRow1();
    test_swapPenultimateRow2();
}

void test_countNonDescendingRowsMatrices1(){
    matrix *A = createArrayOfMatrixFromArray(
            (int []) {
                    1, 2, 3,
                    5, 6, 7,
                    1,3, 17,

                    1, 15, 4,
                    9, 6, 12,
                    5,3, 11,

                    9, 51, 53,
                    5, 15, 17,
                    1,2, 17,

                    1, 15, 3,
                    10, 14, 7,
                    98,74, 17,
            },
            4, 3, 3
    );
    int res = countNonDescendingRowsMatrices(A, 4);
    int expected = 2;
    assert(res == expected);
    freeMemMatrices(A, 4);
}

void test_countNonDescendingRowsMatrices2(){
    matrix *A = createArrayOfMatrixFromArray(
            (int []) {
                    1, 15, 3,
                    5, 6, 7,
                    1,45, 17,

                    1, 15, 4,
                    9, 1, 12,
                    5,3, 11,

                    9, 51, 53,
                    5, 74, 17,
                    1,2, 17,

                    1, 123, 3,
                    10, 14, 7,
                    98,74, 17,
            },
            4, 3, 3
    );
    int res = countNonDescendingRowsMatrices(A, 4);
    int expected = 0;
    assert(res == expected);
    freeMemMatrices(A, 4);
}

void test_countNonDescendingRowsMatrices(){
    test_countNonDescendingRowsMatrices1();
    test_countNonDescendingRowsMatrices2();
}

void test_countZeroRows1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    10, 1, 9,
                    4, 17, 5,
                    6,15, 9
            },
            3, 3
    );
    int res = countZeroRows(A);
    int expected = 0;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_countZeroRows2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    10, 0, 9,
                    0, 0, 0,
                    0,0, 0
            },
            3, 3
    );
    int res = countZeroRows(A);
    int expected = 2;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_countZeroRows(){
    test_countZeroRows1();
    test_countZeroRows2();
}

void test_getMaxAbsoluteValue1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    -15, 3, 9,
                    4, 5, 8,
                    3,19, -7
            },
            3, 3
    );
    int res = getMaxAbsoluteValue(A);
    int expected = 19;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getMaxAbsoluteValue2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    -15, 0, 4,
                    3, 7, 8,
                    -1,15, -7
            },
            3, 3
    );
    int res = getMaxAbsoluteValue(A);
    int expected = 15;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getMaxAbsoluteValue(){
    test_getMaxAbsoluteValue1();
    test_getMaxAbsoluteValue2();
}

void test_getNSpecialElement21(){
    matrix A = createMatrixFromArray(
            (int []) {
                    1, 15, 3, 2, 4,
                    5, 6, 7, 9, 2,
                    9,3, 17, 5, 12
            },
            3, 5
    );
    int res = getNSpecialElement2(A);
    int expected = 1;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getNSpecialElement22(){
    matrix A = createMatrixFromArray(
            (int []) {
                    1, 4, 5, 9, 11,
                    12, 13, 15, 17, 20,
                    6,8, 10, 15, 20
            },
            3, 5
    );
    int res = getNSpecialElement2(A);
    int expected = 15;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getNSpecialElement23(){
    matrix A = createMatrixFromArray(
            (int []) {
                    5, 4, 1,
                    7, 3, 2,
                    10,5, 2,
                    24, 21, 6,
                    9, 4, 1

            },
            5, 3
    );
    int res = getNSpecialElement2(A);
    int expected = 0;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getNSpecialElement2t(){
    test_getNSpecialElement21();
    test_getNSpecialElement22();
    test_getNSpecialElement23();
}

void test_getVectorIndexWithMaxAngle1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    10, 4, 2, 1, 9,
                    14, 0, 7, 9, 2,
                    3,6, 8, 11, 9
            },
            3, 5
    );
    int b[5] = {9, 7, 4, 3, 6};
    int res = getVectorIndexWithMaxAngle(A, b);
    int expected = 1;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getVectorIndexWithMaxAngle2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    10, 4, 2,
                    2, 0, 7,
                    3,6, 8,
                    10, 4, 2,
                    2, 3, 1

            },
            5, 3
    );
    int b[3] = {9, 7, 4};
    int res = getVectorIndexWithMaxAngle(A, b);
    int expected = 1;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getVectorIndexWithMaxAngle(){
    test_getVectorIndexWithMaxAngle1();
    test_getVectorIndexWithMaxAngle2();
}

void test_getSpecialScalarProduct1(){
    matrix A = createMatrixFromArray(
            (int []) {
                    10, 15, 9,
                    4, 17, 5,
                    6,12, 1
            },
            3, 3
    );
    long long res = getSpecialScalarProduct(A, A.nCols);
    long long expected = 126;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getSpecialScalarProduct2(){
    matrix A = createMatrixFromArray(
            (int []) {
                    11, 3, 9,
                    4, 8, 5,
                    0,7, 10
            },
            3, 3
    );
    long long res = getSpecialScalarProduct(A, A.nCols);
    long long expected = 133;
    assert(res == expected);
    freeMemMatrix(&A);
}

void test_getSpecialScalarProduct(){
    test_getSpecialScalarProduct1();
    test_getSpecialScalarProduct2();
}

void test_function_matrix(){
    test_swapRowsWithMaxAndMinElements();
    test_sortRowsByMaxElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasNotEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInArea();
    test_sortByDistances();
    test_countEqClassesByRowsSum();
    test_getNSpecialElement();
    test_swapPenultimateRow();
    test_countNonDescendingRowsMatrices();
    test_countZeroRows();
    test_getMaxAbsoluteValue();
    test_getNSpecialElement2t();
    test_getVectorIndexWithMaxAngle();
    test_getSpecialScalarProduct();
}

void test_findNonSpace1(){
    char s[4] = " 129";
    char *res = findNonSpace(&s[0]);
    assert(*res == '1');
}

void test_findNonSpace2(){
    char s[4] = "785 ";
    char *res = findNonSpace(&s[1]);
    assert(*res == '8');
}

void test_findNonSpace3(){
    char s[4] = "   ";
    char *res = findNonSpace(&s[1]);
    assert(*res == '\0');
}

void test_findNonSpace(){
    test_findNonSpace1();
    test_findNonSpace2();
    test_findNonSpace3();
}

void test_findSpace1(){
    char s[4] = " 453";
    char *res = findSpace(&s[0]);
    assert(*res == ' ');
}

void test_findSpace2(){
    char s[4] = "165 ";
    char *res = findSpace(&s[1]);
    assert(*res == ' ');
}

void test_findSpace3(){
    char s[4] = "914";
    char *res = findSpace(&s[1]);
    assert(*res == '\0');
}

void test_findSpace(){
    test_findSpace1();
    test_findSpace2();
    test_findSpace3();
}

void test_findNonSpaceReverse1(){
    char s[4] = " 432";
    char *res = findNonSpaceReverse(&s[3], &s[0]);
    assert(*res == '2');
}

void test_findNonSpaceReverse2(){
    char s[4] = "134 ";
    char *res = findNonSpaceReverse(&s[3], &s[1]);
    assert(*res == '4');
}

void test_findNonSpaceReverse3(){
    char s[4] = "   ";
    char *res = findNonSpaceReverse(&s[3], &s[0]);
    assert(*res == '\0');
}

void test_findNonSpaceReverse(){
    test_findNonSpaceReverse1();
    test_findNonSpaceReverse2();
    test_findNonSpaceReverse3();
}

void test_findSpaceReverse1(){
    char s[4] = " 194";
    char *res = findSpaceReverse(&s[2], &s[0]);
    assert(*res == ' ');
}

void test_findSpaceReverse2(){
    char s[4] = "197 ";
    char *res = findSpaceReverse(&s[3], &s[2]);
    assert(*res == ' ');
}

void test_findSpaceReverse3(){
    char s[4] = "1651";
    char *res = findSpaceReverse(&s[3], &s[0]);
    assert(*res == '1');
}

void test_findSpaceReverse(){
    test_findSpaceReverse1();
    test_findSpaceReverse2();
    test_findSpaceReverse3();
}

void test_strcmp1(){
    char s1[4] = "1648";
    int res = strcmp(s1, s1);
    assert(res == 0);
}


void test_strcmp2(){
    char s1[4] = "1648";
    char s2[4] = "6487";
    int res = strcmp(s1, s2);
    assert(res == -5);
}

void test_strcmp3(){
    char s1[4] = "stop";
    char s2[4] = "free";
    int res = strcmp(s1, s2);
    assert(res == 13);
}

void test_strcmp(){
    test_strcmp1();
    test_strcmp2();
    test_strcmp3();
}

void test_copy1(){
    char s1[4] = "2024";
    char res[4];
    char expected[4] = "20";
    copy(&s1[0], &s1[2], res);
    for (int i = 0; i < 2; i++){
        assert(expected[i] == res[i]);
    }
}

void test_copy2(){
    char s1[5] = "Hello";
    char res[5];
    char expected[3] = "llo";
    copy(&s1[2], &s1[5], res);
    for (int i = 0; i < 3; i++){
        assert(expected[i] == res[i]);
    }
}

void test_copy3(){
    char s1[11] = "Hello world";
    char res[11];
    char expected[11] = "Hello world";
    copy(&s1[0], &s1[11], res);
    for (int i = 0; i < 11; i++){
        assert(expected[i] == res[i]);
    }
}

void test_copy(){
    test_copy1();
    test_copy2();
    test_copy3();
}

void test_string_(){
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_strcmp();
    test_copy();
}

int main() {
    vector a = createVector(5);
    reserve(&a, 5);
    test_vector();
    test_matrix();
    test_function_matrix();
    test_string_();
    return 0;
}