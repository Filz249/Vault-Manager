#include "functions.h"
#include "dataType.h"

static int attrSortIndex = 0;

inline int compFirstN(const void* a, const void* b) {
    return strcmp(((DWELLER*)a)->firstName, ((DWELLER*)b)->firstName);
}

inline int compLastN(const void* a, const void* b) {
    return strcmp(((DWELLER*)a)->lastName, ((DWELLER*)b)->lastName);
}

inline int compID(const void* a, const void* b) {
    return ((DWELLER*)a)->id - ((DWELLER*)b)->id;
}

inline int compAttrAsc(const void* a, const void* b) {
    return ((DWELLER*)a)->specAttr[attrSortIndex] - ((DWELLER*)b)->specAttr[attrSortIndex];
}

inline int compAttrDesc(const void* a, const void* b) {
    return ((DWELLER*)b)->specAttr[attrSortIndex] - ((DWELLER*)a)->specAttr[attrSortIndex];
}

extern void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void createDweller(DWELLER** dwellers, int* count) {
    if (*count >= MAX_DWELLERS) {
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
        printf("Enter vault ID: ");
        if (scanf("%d", &newDweller->id) == 1 && newDweller->id > 0) {
            break;
        }
        printf("Invalid vault ID. Must be positive integer.\n");
        clearInputBuffer();
    }

    while (1) {
        printf("Enter health (0-100%%): ");
        if (scanf("%f", &newDweller->health) == 1 && newDweller->health >= 0 && newDweller->health <= 100.00) {
            break;
        }
        printf("Invalid health. Must be 0-100%%.\n");
        clearInputBuffer();
    }

    int points = MAX_POINTS;
    for (int i = 0; i < 7; i++) {
        while (1) {
            int val;
            printf("Enter S.P.E.C.I.A.L attribute %d - %s (points left: %d, min 1, max 10): ", i + 1, getAttrName(i), points);
            if (scanf("%d", &val) != 1) {
                printf("Invalid input. Enter an integer.\n");
                clearInputBuffer();
                continue;
            }
            if (val < MIN_ATTR || val > MAX_ATTR) {
                printf("Value must be between %d and %d.\n", MIN_ATTR, MAX_ATTR);
                continue;
            }
            if (val > points - (7 - i - 1)) {
                printf("Not enough points left. Reserve points for remaining attributes.\n");
                continue;
            }
            newDweller->specAttr[i] = val;
            points -= val;
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
            printf("  Health: %.2f%%\n", dwellers[i].health);
            printf("  Vault ID: %d\n", dwellers[i].id);
            printf("  S.P.E.C.I.A.L: ");
            for (int j = 0; j < 7; j++)
                printf("%d ", dwellers[i].specAttr[j]);
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
                printf("Update vault ID (current: %d): ", dwellers[i].id);
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
                printf("Invalid vault ID. Must be positive integer.\n");
            }

            while (1) {
                printf("Update health (0-100%%) (current: %.2f): ", dwellers[i].health);
                char tmp[20];
                float val;
                if (!fgets(tmp, sizeof(tmp), stdin)) {
                    continue;
                }
                if (tmp[0] == '\n') {
                    break;
                }
                val = atof(tmp);
                if (val >= 0 && val <= 100) {
                    dwellers[i].health = val;
                    break;
                }
                printf("Invalid health. Must be 0-100.\n");
            }

            int points = MAX_POINTS;
            for (int j = 0; j < 7; j++) {
                dwellers[i].specAttr[j] = 0;
            }

            for (int j = 0; j < 7; j++) {
                while (1) {
                    printf("Update S.P.E.C.I.A.L. attribute %d - %s (points left: %d): ",
                        j + 1, getAttrName(j), points);
                    char tmp[20];
                    if (!fgets(tmp, sizeof(tmp), stdin)) {
                        continue;
                    }
                    if (tmp[0] == '\n') {
                        break;
                    }
                    int val = atoi(tmp);
                    if (val < MIN_ATTR || val > MAX_ATTR) {
                        printf("Value must be between %d and %d.\n", MIN_ATTR, MAX_ATTR);
                        continue;
                    }
                    if (val > points) {
                        printf("Not enough points left. You have %d points available.\n", points);
                        continue;
                    }
                    dwellers[i].specAttr[j] = val;
                    points -= val;
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

void sortDwellers(DWELLER* dwellers, int count, SORT_CR criteria, int ascending) {
    if (count <= 1) return;

    if (criteria == SORT_ATTR) {
        int attrChoice = displayAttrMenu();
        if (attrChoice < 1 || attrChoice > 7) {
            printf("Invalid attribute choice.\n");
            printf("\nPress Enter to return to main menu...");
            getchar();
            return;
        }
        attrSortIndex = attrChoice - 1;
        if (ascending)
            qsort(dwellers, count, sizeof(DWELLER), compAttrAsc);
        else
            qsort(dwellers, count, sizeof(DWELLER), compAttrDesc);
    }
    else {
        switch (criteria) {
        case SORT_FIRST:
            qsort(dwellers, count, sizeof(DWELLER), compFirstN);
            break;
        case SORT_LAST:
            qsort(dwellers, count, sizeof(DWELLER), compLastN);
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
void searchDweller(DWELLER* dwellers, int count, SEARCH_CR criteria) {
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
            }
        }
        break;

    case SEARCH_ATTR: {
        int attrIndex = displayAttrMenu();
        if (attrIndex < 1 || attrIndex >= 8) {
            printf("Invalid attribute choice.\n");
            return;
        }
        int searchValue;
        printf("Enter value to search for attribute %s: ", getAttrName(attrIndex));
        scanf("%d", &searchValue);
        clearInputBuffer();
        for (int i = 0; i < count; i++) {
            if (dwellers[i].specAttr[attrIndex] == searchValue) {
                printf("Found: %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
                found = 1;
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

void deleteDweller(DWELLER** dwellers, int* count) {
    int id;
    printf("Enter vault ID of dweller to delete: ");
    scanf("%d", &id);
    clearInputBuffer();
    for (int i = 0; i < *count; i++) {
        if ((*dwellers)[i].id == id) {
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
