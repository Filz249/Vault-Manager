#include "functions.h"
#include "dataType.h"

//kreiranje 
void createDweller(DWELLER** const dwellers, int* const count) {
    if (*count >= MAX_DWELLERS) {
        printf("Maximum number of dwellers reached.\n");
        return;
    }
    DWELLER* temp = realloc(*dwellers, (*count + 1) * sizeof(DWELLER));
    if (!temp) {
        perror("Failed to allocate memory");
        free(*dwellers);
        exit(EXIT_FAILURE);
    }
    *dwellers = temp;
    DWELLER* newDweller = &(*dwellers)[*count];
    while (1) {
        printf("Enter first name: ");
        if (!fgets(newDweller->firstName, MAX_NAME, stdin)) {
            continue;
        }
        newDweller->firstName[strcspn(newDweller->firstName, "\n")] = '\0';
        if (strlen(newDweller->firstName)) {
            break;
        }
        printf("First name cannot be empty.\n");
    }
    while (1) {
        printf("Enter last name: ");
        if (!fgets(newDweller->lastName, MAX_NAME, stdin)) {
            continue;
        }
        newDweller->lastName[strcspn(newDweller->lastName, "\n")] = '\0';
        if (strlen(newDweller->lastName)) {
            break;
        }
        printf("Last name cannot be empty.\n");
    }
    while (1) {
        printf("Enter ID: ");
        if (scanf("%d", &newDweller->id) == 1 && newDweller->id > 0) {
            break;
        }
        printf("Invalid ID.\n");
        clearInputBuffer();
    }
    while (1) {
        printf("Enter age: ");
        if (scanf("%d", &newDweller->age) == 1 && newDweller->age > 0) {
            break;
        }
        printf("Invalid age.\n");
        clearInputBuffer();
    }
    while (1) {
        printf("Enter height (in cm): ");
        if (scanf("%f", &newDweller->height) == 1 && newDweller->height > 0) {
            break;
        }
        printf("Invalid height.\n");
        clearInputBuffer();
    }
    while (1) {
        printf("Enter birth date (DD/MM/YYYY): ");
        if (scanf("%d/%d/%d", &newDweller->birthDate.day, &newDweller->birthDate.month, &newDweller->birthDate.year) == 3) {
            if (isValidDate(newDweller->birthDate.day, newDweller->birthDate.month, newDweller->birthDate.year)) {
                break;
            }
        }
        printf("Invalid date. Please enter a valid birth date.\n");
        clearInputBuffer();
    }
    while (1) {
        printf("Enter registration date (DD/MM/YYYY): ");
        if (scanf("%d/%d/%d", &newDweller->regDate.day, &newDweller->regDate.month, &newDweller->regDate.year) == 3) {
            if (isValidDate(newDweller->regDate.day, newDweller->regDate.month, newDweller->regDate.year)) {
                break;
            }
        }
        printf("Invalid date. Please enter a valid registration date.\n");
        clearInputBuffer();
    }
    (*count)++;
}

//čitanje
void readDwellers(const DWELLER* const dwellers, const int count) {
    clearScreen();
    if (count == 0) {
        printf("No dwellers found.\n");
    }else {
        for (int i = 0; i < count; i++) {
            printf("\nDweller %d:\n", i + 1);
            printf("  First Name: %s\n", dwellers[i].firstName);
            printf("  Last Name: %s\n", dwellers[i].lastName);
            printf("  Age: %d\n", dwellers[i].age);
            printf("  Height: %.2f cm\n", dwellers[i].height);
            printf("  Birth Date: %02d/%02d/%04d\n", dwellers[i].birthDate.day, dwellers[i].birthDate.month, dwellers[i].birthDate.year);
            printf("  Registration Date: %02d/%02d/%04d\n", dwellers[i].regDate.day, dwellers[i].regDate.month, dwellers[i].regDate.year);
            printf("  ID: %d\n", dwellers[i].id);
        }
    }
    printf("\nPress Enter to return to main menu...");
    getchar();
}

//ažuriranje
void updateDweller(DWELLER* const dwellers, const int count) {
    int id;
    printf("Enter vault ID of dweller to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (dwellers[i].id == id) {
            printf("Updating dweller %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);

            printf("Update first name (current: %s): ", dwellers[i].firstName);
            char tmp[MAX_NAME];
            if (fgets(tmp, sizeof(tmp), stdin)) {
                tmp[strcspn(tmp, "\n")] = 0;
                if (strlen(tmp) > 0) {
                    strncpy(dwellers[i].firstName, tmp, MAX_NAME);
                }
            }
            printf("Update last name (current: %s): ", dwellers[i].lastName);
            if (fgets(tmp, sizeof(tmp), stdin)) {
                tmp[strcspn(tmp, "\n")] = 0;
                if (strlen(tmp) > 0) {
                    strncpy(dwellers[i].lastName, tmp, MAX_NAME);
                }
            }
            printf("Update ID (current: %d): ", dwellers[i].id);
            if (fgets(tmp, sizeof(tmp), stdin)) {
                if (tmp[0] != '\n') {
                    int val = atoi(tmp);
                    if (val > 0) {
                        dwellers[i].id = val;
                    }else {
                        printf("Invalid ID. Keeping previous value.\n");
                    }
                }
            }
            printf("Update age (current: %d): ", dwellers[i].age);
            if (fgets(tmp, sizeof(tmp), stdin)) {
                if (tmp[0] != '\n') {
                    int val = atoi(tmp);
                    if (val > 0) {
                        dwellers[i].age = val;
                    }else {
                        printf("Invalid age. Keeping previous value.\n");
                    }
                }
            }
            printf("Update height (current: %.2f): ", dwellers[i].height);
            if (fgets(tmp, sizeof(tmp), stdin)) {
                if (tmp[0] != '\n') {
                    float val = atof(tmp);
                    if (val > 0) {
                        dwellers[i].height = val;
                    }else {
                        printf("Invalid height. Keeping previous value.\n");
                    }
                }
            }
            int day, month, year;
            printf("Update birth date (DD/MM/YYYY) (current: %02d/%02d/%04d): ",
                dwellers[i].birthDate.day, dwellers[i].birthDate.month, dwellers[i].birthDate.year);
            if (fgets(tmp, sizeof(tmp), stdin)) {
                if (sscanf(tmp, "%d/%d/%d", &day, &month, &year) == 3) {
                    if (day > 0 && day <= 31 && month > 0 && month <= 12) {
                        dwellers[i].birthDate.day = day;
                        dwellers[i].birthDate.month = month;
                        dwellers[i].birthDate.year = year;
                    }else {
                        printf("Invalid birth date. Keeping previous value.\n");
                    }
                }else if (tmp[0] != '\n') {
                    printf("Invalid format. Keeping previous birth date.\n");
                }
            }
            printf("Update registration date (DD/MM/YYYY) (current: %02d/%02d/%04d): ",
                dwellers[i].regDate.day, dwellers[i].regDate.month, dwellers[i].regDate.year);
            if (fgets(tmp, sizeof(tmp), stdin)) {
                if (sscanf(tmp, "%d/%d/%d", &day, &month, &year) == 3) {
                    if (day > 0 && day <= 31 && month > 0 && month <= 12) {
                        dwellers[i].regDate.day = day;
                        dwellers[i].regDate.month = month;
                        dwellers[i].regDate.year = year;
                    }else {
                        printf("Invalid registration date. Keeping previous value.\n");
                    }
                }else if (tmp[0] != '\n') {
                    printf("Invalid format. Keeping previous registration date.\n");
                }
            }
            return;
        }
    }
    printf("Dweller with ID %d not found.\n", id);
    printf("\nPress Enter to return to main menu...");
    getchar();
}


//sortiranje
void sortDwellers(DWELLER* const dwellers, const int count, const SORT_CR criteria, const int ascending) {
    quickSort(dwellers, 0, count - 1, criteria, ascending);
    printf("Dwellers sorted.\n");
    printf("\nPress Enter to return to main menu...");
    getchar();
}

//pretraživanje
void searchDweller(const DWELLER* const dwellers, const int count, const SEARCH_CR criteria) {

    // KONCEPT 6.
    static int searchCount = 0;
    searchCount++;
    if (count == 0) {
        printf("No dwellers to search.\n");
        printf("\nPress Enter to return to main menu...");
        getchar();
        return;
    }
    char searchString[MAX_NAME];
    int searchID;
    int found = 0;

    switch (criteria) {
    case SEARCH_FIRST:
        printf("Enter first name to search: ");
        scanf("%49s", searchString);
        clearInputBuffer();
        for (int i = 0; i < count; i++) {
            if (strcmp(dwellers[i].firstName, searchString) == 0) {
                printf("Found: %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
                found = 1;
                printf("Searched %d times.\n", searchCount);
            }
        }
        break;

    case SEARCH_LAST:
        printf("Enter last name to search: ");
        scanf("%49s", searchString);
        clearInputBuffer();
        for (int i = 0; i < count; i++) {
            if (strcmp(dwellers[i].lastName, searchString) == 0) {
                printf("Found: %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
                found = 1;
                printf("Searched %d times.\n", searchCount);
            }
        }
        break;

    case SEARCH_ID:
        printf("Enter vault ID to search: ");
        scanf("%d", &searchID);
        clearInputBuffer();
        for (int i = 0; i < count; i++) {
            if (dwellers[i].id == searchID) {
                printf("Found: %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
                found = 1;
                printf("Searched %d times.\n", searchCount);
            }
        }
        break;

    case SEARCH_AGE: {
        int searchAge;
        printf("Enter age to search: ");
        scanf("%d", &searchAge);
        clearInputBuffer();
        for (int i = 0; i < count; i++) {
            if (dwellers[i].age == searchAge) {
                printf("Found: %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
                found = 1;
                printf("Searched %d times.\n", searchCount);
            }
        }
        break;
    }
    default:
        printf("Unknown search criteria.\n");
        break;
    }
    if (!found) {
        printf("No dwellers found matching the criteria.\n");
    }
    printf("\nPress Enter to return to main menu...");
    getchar();
}

//brisanje
void deleteDweller(DWELLER** const dwellers, int* const count) {
    int id;
    printf("Enter vault ID of dweller to delete: ");
    scanf("%d", &id);
    clearInputBuffer();
    for (int i = 0; i < *count; i++) {
        if ((*dwellers)[i].id == id) {
            for (int j = i; j < *count - 1; j++)
                (*dwellers)[j] = (*dwellers)[j + 1];
            DWELLER* temp = realloc(*dwellers, (*count - 1) * sizeof(DWELLER));
            if (!temp) {
                perror("Failed to reallocate memory");
                free(*dwellers);
                *dwellers = NULL;
                *count = 0;
                exit(EXIT_FAILURE);
            }
            *dwellers = temp;
            (*count)--;
            printf("Dweller with ID %d deleted.\n", id);
            printf("\nPress Enter to return to main menu...");
            getchar();
            return;
        }
    }
    printf("Dweller with ID %d not found.\n", id);
    printf("\nPress Enter to return to main menu...");
    getchar();
}

