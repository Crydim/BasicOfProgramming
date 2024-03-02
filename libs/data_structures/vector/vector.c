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

bool isEmpty(vector *v){
    return v->size == 0;
}

bool isFull(vector *v){
    return v->size == v->capacity;
}

void pushBack(vector *v, int x){
    if (isEmpty(v)){
        reserve(v, 1);
    }
    if(isFull(v)){
        reserve(v, v->capacity*2);
    }
    append_(v->data, &v->size, x);
}

void popBack(vector *v){
    if (isEmpty(v)){
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    deleteByPosUnsaveOrder_(v->data, &v->size, v->size-1);
}