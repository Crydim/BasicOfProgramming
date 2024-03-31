#include "function_matrix.h"
#include <stdlib.h>
#include <stdio.h>

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
                        if (a[y].rowIndex  == i-1 && a[y].colIndex == j-1){
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

int getMinInArea(matrix m){
    position max = getMaxValuePos(m);
    int min = m.values[max.rowIndex][max.colIndex];
    int left = max.colIndex-1;
    int right = max.colIndex+1;
    for (int i = max.rowIndex-1; i >= 0; i--){
        for(int j = left; j <= right; j++){
            if (m.values[i][j] < min){
                min = m.values[i][j];
            }
        }
        if (left-1 >= 0){
            left--;
        }
        if(right+1 != m.nCols){
            right++;
        }
    }
    return min;
}

float getDistance(int *a, int n){
    float dis = 0;
    for(int i = 0; i < n; i++){
        dis += a[i]*a[i];
    }
    return sqrt(dis);
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)){
    float *a = (float *) malloc(sizeof (float) * m.nRows);
    for (int i = 0; i < m.nRows; i++){
        a[i] = criteria(m.values[i],  m.nCols);
    }
    for (size_t i = 1; i < m.nRows; i++) {
        float t = a[i];
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

void sortByDistances(matrix m){
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

int cmp_int(const void *pa, const void *pb){
    int arg1 = *(const int*)pa;
    int arg2 = *(const int*)pb;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int countNUnique(const int *a, int n){
    int amount_unique = 1;
    int remembered_sum = a[0];
    for (int i = 1; i < n; i++){
        if (a[i] != remembered_sum){
            amount_unique++;
            remembered_sum = a[i];
        }
    }
    return n == 0 ? 0 : amount_unique;
}

int countEqClassesByRowsSum(matrix m){
    int amount_sums = m.nRows;
    int *a = (int *) malloc(sizeof (int )*amount_sums+1);
    for (int i = 0; i < amount_sums; i++){
        a[i] = getSum1(m.values[i], m.nCols);
    }
    qsort(a, amount_sums, sizeof (int), cmp_int);
    int amount_eq_classes = countNUnique(a, amount_sums);
    free(a);
    return amount_eq_classes;
}

int getNSpecialElement(matrix m){
    int counter = 0;
    for(int j = 0; j < m.nCols; j++){
        int sum = 0;
        int max = m.values[0][j];
        for(int i = 1; i < m.nRows; i++){
            if (m.values[i][j] > max){
                sum += max;
                max = m.values[i][j];
            } else {
                sum += m.values[i][j];
            }
        }
        if (max > sum){
            counter++;
        }
    }
    return counter;
}

position getLeftMin(matrix m){
    position left_min_position = {0, 0};
    int min_value = m.values[0][0];
    for (int i = 0; i < m.nCols; i++){
        for (int j = 0; j < m.nRows; j++){
            if (m.values[j][i] < min_value){
                left_min_position.rowIndex = j;
                left_min_position.colIndex = i;
                min_value = m.values[j][i];
            }
        }
    }
    return left_min_position;
}

void swapPenultimateRow(matrix m, int n){
    if (n == m.nCols-1){
        for (int i = 0; i < m.nRows; i++){
            m.values[m.nRows-2][i] = m.values[i][n];
        }
    } else {
        for (int i = m.nRows-1; i >= 0; i--){
            m.values[m.nRows-2][i] = m.values[i][n];
        }
    }
}

bool isNonDescendingSorted(int *a, int n){
    for (int i = 0; i < n-1; i++){
        if (a[i] > a[i+1]){
            return false;
        }
    }
    return true;
}

bool hasAllNonDescendingRows(matrix m){
    for (int i = 0; i < m.nRows; i++){
        if(!isNonDescendingSorted(m.values[i], m.nCols)){
            return false;
        }
    }
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix){
    int counter = 0;
    for (int i = 0; i < nMatrix; i++){
        if (hasAllNonDescendingRows(ms[i])){
            counter++;
        }
    }
    return counter;
}

int countValues(const int *a, int n, int value){
    int counter = 0;
    for (int i = 0; i < n; i++){
        if (a[i] == value){
            counter++;
        }
    }
    return counter;
}

int countZeroRows(matrix m){
    int counter_rows = 0;
    for (int i = 0; i < m.nRows; i++){
        if (countValues(m.values[i], m.nCols, 0) == m.nCols){
            counter_rows++;
        }
    }
    return counter_rows;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix){
    int counter_max = 0;
    int max_zero_rows = 0;
    for (int i = 0; i < nMatrix; i++){
        if (countZeroRows(ms[i]) > max_zero_rows) {
            max_zero_rows = countZeroRows(ms[i]);
        }
    }
    int *a = (int *) malloc(sizeof (int)*nMatrix);
    for (int i = 0; i < nMatrix; i++){
        if (countZeroRows(ms[i]) == max_zero_rows) {
            a[counter_max] = i;
            counter_max++;
        }
    }
    for (int i = 0; i < counter_max; i++){
        outputMatrix(ms[a[i]]);
    }
    free(a);
}

int getMaxAbsoluteValue(matrix m){
    int max_value = abs(m.values[0][0]);
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            if (abs(m.values[i][j]) > max_value){
                max_value = abs(m.values[i][j]);
            }
        }
    }
    return max_value;
}

void printMatrixWithMinStandard(matrix *ms, int nMatrix){
    int counter_min = 0;
    int lowest_rate = getMaxAbsoluteValue(ms[0]);
    for (int i = 1; i < nMatrix; i++){
        if (getMaxAbsoluteValue(ms[i]) < lowest_rate){
            lowest_rate = getMaxAbsoluteValue(ms[i]);
        }
    }
    int *a = (int *) malloc(sizeof (int)*nMatrix);
    for (int i = 0; i < nMatrix; i++){
        if (getMaxAbsoluteValue(ms[i]) == lowest_rate){
            a[counter_min] = i;
            counter_min++;
        }
    }
    for (int i = 0; i < counter_min; i++){
        outputMatrix(ms[a[i]]);
    }
    free(a);
}

int min2(int a, int b){
    return a > b ? b : a;
}

int getNSpecialElement2(matrix m){
    int counter = 0;
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            bool is_uniq = true;
            for (int right = j+1; right < m.nCols; right++){
                if (m.values[i][j] >= m.values[i][right]){
                    is_uniq = false;
                    break;
                }
            }
            for (int left = j-1; left >= 0; left--){
                if (m.values[i][j] <= m.values[i][left] || !is_uniq){
                    is_uniq = false;
                    break;
                }
            }
            if (is_uniq){
                counter++;
            }
        }
    }
    return counter;
}