#include "functions.h"

int main() {
    DWELLER* dwellers = NULL;
    int count = 0;
    loadFromFile(&dwellers, &count);
    int choice;

    do {
        choice = displayMenu();

        switch (choice) {
        case CREATE:
            createDweller(&dwellers, &count);
            break;
        case READ:
            readDwellers(dwellers, count);
            break;
        case UPDATE:
            updateDweller(dwellers, count);
            break;
        case SEARCH: {
            int searchChoice = displaySearchMenu();
            if (searchChoice >= 1 && searchChoice <= 3) {
                searchDweller(dwellers, count, (SearchCriteria)(searchChoice - 1));
            }
            else if (searchChoice == 4) {
                searchBySpecialAttributeDetailed(dwellers, count);
            }
            else {
                printf("Invalid search criteria.\n");
                printf("\nPress Enter to return to main menu...");
                getchar();
            }
            break;
        }
        case SORT: {
            int sortChoice = displaySortMenu();
            if (sortChoice >= 1 && sortChoice <= 4) {
                int orderChoice = 1; // default ascending
                if (sortChoice == 4) {
                    orderChoice = displaySortOrderMenu();
                    if (orderChoice != 1 && orderChoice != 2) {
                        printf("Invalid sort order. Defaulting to ascending.\n");
                        orderChoice = 1;
                    }
                }
                sortDwellers(dwellers, count, (SortCriteria)(sortChoice - 1), (orderChoice == 1));
            }
            else {
                printf("Invalid sort criteria.\n");
                printf("\nPress Enter to return to main menu...");
                getchar();
            }
            break;
        }
        case DELETE:
            deleteDweller(&dwellers, &count);
            break;
        case EXIT: {
            printf("Are you sure you want to exit? (Y/N): ");
            char confirm[4];
            scanf("%3s", confirm);
            clearInputBuffer();
            if (confirm[0] == 'Y' || confirm[0] == 'y') {
                saveToFile(dwellers, count);
                printf("Exiting program.\n");
                break;
            }
            else {
                choice = 0;
            }
            break;
        }
        default:
            printf("Invalid choice. Please try again.\n");
            printf("\nPress Enter to return to main menu...");
            getchar();
        }
    } while (choice != EXIT);

    free(dwellers);
    return 0;
}
