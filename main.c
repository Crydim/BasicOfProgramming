#include "vector.h"
#include "matrix.h"

void test_pushBack_emptyVector(){
    vector v = createVector(0);
    pushBack(&v, 1);
    assert(v.data[0] == 1);
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_atVector_notEmptyVector(){
    vector v = createVector(0);
    pushBack(&v, 9);
    assert(atVector(&v, 0) != NULL);
}

void test_atVector_requestToLastElement(){
    vector v = createVector(0);
    pushBack(&v, 9);
    pushBack(&v, 8);
    assert(atVector(&v, v.size-1) != NULL);
}

void test_back_oneElementInVector(){
    vector v = createVector(0);
    pushBack(&v, 9);
    pushBack(&v, 8);
    assert(back(&v) != NULL);
}

void test_front_oneElementInVector(){
    vector v = createVector(0);
    pushBack(&v, 9);
    pushBack(&v, 8);
    assert(front(&v) != NULL);
}

void test_pushBack_fullVector(){
    vector v = createVector(4);
    for (int i = 0; i < 5; i++){
        pushBack(&v, i);
    }
    assert(v.data[4] == 4);
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

int getSum(int *a, int n){
    int s = 0;
    for (int i = 0; i < n; i++){
        s += a[i];
    }
    return s;
}

int main() {
    vector a = createVector(5);
    reserve(&a, 5);
    test_vector();
    return 0;
}
