# Kanban Style Board

This project is a simple command-line implementation of a Kanban-style board, allowing you to manage lists and tasks using linked lists. It includes functionalities to add, delete, edit, save, and load lists and items.

## Features

- **Add Lists**: Create new lists to organize your tasks.
- **Delete Lists**: Remove lists you no longer need.
- **Add Items**: Add tasks to your lists.
- **Delete Items**: Remove tasks from your lists.
- **Edit Lists/Items**: Modify the name of a list or the content of an item.
- **Save Lists**: Save all your lists to a text file.
- **Load Lists**: Load lists from a text file to continue managing your tasks.

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/kanban-style-board.git
    ```

2. Navigate to the project directory:
    ```sh
    cd kanban-style-board
    ```

3. Compile the code:
    ```sh
    gcc main.c Functions.c -o kanban-board
    ```

4. Run the program:
    ```sh
    ./kanban-board
    ```

## Usage

### Adding a List
- Use the `addList` function to create a new list.
- Example:
    ```c
    addList(&lists, "To Do");
    ```

### Deleting a List
- Use the `deleteList` function to remove an existing list.
- Example:
    ```c
    deleteList(&lists, "To Do");
    ```

### Adding an Item to a List
- Use the `addItem` function to add a new task to a list.
- Example:
    ```c
    addItem(findList(&lists, "To Do"), "Finish homework");
    ```

### Deleting an Item from a List
- Use the `deleteItem` function to remove a task from a list.
- Example:
    ```c
    deleteItem(&lists, "To Do", "Finish homework");
    ```

### Editing a List or Item
- Use the `editItemorList` function to modify a list name or an item.
- Example:
    ```c
    editItemorList(&lists, "To Do", "Finish homework", "Complete homework");
    ```

### Saving Lists to a File
- Use the `saveList` function to save all lists to a text file.
- Example:
    ```c
    saveList("kanban_board.txt", &lists);
    ```

### Loading Lists from a File
- Use the `loadList` function to load lists from a text file.
- Example:
    ```c
    loadList("kanban_board.txt", &lists);
    ```
- Note that the function only works on the following file structure;

  Person:

  item

  item

  item

  Person:

  item

  ...

## File Structure

- `main.c`: The main file to run the program.
- `Functions.c`: Contains the core functions for managing lists and items.
- `Functions.h`: Header file with function declarations.

