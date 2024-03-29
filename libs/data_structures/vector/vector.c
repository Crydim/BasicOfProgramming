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
    realloc(v->data, newCapacity);
    if (v->data == NULL && newCapacity != 0){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    v->capacity = newCapacity;
}

void clear(vector *v){
    reserve(v, 0);
}

void shrinkToFit(vector *v){
    reserve(v, v->size);
}

void deleteVector(vector *v){
    if (v->data != NULL){
        free(v->data);
        v->data = NULL;
    }
    v->size = 0;
    v->capacity = 0;
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

int* atVector(vector *v, size_t index){
    if (index >= v->size){
        fprintf(stderr, "IndexError: a[", index, "] is not exists");
        exit(1);
    }
    return &v->data[index];
}

int* back(vector *v){
    return atVector(v, v->size-1);
}

int* front(vector *v){
    return atVector(v, 0);
}