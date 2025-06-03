#include "functions.h"
#include "dataType.h"


//kreiranje 
void createDwellers(DWELLER** const dwellers, int* const count){
if(*count >= MAX_DWELLERS){
        printf("Maximum number of dwellers reached.\n");
        return;
    }

    DWELLER* temp = realloc(*dwellers, (*count + 1) * sizeof(DWELLER));
    if(!temp){
        perror("Failed to allocate memory");
        return;
    }
    *dwellers = temp;
    DWELLER* newDweller = &(*dwellers)[*count];

    do{
        printf("Enter first name: ");
        if(!fgets(newDweller->firstName, MAX_NAME, stdin)){
            continue;
        }
        newDweller->firstName[strcspn(newDweller->firstName, "\n")] = '\0';
    }while(!strlen(newDweller->firstName) || !validName(newDweller->firstName));

    do{
        printf("Enter last name: ");
        if(!fgets(newDweller->lastName, MAX_NAME, stdin)){
            continue;
        }
        newDweller->lastName[strcspn(newDweller->lastName, "\n")] = '\0';
    }while(!strlen(newDweller->lastName) || !validName(newDweller->lastName));

    do{
        printf("Enter ID: ");
        if(scanf("%d", &newDweller->id) == 1 && newDweller->id > 0){
            if(!validID(*dwellers, *count, newDweller->id)){
                break;
            }
            printf("ID already in use.\n");
        }else{
            printf("Invalid ID.\n");
        }
        clearInputBuffer();
    }while(1);

    do{
        printf("Enter age: ");
        if(scanf("%d", &newDweller->age) == 1 && newDweller->age > 0 && newDweller->age <= 120){
            break;
        }
        printf("Invalid age.\n");
        clearInputBuffer();
    }while(1);

    do{
        printf("Enter height (in cm): ");
        if(scanf("%f", &newDweller->height) == 1 &&
            newDweller->height >= 50.0f && newDweller->height <= 300.0f){
            break;
        }
        printf("Invalid height. Must be between 50 and 300 cm.\n");
        clearInputBuffer();
    }while(1);

    do{
        printf("Enter birth date (DD/MM/YYYY): ");
        if(scanf("%d/%d/%d", &newDweller->birthDate.day, &newDweller->birthDate.month, &newDweller->birthDate.year) == 3){
            if(validDate(newDweller->birthDate.day, newDweller->birthDate.month, newDweller->birthDate.year)){
                break;
            }
        }
        printf("Invalid date. Please enter a valid birth date.\n");
        clearInputBuffer();
    }while(1);

    do{
        printf("Enter registration date (DD/MM/YYYY): ");
        if(scanf("%d/%d/%d", &newDweller->regDate.day, &newDweller->regDate.month, &newDweller->regDate.year) == 3){
            if(validDate(newDweller->regDate.day, newDweller->regDate.month, newDweller->regDate.year)){
                break;
            }
        }
        printf("Invalid date. Please enter a valid registration date.\n");
        clearInputBuffer();
    }while(1);

    (*count)++;
    totalDwellers++;
    printf("Dweller created successfully.\n");
    saveToFile(*dwellers, *count);
}


//čitanje
void readDwellers(const DWELLER* const dwellers, const int count) {
    clearScreen();
    printf("Total dwellers: %d\n\n", totalDwellers);
    if (count == 0) {
        printf("No dwellers found.\n");
    }
    else {
        for (int i = 0; i < count; i++) {
            printf("  First Name: %s\n", dwellers[i].firstName);
            printf("  Last Name: %s\n", dwellers[i].lastName);
            printf("  Age: %d\n", dwellers[i].age);
            printf("  Height: %.2f cm\n", dwellers[i].height);
            printf("  Birth Date: %02d/%02d/%04d\n", dwellers[i].birthDate.day, dwellers[i].birthDate.month, dwellers[i].birthDate.year);
            printf("  Registration Date: %02d/%02d/%04d\n", dwellers[i].regDate.day, dwellers[i].regDate.month, dwellers[i].regDate.year);
            printf("  ID: %d\n\n", dwellers[i].id);
        }
    }
    printf("Press Enter to return to main menu...");
    getchar();
}



//ažuriranje
void updateDwellers(DWELLER* const dwellers, const int count){
    int id;
    printf("Enter ID of dweller to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (dwellers[i].id == id) {
            UPDATE_CH updateChoices[] = {
                updateFirstName,
                updateLastName,
                updateAge,
                updateHeight,
                updateBirthDate,
                updateRegDate
            };

            int updateChoice;
            do {
                updateChoice = displayUpdateMenu();
                if (updateChoice >= UPDATE_FIRST_NAME && updateChoice <= UPDATE_REG_DATE) {
                    updateChoices[updateChoice - 1](&dwellers[i]);
                }else if (updateChoice == UPDATE_EXIT) {
                    printf("Exiting update menu.\n");
                }else {
                    printf("Invalid choice. Please try again.\n");
                }
            }while (updateChoice != UPDATE_EXIT);
            return;
        }
    }
    printf("Dweller with ID %d not found.\n", id);
    printf("\nPress Enter to return to main menu...");
    getchar();
}


// SORTIRANJE
void sortDwellers(DWELLER* const dwellers, const int count, const SORT_CR criteria){
    insertionSort(dwellers, count, criteria);
    printf("Dwellers sorted.\n");
    printf("\nPress Enter to return to main menu...");
    getchar();
}


// PRETRAŽIVANJE
void searchDwellers(const DWELLER* const dwellers, const int count, const SEARCH_CR criteria){

    /*
   ========================
           KONCEPT 6.
   ========================
   */
    static int searchCount = 0;
    searchCount++;
    if (count == 0) {
        printf("No dwellers to search.\n");
        printf("\nPress Enter to return to main menu...");
        getchar();
        return;
    }
    char searchString[MAX_NAME];
    int searchID;
    int found = 0;

    switch (criteria) {
    case SEARCH_FIRST:
        printf("Enter first name to search: ");
        scanf("%49s", searchString);
        clearInputBuffer();
        for (int i = 0; i < count; i++) {
            if (strcmp(dwellers[i].firstName, searchString) == 0) {
                printf("Found: %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
                found = 1;
                printf("Searched %d times.\n", searchCount);
            }
        }
        break;

    case SEARCH_LAST:
        printf("Enter last name to search: ");
        scanf("%49s", searchString);
        clearInputBuffer();
        for (int i = 0; i < count; i++) {
            if (strcmp(dwellers[i].lastName, searchString) == 0) {
                printf("Found: %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
                found = 1;
                printf("Searched %d times.\n", searchCount);
            }
        }
        break;

    case SEARCH_ID:
        printf("Enter vault ID to search: ");
        scanf("%d", &searchID);
        clearInputBuffer();
        for (int i = 0; i < count; i++) {
            if (dwellers[i].id == searchID) {
                printf("Found: %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
                found = 1;
                printf("Searched %d times.\n", searchCount);
            }
        }
        break;

    case SEARCH_AGE: {
        int searchAge;
        printf("Enter age to search: ");
        scanf("%d", &searchAge);
        clearInputBuffer();
        for (int i = 0; i < count; i++) {
            if (dwellers[i].age == searchAge) {
                printf("Found: %s %s (ID: %d)\n", dwellers[i].firstName, dwellers[i].lastName, dwellers[i].id);
                found = 1;
                printf("Searched %d times.\n", searchCount);
            }
        }
        break;
    }
    default:
        printf("Unknown search criteria.\n");
        break;
    }
    if (!found) {
        printf("No dwellers found matching the criteria.\n");
    }
    printf("\nPress Enter to return to main menu...");
    getchar();
}


//brisanje
void deleteDwellers(DWELLER** const dwellers, int* const count) {
    int choice = displayDeletionMenu();
    if (choice == 1) {
        copyFile("dwellers.txt", "dwellers_backup.txt");

        removeDwellersFile();
        *count = 0;
        free(*dwellers);
        *dwellers = NULL;
        printf("All dwellers have been removed. Backup saved as dwellers_backup.txt\n");
    }
    else if (choice == 2) {
        int id;
        printf("Enter ID of dweller to delete: ");
        scanf("%d", &id);
        clearInputBuffer();

        for (int i = 0; i < *count; i++) {
            if ((*dwellers)[i].id == id) {
                for (int j = i; j < *count - 1; j++) {
                    (*dwellers)[j] = (*dwellers)[j + 1];
                }
                (*count)--;

                DWELLER* temp = realloc(*dwellers, (*count) * sizeof(DWELLER));
                if (temp || *count == 0) {
                    *dwellers = temp;
                }
                else {
                    perror("Failed to reallocate memory");
                    free(*dwellers);
                    *dwellers = NULL;
                    *count = 0;
                    exit(EXIT_FAILURE);
                }

                saveToFile(*dwellers, *count);
                printf("Dweller with ID %d deleted.\n", id);
                printf("\nPress Enter to return to main menu...");
                getchar();
                return;
            }
        }
        printf("Dweller with ID %d not found.\n", id);
    }
    else {
        printf("Returning to main menu...\n");
    }
    printf("\nPress Enter to return to main menu...");
    getchar();
}

