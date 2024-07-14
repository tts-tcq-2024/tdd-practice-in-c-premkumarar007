#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H
 
#include "StringCalculator.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void parseDelimiter(const char** numbers, char* delimiter, int* offset);
static bool isDelimiter(char c, char delimiter);
static int calculateSum(const char** numbers, char delimiter, int* negCount, int* negatives);
static void handleSingleNumber(const char** numbers, char delimiter, int* result, int* negCount, int* negatives);
static int parseNumber(const char** numbers, char delimiter);
static void throwIfNegative(int number, int* negatives, int* negCount);
static void checkAndHandleNegatives(int* negatives, int negCount);

int add(const char* numbers) {
    if (numbers == NULL || strlen(numbers) == 0) {
        return 0;
    }

    const char* ptr = numbers;
    char delimiter = ',';
    int offset = 0;
    int result = 0;
    int negatives[100];
    int negCount = 0;

    parseDelimiter(&ptr, &delimiter, &offset);
    ptr += offset;

    result = calculateSum(&ptr, delimiter, &negCount, negatives);

    checkAndHandleNegatives(negatives, negCount);

    return result;
}

static void parseDelimiter(const char** numbers, char* delimiter, int* offset) {
    if (**numbers == '/' && *(*numbers + 1) == '/') {
        *delimiter = *(*numbers + 2);
        *offset = 4;
    } else {
        *offset = 0;
    }
}

static bool isDelimiter(char c, char delimiter) {
    return c == delimiter || c == '\n';
}

static int calculateSum(const char** numbers, char delimiter, int* negCount, int* negatives) {
    int result = 0;

    while (**numbers != '\0') {
        handleSingleNumber(numbers, delimiter, &result, negCount, negatives);

        if (isDelimiter(**numbers, delimiter)) {
            (*numbers)++;
        }
    }

    return result;
}

static void handleSingleNumber(const char** numbers, char delimiter, int* result, int* negCount, int* negatives) {
    int number = parseNumber(numbers, delimiter);
    throwIfNegative(number, negatives, negCount);

    if (number <= 1000) {
        *result += number;
    }
}

static int parseNumber(const char** numbers, char delimiter) {
    char buffer[100];
    int i = 0;
    while (**numbers != '\0' && !isDelimiter(**numbers, delimiter)) {
        buffer[i++] = **numbers;
        (*numbers)++;
    }
    buffer[i] = '\0';
    return atoi(buffer);
}

static void throwIfNegative(int number, int* negatives, int* negCount) {
    if (number < 0) {
        negatives[*negCount] = number;
        (*negCount)++;
    }
}

static void checkAndHandleNegatives(int* negatives, int negCount) {
    if (negCount > 0) {
        char message[200];
        sprintf(message, "negatives not allowed: ");
        for (int i = 0; i < negCount; i++) {
            char buffer[12];
            sprintf(buffer, "%d", negatives[i]);
            strcat(message, buffer);
            if (i < negCount - 1) {
                strcat(message, ",");
            }
        }
        fprintf(stderr, "%s\n", message);
        exit(EXIT_FAILURE);
    }
}


#endif
