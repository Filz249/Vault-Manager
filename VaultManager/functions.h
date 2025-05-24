#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"

// KONCEPT 13.
extern void clearInputBuffer(void);
extern void clearScreen(void);
int isValidDate(int day, int month, int year);
void saveToFile(const DWELLER* const dwellers, const int count);
void loadFromFile(DWELLER** const dwellers, int* const count);
void swap(DWELLER* const a, DWELLER* const b);
void quickSort(DWELLER* const dwellers, const int low, const int high, const SORT_CR criteria, const int ascending);
int partition(DWELLER* const dwellers, const int low, const int high, const SORT_CR criteria, const int ascending);

int displayMenu(void);
int displaySortMenu(void);
int displaySortOrderMenu(void);
int displaySearchMenu(void);

void createDweller(DWELLER** const dwellers, int* const count);
void readDwellers(const DWELLER* const dwellers, const int count);
void updateDweller(DWELLER* const dwellers, const int count);
void sortDwellers(DWELLER* const dwellers, const int count, const SORT_CR criteria, const int ascending);
void searchDweller(const DWELLER* const dwellers, const int count, const SEARCH_CR criteria);
void deleteDweller(DWELLER** const dwellers, int* const count);



#endif
