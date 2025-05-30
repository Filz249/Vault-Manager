#include "functions.h"
#include "dataType.h"

int main() {
    DWELLER* dwellers = NULL;
    int count = 0;
    loadFromFile(&dwellers, &count);
    int choice;

    // KONCEPT 11.
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
            if (searchChoice >= 1 && searchChoice <= 4) {
                searchDweller(dwellers, count, (SEARCH_CR)(searchChoice - 1));
            }
            else {
                printf("Invalid search choice.\n");
            }
            break;
        }
        case SORT: {
            int sortChoice = displaySortMenu();
            if (sortChoice >= 1 && sortChoice <= 6) {
                int orderChoice = 1;
                if (sortChoice == 5 || sortChoice == 6) {
                    orderChoice = displaySortOrderMenu();
                    if (orderChoice != 1 && orderChoice != 2) {
                        printf("Invalid sort order. Defaulting to ascending.\n");
                        orderChoice = 1;
                    }
                }
                sortDwellers(dwellers, count, (SORT_CR)(sortChoice - 1), (orderChoice == 1));
            }
            else {
                printf("Invalid sort criteria.\n");
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
        }
    } while (choice != EXIT);

    free(dwellers);
    return 0;
}
