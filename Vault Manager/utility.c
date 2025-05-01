#include "functions.h"
#include "dataType.h"


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
            printf("  %s %s, Vault ID: %d, Health: %.1f%%, S.P.E.C.I.A.L: ",
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


void quickSortLastName(DWELLER* arr, int low, int high) {
    if (low < high) {
        DWELLER pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (compareLastName(&arr[j], &pivot) <= 0) {
                i++;
                DWELLER temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        DWELLER temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;

        quickSortLastName(arr, low, pi - 1);
        quickSortLastName(arr, pi + 1, high);
    }
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


int copyFile(const char* src, const char* dest) {
    FILE* source = fopen(src, "rb");
    if (!source) return 0;

    FILE* destination = fopen(dest, "wb");
    if (!destination) {
        fclose(source);
        return 0;
    }

    char buffer[4096];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes, destination) != bytes) {
            fclose(source);
            fclose(destination);
            return 0;
        }
    }

    fclose(source);
    fclose(destination);
    return 1;
}


void saveToFile(DWELLER* dwellers, int count) {
    FILE* file = fopen("dwellers.txt", "w");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "First name: %s\nLast name: %s\nID: %d\nHealth: %.1f%%\n",
            dwellers[i].firstName,
            dwellers[i].lastName,
            dwellers[i].vaultID,
            dwellers[i].health);
        for (int j = 0; j < 7; j++) {
            char attr_letter = "SPECIAL"[j]; // Prvo slovo atributa
            fprintf(file, "%c: %d ", attr_letter, dwellers[i].specialAttributes[j]);
        }
        fprintf(file, "\n"); // New line for each dweller
    }

    if (fclose(file) != 0) {
        perror("Error closing file after writing");
    }
}


void loadFromFile(DWELLER** dwellers, int* count) {
    FILE* file = fopen("dwellers.txt", "r");
    if (!file) {
        *count = 0;
        *dwellers = NULL;
        return;
    }

    *count = 0;
    *dwellers = malloc(MAX_VAULT_RESIDENTS * sizeof(DWELLER));
    if (!*dwellers) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "First name: %49s\nLast name: %49s\nID: %d\nHealth: %f\n",
        (*dwellers)[*count].firstName,
        (*dwellers)[*count].lastName,
        &(*dwellers)[*count].vaultID,
        &(*dwellers)[*count].health) == 4) {

        for (int j = 0; j < 7; j++) {
            char attr_letter;
            int val;
            fscanf(file, " %c: %d", &attr_letter, &val);
            (*dwellers)[*count].specialAttributes[j] = val;
        }
        (*count)++;
        if (*count >= MAX_VAULT_RESIDENTS) {
            break; // Prevent overflow
        }
    }

    if (ferror(file)) {
        perror("Error reading file");
        free(*dwellers);
        *dwellers = NULL;
        *count = 0;
    }

    if (fclose(file) != 0) {
        perror("Error closing file after reading");
    }
}