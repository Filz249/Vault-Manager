#pragma once
#ifndef DATATYPE_H
#define DATATYPE_H
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME 20 // KONCEPT 15.
#define MAX_DWELLERS 20 // KONCEPT 15.

typedef struct {
    int day;
    int month;
    int year;
} DATE;

typedef struct {
    char firstName[MAX_NAME]; // KONCEPT 2. 
    char lastName[MAX_NAME];
    int age;
    float height; 
    DATE birthDate;
    DATE regDate;
    int id;
} DWELLER; // KONCEPT 3.

typedef enum { 
    CREATE = 1,
    READ,
    UPDATE,
    SEARCH,
    SORT,
    DELETE,
    EXIT
} CHOICE;  // KONCEPT 4.

typedef enum {
    UPDATE_FIRST_NAME = 1,
    UPDATE_LAST_NAME,
    UPDATE_AGE,
    UPDATE_HEIGHT,
    UPDATE_BIRTH_DATE,
    UPDATE_REG_DATE,
    UPDATE_EXIT
} UPDATE_CR;

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

 // KONCEPT 26.
typedef void (*UPDATE_CH)(DWELLER*);

extern int totalDwellers;

#endif