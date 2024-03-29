#include "function_matrix.h"
#include <stdlib.h>

void swapRowsWithMaxAndMinElements(matrix m){
    position max = getMaxValuePos(m);
    position min = getMinValuePos(m);
    swapRows(m, max.rowIndex, min.rowIndex);
}

int getMax(int *a, int n){
    int max = a[0];
    for (int i = 1; i < n; i++){
        if (a[i] > max){
            max = a[i];
        }
    }
    return max;
}

void sortRowsByMaxElement(matrix m){
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

int getMin(int *a, int n){
    int min = a[0];
    for (int i = 1; i < n; i++){
        if (a[i] < min){
            min = a[i];
        }
    }
    return min;
}

void sortColsByMinElement(matrix m){
    selectionSortColsMatrixByColCriteria(m, getMin);
}

matrix mulMatrices(matrix m1, matrix m2){
    matrix result_matrix = getMemMatrix(m1.nRows, m1.nCols);
    int row = 0;
    int col = 0;
    while(row < result_matrix.nRows && col < result_matrix.nCols){
        int sum = 0;
        for(int i = 0; i < result_matrix.nRows; i++){
            sum += m1.values[row][i]*m2.values[i][col];
        }
        result_matrix.values[row][col] = sum;
        if (col+1 != result_matrix.nCols){
            col++;
        } else {
            col = 0;
            row++;
        }
    }
    return result_matrix;
}

void getSquareOfMatrixIfSymmetric(matrix *m){
    if (isSymmetricMatrix(m)){
        matrix res_m = mulMatrices(*m, *m);
        freeMemMatrix(m);
        m->nRows = res_m.nRows;
        m->nCols = res_m.nCols;
        m->values = res_m.values;
    }
}

long long getSum1(int *a, int n){
    long long sum = 0;
    for(int i = 0 ; i < n; i++){
        sum += a[i];
    }
    return sum;
}

bool isUnique(long long *a, int n){
    for (int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if (a[i] == a[j]){
                return false;
            }
        }
    }
    return true;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m){
    long long *array_sum = (long long *) malloc(sizeof (long long ) * m.nRows);
    for (int i = 0; i < m.nRows; i++){
        array_sum[i] = getSum1(m.values[i], m.nCols);
    }
    if (isUnique(array_sum, m.nRows)){
        transposeSquareMatrix(&m);
    }
    free(array_sum);
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2){
    matrix res = mulMatrices(m1, m2);
    bool t = isEMatrix(&res);
    freeMemMatrix(&res);
    return t;
}

int max(int a, int b){
    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m){
    long long sum = 0;
    position *a = (position *) malloc(sizeof (position) * (m.nCols+m.nRows-1));
    int amount_diagonals = 0;
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            if (i != j){
                if (i == 0 || j == 0){
                    position t = {i, j};
                    a[amount_diagonals] = t;
                    amount_diagonals++;
                } else {
                    for (int y = 0; y < amount_diagonals; y++){
                        if (a[y].colIndex  == i-1 && a[y].rowIndex == j-1){
                            if (m.values[i][j] > m.values[a[y].rowIndex][a[y].colIndex]){
                                position t = {i, j};
                                a[y] = t;
                                break;
                            }
                        }
                    }
                }

            }
        }
    }
    for (int i = 0; i < amount_diagonals; i++){
        sum += m.values[a[i].rowIndex][a[i].colIndex];
    }
    free(a);
    return sum;
}