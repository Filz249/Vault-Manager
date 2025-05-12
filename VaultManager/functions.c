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
		char buf[20];
		printf("Enter vault ID: ");
		if (!fgets(buf, sizeof(buf), stdin)) {
			continue;
		}
		if (sscanf(buf, "%d", &newDweller->id) == 1 && newDweller->id > 0) {
			break;
		}
		printf("Invalid vault ID. Must be positive integer.\n");
	}
	while (1) {
		char buf[20];
		float val;
		printf("Enter health (0-100%%): ");
		if (!fgets(buf, sizeof(buf), stdin)) {
			continue;
		}
		if (sscanf(buf, "%f", &val) == 1 && val >= 0 && val <= 100.00) {
			newDweller->health = val;
			break;
		}
		printf("Invalid health. Must be 0-100%%.\n");
	}
	int points = MAX_POINTS;
	for (int i = 0; i < 7; i++) {
		while (1) {
			int val;
			char buf[20];
			printf("Enter S.P.E.C.I.A.L attribute %d - %s (points left: %d, min 1, max 10): ", i + 1, getAttrName(i), points);
			if (!fgets(buf, sizeof(buf), stdin)) {
				continue;
			}
			if (sscanf(buf, "%d", &val) != 1) {
				printf("Invalid input. Enter an integer.\n");
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
				if (!strlen(tmp)){
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
				val = atoi(tmp);
				if (val >= 0 && val <= 100) {
					dwellers[i].health = val;
					break;
				}
				printf("Invalid health. Must be 0-100.\n");
			}
			int points = MAX_POINTS;
			for (int j = 0; j < 7; j++) {
				points -= dwellers[i].specAttr[j];
			}
			for (int j = 0; j < 7; j++) {
				while (1) {
					printf("Update S.P.E.C.I.A.L. attribute %d - %s (current: %d, points left: %d): ", 
						j + 1, getAttrName(j), 
						dwellers[i].specAttr[j], 
						points + dwellers[i].specAttr[j]);

					char tmp[20];
					if (!fgets(tmp, sizeof(tmp), stdin)) continue;
					if (tmp[0] == '\n') break;
					int val = atoi(tmp);
					if (val < MIN_ATTR || val > MAX_ATTR) {
						printf("Value must be between %d and %d.\n", MIN_ATTR, MAX_ATTR);
						continue;
					}
					int potentialTotal = (MAX_POINTS - points) - dwellers[i].specAttr[j] + val;
					if (potentialTotal > MAX_POINTS) {
						printf("Total points would exceed %d. Adjust accordingly.\n", MAX_POINTS);
						continue;
					}
					points += dwellers[i].specAttr[j];
					points -= val;
					dwellers[i].specAttr[j] = val;
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


void sortDwellers(DWELLER* dwellers, int count, SortCriteria criteria, int ascending) {
	if (count <= 1)
		return;

	if (criteria == SORT_ATTR ) {
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


void searchDweller(DWELLER* dwellers, int count, SearchCriteria criteria) {
	if (count == 0) {
		printf("No dwellers to search.\n");
		printf("\nPress Enter to return to main menu...");
		getchar();
		return;
	}
	char searchString[MAX_NAME];
	int searchID;
	int searchAttr;
	DWELLER key;
	DWELLER* result = NULL;
	
	//KONCEPT 11.

	switch (criteria) {

	case SEARCH_FIRST:

		printf("Enter first name to search: ");
		scanf("%49s", searchString);
		clearInputBuffer();
		memset(&key, 0, sizeof(DWELLER));
		strncpy(key.firstName, searchString, MAX_NAME - 1);
		result = (DWELLER*)bsearch(&key, dwellers, count, sizeof(DWELLER), compFirstN);
		break;

	case SEARCH_LAST:

		printf("Enter last name to search: ");
		scanf("%49s", searchString);
		clearInputBuffer();
		memset(&key, 0, sizeof(DWELLER));
		strncpy(key.lastName, searchString, MAX_NAME - 1);
		result = (DWELLER*)bsearch(&key, dwellers, count, sizeof(DWELLER), compLastN);
		break;

	case SEARCH_ID:

		printf("Enter vault ID to search: ");
		scanf("%d", &searchID);
		clearInputBuffer();
		memset(&key, 0, sizeof(DWELLER));
		key.id = searchID;
		result = (DWELLER*)bsearch(&key, dwellers, count, sizeof(DWELLER), compID);
		break;

	case SEARCH_ATTR: 
	{
		int attrIndex;
		do {
			attrIndex = displayAttrMenu();
			printf("Invalid attribute choice.\n");
		}while (attrIndex < 1 || attrIndex > 7);
		printf("Enter attribute number %s: ", getAttrName(attrIndex - 1));
		scanf("%d", &searchAttr);
		clearInputBuffer();

		int found = 0;
		for (int i = 0; i < count; i++) { 
			if (dwellers[i].specAttr[attrIndex - 1] == searchAttr) {
				if (!found) {
					printf("Dwellers with %d in attribute %s:\n", searchAttr, getAttrName(attrIndex - 1));
				}
				found = 1;
				printf(" %s %s, ID: %d, Health %.2f%%, Attributes: ", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id, dwellers[i].health);
				for (int i = 0; i < 7; i++) {
					printf("%s: %d\t", );
				}
			}
		}
		break;
	}

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
		printf("  Health: %.2f%%\n", result->health);
		printf("  Vault ID: %d\n", result->id);
		printf("  S.P.E.C.I.A.L.: ");
		for (int i = 0; i < 7; i++) {
			printf("%d ", result-> specAttr[i]);
		}
		printf("\n");
	}
	else {
		printf("Dweller not found.\n");
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