#include "functions.h"
#include "dataType.h"

//koncept 10.

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
	printf("[3. S.P.E.C.I.A.L. attribute]\n");
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

int displayAttrMenu(void) {
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

