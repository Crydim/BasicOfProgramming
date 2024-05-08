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

//3
int operation(int a, int b, char symbol_operation){
    if (symbol_operation == '+'){
        return a+b;
    }
    if (symbol_operation == '-'){
        return a-b;
    }
    if (symbol_operation == '*'){
        return a*b;
    }
    if (symbol_operation == '/'){
        return a/b;
    }
}

//3
void calculateValueOfExpressionInFile(char *file){
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(-3);
    }
    int numbers[5];
    int quantity_numbers = 0;
    char operations[2];
    int quantity_operations = 0;
    int numbers_and_operations_in_file = 0;
    while(!feof(fp)){
        if (numbers_and_operations_in_file % 2 == 0){
            fscanf(fp, "%d ", &numbers[quantity_numbers++]);
        } else {
            fscanf(fp, "%c ", &operations[quantity_operations++]);
        }
        numbers_and_operations_in_file++;
    }
    fclose(fp);
    fp = fopen(file, "a");
    if (quantity_operations > 1){
        int result = 0;
        if ((operations[1] == '/' || operations[1] == '*') && operations[0] != '*' && operations[0] != '/'){
            result = operation(numbers[1], numbers[2], operations[1]);
            result = operation(numbers[0], result, operations[0]);
        } else {
            result = operation(numbers[0], numbers[1], operations[0]);
            result = operation(result, numbers[2], operations[1]);
        }
        fprintf(fp, " = %d", result);
    } else {
        fprintf(fp, " = %d", operation(numbers[0], numbers[1], operations[0]));
    }
    fclose(fp);
}

//4
void deleteInFIleWordsWithoutGivenSymbols(char *file, char* symbols){
    FILE* fp;
    fp = fopen(file, "r");
    if (fp == NULL){
        printf("%d", 1);
        return;
    }
    char str_file[MAX_STRING_SIZE];
    fgets(str_file, MAX_STRING_SIZE, fp);
    fclose(fp);
    fp = fopen(file, "w");
    WordDescriptor word;
    char *beginSearch = str_file;
    while (getWord(beginSearch, &word)){
        bool has_symbols = true;
        for (char *i = symbols; i < symbols+strlen(symbols); i++){
            bool is_find = false;
            for (char *j = word.begin; j < word.end; j++){
                if (*j == *i){
                    is_find = true;
                    break;
                }
            }
            if (!is_find){
                has_symbols = false;
                break;
            }
        }
        if (has_symbols){
            for (char *j = word.begin; j < word.end; j++){
                fputc(*j, fp);
            }
            fputc(' ', fp);
        }
        beginSearch = word.end;
    }
    fclose(fp);
}

//5
void saveMaxWordInEachString(char *file){
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(-3);
    }
    char buffer[MAX_STRING_SIZE];
    char *beginCopy = buffer;
    char *beginRemember = buffer;
    while(!feof(fp)){
        char str[100];
        fgets(str, 99, fp);
        long long max = 0;
        char max_str[30];
        WordDescriptor word;
        char *ptr = str;
        while(getWord(ptr, &word)){
            if(word.end - word.begin > max){
                wordDescriptorToString(word, max_str);
                max = word.end - word.begin;
            }
            ptr = word.end;
        }
        beginRemember = copy(max_str, getEndOfString(max_str)+1, beginRemember);
        *beginRemember++ = ' ';
    }
    *beginRemember = '\0';
    fclose(fp);
    FILE *fpw = fopen(file, "w");
    WordDescriptor word;
    while (getWord(beginCopy, &word)){
        char max_str[MAX_WORD_SIZE];
        wordDescriptorToString(word, max_str);
        fputs(max_str, fpw);
        fputs("\n", fpw);
        beginCopy = word.end;
    }
    fclose(fpw);
}

//6
int pow_(int a, int n) {
    int result = 1;
    while (n > 0) {
        result *= a;
        n--;
    }
    return result;
}

//6
typedef struct{
    int degree;
    int coefficient;
} polynomial;

//6
void deletePolynomialsWithRootX(char *file, int x){
    FILE *fp, *result;
    fp = fopen(file, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(-3);
    }
    result = fopen("task6.txt", "wb");
    if (result == NULL) {
        printf("Error opening file\n");
        exit(-3);
    }
    while(!feof(fp)){
        polynomial poly;
        int sum = 0;
        polynomial polys[100];
        int size_polys = 0;
        while (fread(&poly, sizeof (poly), 1, fp)){
            polys[size_polys++] = poly;
            int n = poly.degree;
            sum += poly.coefficient * (pow_(x, n));
            if (!n){
                break;
            }
        }
        if (sum != 0){
            for (int i = 0; i < size_polys; i++){
                fwrite(&polys[i], sizeof (polys[i]), 1, result);
            }
        }
    }
    copyFile("task6.txt", file);
    fclose(result);
    fclose(fp);
}

//7
void sortFileFirstPositiveNumbersSecondNegativeNumbers(char *file){
    FILE *fp, *result;
    fp = fopen(file, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(-3);
    }
    result = fopen("task7.txt", "wb");
    if (result == NULL) {
        printf("Error opening file\n");
        exit(-3);
    }
    int positive[1000];
    int quantity_positive = 0;
    int negative[1000];
    int quantity_negative = 0;
    while(!feof(fp)){
        int number;
        fread(&number, sizeof(number), 1, fp);
        if(number >= 0)
            positive[quantity_positive++] = number;
        else
            negative[quantity_negative++] = number;
    }
    fclose(fp);
    for(int i = 0; i < quantity_positive; i++)
        fwrite(&positive[i], sizeof(positive[i]), 1, result);
    for(int i = 0; i < quantity_negative; i++)
        fwrite(&negative[i], sizeof(negative[i]), 1, result);
    copyFile("task7.txt", file);
    fclose(fp);
    fclose(result);
}