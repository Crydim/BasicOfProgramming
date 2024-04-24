#include "string.h"
#include <stdbool.h>
#include <stdio.h>

#ifndef STRUCTURES_FUNCTION__STRING_H
#define STRUCTURES_FUNCTION__STRING_H

char* getEndOfString(char  *s);

void removeNonLetters(char *s);

//2
void adjacentEqualLetters(char *s);

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символ слова
} WordDescriptor;

int getWord(char *beginSearch, WordDescriptor *word);

void digitToStart(WordDescriptor word);

void stringDigitToStart(char *beginString);

//3
void DigitsToEnd(WordDescriptor word);

//3
void stringDigitsToEnd(char *beginString);

//3
bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word);

//4
void transformDigitsInSpace(char *s);

#endif //STRUCTURES_FUNCTION__STRING_H
