#include "vector.h"

vector createVector(size_t n){
    vector vector1 = {
            malloc(sizeof(int ) * n),
            0,
            n
    };
    if (vector1.data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    return vector1;
}

void reserve (vector *v, size_t newCapacity){
    if (newCapacity < v->size){
        v->size = newCapacity;
    }
    v->data = malloc(sizeof (int) * newCapacity);
    if (v->data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    v->capacity = newCapacity;
    if (newCapacity == 0){
        v->data = NULL;
    }
}

void clear(vector *v){
    reserve(v, 0);
}

void shrinkToFit(vector *v){
    reserve(v, v->size);
}

void deleteVector(vector *v){
    free(v->data);
}