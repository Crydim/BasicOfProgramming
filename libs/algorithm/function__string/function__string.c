#include "function__string.h"
#include "string_.h"

char* getEndOfString(char  *s){
    while (*s != '\0'){
        s++;
    }
    s--;
    return s;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void adjacentEqualLetters(char *s){
    char *prev = s;
    char *current = s+1;
    while (*current != '\0'){
        if (*prev != *current) {
            prev++;
            *prev = *current;
        }
        current++;
    }
    *(prev+1) = '\0';
}
