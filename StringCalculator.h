#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H
 
#include "StringCalculator.h"
#include <stdbool.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int handleDelimiter(const char** numbers, char* delimiter);
static int parseNumber(const char** numbers, char delimiter);
static void throwIfNegative(int number, int* negatives, int* negCount);

int add(const char* numbers) {
    if (numbers == NULL || strlen(numbers) == 0) {
        return 0;
    }

    const char* ptr = numbers;
    char delimiter = ',';
    int result = 0;
    int negatives[100];
    int negCount = 0;

    ptr += handleDelimiter(&ptr, &delimiter);

    while (*ptr != '\0') {
        int number = parseNumber(&ptr, delimiter);
        throwIfNegative(number, negatives, &negCount);

        if (number <= 1000) {
            result += number;
        }

        if (*ptr == delimiter || *ptr == '\n') {
            ptr++;
        }
    }

    if (negCount > 0) {
        char message[100];
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

    return result;
}

static int handleDelimiter(const char** numbers, char* delimiter) {
    if (**numbers == '/' && *(*numbers + 1) == '/') {
        *delimiter = *(*numbers + 2);
        return 4;
    }
    return 0;
}

static int parseNumber(const char** numbers, char delimiter) {
    char buffer[100];
    int i = 0;
    while (**numbers != '\0' && **numbers != delimiter && **numbers != '\n') {
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
#endif
