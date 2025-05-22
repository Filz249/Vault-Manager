#ifndef DATATYPE_H
#define DATATYPE_H
#define _CRT_SECURE_NO_WARNINGS

#define MAX_NAME 50
#define MAX_DWELLERS 100
#define MAX_POINTS 40
#define MAX_ATTR 10
#define MIN_ATTR 1

typedef struct {
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];
    int specAttr[7];
    float health;
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
    SORT_ATTR
} SORT_CR;

typedef enum {
    SEARCH_FIRST,
    SEARCH_LAST,
    SEARCH_ID,
    SEARCH_ATTR
} SEARCH_CR;

#endif
