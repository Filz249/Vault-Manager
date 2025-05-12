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

void searchByAttr(DWELLER* dwellers, int count) {
	int attrIndex = displayAttrMenu();
	if (attrIndex < 1 || attrIndex > 7) {
		printf("Invalid attribute choice.\n");
		printf("\nPress Enter to return to main menu...");
		getchar();
		return;
	}
	int searchValue;
	printf("Enter value to search for attribute %s: ", getAttrName(attrIndex - 1));
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
		if (dwellers[i].specAttr[attrIndex - 1] == searchValue) {
			if (!found) {
				printf("Dwellers with %d in attribute %s:\n", searchValue, getAttrName(attrIndex - 1));
			}
			found = 1;
			printf("  %s %s, Vault ID: %d, Health: %.2f%%, S.P.E.C.I.A.L: ",
				dwellers[i].firstName, dwellers[i].lastName,
				dwellers[i].id, dwellers[i].health);
			for (int j = 0; j < 7; j++) {
				printf("%d ", dwellers[i].specAttr[j]);
			}
			printf("\n");
		}
	}
	if (!found) {
		printf("No dwellers found with attribute %s equal to %d.\n", getAttrName(attrIndex - 1), searchValue);
	}
	printf("\nPress Enter to return to main menu...");
	getchar();
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