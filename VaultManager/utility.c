#include "functions.h"
#include "dataType.h"

extern void clearInputBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

extern void clearScreen(void){
    printf("\033[H\033[J");
}


extern int totalDwellers = 0;  // KONCEPT 8.

void saveToFile(const DWELLER* const dwellers, const int count){  // KONCEPT 1.
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


void loadFromFile(DWELLER** const dwellers, int* const count) { 
    FILE* file = fopen("dwellers.txt", "r"); // KONCEPT 19.
    if (!file) { // KONCEPT 19.
        *count = 0;
        *dwellers = NULL;
        totalDwellers = 0;
        return;
    }
    // KONCEPT 16.
    *dwellers = malloc(MAX_DWELLERS * sizeof(DWELLER)); // KONCEPT 17., 18.
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
    rewind(file);  // KONCEPT 20.

    totalDwellers = *count;

    fclose(file); // KONCEPT 19.
}


void printDwellerInfo(const DWELLER* dweller) {
    printf("  First Name: %s\n", dweller->firstName);
    printf("  Last Name: %s\n", dweller->lastName);
    printf("  Age: %d\n", dweller->age);
    printf("  Height: %.2f cm\n", dweller->height);
    printf("  Birth Date: %02d/%02d/%04d\n", dweller->birthDate.day, dweller->birthDate.month, dweller->birthDate.year);
    printf("  Registration Date: %02d/%02d/%04d\n", dweller->regDate.day, dweller->regDate.month, dweller->regDate.year);
}


//    -- AŽURIRANJE --
void updateFirstName(DWELLER* const dweller) {
    char temp[MAX_NAME];
    do {
        printf("Update first name (current: %s): ", dweller->firstName);
        if (!fgets(temp, MAX_NAME, stdin)) {
            continue;
        }
        temp[strcspn(temp, "\n")] = '\0';
    } while (!strlen(temp) || !validName(temp));

    strcpy(dweller->firstName, temp);
}

void updateLastName(DWELLER* const dweller) {
    char temp[MAX_NAME];
    do {
        printf("Update last name (current: %s): ", dweller->lastName);
        if (!fgets(temp, MAX_NAME, stdin)) {
            continue;
        }
        temp[strcspn(temp, "\n")] = '\0';
    } while (!strlen(temp) || !validName(temp));

    strcpy(dweller->lastName, temp);
}

void updateAge(DWELLER* const dweller) {
    int age;
    do {
        printf("Update age (current: %d): ", dweller->age);
        if (scanf("%d", &age) != 1 || age <= 0 || age > 120) {
            printf("Invalid age.\n");
            clearInputBuffer();
        }
    } while (age <= 0 || age > 120);

    dweller->age = age;
    clearInputBuffer();
}

void updateHeight(DWELLER* const dweller) {
    float height;
    do {
        printf("Update height (current: %.2f cm): ", dweller->height);
        if (scanf("%f", &height) != 1 || height < 50.0f || height > 300.0f) {
            printf("Invalid height. Must be between 50 and 300 cm.\n");
            clearInputBuffer();
        }
    } while (height < 50.0f || height > 300.0f);

    dweller->height = height;
    clearInputBuffer();
}

void updateBirthDate(DWELLER* const dweller) {
    int d, m, y;
    do {
        printf("Update birth date (DD/MM/YYYY) (current: %02d/%02d/%04d): ",
            dweller->birthDate.day, dweller->birthDate.month, dweller->birthDate.year);
        if (scanf("%d/%d/%d", &d, &m, &y) != 3 || !validDate(d, m, y)) {
            printf("Invalid date.\n");
            clearInputBuffer();
        }
    } while (!validDate(d, m, y));

    dweller->birthDate.day = d;
    dweller->birthDate.month = m;
    dweller->birthDate.year = y;
    clearInputBuffer();
}

void updateRegDate(DWELLER* const dweller) {
    int d, m, y;
    do {
        printf("Update registration date (DD/MM/YYYY) (current: %02d/%02d/%04d): ",
            dweller->regDate.day, dweller->regDate.month, dweller->regDate.year);
        if (scanf("%d/%d/%d", &d, &m, &y) != 3 || !validDate(d, m, y)) {
            printf("Invalid date.\n");
            clearInputBuffer();
        }
    } while (!validDate(d, m, y));

    dweller->regDate.day = d;
    dweller->regDate.month = m;
    dweller->regDate.year = y;
    clearInputBuffer();
}

  
//    *** SORTIRANJE ***
void insertionSort(DWELLER* const dwellers, const int n, const SORT_CR criteria){  // KONCEPT 23.
    if (n <= 1) {
        return;
    }

    insertionSort(dwellers, n - 1, criteria); // KONCEPT 25.

    DWELLER last = dwellers[n - 1];
    int i = n - 2;

    switch (criteria) {
    case SORT_FIRST:
        while (i >= 0 && strcmp(dwellers[i].firstName, last.firstName) > 0) {
            dwellers[i + 1] = dwellers[i];
            i--;
        }
        break;
    case SORT_LAST:
        while (i >= 0 && strcmp(dwellers[i].lastName, last.lastName) > 0) {
            dwellers[i + 1] = dwellers[i];
            i--;
        }
        break;
    case SORT_AGE:
        while (i >= 0 && dwellers[i].age > last.age) {
            dwellers[i + 1] = dwellers[i];
            i--;
        }
        break;
    case SORT_HEIGHT:
        while (i >= 0 && dwellers[i].height > last.height) {
            dwellers[i + 1] = dwellers[i];
            i--;
        }
        break;
    case SORT_BIRTH_DATE:
        while (i >= 0 && (dwellers[i].birthDate.year > last.birthDate.year ||
            (dwellers[i].birthDate.year == last.birthDate.year &&
                (dwellers[i].birthDate.month > last.birthDate.month ||
                    (dwellers[i].birthDate.month == last.birthDate.month &&
                        dwellers[i].birthDate.day > last.birthDate.day))))) {
            dwellers[i + 1] = dwellers[i];
            i--;
        }
        break;
    case SORT_REG_DATE:
        while (i >= 0 && (dwellers[i].regDate.year > last.regDate.year ||
            (dwellers[i].regDate.year == last.regDate.year &&
                (dwellers[i].regDate.month > last.regDate.month ||
                    (dwellers[i].regDate.month == last.regDate.month &&
                        dwellers[i].regDate.day > last.regDate.day))))) {
            dwellers[i + 1] = dwellers[i];
            i--;
        }
        break;
    default:
        break;
    }
    dwellers[i + 1] = last;
}


int readInput(const char* input, void* outValue, const char* data, int minInt, int maxInt, float minFloat, float maxFloat) {
    char line[128];
    while (1) {
        printf("%s", input);
        if (!fgets(line, sizeof(line), stdin)) continue;

        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }

        if (strcmp(data, "name") == 0) {
            int valid = 1;
            for (size_t i = 0; i < strlen(line); ++i) {
                if (!isalpha(line[i]) && line[i] != '-' && line[i] != '\'') {
                    valid = 0;
                    break;
                }
            }
            if (!valid) {
                printf("Invalid name. Use only letters.\n");
                continue;
            }
            strncpy((char*)outValue, line, MAX_NAME - 1);
            ((char*)outValue)[MAX_NAME - 1] = '\0';
            return 1;
        }
        else if (strcmp(data, "int") == 0) {
            int val;
            char extra;
            if (sscanf(line, "%d %c", &val, &extra) != 1) {
                printf("Invalid integer. Please enter a valid number.\n");
                continue;
            }
            if (val < minInt || val > maxInt) {
                printf("Value must be between %d and %d.\n", minInt, maxInt);
                continue;
            }
            *(int*)outValue = val;
            return 1;
        }
        else if (strcmp(data, "float") == 0) {
            float val;
            char extra;
            if (sscanf(line, "%f %c", &val, &extra) != 1) {
                printf("Invalid number. Please enter a valid floating point number.\n");
                continue;
            }
            if (val < minFloat || val > maxFloat) {
                printf("Value must be between %.2f and %.2f.\n", minFloat, maxFloat);
                continue;
            }
            *(float*)outValue = val;
            return 1;
        }
        else if (strcmp(data, "date") == 0) {
            int d, m, y;
            if (sscanf(line, "%d/%d/%d", &d, &m, &y) != 3) {
                printf("Invalid format. Enter date as DD/MM/YYYY.\n");
                continue;
            }
            if (!validDate(d, m, y)) {
                printf("Invalid date. Please enter a valid date.\n");
                continue;
            }
            DATE* datePtr = (DATE*)outValue;
            datePtr->day = d;
            datePtr->month = m;
            datePtr->year = y;
            return 1;
        }
        else {
            printf("Unknown input type requested.\n");
            return 0;
        }
    }
}


inline int validDate(const int day, const int month, const int year) { // KONCEPT 9.
    if (year < 1900 || year > 2025) {
        return 0;
    }
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


inline int validName(const char* const name){ // KONCEPT 9.
    for (int i = 0; name[i]; ++i) {
        if (!isalpha(name[i]) && name[i] != '-' && name[i] != '\'') {
            return 0;
        }
    }
    return 1;
}


inline int validID(const DWELLER* const dwellers, const int count, const int id){ // KONCEPT 9.
    for (int i = 0; i < count; i++) {
        if (dwellers[i].id == id) {
            return 1;
        }
    }
    return 0;
}


void deleteOption(DWELLER** const dwellers, int* const count) { 
    char backupChoice[4];
    printf("Do you want to create a backup before deleting dwellers.txt? (Y/N): ");
    if (fgets(backupChoice, sizeof(backupChoice), stdin)) {
        if (backupChoice[0] == 'Y' || backupChoice[0] == 'y') {
            if (rename("dwellers.txt", "dwellers_backup.txt") == 0) { // KONCEPT 21.
                *count = 0;
                free(*dwellers);
                *dwellers = NULL;
                totalDwellers = 0;
                printf("Backup created as dwellers_backup.txt and original file deleted.\n");
            }else {
                perror("Failed to create backup and delete original");
            }
        }else if (backupChoice[0] == 'N' || backupChoice[0] == 'n') {
            if (remove("dwellers.txt") == 0) { // KONCEPT 21.
                *count = 0;
                free(*dwellers);
                *dwellers = NULL;
                totalDwellers = 0;
                printf("Original dwellers.txt deleted without backup.\n");
            }
            else {
                perror("Failed to delete dwellers.txt");
            }
        }
        else {
            printf("Invalid input. Returning to main menu without deleting file.\n");
        }
    }
}