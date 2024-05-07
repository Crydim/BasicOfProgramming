#include "string_.h"
#include "matrix.h"
#define MAX_FILE_SIZE 1024
#ifndef STRUCTURES_FUNCTION_FILES_H
#define STRUCTURES_FUNCTION_FILES_H

void assert_TXT(const char *file1, const char *file2, char const *funcName);

void copyFile(const char* sourceFile, const char* destinationFile);

//1
void transposeMatrixInFile(char *file);

#endif //STRUCTURES_FUNCTION_FILES_H
