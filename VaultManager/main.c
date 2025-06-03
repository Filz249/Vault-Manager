#include "functions.h"
#include "dataType.h"

int main() {
    DWELLER* dwellers = NULL;
    long* positions = NULL; 
    int count = 0;

    loadFromFile(&dwellers, &count);

    int choice;

    do {
        choice = displayMenu();

        switch (choice) {
        case CREATE:
            createDwellers(&dwellers, &count);
            break;

        case READ:
            readDwellers(dwellers, count);
            break;

        case UPDATE:
            updateDwellers(dwellers, count);
            break;

        case SEARCH: {
            int searchChoice = displaySearchMenu();
            if (searchChoice >= 1 && searchChoice <= 4) {
                searchDwellers(dwellers, count, (SEARCH_CR)(searchChoice - 1));
            }
            else if (searchChoice == 5) {
                continue;
            }
            else {
                printf("Invalid search choice.\n");
            }
            break;
        }

        case SORT: {
            int sortChoice = displaySortMenu();
            if (sortChoice >= 1 && sortChoice <= 6) {
                sortDwellers(dwellers, count, (SORT_CR)(sortChoice - 1));
            }
            else if (sortChoice == 7) {
                continue;
            }
            else {
                printf("Invalid sort criteria.\n");
            }
            break;
        }

        case DELETE:
            deleteDwellers(&dwellers, &count);
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
    free(positions);

    return 0;
}