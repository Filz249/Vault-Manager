#include "functions.h"
#include "dataType.h"

/*
========================
        KONCEPT 10.
========================
*/

int displayMenu(void) {
    clearScreen();
    printf("\033[32m");
    printf("=============== VAULT MANAGER =================\n");
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

int displayUpdateMenu(void) {
    clearScreen();
    printf("\033[32m");
    printf("=============== UPDATE DWELLER =================\n");
    printf("_______________________________________________\n");
    printf("[1. First Name]\n");
    printf("[2. Last Name]\n");
    printf("[3. Age]\n");
    printf("[4. Height]\n");
    printf("[5. Birth Date]\n");
    printf("[6. Registration Date]\n");
    printf("[7. Back]\n");
    printf("_______________________________________________\n");
    printf("Enter data to update: ");

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
    printf("[3. Age]\n");
    printf("[4. Height]\n");
    printf("[5. Birth Date]\n");
    printf("[6. Registration Date]\n");
    printf("[7. Back]\n");
    printf("_______________________________________________\n");
    printf("Enter sort criteria: ");

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
    printf("[3. ID]\n");
    printf("[4. Age]\n");
    printf("[5. Back]\n");
    printf("_______________________________________________\n");
    printf("Enter search criteria: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

int displayDeletionMenu() {
    printf("\033[32m");
    printf("=============== DELETE DWELLERS ===============\n");
    printf("_______________________________________________\n");
    printf("[1. Delete dwellers.txt]\n");
    printf("[2. Delete individual dweller by ID]\n");
    printf("[3. Back to main menu]\n");
    printf("_______________________________________________\n");
    printf("Choose action: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

