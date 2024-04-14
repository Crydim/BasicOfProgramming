#include "string_.h"

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char* findNonSpace(char *begin){
    while(*begin != '\0' && isspace(*begin)){
        begin++;
    }
    return begin;
}

char* findSpace(char *begin){
    while(*begin != '\0' && !isspace(*begin)){
        begin++;
    }
    return begin;
}

char* findNonSpaceReverse(char *rbegin, const char *rend){
    while(rbegin != rend && isspace(*rbegin)){
        rbegin--;
    }
    return rbegin;
}

char* findSpaceReverse(char *rbegin, const char *rend){
    while(rbegin != rend && !isspace(*rbegin)){
        rbegin--;
    }
    return rbegin;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs  && (*lhs == *rhs)) {
        lhs++;
        rhs++;
    }
    return *(unsigned char *)lhs - *(unsigned char *)rhs;
}

char* copy(const char *beginSource, const char *endSource, char *beginDestination) {
    memcpy(beginDestination, beginSource, endSource - beginSource);
    return beginDestination + (endSource - beginSource);
}

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    char *pSrc = beginSource;
    char *pDest = beginDestination;
    while (pSrc != endSource) {
        if (f(*pSrc)) {
            memcpy(pDest, pSrc, 1);
            pDest++;
        }
        pSrc++;
    }
    return pDest;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    while (rbeginSource != rendSource){
        if (f(*rbeginSource)){
            memcpy(beginDestination, rbeginSource, 1);
            beginDestination++;
        }
        rbeginSource--;
    }
    return beginDestination;
}