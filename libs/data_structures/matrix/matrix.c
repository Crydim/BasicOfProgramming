#include "matrix.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void swap (int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

bool isSquareMatrix(matrix *m){
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols){
        return false;
    }
    for (int i = 0; i < m1->nRows-1; i++){
        if (memcmp(m1->values[i], m2->values[i], sizeof (int) * m1->nCols) != 0){
            return false;
        }
    }
    return true;
}

bool isEMatrix(matrix *m){
    if (!isSquareMatrix(m)){
        return false;
    }
    for (int i = 0; i < m->nRows; i++){
        for (int j = 0; j < m->nCols; j++){
            if ((j == i && m->values[i][j] != 1) || ((j != i && m->values[i][j] != 0))){
                return false;
            }
        }
    }
    return true;
}


bool isSymmetricMatrix(matrix *m){
    if (!isSquareMatrix(m)){
        return false;
    }
    int j = 1;
    for (int i = 0; i < m->nRows; i++){
        for (j; j < m->nCols; j++){
            if (m->values[i][j] != m->values[j][i]){
                return false;
            }
        }
        j++;
    }
    return true;
}

void swapRows(matrix m, int i1, int i2){
    assert(i1 < m.nRows && i2 < m.nRows && i1 > -1 && i2 > -1);
    swap(&m.values[i1], &m.values[i2]);
}

void swapColumns(matrix m, int j1, int j2){
    assert(j1 < m.nCols && j2 < m.nCols && j1 > -1 && j2 > -1);
    for (int i = 0; i < m.nRows; i++){
        swap(&m.values[i][j1], &m.values[i][j2]);
    }
}

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i++){
        if (m->values[i] != NULL){
            free(m->values[i]);
            m->values[i] = NULL;
        }
    }
    m->nCols= 0;
    m->nRows = 0;
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++){
        freeMemMatrix(&ms[i]);
    }
}

void inputMatrix(matrix *m){
    for(int i = 0; i < m->nRows; i++){
        inputArray_(m->values[i], m->nCols);
    }
}

void inputMatrices(matrix *ms, int nMatrices){
    for(int i = 0; i < nMatrices; i++){
        inputMatrix(&ms[i]);
    }
}

void outputMatrix(matrix m){
    for(int i = 0; i < m.nRows; i++){
        outputArray_(m.values[i], m.nCols);
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for(int i = 0; i < nMatrices; i++){
        outputMatrix(ms[i]);
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)){
    int *a = (int *) malloc(sizeof (int) * m.nRows);
    for (int i = 0; i < m.nRows; i++){
        a[i] = criteria(m.values[i], m.nRows);
    }
    for (size_t i = 1; i < m.nRows; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            swapRows(m, j, j-1);
            j--;
        }
        a[j] = t;
    }
    free(a);
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)){
    int *a = (int *) malloc(sizeof (int) * m.nCols);
    for (int i = 0; i < m.nCols; i++){
        int *b = (int *) malloc(sizeof (int) * m.nRows);
        for(int j = 0; j < m.nRows; j++){
            b[j] = m.values[j][i];
        }
        a[i] = criteria(b, m.nRows);
        free(b);
    }
    for (int i = 0; i < m.nCols - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < m.nCols; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos]);
        swapColumns(m, i, minPos);
    }
    free(a);
}

void transposeSquareMatrix(matrix *m){
    int j = 0;
    for (int i = 0; i < m->nRows; i++){
        j++;
        for (int j1 = j; j1 < m->nCols; j1++){
            swap(&m->values[i][j1], &m->values[j1][i]);
        }
    }
}

void transposeMatrix(matrix *m){
    matrix mT = getMemMatrix(m->nCols, m->nRows);
    for (int i = 0; i < m->nCols; i++){
        for (int j = 0; j < m->nRows; j++){
            mT.values[i][j] = m->values[j][i];
        }
    }
    freeMemMatrix(m);
    m->nRows = mT.nRows;
    m->nCols = mT.nCols;
    m->values = mT.values;
}

position getMinValuePos(matrix m){
    position min_position = {0, 0};
    int min_value = m.values[0][0];
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            if (m.values[i][j] < min_value){
                min_position.rowIndex = i;
                min_position.colIndex = j;
                min_value = m.values[i][j];
            }
        }
    }
    return min_position;
}

position getMaxValuePos(matrix m){
    position max_position = {0, 0};
    int max_value = m.values[0][0];
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            if (m.values[i][j] > max_value){
                max_position.rowIndex = i;
                max_position.colIndex = j;
                max_value = m.values[i][j];
            }
        }
    }
    return max_position;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++){
        for (int j = 0; j < nCols; j++){
            m.values[i][j] = a[k++];
        }
    }
    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, int nMatrices, int nRows, int nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++){
        for (size_t i = 0; i < nRows; i++) {
            for (size_t j = 0; j < nCols; j++){
                ms[k].values[i][j] = values[l++];
            }
        }
    }
    return ms;
}
