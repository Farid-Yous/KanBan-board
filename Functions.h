//
// Created by farid on 06/04/2024.
//
#ifndef ASSIGNMENT3_FUNCTIONS_H
#define ASSIGNMENT3_FUNCTIONS_H

#define STRING_LENGTH 50

/** Linked list for items */
typedef struct item {
    char data[50];
    struct item* next;
} Item;

/** Linked list for lists */
typedef struct list {
    Item* head;
    char name[50];
    struct list* next;
} List;

/** Lists keep track of all the list heads */
typedef struct {
    List* head;
} Lists;

/* ListManager */
void deleteList(Lists* lists, char name[]);
void addList(Lists* lists , char name[]);
void printLists(const Lists* lists);
void editItemorList(Lists* lists, char* name, char* oldData, char* newData);
int deleteItem(Lists* lists, char* name, char* data);
void addItem(List* list, char* name);

/* FileManager */
void saveList(char listName[], Lists *list);
void loadList(char listName[], Lists *lists);

/* Utility */
void query(char question[], char response[STRING_LENGTH]);
List* findList(Lists* lists, char* name);

#endif //ASSIGNMENT3_FUNCTIONS_H



