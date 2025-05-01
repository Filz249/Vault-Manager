#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#ifndef DATATYPE_H
#define DATATYPE_H

#define MAX_NAME_LENGTH 50
#define MAX_VAULT_RESIDENTS 100
#define MAX_SPECIAL_POINTS 40
#define MAX_SPECIAL_ATTRIBUTE 10
#define MIN_SPECIAL_ATTRIBUTE 1

typedef struct {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int specialAttributes[7];
    float health;
    int vaultID;
} DWELLER;

typedef enum {
    CREATE = 1,
    READ,
    UPDATE,
    SEARCH,
    SORT,
    DELETE,
    EXIT
} MenuOption;

typedef enum {
    SORT_BY_FIRST_NAME,
    SORT_BY_LAST_NAME,
    SORT_BY_VAULT_ID,
    SORT_BY_SPECIAL_ATTRIBUTE
} SortCriteria;

typedef enum {
    SEARCH_BY_FIRST_NAME,
    SEARCH_BY_LAST_NAME,
    SEARCH_BY_VAULT_ID,
    SEARCH_BY_SPECIAL_ATTRIBUTE
}SearchCriteria;

#endif
