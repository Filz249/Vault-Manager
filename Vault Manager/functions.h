#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include "dataType.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int displayMenu();
int displaySortMenu();
int displaySortOrderMenu();
int displaySearchMenu();
int displaySpecialAttributeMenu();

inline void clearInputBuffer();
inline void clearScreen();

inline int compareFirstName(const void* a, const void* b);
inline int compareLastName(const void* a, const void* b);
inline int compareVaultID(const void* a, const void* b);
inline int compareSpecialAttributeByIndex(const void* a, const void* b);
inline int compareSpecialAttributeByIndexDesc(const void* a, const void* b);

void createDweller(DWELLER** dwellers, int* count);
void readDwellers(DWELLER* dwellers, int count);
void updateDweller(DWELLER* dwellers, int count);
void deleteDweller(DWELLER** dwellers, int* count);
void saveToFile(DWELLER* dwellers, int count);
void loadFromFile(DWELLER** dwellers, int* count);
void sortDwellers(DWELLER* dwellers, int count, SortCriteria criteria, int ascending);
void searchDweller(DWELLER* dwellers, int count, SearchCriteria criteria);
void searchBySpecialAttributeDetailed(DWELLER* dwellers, int count);

const char* getSpecialAttributeName(int index);

int copyFile(const char* src, const char* dest);

extern int g_specialAttributeSortIndex;

#endif
