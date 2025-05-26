#ifndef DATATYPE_H
#define DATATYPE_H
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#define MAX_NAME 20
#define MAX_DWELLERS 20

// KONCEPT 4 I 13.
typedef struct {
    int day;
    int month;
    int year;
} DATE;

typedef struct {
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];
    int age;
    float height;
    DATE birthDate;
    DATE regDate;
    int id;
} DWELLER;

typedef enum {
    CREATE = 1,
    READ,
    UPDATE,
    SEARCH,
    SORT,
    DELETE,
    EXIT
} CHOICE;

typedef enum {
    SORT_FIRST,
    SORT_LAST,
    SORT_AGE,
    SORT_HEIGHT,
    SORT_BIRTH_DATE,
    SORT_REG_DATE
} SORT_CR;

typedef enum {
    SEARCH_FIRST,
    SEARCH_LAST,
    SEARCH_ID,
    SEARCH_AGE
} SEARCH_CR;

#endif
