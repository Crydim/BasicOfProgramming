#include "function_files.h"
#include <stdio.h>
#include <stdbool.h>

void assert_TXT(const char *file1, const char *file2, char const *funcName) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (f1 == NULL || f2 == NULL) {
        printf("Error\n");
        return;
    }
    char buffer1[MAX_FILE_SIZE];
    char buffer2[MAX_FILE_SIZE];
    while (fgets(buffer1, MAX_FILE_SIZE, f1) != NULL
           && fgets(buffer2, MAX_FILE_SIZE, f2) != NULL) {
        if (strcmp(buffer1, buffer2) != 0) {
            printf("Files is not similar\n");
            fclose(f1);
            fclose(f2);
            return;
        }
    }
    printf("Testing %s - passed\n", funcName);
}

void copyFile(const char* sourceFile, const char* destinationFile) {
    FILE *source, *destination;
    char ch;
    source = fopen(sourceFile, "r");
    if (source == NULL) {
        printf("Source file could not be opened\n");
        return;
    }
    destination = fopen(destinationFile, "w");
    if (destination == NULL) {
        printf("Destination file could not be opened\n");
        fclose(source);
        return;
    }
    while ((ch = fgetc(source)) != EOF)
        fputc(ch, destination);
    fclose(source);
    fclose(destination);
}

//1
void transposeMatrixInFile(char *file){
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("File opening error\n");
        return;
    }
    FILE *result_file = fopen("task1.txt", "w");
    if (result_file == NULL) {
        printf("File creation error\n");
        return;
    }
    int n;
    while (fscanf(fp, "%d", &n) == 1) {
        int matrix[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                fscanf(fp, "%d", &matrix[i][j]);
        fprintf(result_file, "%d ", n);
        for (int j = 0; j < n; j++)
            for (int i = 0; i < n; i++)
                fprintf(result_file, "%d ", matrix[i][j]);
    }
    fclose(fp);
    fclose(result_file);
    copyFile("task1.txt", file);

}

//2
void transformNumbersWithFixedDotIntoNumbersWithFloatedDot(char *file){
    FILE* fp, *result;
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("File opening error\n");
        return;
    }
    result = fopen("task2.txt", "w");
    if (result == NULL) {
        printf("File creation error\n");
        return;
    }
    while (!feof(fp)){
        float n;
        fscanf(fp, "%f ", &n);
        if (feof(fp)){
            break;
        }
        fprintf(result, "%.2f ", n);
    }
    copyFile("task2.txt", file);
    fclose(result);
    fclose(fp);
}