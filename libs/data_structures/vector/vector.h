#ifndef VECTORS_VECTOR_H
#define VECTORS_VECTOR_H

# include "array.h"
# include <assert.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct vector {
    int *data;
    size_t size;
    size_t capacity;
} vector;

vector createVector(size_t n);

void reserve (vector *v, size_t newCapacity);

void clear(vector *v);

void shrinkToFit(vector *v);

void deleteVector(vector *v);

bool isEmpty(vector *v);

bool isFull(vector *v);

void pushBack(vector *v, int x);

void popBack(vector *v);

#endif //VECTORS_VECTOR_H
