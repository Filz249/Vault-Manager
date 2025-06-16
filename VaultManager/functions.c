#include "functions.h"
#include "dataType.h"


// *** KREIRANJE ***
void createDwellers(DWELLER** const dwellers, int* const count) {
    if (*count >= MAX_DWELLERS) {
        printf("Maximum number of dwellers reached.\n");
        return;
    }

    DWELLER newDweller;

    readInput("Enter first name: ", newDweller.firstName, "name", 0, 0, 0, 0);

    readInput("Enter last name: ", newDweller.lastName, "name", 0, 0, 0, 0);

    readInput("Enter age: ", &newDweller.age, "int", 1, 120, 0, 0);

    readInput("Enter height (in cm): ", &newDweller.height, "float", 0, 0, 50.0f, 300.0f);

    readInput("Enter birth date (DD/MM/YYYY): ", &newDweller.birthDate, "date", 1905, 2025, 0, 0);

    readInput("Enter registration date (DD/MM/YYYY): ", &newDweller.regDate, "date", 0, 0, 0, 0);

    newDweller.id = *count + 1;

    DWELLER* temp = realloc(*dwellers, (*count + 1) * sizeof(DWELLER)); // KONCEPT 17.
    if (temp == NULL) {
        perror("Failed to allocate memory"); // KONCEPT 22.
        return;
    }
    *dwellers = temp;
    (*dwellers)[*count] = newDweller;
    (*count)++;
    totalDwellers++;
    printf("Dweller added successfully!\n");
    saveToFile(*dwellers, *count);
}


// *** ČITANJE ***
void readDwellers(const DWELLER* const dwellers, const int count) {
    clearScreen();
    printf("Total dwellers: %d\n\n", totalDwellers);
    if (count == 0) {
        printf("No dwellers found.\n");
    }else {
        for (int i = 0; i < count; i++) {
            printf("-----------------------------------------\n");
            printf("  First Name: %s\n", dwellers[i].firstName);
            printf("  Last Name: %s\n", dwellers[i].lastName);
            printf("  Age: %d\n", dwellers[i].age);
            printf("  Height: %.2f cm\n", dwellers[i].height);
            printf("  Birth Date: %02d/%02d/%04d\n", dwellers[i].birthDate.day, dwellers[i].birthDate.month, dwellers[i].birthDate.year);
            printf("  Registration Date: %02d/%02d/%04d\n", dwellers[i].regDate.day, dwellers[i].regDate.month, dwellers[i].regDate.year);
            printf("  ID: %d\n\n", dwellers[i].id);

        }
    }
    printf("Press Enter to return to main menu...");
    getchar();
}


// *** AŽURIRANJE ***
void updateDwellers(DWELLER* const dwellers, const int count) {
    int id;
    readInput("Enter ID of dweller to update: ", &id, "int", 1, 20, 0, 0);

    for (int i = 0; i < count; i++) {
        if (dwellers[i].id == id) {
            UPDATE_CH updateChoices[] = { // KONCEPT 26.
                updateFirstName,
                updateLastName,
                updateAge,
                updateHeight,
                updateBirthDate,
                updateRegDate
            };

            int updateChoice;
            do {
                updateChoice = displayUpdateMenu();
                if (updateChoice >= UPDATE_FIRST_NAME && updateChoice <= UPDATE_REG_DATE) {
                    updateChoices[updateChoice - 1](&dwellers[i]);
                }else if (updateChoice == UPDATE_EXIT) {
                    printf("Exiting update menu.\n");
                }else {
                    printf("Invalid choice. Please try again.\n");
                }
            } while (updateChoice != UPDATE_EXIT);
            return;
        }
    }
    printf("Dweller with ID %d not found.\n", id);
    printf("\nPress Enter to return to main menu...");
    getchar();
}


// *** SORTIRANJE*** 
void sortDwellers(DWELLER* const dwellers, const int count, const SORT_CR criteria){
    insertionSort(dwellers, count, criteria);
    printf("Dwellers sorted.\n");
    printf("\nPress Enter to return to main menu...");
    getchar();
}


// *** PRETRAŽIVANJE ***
void searchDwellers(const DWELLER* const dwellers, const int count, const SEARCH_CR criteria) {  // KONCEPT 24.
    static int searchCount = 0; // KONCEPT 6.
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
                printDwellerInfo(&dwellers[i]);
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
                printDwellerInfo(&dwellers[i]);
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
                printDwellerInfo(&dwellers[i]);
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
                printDwellerInfo(&dwellers[i]);
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


// *** BRISANJE ***
void deleteDwellers(DWELLER** const dwellers, int* const count) {
    int choice = displayDeletionMenu();
    if (choice == 1) {
        deleteOption(dwellers, count);
    }else if (choice == 2) {
        int id;
        readInput("Enter ID of dweller to delete: ", &id, "int", 1, 1000000, 0, 0);
        int found = 0;
        for (int i = 0; i < *count; i++) {
            if ((*dwellers)[i].id == id) {
                found = 1;
                for (int j = i; j < *count - 1; j++) {
                    (*dwellers)[j] = (*dwellers)[j + 1];
                }
                (*count)--;
                totalDwellers--;

                DWELLER* temp = realloc(*dwellers, (*count) * sizeof(DWELLER));
                if (temp || *count == 0) {
                    *dwellers = temp;
                }else {
                    perror("Failed to reallocate memory");
                    free(*dwellers);
                    *dwellers = NULL;
                    *count = 0;
                    exit(EXIT_FAILURE);
                }

                saveToFile(*dwellers, *count);
                printf("Dweller with ID %d deleted.\n", id);
                break;
            }
        }
        if (!found) {
            printf("Dweller with ID %d not found.\n", id);
        }
    }else {
        printf("Returning to main menu...\n");
    }
}