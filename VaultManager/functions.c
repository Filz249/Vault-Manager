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

//?itanje
void readDwellers(const DWELLER* const dwellers, const int count) {
    clearScreen();
    if (count == 0) {
        printf("No dwellers found.\n");
    }
    else {
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
void updateDweller(DWELLER* dwellers, int count) {
    int id;
    printf("Enter ID of dweller to update: ");
    scanf("%d", &id);
    clearInputBuffer();
    for (int i = 0; i < count; i++) {
        if (dwellers[i].id == id) {
            printf("Updating dweller %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
            while (1) {
                printf("Update first name (current: %s): ", dwellers[i].firstName);
                char tmp[MAX_NAME];
                if (!fgets(tmp, sizeof(tmp), stdin)) {
                    continue;
                }
                tmp[strcspn(tmp, "\n")] = 0;
                if (!strlen(tmp)) {
                    break;
                }
                strncpy(dwellers[i].firstName, tmp, MAX_NAME);
                break;
            }
            while (1) {
                printf("Update last name (current: %s): ", dwellers[i].lastName);
                char tmp[MAX_NAME];
                if (!fgets(tmp, sizeof(tmp), stdin)) {
                    continue;
                }
                tmp[strcspn(tmp, "\n")] = 0;
                if (!strlen(tmp)) {
                    break;
                }
                strncpy(dwellers[i].lastName, tmp, MAX_NAME);
                break;
            }
            while (1) {
                printf("Update ID (current: %d): ", dwellers[i].id);
                char tmp[20];
                if (!fgets(tmp, sizeof(tmp), stdin)) {
                    continue;
                }
                if (tmp[0] == '\n') {
                    break;
                }
                int val = atoi(tmp);
                if (val > 0) {
                    dwellers[i].id = val;
                    break;
                }
                printf("Invalid ID.\n");
            }
            while (1) {
                printf("Update age (current: %d): ", dwellers[i].age);
                char tmp[20];
                if (!fgets(tmp, sizeof(tmp), stdin)) {
                    continue;
                }
                if (tmp[0] == '\n') {
                    break;
                }
                int val = atoi(tmp);
                if (val > 0) {
                    dwellers[i].age = val;
                    break;
                }
                printf("Invalid age.\n");
            }
            while (1) {
                printf("Update height (current: %.2f cm): ", dwellers[i].height);
                char tmp[20];
                if (!fgets(tmp, sizeof(tmp), stdin)) {
                    continue;
                }
                if (tmp[0] == '\n') {
                    break;
                }
                float val = atof(tmp);
                if (val > 0) {
                    dwellers[i].height = val;
                    break;
                }
                printf("Invalid height.\n");
            }
            while (1) {
                printf("Update birth date (DD/MM/YYYY) (current: %02d/%02d/%04d): ",
                    dwellers[i].birthDate.day, dwellers[i].birthDate.month, dwellers[i].birthDate.year);
                if (scanf("%d/%d/%d", &dwellers[i].birthDate.day, &dwellers[i].birthDate.month, &dwellers[i].birthDate.year) == 3) {
                    if (dwellers[i].birthDate.day > 0 && dwellers[i].birthDate.day <= 31 &&
                        dwellers[i].birthDate.month > 0 && dwellers[i].birthDate.month <= 12) {
                        break;
                    }
                }
                printf("Invalid date. Please enter a valid birth date.\n");
                clearInputBuffer();
            }
            while (1) {
                printf("Update registration date (DD/MM/YYYY) (current: %02d/%02d/%04d): ",
                    dwellers[i].regDate.day, dwellers[i].regDate.month, dwellers[i].regDate.year);
                if (scanf("%d/%d/%d", &dwellers[i].regDate.day, &dwellers[i].regDate.month, &dwellers[i].regDate.year) == 3) {
                    if (dwellers[i].regDate.day > 0 && dwellers[i].regDate.day <= 31 &&
                        dwellers[i].regDate.month > 0 && dwellers[i].regDate.month <= 12) {
                        break;
                    }
                }
                printf("Invalid date. Please enter a valid registration date.\n");
                clearInputBuffer();
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

