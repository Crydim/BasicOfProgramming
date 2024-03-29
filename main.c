#include "vector.h"
#include "matrix.h"
#include "function_matrix.h"

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
    test_swapRowsWithMaxAndMinElements1;
    test_swapRowsWithMaxAndMinElements2;
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
    test_sortRowsByMaxElement1;
    test_sortRowsByMaxElement2;
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
    sortRowsByMaxElement(A);
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
    sortRowsByMaxElement(A);
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
    sortRowsByMaxElement(A);
    matrix res = createMatrixFromArray(
            (int []) {
                    2, 1, 6,
                    5, 2, 12,
                    3,5, 4,
                    4, 15, 9,
                    15, 42, 4,
            },
            5, 3
    );
    assert(areTwoMatricesEqual(&A, &res));
    freeMemMatrix(&A);
    freeMemMatrix(&res);
}

void test_sortColsByMinElement(){
    test_sortColsByMinElement1;
    test_sortColsByMinElement2;
    test_sortColsByMinElement3;
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
    sortRowsByMaxElement(A);
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
    sortRowsByMaxElement(A);
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
    test_getSquareOfMatrixIfSymmetric1;
    test_getSquareOfMatrixIfSymmetric2;
}


void test_function_matrix(){
    test_swapRowsWithMaxAndMinElements;
    test_sortRowsByMaxElement;
    test_sortColsByMinElement;
    test_getSquareOfMatrixIfSymmetric;
}


int main() {
    vector a = createVector(5);
    reserve(&a, 5);
    test_vector();
    test_matrix();
    test_function_matrix();
    return 0;
}