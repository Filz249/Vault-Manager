#include "functions.h"
#include "dataType.h"

/*
========================
        KONCEPT 10.
========================
*/

int displayMenu(void) {
    int choice;
    do {
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

        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 7) {
            printf("Invalid choice. Please enter a number between 1 and 7.\n");
            printf("Press Enter to try again...");
            getchar();
        }
    } while (choice < 1 || choice > 7);

    return choice;
}


int displayUpdateMenu(void) {
    int choice;
    do {
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

        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 7) {
            printf("Invalid choice. Please enter a number between 1 and 7.\n");
            printf("Press Enter to try again...");
            getchar();
        }
    } while (choice < 1 || choice > 7);

    return choice;
}


int displaySortMenu(void) {
    int choice;
    do {
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

        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 7) {
            printf("Invalid choice. Please enter a number between 1 and 7.\n");
            printf("Press Enter to try again...");
            getchar();
        }
    } while (choice < 1 || choice > 7);

    return choice;
}


int displaySearchMenu(void) {
    int choice;
    do {
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

        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 5) {
            printf("Invalid choice. Please enter a number between 1 and 5.\n");
            printf("Press Enter to try again...");
            getchar(); 
        }
    } while (choice < 1 || choice > 5);

    return choice;
}


int displayDeletionMenu() {
    int choice;
    do {
        clearScreen();
        printf("\033[32m");
        printf("=============== DELETE DWELLERS ===============\n");
        printf("_______________________________________________\n");
        printf("[1. Delete dwellers.txt]\n");
        printf("[2. Delete individual dweller by ID]\n");
        printf("[3. Back to main menu]\n");
        printf("_______________________________________________\n");
        printf("Choose action: ");

        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 3) {
            printf("Invalid choice. Please enter a number between 1 and 3.\n");
            printf("Press Enter to try again...");
            getchar();
        }
    } while (choice < 1 || choice > 3);

    return choice;
}
