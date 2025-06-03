#include "functions.h"
#include "dataType.h"

extern void clearInputBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

extern void clearScreen(void){
    printf("\033[H\033[J");
}

/*
========================
       KONCEPT 6.
========================
*/

extern int totalDwellers = 0;

/*
========================
       KONCEPT 1.
========================
*/
void saveToFile(const DWELLER* const dwellers, const int count){
    FILE* file = fopen("dwellers.txt", "w");
    if(!file) {
        perror("Failed to open file for writing");
        return;
    }

    for(int i = 0; i < count; i++){
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

/*
========================
       KONCEPT 19.
========================
*/

void loadFromFile(DWELLER** const dwellers, int* const count){
    FILE* file = fopen("dwellers.txt", "r");
    if(!file){
        *count = 0;
        *dwellers = NULL;
        totalDwellers = 0;
        return;
    }

    *dwellers = malloc(MAX_DWELLERS * sizeof(DWELLER));
    if(!*dwellers){
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    *count = 0;
    while(fscanf(file, "First name: %49s\nLast name: %49s\nAge: %d\nHeight(cm): %f\nDate of birth: %d/%d/%d\nDate of registration: %d/%d/%d\nID: %d\n\n",
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
        &(*dwellers)[*count].id) == 11){
        (*count)++;
        if (*count >= MAX_DWELLERS) {
            break;
        }
    }

    totalDwellers = *count;

    fclose(file);
}

//    AŽURIRANJE

void updateFirstName(DWELLER* const dweller){
    char temp[MAX_NAME];
    while (1) {
        printf("Update first name (current: %s): ", dweller->firstName);
        if (!fgets(temp, MAX_NAME, stdin)) continue;
        temp[strcspn(temp, "\n")] = '\0';
        if (strlen(temp) && validName(temp)) {
            strcpy(dweller->firstName, temp);
            break;
        }
        printf("Invalid name. Use only letters, hyphens, or apostrophes.\n");
    }
}

void updateLastName(DWELLER* const dweller){
    char temp[MAX_NAME];
    while (1) {
        printf("Update last name (current: %s): ", dweller->lastName);
        if (!fgets(temp, MAX_NAME, stdin)) continue;
        temp[strcspn(temp, "\n")] = '\0';
        if (strlen(temp) && validName(temp)) {
            strcpy(dweller->lastName, temp);
            break;
        }
        printf("Invalid name. Use only letters, hyphens, or apostrophes.\n");
    }
}

void updateAge(DWELLER* const dweller){
    int age;
    while (1) {
        printf("Update age (current: %d): ", dweller->age);
        if (scanf("%d", &age) == 1 && age > 0 && age <= 120) {
            dweller->age = age;
            break;
        }
        printf("Invalid age.\n");
        clearInputBuffer();
    }
    clearInputBuffer();
}

void updateHeight(DWELLER* const dweller){
    float height;
    while (1) {
        printf("Update height (current: %.2f cm): ", dweller->height);
        if (scanf("%f", &height) == 1 && height >= 50.0f && height <= 300.0f) {
            dweller->height = height;
            break;
        }
        printf("Invalid height. Must be between 50 and 300 cm.\n");
        clearInputBuffer();
    }
    clearInputBuffer();
}

void updateBirthDate(DWELLER* const dweller){
    int d, m, y;
    while (1) {
        printf("Update birth date (DD/MM/YYYY) (current: %02d/%02d/%04d): ",
            dweller->birthDate.day, dweller->birthDate.month, dweller->birthDate.year);
        if (scanf("%d/%d/%d", &d, &m, &y) == 3 && validDate(d, m, y)) {
            dweller->birthDate.day = d;
            dweller->birthDate.month = m;
            dweller->birthDate.year = y;
            break;
        }
        printf("Invalid date.\n");
        clearInputBuffer();
    }
    clearInputBuffer();
}

void updateRegDate(DWELLER* const dweller){
    int d, m, y;
    while (1) {
        printf("Update registration date (DD/MM/YYYY) (current: %02d/%02d/%04d): ",
            dweller->regDate.day, dweller->regDate.month, dweller->regDate.year);
        if (scanf("%d/%d/%d", &d, &m, &y) == 3 && validDate(d, m, y)) {
            dweller->regDate.day = d;
            dweller->regDate.month = m;
            dweller->regDate.year = y;
            break;
        }
        printf("Invalid date.\n");
        clearInputBuffer();
    }
    clearInputBuffer();
}

  
//        SORTIRANJE
/*
==============================
       KONCEPT 23. i 25.
==============================
*/
void insertionSort(DWELLER* const dwellers, const int n, const SORT_CR criteria){
    if (n <= 1) {
        return;
    }

    insertionSort(dwellers, n - 1, criteria);

    DWELLER last = dwellers[n - 1];
    int j = n - 2;

    switch (criteria) {
    case SORT_FIRST:
        while (j >= 0 && strcmp(dwellers[j].firstName, last.firstName) > 0) {
            dwellers[j + 1] = dwellers[j];
            j--;
        }
        break;
    case SORT_LAST:
        while (j >= 0 && strcmp(dwellers[j].lastName, last.lastName) > 0) {
            dwellers[j + 1] = dwellers[j];
            j--;
        }
        break;
    case SORT_AGE:
        while (j >= 0 && dwellers[j].age > last.age) {
            dwellers[j + 1] = dwellers[j];
            j--;
        }
        break;
    case SORT_HEIGHT:
        while (j >= 0 && dwellers[j].height > last.height) {
            dwellers[j + 1] = dwellers[j];
            j--;
        }
        break;
    case SORT_BIRTH_DATE:
        while (j >= 0 && (dwellers[j].birthDate.year > last.birthDate.year ||
            (dwellers[j].birthDate.year == last.birthDate.year &&
                (dwellers[j].birthDate.month > last.birthDate.month ||
                    (dwellers[j].birthDate.month == last.birthDate.month &&
                        dwellers[j].birthDate.day > last.birthDate.day))))) {
            dwellers[j + 1] = dwellers[j];
            j--;
        }
        break;
    case SORT_REG_DATE:
        while (j >= 0 && (dwellers[j].regDate.year > last.regDate.year ||
            (dwellers[j].regDate.year == last.regDate.year &&
                (dwellers[j].regDate.month > last.regDate.month ||
                    (dwellers[j].regDate.month == last.regDate.month &&
                        dwellers[j].regDate.day > last.regDate.day))))) {
            dwellers[j + 1] = dwellers[j];
            j--;
        }
        break;
    default:
        break;
    }
    dwellers[j + 1] = last;
}


int validDate(const int day, const int month, const int year){
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
        }
        else {
            if (day > 28) return 0;
        }
    }
    return 1;
}

int validName(const char* const name){
    for (int i = 0; name[i]; ++i) {
        if (!isalpha(name[i]) && name[i] != '-' && name[i] != '\'') {
            return 0;
        }
    }
    return 1;
}

int validID(const DWELLER* const dwellers, const int count, const int id){
    for (int i = 0; i < count; i++) {
        if (dwellers[i].id == id) {
            return 1;
        }
    }
    return 0;
}

void removeDwellersFile() {
    const char* filename = "dwellers.txt";
    if (remove(filename) == 0) {
        printf("Successfully removed the dwellers file: %s\n", filename);
    }
    else {
        perror("Error removing the dwellers file");
    }
}

void copyFile(const char* srcFileName, const char* destFileName) {
    FILE* src = fopen(srcFileName, "r");
    if (!src) {
        perror("Failed to open source file for copying");
        return;
    }

    FILE* dest = fopen(destFileName, "w");
    if (!dest) {
        perror("Failed to open destination file for copying");
        fclose(src);
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(src);
    fclose(dest);
}