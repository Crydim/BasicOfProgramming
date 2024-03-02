#include <stdio.h>
#include "vector.h"

int main() {
    vector a = createVector(5);
    reserve(&a, 0);
    return 0;
}
