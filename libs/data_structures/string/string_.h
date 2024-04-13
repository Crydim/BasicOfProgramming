#ifndef STRUCTURES_STRING__H
#define STRUCTURES_STRING__H

# include <stddef.h>
#include <ctype.h>

size_t strlen_(const char *begin);

char* find(char *begin, char *end, int ch);

char* findNonSpace(char *begin);

char* findSpace(char *begin);

char* findNonSpaceReverse(char *rbegin, const char *rend);

#endif //STRUCTURES_STRING__H
