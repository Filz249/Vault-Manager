#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_VAULT_RESIDENTS 100
#define MAX_SPECIAL_POINTS 40
#define MAX_SPECIAL_ATTRIBUTE 10
#define MIN_SPECIAL_ATTRIBUTE 1

typedef struct {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int specialAttributes[7];
    int health;
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
} SearchCriteria;

// Function prototypes
int displayMenu(void);
int displaySortMenu(void);
int displaySortOrderMenu(void);
int displaySearchMenu(void);
int displaySpecialAttributeMenu(void);
void createDweller(DWELLER** dwellers, int* count);
void readDwellers(DWELLER* dwellers, int count);
void updateDweller(DWELLER* dwellers, int count);
void deleteDweller(DWELLER** dwellers, int* count);
void saveToFile(DWELLER* dwellers, int count);
void loadFromFile(DWELLER** dwellers, int* count);
void sortDwellers(DWELLER* dwellers, int count, SortCriteria criteria, int ascending);
int compareFirstName(const void* a, const void* b);
int compareLastName(const void* a, const void* b);
int compareVaultID(const void* a, const void* b);
int compareSpecialAttributeByIndex(const void* a, const void* b);
int compareSpecialAttributeByIndexDesc(const void* a, const void* b);
void searchDweller(DWELLER* dwellers, int count, SearchCriteria criteria);
void searchBySpecialAttributeDetailed(DWELLER* dwellers, int count);
void clearInputBuffer(void);
void clearScreen(void);
const char* getSpecialAttributeName(int index);

#endif 
