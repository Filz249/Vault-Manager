#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "dataType.h"

// KONCEPTI 13. I 14.


//  glavne funkcije
void createDwellers(DWELLER** const dwellers, int* const count);
void readDwellers(const DWELLER* const dwellers, const int count);
void updateDwellers(DWELLER* const dwellers, const int count);
void sortDwellers(DWELLER* const dwellers, const int count, const SORT_CR criteria);
void searchDwellers(const DWELLER* const dwellers, const int count, const SEARCH_CR criteria);
void deletion(DWELLER** const dwellers, int* const count);
void saveToFile(const DWELLER* const dwellers, const int count);
void loadFromFile(DWELLER** const dwellers, int* const count);
void deleteOption(DWELLER** const dwellers, int* const count);

// podfunkcije
extern void clearInputBuffer(void);
extern void clearScreen(void);
void printDwellerInfo(const DWELLER* dweller);
extern int fileDeleted;

// meni, pod-meni
int displayMenu(void);
int displaySortMenu(void);
int displaySearchMenu(void);
int displayUpdateMenu(void);
int displayDeletionMenu();

// provjera 
int validDate(const int day, const int month, const int year);
int validName(const char* const name);
int validID(const DWELLER* const dwellers, const int count, const int id);
void getCurrentDate(int* day, int* month, int* year);
int validRegDate(const DATE* birthDate, const DATE* regDate);
int calculateAge(const DATE* birthDate);
int readInput(const char* input, void* value, const char* data, int minInt, int maxInt, float minFloat, float maxFloat);

// funkcije ažuriranja
void updateFirstName(DWELLER* const dweller);
void updateLastName(DWELLER* const dweller);
void updateHeight(DWELLER* const dweller);
void updateBirthDate(DWELLER* const dweller); 
void updateRegDate(DWELLER* const dweller);

//sortiranje
void insertionSort(DWELLER* const dwellers, const int n, const SORT_CR criteria);

#endif