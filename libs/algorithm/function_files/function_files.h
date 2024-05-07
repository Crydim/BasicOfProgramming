#include "function__string.h"
#include "matrix.h"
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

#endif //STRUCTURES_FUNCTION_FILES_H
