#include "functions.h"
#include "dataType.h"

void saveToFile(DWELLER* dwellers, int count) {
    FILE* file = fopen("dwellers.txt", "w");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(dwellers, sizeof(DWELLER), count, file);
    fclose(file);
}

void loadFromFile(DWELLER** dwellers, int* count) {
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
        exit(EXIT_FAILURE);
    }
    *count = fread(*dwellers, sizeof(DWELLER), MAX_DWELLERS, file);
    fclose(file);
}

const char* getAttrName(int index) {
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
