#include "function__string.h"
#include "string_.h"
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

char _stringBuffer[MAX_STRING_SIZE + 1];
BagOfWords _bag;
BagOfWords _bag2;

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

//7
void getBagOfWords(BagOfWords *bag, char *s) {
    bag->size = 0;
    WordDescriptor w;
    char *beginSearch = s;
    while (getWord(beginSearch, &w)) {
        bag->words[bag->size++] = w;
        beginSearch = w.end;
    }
}

//7
void printWord(WordDescriptor word) {
    while (word.begin != word.end) {
        putchar(*word.begin);
        word.begin++;
    }
    printf("\n");
}

//7
void printWordsInReverseOrder(char *s) {
    getBagOfWords(&_bag, s);
    for (int i = _bag.size - 1; i >= 0; i--) {
        printWord(_bag.words[i]);
    }
}

//8
bool isPalindrome(char *begin, char *end) {
    while (begin < end) {
        if (*begin != *end)
            return false;
        begin++;
        end--;
    }
    return true;
}

//8
int countWordsPalindromes(char *s) {
    int palindromes = 0;
    char *endS = getEndOfString(s)+1;
    char *commaPosition = find(s, endS, ',');
    char *lastWord = findNonSpaceReverse(endS, s);
    char *currentPosition = findNonSpace(s);
    while (*currentPosition != '\0') {
        if (*commaPosition == '\0') {
            palindromes += isPalindrome(currentPosition,lastWord - 1);
            currentPosition = endS;
        } else {
            palindromes += isPalindrome(currentPosition, commaPosition - 1);
            currentPosition = commaPosition+1;
            commaPosition = find(currentPosition, endS, ',');
        }
    }
    return palindromes;
}

//9
char *alternatingWordsInString(char *string1, char *string2, char *s) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginCopy = s;
    char *beginSearch1 = string1, *beginSearch2 = string2;
    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {
        if (isW1Found) {
            s = copy(word1.begin, word1.end, s);
            *s++ = ' ';
            beginSearch1 = word1.end;
        }
        if (isW2Found) {
            s = copy(word2.begin, word2.end, s);
            *s++ = ' ';
            beginSearch2 = word2.end;
        }
    }
    if (s != beginCopy)
        --s;
    *s = '\0';
    return beginCopy;
}

//10
void reverseWordOrder(char *string) {
    *copy(string, getEndOfString(string)+1, _stringBuffer) = '\0';
    getBagOfWords(&_bag, _stringBuffer);
    char *beginSearch = string;
    for (int i = _bag.size - 1; i >= 0; --i) {
        string = copy(_bag.words[i].begin, _bag.words[i].end, string);
        *string++ = ' ';
    }
    if (string != beginSearch)
        --string;
    *string = '\0';
}

//11
WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, char **beginWordBefore, char **endWordBefore) {
    WordDescriptor word;
    char *begin = s;
    WordDescriptor nextWord;
    if (!getWord(begin, &word))
        return EMPTY_STRING;
    else if (find(word.begin, word.end, 'A') != word.end || find(word.begin, word.end, 'a') != word.end)
        return FIRST_WORD_WITH_A;
    while (getWord(begin, &nextWord)) {
        if (find(nextWord.begin, nextWord.end, 'A') != nextWord.end ||
            find(nextWord.begin, nextWord.end, 'a') != nextWord.end) {
            *beginWordBefore = word.begin;
            *endWordBefore = word.end;
            return WORD_FOUND;
        }
        begin = word.end;
        word = nextWord;
    }
    return NOT_FOUND_A_WORD_WITH_A;
}