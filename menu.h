#ifndef MENU_H
#define MENU_H

#include "editor.h"

// Menu options (using #define macros)
#define MENU_NEW     1
#define MENU_DISPLAY 2
#define MENU_EXIT    3

// Structure to hold menu data
struct MenuData {
    EditorData* editor;    // Pointer to editor
    int selectedOption;    // Current menu choice (0-2 for arrow navigation)
};

// Function declarations
MenuData* createMenu();
void destroyMenu(MenuData* menu);
void runMenu(MenuData* menu);
void displayMenu(int selected);
void handleChoice(MenuData* menu);
void showText(MenuData* menu);
void exitProgram();
char getMenuChar();

#endif
