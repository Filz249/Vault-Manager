#include "functions.h"

static int g_specialAttributeSortIndex = 0;

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen(void) {
    printf("\033[H\033[J");
}

int displayMenu(void) {
    clearScreen();
    printf("\033[32m");
    printf("================ROBCO INDUSTRIES===============\n");
    printf("_______________________________________________\n");
    printf("                                               \n");
    printf("           VAULT-TEC DWELLER MANAGER           \n");
    printf("_______________________________________________\n");
    printf("CHOOSE ACTION:                                 \n");
    printf("[1. Add new dwellers]                          \n");
    printf("[2. Print dwellers]                            \n");
    printf("[3. Update dweller info]                       \n");
    printf("[4. Search dwellers]                           \n");
    printf("[5. Sort dwellers]                             \n");
    printf("[6. Delete dwellers]                           \n");
    printf("[7. Exit]                                      \n");
    printf("_______________________________________________\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

int displaySortMenu(void) {
    clearScreen();
    printf("\033[32m");
    printf("=============== SORT DWELLERS =================\n");
    printf("_______________________________________________\n");
    printf("Sort by:                                      \n");
    printf("[1. First Name]\n");
    printf("[2. Last Name]\n");
    printf("[3. Vault ID]\n");
    printf("[4. S.P.E.C.I.A.L. attribute]\n");
    printf("_______________________________________________\n");
    printf("Enter sort criteria: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

int displaySortOrderMenu(void) {
    clearScreen();
    printf("\033[32m");
    printf("============== SORT ORDER =====================\n");
    printf("_______________________________________________\n");
    printf("[1. Ascending]\n");
    printf("[2. Descending]\n");
    printf("_______________________________________________\n");
    printf("Enter sort order: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

int displaySearchMenu(void) {
    clearScreen();
    printf("\033[32m");
    printf("============== SEARCH DWELLERS =================\n");
    printf("_______________________________________________\n");
    printf("Search by:                                    \n");
    printf("[1. First Name]\n");
    printf("[2. Last Name]\n");
    printf("[3. Vault ID]\n");
    printf("[4. S.P.E.C.I.A.L. attribute]\n");
    printf("_______________________________________________\n");
    printf("Enter search criteria: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

int displaySpecialAttributeMenu(void) {
    clearScreen();
    printf("\033[32m");
    printf("======== CHOOSE S.P.E.C.I.A.L. ATTRIBUTE ======\n");
    printf("_______________________________________________\n");
    printf("[1. Strength (S)]\n");
    printf("[2. Perception (P)]\n");
    printf("[3. Endurance (E)]\n");
    printf("[4. Charisma (C)]\n");
    printf("[5. Intelligence (I)]\n");
    printf("[6. Agility (A)]\n");
    printf("[7. Luck (L)]\n");
    printf("_______________________________________________\n");
    printf("Enter attribute number: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

const char* getSpecialAttributeName(int index) {
    static const char* names[7] = {
        "Strength (S)",
        "Perception (P)",
        "Endurance (E)",
        "Charisma (C)",
        "Intelligence (I)",
        "Agility (A)",
        "Luck (L)"
    };
    if (index >= 0 && index < 7)
        return names[index];
    return "Unknown";
}

void createDweller(DWELLER** dwellers, int* count) {
    if (*count >= MAX_VAULT_RESIDENTS) {
        printf("Maximum number of dwellers reached.\n");
        return;
    }
    DWELLER* temp = realloc(*dwellers, (*count + 1) * sizeof(DWELLER));
    if (!temp) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    *dwellers = temp;
    DWELLER* newDweller = &(*dwellers)[*count];

    while (1) {
        printf("Enter first name: ");
        if (!fgets(newDweller->firstName, MAX_NAME_LENGTH, stdin)) continue;
        newDweller->firstName[strcspn(newDweller->firstName, "\n")] = '\0';
        if (strlen(newDweller->firstName)) break;
        printf("First name cannot be empty.\n");
    }
    while (1) {
        printf("Enter last name: ");
        if (!fgets(newDweller->lastName, MAX_NAME_LENGTH, stdin)) continue;
        newDweller->lastName[strcspn(newDweller->lastName, "\n")] = '\0';
        if (strlen(newDweller->lastName)) break;
        printf("Last name cannot be empty.\n");
    }
    while (1) {
        char buf[20];
        printf("Enter vault ID: ");
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        if (sscanf(buf, "%d", &newDweller->vaultID) == 1 && newDweller->vaultID > 0) break;
        printf("Invalid vault ID. Must be positive integer.\n");
    }
    while (1) {
        char buf[20];
        printf("Enter health (0-100): ");
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        int val;
        if (sscanf(buf, "%d", &val) == 1 && val >= 0 && val <= 100) {
            newDweller->health = val;
            break;
        }
        printf("Invalid health. Must be 0-100.\n");
    }
    int pointsLeft = MAX_SPECIAL_POINTS;
    for (int i = 0; i < 7; i++) {
        while (1) {
            char buf[20];
            printf("Enter S.P.E.C.I.A.L attribute %d - %s (points left: %d, min 1, max 10): ", i + 1, getSpecialAttributeName(i), pointsLeft);
            if (!fgets(buf, sizeof(buf), stdin)) continue;
            int val;
            if (sscanf(buf, "%d", &val) != 1) {
                printf("Invalid input. Enter an integer.\n");
                continue;
            }
            if (val < MIN_SPECIAL_ATTRIBUTE || val > MAX_SPECIAL_ATTRIBUTE) {
                printf("Value must be between %d and %d.\n", MIN_SPECIAL_ATTRIBUTE, MAX_SPECIAL_ATTRIBUTE);
                continue;
            }
            if (val > pointsLeft - (7 - i - 1)) {
                printf("Not enough points left. Reserve points for remaining attributes.\n");
                continue;
            }
            newDweller->specialAttributes[i] = val;
            pointsLeft -= val;
            break;
        }
    }
    (*count)++;
}

void readDwellers(DWELLER* dwellers, int count) {
    clearScreen();
    if (count == 0) {
        printf("No dwellers found.\n");
    }
    else {
        for (int i = 0; i < count; i++) {
            printf("Dweller %d:\n", i + 1);
            printf("  First Name: %s\n", dwellers[i].firstName);
            printf("  Last Name: %s\n", dwellers[i].lastName);
            printf("  Health: %d%%\n", dwellers[i].health);
            printf("  Vault ID: %d\n", dwellers[i].vaultID);
            printf("  S.P.E.C.I.A.L: ");
            for (int j = 0; j < 7; j++)
                printf("%d ", dwellers[i].specialAttributes[j]);
            printf("\n");
        }
    }
    printf("\nPress Enter to return to main menu...");
    getchar();
}

void updateDweller(DWELLER* dwellers, int count) {
    int id;
    printf("Enter vault ID of dweller to update: ");
    scanf("%d", &id);
    clearInputBuffer();
    for (int i = 0; i < count; i++) {
        if (dwellers[i].vaultID == id) {
            printf("Updating dweller %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].vaultID);
            while (1) {
                printf("Update first name (current: %s): ", dwellers[i].firstName);
                char tmp[MAX_NAME_LENGTH];
                if (!fgets(tmp, sizeof(tmp), stdin)) continue;
                tmp[strcspn(tmp, "\n")] = 0;
                if (!strlen(tmp)) break;
                strncpy(dwellers[i].firstName, tmp, MAX_NAME_LENGTH);
                break;
            }
            while (1) {
                printf("Update last name (current: %s): ", dwellers[i].lastName);
                char tmp[MAX_NAME_LENGTH];
                if (!fgets(tmp, sizeof(tmp), stdin)) continue;
                tmp[strcspn(tmp, "\n")] = 0;
                if (!strlen(tmp)) break;
                strncpy(dwellers[i].lastName, tmp, MAX_NAME_LENGTH);
                break;
            }
            while (1) {
                printf("Update vault ID (current: %d): ", dwellers[i].vaultID);
                char tmp[20];
                if (!fgets(tmp, sizeof(tmp), stdin)) continue;
                if (tmp[0] == '\n') break;
                int val = atoi(tmp);
                if (val > 0) {
                    dwellers[i].vaultID = val;
                    break;
                }
                printf("Invalid vault ID. Must be positive integer.\n");
            }
            while (1) {
                printf("Update health (0-100) (current: %d): ", dwellers[i].health);
                char tmp[20];
                if (!fgets(tmp, sizeof(tmp), stdin)) continue;
                if (tmp[0] == '\n') break;
                int val = atoi(tmp);
                if (val >= 0 && val <= 100) {
                    dwellers[i].health = val;
                    break;
                }
                printf("Invalid health. Must be 0-100.\n");
            }
            int pointsLeft = MAX_SPECIAL_POINTS;
            for (int j = 0; j < 7; j++) pointsLeft -= dwellers[i].specialAttributes[j];
            for (int j = 0; j < 7; j++) {
                while (1) {
                    printf("Update S.P.E.C.I.A.L. attribute %d - %s (current: %d, points left: %d): ", j + 1, getSpecialAttributeName(j), dwellers[i].specialAttributes[j], pointsLeft + dwellers[i].specialAttributes[j]);
                    char tmp[20];
                    if (!fgets(tmp, sizeof(tmp), stdin)) continue;
                    if (tmp[0] == '\n') break;
                    int val = atoi(tmp);
                    if (val < MIN_SPECIAL_ATTRIBUTE || val > MAX_SPECIAL_ATTRIBUTE) {
                        printf("Value must be between %d and %d.\n", MIN_SPECIAL_ATTRIBUTE, MAX_SPECIAL_ATTRIBUTE);
                        continue;
                    }
                    int potentialTotal = (MAX_SPECIAL_POINTS - pointsLeft) - dwellers[i].specialAttributes[j] + val;
                    if (potentialTotal > MAX_SPECIAL_POINTS) {
                        printf("Total points would exceed %d. Adjust accordingly.\n", MAX_SPECIAL_POINTS);
                        continue;
                    }
                    pointsLeft += dwellers[i].specialAttributes[j];
                    pointsLeft -= val;
                    dwellers[i].specialAttributes[j] = val;
                    break;
                }
            }
            return;
        }
    }
    printf("Dweller with ID %d not found.\n", id);
    printf("\nPress Enter to return to main menu...");
    getchar();
}

void deleteDweller(DWELLER** dwellers, int* count) {
    int id;
    printf("Enter vault ID of dweller to delete: ");
    scanf("%d", &id);
    clearInputBuffer();
    for (int i = 0; i < *count; i++) {
        if ((*dwellers)[i].vaultID == id) {
            for (int j = i; j < *count - 1; j++)
                (*dwellers)[j] = (*dwellers)[j + 1];
            DWELLER* temp = realloc(*dwellers, (*count - 1) * sizeof(DWELLER));
            if (temp != NULL || *count - 1 == 0)
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

void saveToFile(DWELLER* dwellers, int count) {
    FILE* file = fopen("dwellers.dat", "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(dwellers, sizeof(DWELLER), count, file);
    fclose(file);
}

void loadFromFile(DWELLER** dwellers, int* count) {
    FILE* file = fopen("dwellers.dat", "rb");
    if (!file) {
        *count = 0;
        *dwellers = NULL;
        return;
    }
    *dwellers = malloc(MAX_VAULT_RESIDENTS * sizeof(DWELLER));
    if (!*dwellers) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    *count = fread(*dwellers, sizeof(DWELLER), MAX_VAULT_RESIDENTS, file);
    fclose(file);
}

inline int compareFirstName(const void* a, const void* b) {
    return strcmp(((DWELLER*)a)->firstName, ((DWELLER*)b)->firstName);
}

inline int compareLastName(const void* a, const void* b) {
    return strcmp(((DWELLER*)a)->lastName, ((DWELLER*)b)->lastName);
}

inline int compareVaultID(const void* a, const void* b) {
    return ((DWELLER*)a)->vaultID - ((DWELLER*)b)->vaultID;
}

inline int compareSpecialAttributeByIndex(const void* a, const void* b) {
    return ((DWELLER*)a)->specialAttributes[g_specialAttributeSortIndex] - ((DWELLER*)b)->specialAttributes[g_specialAttributeSortIndex];
}

inline int compareSpecialAttributeByIndexDesc(const void* a, const void* b) {
    return ((DWELLER*)b)->specialAttributes[g_specialAttributeSortIndex] - ((DWELLER*)a)->specialAttributes[g_specialAttributeSortIndex];
}

void sortDwellers(DWELLER* dwellers, int count, SortCriteria criteria, int ascending) {
    if (count <= 1)
        return;

    if (criteria == SORT_BY_SPECIAL_ATTRIBUTE) {
        int attrChoice = displaySpecialAttributeMenu();
        if (attrChoice < 1 || attrChoice > 7) {
            printf("Invalid attribute choice.\n");
            printf("\nPress Enter to return to main menu...");
            getchar();
            return;
        }
        g_specialAttributeSortIndex = attrChoice - 1;
        if (ascending)
            qsort(dwellers, count, sizeof(DWELLER), compareSpecialAttributeByIndex);
        else
            qsort(dwellers, count, sizeof(DWELLER), compareSpecialAttributeByIndexDesc);
    }
    else {
        switch (criteria) {
        case SORT_BY_FIRST_NAME:
            qsort(dwellers, count, sizeof(DWELLER), compareFirstName);
            break;
        case SORT_BY_LAST_NAME:
            qsort(dwellers, count, sizeof(DWELLER), compareLastName);
            break;
        case SORT_BY_VAULT_ID:
            qsort(dwellers, count, sizeof(DWELLER), compareVaultID);
            break;
        default:
            printf("Unknown sort criteria.\n");
            printf("\nPress Enter to return to main menu...");
            getchar();
            return;
        }
    }
    printf("Dwellers sorted.\n");
    printf("\nPress Enter to return to main menu...");
    getchar();
}

void searchBySpecialAttributeDetailed(DWELLER* dwellers, int count) {
    int attrIndex = displaySpecialAttributeMenu();
    if (attrIndex < 1 || attrIndex > 7) {
        printf("Invalid attribute choice.\n");
        printf("\nPress Enter to return to main menu...");
        getchar();
        return;
    }
    int searchValue;
    printf("Enter value to search for attribute %s: ", getSpecialAttributeName(attrIndex - 1));
    if (scanf("%d", &searchValue) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        printf("\nPress Enter to return to main menu...");
        getchar();
        return;
    }
    clearInputBuffer();

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (dwellers[i].specialAttributes[attrIndex - 1] == searchValue) {
            if (!found) {
                printf("Dwellers with %d in attribute %s:\n", searchValue, getSpecialAttributeName(attrIndex - 1));
            }
            found = 1;
            printf("  %s %s, Vault ID: %d, Health: %d%%, S.P.E.C.I.A.L: ",
                dwellers[i].firstName, dwellers[i].lastName,
                dwellers[i].vaultID, dwellers[i].health);
            for (int j = 0; j < 7; j++) {
                printf("%d ", dwellers[i].specialAttributes[j]);
            }
            printf("\n");
        }
    }
    if (!found) {
        printf("No dwellers found with attribute %s equal to %d.\n", getSpecialAttributeName(attrIndex - 1), searchValue);
    }
    printf("\nPress Enter to return to main menu...");
    getchar();
}

void searchDweller(DWELLER* dwellers, int count, SearchCriteria criteria) {
    if (count == 0) {
        printf("No dwellers to search.\n");
        printf("\nPress Enter to return to main menu...");
        getchar();
        return;
    }
    char searchString[MAX_NAME_LENGTH];
    int searchID;
    DWELLER key;
    DWELLER* result = NULL;

    switch (criteria) {
    case SEARCH_BY_FIRST_NAME:
        printf("Enter first name to search: ");
        scanf("%49s", searchString);
        clearInputBuffer();
        memset(&key, 0, sizeof(DWELLER));
        strncpy(key.firstName, searchString, MAX_NAME_LENGTH - 1);
        result = (DWELLER*)bsearch(&key, dwellers, count, sizeof(DWELLER), compareFirstName);
        break;
    case SEARCH_BY_LAST_NAME:
        printf("Enter last name to search: ");
        scanf("%49s", searchString);
        clearInputBuffer();
        memset(&key, 0, sizeof(DWELLER));
        strncpy(key.lastName, searchString, MAX_NAME_LENGTH - 1);
        result = (DWELLER*)bsearch(&key, dwellers, count, sizeof(DWELLER), compareLastName);
        break;
    case SEARCH_BY_VAULT_ID:
        printf("Enter vault ID to search: ");
        scanf("%d", &searchID);
        clearInputBuffer();
        memset(&key, 0, sizeof(DWELLER));
        key.vaultID = searchID;
        result = (DWELLER*)bsearch(&key, dwellers, count, sizeof(DWELLER), compareVaultID);
        break;
    default:
        printf("Unknown search criteria.\n");
        printf("\nPress Enter to return to main menu...");
        getchar();
        return;
    }

    if (result != NULL) {
        printf("Dweller found:\n");
        printf("  First Name: %s\n", result->firstName);
        printf("  Last Name: %s\n", result->lastName);
        printf("  Health: %d%%\n", result->health);
        printf("  Vault ID: %d\n", result->vaultID);
        printf("  S.P.E.C.I.A.L.: ");
        for (int i = 0; i < 7; i++) {
            printf("%d ", result->specialAttributes[i]);
        }
        printf("\n");
    }
    else {
        printf("Dweller not found.\n");
    }
    printf("\nPress Enter to return to main menu...");
    getchar();
}
