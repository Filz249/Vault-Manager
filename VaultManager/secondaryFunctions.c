#include "functions.h"
#include "dataType.h"

extern void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

extern void clearScreen(void) {
    printf("\033[H\033[J");
}

//KONCEPT 1
void saveToFile(const DWELLER* const dwellers, const int count) {
    FILE* file = fopen("dwellers.txt", "w");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "First name: %s\nLast name: %s\nAge: %d\nHeight(cm): %.2f\nDate of birth: %02d/%02d/%04d\nDate of registration: %02d/%02d/%04d\nID: %d\n\n",
            dwellers[i].firstName,
            dwellers[i].lastName,
            dwellers[i].age,
            dwellers[i].height,
            dwellers[i].birthDate.day,
            dwellers[i].birthDate.month,
            dwellers[i].birthDate.year,
            dwellers[i].regDate.day,
            dwellers[i].regDate.month,
            dwellers[i].regDate.year,
            dwellers[i].id);
    }

    fclose(file);
}

void loadFromFile(DWELLER** const dwellers, int* const count) {
    FILE* file = fopen("dwellers.txt", "r");
    if (!file) {
        *count = 0;
        *dwellers = NULL;
        return;
    }

    *dwellers = malloc(MAX_DWELLERS * sizeof(DWELLER));
    if (!*dwellers) {
        perror("Failed to allocate memory");
        fclose(file);
        free(*dwellers);
        exit(EXIT_FAILURE);
    }


    *count = 0;
    while (fscanf(file, "First name: %49s\nLast name: %49s\nAge: %d\nHeight(cm): %f\nDate of birth: %d/%d/%d\nDate of registration: %d/%d/%d\nID: %d\n\n",
        (*dwellers)[*count].firstName,
        (*dwellers)[*count].lastName,
        &(*dwellers)[*count].age,
        &(*dwellers)[*count].height,
        &(*dwellers)[*count].birthDate.day,
        &(*dwellers)[*count].birthDate.month,
        &(*dwellers)[*count].birthDate.year,
        &(*dwellers)[*count].regDate.day,
        &(*dwellers)[*count].regDate.month,
        &(*dwellers)[*count].regDate.year,
        &(*dwellers)[*count].id) == 11) {
        (*count)++;
        if (*count >= MAX_DWELLERS) {
            break;
        }
    }

    fclose(file);
}

int isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) {
        return 0;
    }
    if (day < 1 || day > 31) {
        return 0;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return 0;
    }
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) return 0;
        }else {
            if (day > 28) return 0;
        }
    }
    return 1; 
}

// KONCEPT 9.
inline void swap(DWELLER* const a, DWELLER* const b) {
    DWELLER temp = *a;
    *a = *b;
    *b = temp;
}

// KONCEPT 25.
void quickSort(DWELLER* const dwellers, const int low, const int high, const SORT_CR criteria, const int ascending) {
    if (low < high) {
        int pi = partition(dwellers, low, high, criteria, ascending);
        quickSort(dwellers, low, pi - 1, criteria, ascending);
        quickSort(dwellers, pi + 1, high, criteria, ascending);
    }
}

int partition(DWELLER* const dwellers, const int low, const int high, const SORT_CR criteria, const int ascending) {
    DWELLER pivot = dwellers[high];
    int i = low - 1; 

    for (int j = low; j < high; j++) {
        int comparison = 0;
        switch (criteria) {
        case SORT_FIRST:
            comparison = strcmp(dwellers[j].firstName, pivot.firstName);
            break;
        case SORT_LAST:
            comparison = strcmp(dwellers[j].lastName, pivot.lastName);
            break;
        case SORT_AGE:
            comparison = dwellers[j].age - pivot.age;
            break;
        case SORT_HEIGHT:
            comparison = (dwellers[j].height > pivot.height) ? 1 : -1;
            break;
        case SORT_BIRTH_DATE:
            comparison = (dwellers[j].birthDate.year != pivot.birthDate.year) ?
                (dwellers[j].birthDate.year - pivot.birthDate.year) :
                (dwellers[j].birthDate.month != pivot.birthDate.month) ?
                (dwellers[j].birthDate.month - pivot.birthDate.month) :
                (dwellers[j].birthDate.day - pivot.birthDate.day);
            break;
        case SORT_REG_DATE:
            comparison = (dwellers[j].regDate.year != pivot.regDate.year) ?
                (dwellers[j].regDate.year - pivot.regDate.year) :
                (dwellers[j].regDate.month != pivot.regDate.month) ?
                (dwellers[j].regDate.month - pivot.regDate.month) :
                (dwellers[j].regDate.day - pivot.regDate.day);
            break;
        }
        if ((ascending && comparison < 0) || (!ascending && comparison > 0)) {
            i++;
            swap(&dwellers[i], &dwellers[j]);
        }
    }
    swap(&dwellers[i + 1], &dwellers[high]);
    return (i + 1);
}
