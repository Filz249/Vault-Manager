#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"


int displayMenu(void);
int displaySortMenu(void);
int displaySortOrderMenu(void);
int displaySearchMenu(void);
int displayAttrMenu(void);

void createDweller(DWELLER** dwellers, int* count);
void readDwellers(DWELLER* dwellers, int count);
void updateDweller(DWELLER* dwellers, int count);
void deleteDweller(DWELLER** dwellers, int* count);
void saveToFile(DWELLER* dwellers, int count);
void loadFromFile(DWELLER** dwellers, int* count);
void sortDwellers(DWELLER* dwellers, int count, SortCriteria criteria, int asc);
void searchDweller(DWELLER* dwellers, int count, SearchCriteria criteria);
void searchByAttr(DWELLER* dwellers, int count);
void clearInputBuffer(void);
void clearScreen(void);
const char* getAttrName(int index);

#endif 
