#include "function__string.h"
#include "matrix.h"
#include "string_.h"
#include <malloc.h>
#define MAX_FILE_SIZE 1024
#ifndef STRUCTURES_FUNCTION_FILES_H
#define STRUCTURES_FUNCTION_FILES_H

void assert_TXT(const char *file1, const char *file2, char const *funcName);

void copyFile(const char* sourceFile, const char* destinationFile);

//1
void transposeMatrixInFile(char *file);

//2
void transformNumbersWithFixedDotIntoNumbersWithFloatedDot(char *file);

//3
int operation(int a, int b, char symbol_operation);

//3
void calculateValueOfExpressionInFile(char *file);

//4
void deleteInFIleWordsWithoutGivenSymbols(char *file, char* symbols);

//5
void saveMaxWordInEachString(char *file);

//6
int pow_(int a, int n);

//6
void deletePolynomialsWithRootX(char *file, int x);

//7
void sortFileFirstPositiveNumbersSecondNegativeNumbers(char *file);

//8
void transposeIfNotSymmetricalSquareMatrixInFile(char *file, int n);

//9
void formTeamOfBestSportsmen(char *file, int n);

#endif //STRUCTURES_FUNCTION_FILES_H