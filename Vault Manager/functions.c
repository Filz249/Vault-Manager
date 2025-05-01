#include "functions.h"
#include "dataType.h"


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


static int g_specialAttributeSortIndex = 0;

inline void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

inline void clearScreen(void) {
    printf("\033[H\033[J");
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
        int val = 0;
        if (sscanf(buf, "%d", &val) == 1 && val > 0) {
            newDweller->vaultID = val;
            break;
        }
        printf("Invalid vault ID. Must be positive integer.\n");
    }
    while (1) {
        char buf[20];
        printf("Enter health (0.0-100.0): ");
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        float val = -1.0f;
        if (sscanf(buf, "%f", &val) == 1 && val >= 0.0f && val <= 100.0f) {
            newDweller->health = val;
            break;
        }
        printf("Invalid health. Must be 0.0-100.0.\n");
    }
    int pointsLeft = MAX_SPECIAL_POINTS;
    for (int i = 0; i < 7; i++) {
        while (1) {
            char buf[20];
            printf("Enter S.P.E.C.I.A.L attribute %d - %s (points left: %d, min 1, max 10): ",
                i + 1, getSpecialAttributeName(i), pointsLeft);
            if (!fgets(buf, sizeof(buf), stdin)) continue;
            int val = 0;
            if (sscanf(buf, "%d", &val) == 1 && val >= MIN_SPECIAL_ATTRIBUTE && val <= MAX_SPECIAL_ATTRIBUTE && val <= pointsLeft - (7 - i - 1)) {
                newDweller->specialAttributes[i] = val;
                pointsLeft -= val;
                break;
            }
            printf("Invalid value or not enough points left.\n");
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
            printf("  Health: %.1f%%\n", dwellers[i].health);
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
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID.\n");
        return;
    }
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
                printf("Update health (0.0-100.0) (current: %.1f): ", dwellers[i].health);
                char tmp[20];
                if (!fgets(tmp, sizeof(tmp), stdin)) continue;
                if (tmp[0] == '\n') break;
                float val = atof(tmp);
                if (val >= 0.0f && val <= 100.0f) {
                    dwellers[i].health = val;
                    break;
                }
                printf("Invalid health. Must be 0.0-100.0.\n");
            }
            int pointsLeft = MAX_SPECIAL_POINTS;
            for (int j = 0; j < 7; j++)
                pointsLeft -= dwellers[i].specialAttributes[j];
            for (int j = 0; j < 7; j++) {
                while (1) {
                    printf("Update S.P.E.C.I.A.L. attribute %d - %s (current: %d, points left: %d): ",
                        j + 1, getSpecialAttributeName(j), dwellers[i].specialAttributes[j], pointsLeft + dwellers[i].specialAttributes[j]);
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
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID.\n");
        return;
    }
    clearInputBuffer();
    for (int i = 0; i < *count; i++) {
        if ((*dwellers)[i].vaultID == id) {
            for (int j = i; j < *count - 1; j++) {
                (*dwellers)[j] = (*dwellers)[j + 1];
            }
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
        printf("  Health: %.1f%%\n", result->health);
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