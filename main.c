#include "vector.h"
#include "matrix.h"
#include "function_matrix.h"
#include <stdio.h>

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
}


int main() {
    vector a = createVector(5);
    reserve(&a, 5);
    test_vector();
    test_matrix();
    test_function_matrix();
    return 0;
}