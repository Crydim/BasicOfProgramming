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

//12
void wordDescriptorToString(WordDescriptor word, char *destination) {
    *copy(word.begin, word.end, destination) = '\0';
}

//12
WordDescriptor lastWordInFirstStringIsInSecondString(char *string1, char *string2) {
    getBagOfWords(&_bag, string1);
    for (int i = _bag.size - 1; i >= 0; --i) {
        char *beginSearch = string2;
        WordDescriptor wordSting2;
        while(getWord(beginSearch, &wordSting2)) {
            if (areWordsEqual(_bag.words[i], wordSting2) == 0) {
                return _bag.words[i];
            }
            beginSearch = wordSting2.end;
        }
    }
    WordDescriptor word = {NULL, NULL};
    return word;
}

//13
bool isStringHasEqualWords(char *s){
    getBagOfWords(&_bag, s);
    char *beginSearch = s;
    WordDescriptor word;
    int counter = 0;
    while(getWord(beginSearch, &word)){
        for (int i = 0; i < _bag.size; i++){
            if (areWordsEqual(_bag.words[i], word) == 0 && i != counter){
                return true;
            }
        }
        counter++;
        beginSearch = word.end;
    }
    return false;
}

//14
int cmp(const void *a, const void *b) {
    return *(const char *) a - *(const char *) b;
}

//14
bool haveWordsMadeUpSameLetters(char *s) {
    *copy(s, getEndOfString(s)+1, _stringBuffer) = '\0';
    getBagOfWords(&_bag, _stringBuffer);
    for (size_t i = 0; i < _bag.size; i++)
        qsort(_bag.words[i].begin, _bag.words[i].end - _bag.words[i].begin,
              sizeof(char), cmp);
    return isStringHasEqualWords(_stringBuffer);
}

//15
void getStringWithoutLastWordAndSamesWithLast(char *s){
    WordDescriptor lastWord, word;
    if (!getWordReverse(getEndOfString(s), s-1, &lastWord)){
        return;
    }
    char *beginSearch = s;
    while (getWord(beginSearch, &word)){
        if (areWordsEqual(lastWord, word) != 0){
            s = copy(word.begin, word.end, s);
            *s++ = ' ';
        }
        beginSearch = word.end;
    }
    if (findNonSpace(s) != '\0'){
        s--;
    }
    *s = '\0';
}

//16
WordDescriptor findWordPreviousFirstWordInString1InString2(char *string1, char *string2){
    getBagOfWords(&_bag, string1);
    getBagOfWords(&_bag2, string2);
    WordDescriptor word = {NULL, NULL};
    int condition = -1;
    for (int i = 0; i < _bag.size; i++){
        for (int j = 0; j < _bag2.size; j++){
            condition = areWordsEqual(_bag.words[i], _bag2.words[j]);
            if (condition == 0){
                if (i != 0){
                    return _bag.words[i-1];
                }
                break;
            }
        }
        if (condition == 0){
            break;
        }
    }
    return word;
}

//17
void removePalindromes(char *s){
    char *beginSearch = s;
    char *result = _stringBuffer;
    char *beginCopy = result;
    WordDescriptor word;
    while(getWord(beginSearch, &word)){
        if (!isPalindrome(word.begin, word.end-1)){
            result = copy(word.begin, word.end, result);
            *result++ = ' ';
        }
        beginSearch = word.end;
    }
    s = copy(beginCopy, result, s);
    s--;
    *s = '\0';
}

//18
void addStringWithLowerCountWords(char *s1, char *s2){
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);
    if (_bag.size > _bag2.size){
        s2 = _bag2.words[_bag2.size-1].end;
        *s2++ = ' ';
        for (int i = _bag2.size; i < _bag.size; i++){
            s2 = copy(_bag.words[i].begin, _bag.words[i].end, s2);
            *s2++ = ' ';
        }
        s2--;
        *s2 = '\0';
    } else if (_bag.size < _bag2.size){
        s1 = _bag.words[_bag.size-1].end;
        *s1++ = ' ';
        for (int i = _bag.size; i < _bag2.size; i++){
            s1 = copy(_bag2.words[i].begin, _bag2.words[i].end, s1);
            *s1++ = ' ';
        }
        s1--;
        *s1 = '\0';
    }
}

//19
bool isStringHasAllLettersWord(char *s, WordDescriptor word){
    char *beginSearch = s;
    char *beginSearchLetters = s;
    WordDescriptor words;
    if (*s == '\0' || *word.begin == '\0'){
        return false;
    }
    while(getWord(beginSearch, &words)){
        s = copy(words.begin, words.end, s);
        beginSearch = words.end;
    }
    *s = '\0';
    char wordLetters[MAX_STRING_SIZE];
    char *beginSearchLettersInWord = wordLetters;
    wordDescriptorToString(word, wordLetters);
    qsort(beginSearchLetters, getEndOfString(s)+1-beginSearchLetters, sizeof(char ), cmp);
    qsort(wordLetters, getEndOfString(wordLetters)+1-wordLetters, sizeof(char ), cmp);
    int counter = 0;
    adjacentEqualLetters(beginSearch);
    adjacentEqualLetters(beginSearchLettersInWord);
    while(*beginSearchLetters != '\0' && *beginSearchLettersInWord != '\0'){
        if (*beginSearchLetters > *beginSearchLettersInWord){
            beginSearchLettersInWord++;
        } else if (*beginSearchLetters < *beginSearchLettersInWord){
            beginSearchLetters++;
        } else {
            beginSearchLetters++;
            beginSearchLettersInWord++;
            counter++;
        }
    }
    return strlen_(wordLetters) == counter;
}