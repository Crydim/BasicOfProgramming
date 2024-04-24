#include "function__string.h"
#include "string_.h"
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

char _stringBuffer[MAX_STRING_SIZE + 1];

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

//2
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

//3
int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

//3
void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

//3
void stringDigitToStart(char *beginString){
    char *beginSearch = beginString;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {
        digitToStart(word);
        beginSearch = word.end;
    }
}

//3
void DigitsToEnd(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIf(_stringBuffer,
                               endStringBuffer,
                               word.begin, isalpha);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isdigit);
}

//3
void stringDigitsToEnd(char *beginString){
    char *beginSearch = beginString;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {
        DigitsToEnd(word);
        beginSearch = word.end;
    }
}

//3
bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    word->end = findNonSpaceReverse(rbegin, rend)+1;
    if (word->end == rend)
        return false;
    word->begin = findSpaceReverse(word->end, rend)+1;
    return true;
}

//4
void transformDigitsInSpace(char *s){
    char *recPtr = s;
    char stringS[MAX_STRING_SIZE+1];
    copy(s, getEndOfString(s)+1, stringS);
    char *readPtr = stringS;
    while (*readPtr != '\0'){
        if (isdigit(*readPtr)) {
            int digit = *readPtr - '0';
            for (int i = 0; i < digit; i++){
                *recPtr = ' ';
                recPtr++;
            }
        } else {
            *recPtr = *readPtr;
            recPtr++;
        }
        readPtr++;
    }
    *recPtr = '\0';
}

//5
int areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    char *begin1 = w1.begin;
    char *begin2 = w2.begin;
    while (begin1 != w1.end - 1 && *begin1 == *begin2){
        begin1++;
        begin2++;
    }
    return *begin1 - *begin2;
}

//5
void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    char *readPtr, *recPtr;
    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }
    WordDescriptor curWord;
    while (getWord(readPtr, &curWord)) {
        recPtr = copy(readPtr, curWord.begin, recPtr);
        if (areWordsEqual(curWord, word1) == 0) {
            recPtr = copy(word2.begin, word2.end, recPtr);
        } else {
            recPtr = copy(curWord.begin, curWord.end, recPtr);
        }
        readPtr = curWord.end;
    }
    *recPtr = '\0';
}

//6
bool areWordsOrdered(char *string) {
    WordDescriptor word1;
    WordDescriptor word2;
    if (getWord(string, &word1)) {
        word2 = word1;
        while (getWord(string, &word1)) {
            if (areWordsEqual(word1, word2) < 0)
                return false;
            word2 = word1;
            string = word1.end;
        }
        return true;
    } else{
        return true;
    }
}
