#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"

void clearInputBuffer(void);
void clearScreen(void);

int displayMenu(void);
int displaySortMenu(void);
int displaySortOrderMenu(void);
int displaySearchMenu(void);
int displayAttrMenu(void);
const char* getAttrName(int index);

void createDweller(DWELLER** dwellers, int* count);
void readDwellers(DWELLER* dwellers, int count);
void updateDweller(DWELLER* dwellers, int count);
void deleteDweller(DWELLER** dwellers, int* count);
void saveToFile(DWELLER* dwellers, int count);
void loadFromFile(DWELLER** dwellers, int* count);
void sortDwellers(DWELLER* dwellers, int count, SORT_CR criteria, int asc);
void searchDweller(DWELLER* dwellers, int count, SEARCH_CR criteria);

#endif
