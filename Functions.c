//
// Created by farid on 06/04/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
void deleteList(Lists* lists , char name[])
{
    List* prevlist = lists->head;               //initialise a pointer to point to the list before the current one
    List* list = lists->head;                   //initialise a pointer to point to the current list
    if(lists->head == NULL)                     // error handling
    {
        printf("no lists to delete");
    }
    else if(strcmp(lists->head->name , name) == 0 ) {   //the case that the head is the first list to delete
        printf("deleting....");
        lists->head = list->next;                       //reassign the head to the next list
        free(list);                             //prevent memory leaking
        printf("list deleted.");
    }
    else{

        while (list != NULL && strcmp(list->name, name) != 0) {         //traverse the list until we either reach the end or find the list to delete
            prevlist = list;
            list = list->next;
        }
        if (list == NULL) {
            printf("list doesn't exist, please try again");

        }
        else {
            printf("deleting....");
            prevlist->next = list->next;   //make the last list skip and point to the next list
            free(list);             //prevent memory leaking
            printf("list deleted.");
        }
    }

}
void addList(Lists* lists , char name[]) {
    List* newList = malloc(sizeof(List));          // Memory allocation
    newList->head = NULL;                          // No items in this list as of now
    newList->next = NULL;                          // Set to the last list (null)
    strcpy(newList->name , name);
    if (lists->head == NULL) {
        lists->head = newList;                     // Checks if there's any prior lists, if not then it will be the first item
    } else {
        List* temp = lists->head;
        while (temp->next != NULL) {               // Iterating until we reach the end of lists
            temp = temp->next;
        }
        temp->next = newList;
    }
}
void printLists(const Lists* lists) {
    List* list = lists->head;                       //memory allocation for a pointer to iterate through the linked list

    while (list != NULL) {                          //while loop running to the end of the linked list
        printf("%s:\n", list->name);
        Item* item = list->head;
        while (item != NULL) {                      //iterating through each lists items
            printf("  %s\n", item->data);
            item = item->next;
        }
        list = list->next;
    }
}
void editItemorList(Lists* lists, char* name, char* oldData, char* newData) {
    List* list = lists->head;                               //
    while(list != NULL && strcmp(list->name, name) != 0 ){ //iterating through the lists to find where to edit
        list = list->next;
    }
    if (list == NULL) {                                     //means it reached the end of the linked list without finding it
        printf("List '%s' does not exist.\n", name);
        return;
    }
    if(strcmp(oldData , "edit list") == 0)
    {
        strcpy(list->name, newData);
        printf("list %s changed to %s" , name , newData);
    }

    else {
        Item *item = list->head;
        while (item != NULL &&
               strcmp(item->data, oldData) != 0) {      //iterating through the items in the list until item is found
            item = item->next;
        }

        if (item == NULL) {                                         //reached the end of the linked list without finding the item
            printf("Item %s not found in list %s.\n", oldData, name);
        } else {
            strcpy(item->data, newData);                //copying desired name into the list
            printf("Item %s in list %s changed to %s.\n", oldData, name, newData);
        }
    }
}
int deleteItem(Lists* lists, char* name, char* data) {   //farid
    if (lists == NULL || lists->head == NULL) {             //error handling
        printf("list not found");
        return 0; // Lists is empty or not initialized
    }
    List* list = lists->head;
    while (list != NULL && strcmp(list->name, name) != 0) {     //iterating through the linked list until the desired list is found
        list = list->next;
    }

    if (list == NULL) {                                 //indicating we reached the end of the linked list without finding it
        printf("list not found");
        return 0;
    }

    Item* item = list->head;
    Item* prev = NULL;                                          //pointer to the previous item
    while (item != NULL && strcmp(item->data, data) != 0) {     //iterating until finding the item to delete
        prev = item;                                            //assigning previous the address of the item before updating item
        item = item->next;                                      //updating item
    }

    if (item == NULL) {
        printf("Item %s not found in list %s.\n", data, name);
        return 0;
    }

    if (prev == NULL) {
        // Item to delete is the head
        list->head = item->next;
    } else {
        // Item is not the head
        prev->next = item->next;
    }

    free(item);
    printf("Item %s has been deleted from list %s.\n", data, name);
    return 1;
}
void addItem(List* list, char* data) {   //farid
    Item* newItem = (Item*)malloc(sizeof(Item));    // Memory allocation
    strcpy(newItem->data, data);                    // Assigning data to the node
    newItem->next = NULL;                           // Set to the last item

    if (list->head == NULL) {                       // Checks if list is empty
        list->head = newItem;
    } else {
        Item* temp = list->head;                    // Iterating to find the last element
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}
/**
 * Saves some list to a txt file
 * @param listName String, name of file + .txt
 * @param list List, list whose data is being written
 */
void saveList(char fileName[], Lists *lists) {
    FILE *file = fopen(fileName, "w+");
    if (file == NULL) {
        printf("File with that name can't be opened!\n");
        return;
    }

    List *currentList = lists->head;
    while (currentList != NULL) {
        // Write the person's name followed by a colon
        fputs(currentList->name, file);
        fputs(":\n", file);

        // Write each item in the list
        Item *item = currentList->head;
        while (item != NULL) {
            fputs(item->data, file);
            fputs("\n", file);
            item = item->next;
        }

        fputs("\n", file);  // Add an extra newline to separate different lists

        currentList = currentList->next;
    }

    fclose(file);
    printf("Saved all lists to %s\n", fileName);
}
/**
 * Loads some list from a txt file
 * @param listName String, name of file + .txt to load from
 * @param lists Lists, linked list where some new list is being added
 */
void loadList(char fileName[],Lists *lists) {  //farid
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File with that name can't be opened!\n");
        return;
    }

    char data[STRING_LENGTH];
    List *currentList = NULL;

    while (fgets(data, STRING_LENGTH, file)) {
        data[strcspn(data, "\n")] = 0;  // Remove newline character

        // Check if the line is a person's name (has a colon)
        char *colonPos = strchr(data, ':');
        if (colonPos) {
            // Remove the colon
            *colonPos = '\0';

            // Create a new list for this person
            addList(lists, data);
            currentList = findList(lists, data);
        } else if (currentList) {
            // Add the item to the current person's list
            addItem(currentList, data);
        }
    }

    fclose(file);
    printf("Loaded %s\n", fileName);
}

/**
 * Queries the user for some input
 * @param question String, question to ask the user
 * @param response String, user input
 */
void query(char question[], char response[STRING_LENGTH]) { //steven
    printf("%s", question);
    fgets(response, STRING_LENGTH, stdin);
    response[strcspn(response , "\n")] = 0; // Removes new line char
}

/**
 * Locates some list by advancing through a linked list
 * @param lists List, linked list to iterate through
 * @param name String, name of list to find
 * @return List*, pointer of list if found, else NULL
 */
List* findList(Lists* lists, char* name) { //steven
    List *list = lists->head;
    while((list != NULL) && (strcmp(list->name, name) != 0))
        list = list->next;
    return list;
}


