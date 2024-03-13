#include "matrix.h"
#include <stdbool.h>
#include <stdlib.h>

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