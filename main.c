#include <stdio.h>
#include <string.h>
#include "Functions.h"

int main() {  //farid

    Lists lists = {NULL};
    int choice = 0, subchoice = 0; /* Choice controls overall menu option, subchoice controls submenu options */
    char data[STRING_LENGTH], oldData[STRING_LENGTH], newData[STRING_LENGTH] , name[STRING_LENGTH];

    while (choice != 6) {

        printf("\nMenu:\n");
        printf("1. Display board\n");
        printf("2. load board from file\n");
        printf("3. Edit list\n");
        printf("4. Edit board\n");
        printf("5. Save board to a file\n");
        printf("6. Exit\n");

        printf("Enter your choice: \n");
        scanf("%d", &choice);
        getchar(); // consume newline character
        subchoice = 0; // Resets subchoice to avoid bug where submenu becomes unaccessible

        switch (choice) {

            /* Print board */
            case 1:
                printLists(&lists);
                break;

                /* List load from file */
            case 2:
                query("Please enter name of list to load: ", name);
                /* Prevents overwriting a pre-existing list */
                if(findList(&lists, name) != NULL) {
                    printf("Some list with this name already exists!\n");
                    break;
                }
                loadList(name, &lists);
                break;

                /* List Editing */
            case 3:
                while(subchoice != 4) {
                    printf("\nOptions\n");
                    printf("1. Edit an item\n");
                    printf("2. Add a new item\n");
                    printf("3. Delete an item\n");
                    printf("4. Return to main menu\n");
                    scanf("%d" , &subchoice);
                    getchar();
                    switch (subchoice) {

                        case 1:
                            query("Enter the list to edit an item in:\n ", name);
                            query("Enter the old item : \n", oldData);
                            query("Enter the new item data: ", newData);
                            editItemorList(&lists, name, oldData, newData);
                            break;

                        case 2:
                            query("Enter the list to add an item to: \n", name);
                            query("Enter the item name:\n ", data);

                            List* list = lists.head;
                            while(list != NULL  && strcmp(list->name , name) != 0 ) {        //iterating through lists to find the one to add to
                                list = list->next;                                      //updating list pointer
                            }
                            if (list == NULL)
                                printf("List '%s' does not exist.\n", name);
                            else {
                                addItem(list, data);
                                printf("Item '%s' added to list '%s'.\n", data, name);
                            }
                            break;

                        case 3:
                            query("Enter the list to delete an item from:\n ", name);
                            query("Enter the item to delete:\n ", data);
                            deleteItem(&lists, name, data);
                            break;

                            /* Returns to main menu */
                        case 4: break;

                        default: printf("invalid input, please try again\n");
                    }
                }
                break;

                /* Board editing */
            case 4:
                while(subchoice != 4) {
                    printf("\nOptions\n");
                    printf("1. Edit the name of a list\n");
                    printf("2. Add a new list\n");
                    printf("3. delete a list\n");
                    printf("4. Return to main menu\n");
                    scanf("%d" , &subchoice);
                    getchar();

                    switch(subchoice){
                        /* Renames list */
                        case 1:
                            query("enter the name of the list name you would like to edit", name);
                            query("enter the new name of this list", newData);
                            editItemorList(&lists , name , "edit list" , newData);
                            break;

                            /* Creates list */
                        case 2:
                            query("what would you like the name of your list to be\n", name);
                            addList(&lists , name);
                            printf("New list '%s' added.\n" , name);
                            break;

                            /* Deletes list */
                        case 3:
                            query("Enter the list to delete:\n", name);
                            deleteList(&lists , name);
                            break;

                            /* Returns to main menu */
                        case 4: break;

                        default:
                            printf("invalid input, please try again\n");

                    }
                }
                break;

                /* List save to file */
            case 5:
                query("Please enter name of list to save: ", name);
                /* Locates list position in linked list */
                saveList(name, &lists);
                break;

                /* Exiting program */
            case 6:
                printf("Exiting program! Goodbye!\n");
                break;

            default:
                printf("invalid choice, please try again\n");
                break;
        }

    }
}

