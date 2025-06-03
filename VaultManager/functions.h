#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dataType.h"


//========================
//        KONCEPT 13.
//========================

void createDwellers(DWELLER** const dwellers, int* const count);
void readDwellers(const DWELLER* const dwellers, const int count);
void updateDwellers(DWELLER* const dwellers, const int count);
void sortDwellers(DWELLER* const dwellers, const int count, const SORT_CR criteria);
void searchDwellers(const DWELLER* const dwellers, const int count, const SEARCH_CR criteria);
void deleteDwellers(DWELLER** const dwellers, int* const count);

void saveToFile(const DWELLER* const dwellers, const int count);
void loadFromFile(DWELLER** const dwellers, int* const count);
extern void clearInputBuffer(void);
extern void clearScreen(void);
int displayMenu(void);
int displaySortMenu(void);
int displaySearchMenu(void);
int displayUpdateMenu(void);
int displayDeletionMenu();

int validDate(const int day, const int month, const int year);
int validName(const char* const name);
int validID(const DWELLER* const dwellers, const int count, const int id);

extern int totalDwellers;

void updateFirstName(DWELLER* const dweller);
void updateLastName(DWELLER* const dweller);
void updateAge(DWELLER* const dweller);
void updateHeight(DWELLER* const dweller);
void updateBirthDate(DWELLER* const dweller); 
void updateRegDate(DWELLER* const dweller);

void insertionSort(DWELLER* const dwellers, const int n, const SORT_CR criteria);

void removeDwellersFile();
void copyFile(const char* srcFileName, const char* destFileName);

#endif
