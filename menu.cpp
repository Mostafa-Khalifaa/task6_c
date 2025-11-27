#include "menu.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <termios.h>

// Get single character without Enter (for menu navigation)
char getMenuChar() {
    struct termios old, current;
    tcgetattr(STDIN_FILENO, &old);
    current = old;
    current.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &current);

    char ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return ch;
}

// Create menu in heap
MenuData* createMenu() {
    MenuData* menu = (MenuData*)malloc(sizeof(MenuData));
    menu->editor = createEditor();  // Create editor on heap
    menu->selectedOption = 0;
    return menu;
}

// Free memory
void destroyMenu(MenuData* menu) {
    destroyEditor(menu->editor);
    free(menu);
}

// Display main menu with highlight
void displayMenu(int selected) {
    system("clear");
    std::cout << "\n";
    std::cout << "╔════════════════════════════╗\n";
    std::cout << "║    SIMPLE TEXT EDITOR      ║\n";
    std::cout << "╚════════════════════════════╝\n";
    std::cout << "\n";

    // Highlight selected option
    if (selected == 0) {
        std::cout << " → 1. New - Create/Edit Text ←\n";
    } else {
        std::cout << "   1. New - Create/Edit Text\n";
    }

    if (selected == 1) {
        std::cout << " → 2. Display - View Saved Text ←\n";
    } else {
        std::cout << "   2. Display - View Saved Text\n";
    }

    if (selected == 2) {
        std::cout << " → 3. Exit ←\n";
    } else {
        std::cout << "   3. Exit\n";
    }

    std::cout << "\n";
    std::cout << "Use Arrow keys to navigate, Enter to select\n";
}

// Show saved text
void showText(MenuData* menu) {
    system("clear");
    std::cout << "=== DISPLAY TEXT ===\n\n";

    char* text = getText(menu->editor);
    if (strlen(text) == 0) {
        std::cout << "(No text saved yet)\n";
    } else {
        std::cout << "Your text:\n";
        std::cout << text << "\n";
    }

std::cout << "\n\nPress Enter to return to menu...";
std::cin.get(); // only this

}

// Exit with goodbye message
void exitProgram() {
    system("clear");
    std::cout << "\n\n";
    std::cout << "       GOODBYE!         \n";
    std::cout << "    Thanks for using    \n";
    std::cout << "\n\n";
    sleep(2);
    system("clear");
}

// Handle menu choice
void handleChoice(MenuData* menu) {
    int choice = menu->selectedOption + 1;

    if (choice == MENU_NEW) {

        // If buffer not empty, ask user what they want
        if (strlen(getText(menu->editor)) > 0) {
            system("clear");
            std::cout << "You already have saved text.\n";
            std::cout << "1. Continue editing\n";
            std::cout << "2. Clear and write new text\n\n";
            std::cout << "Enter choice: ";

            int subChoice;
            std::cin >> subChoice;
            std::cin.ignore(); // fix input issues

            if (subChoice == 2) {
                clearEditor(menu->editor);
            }
        }

        runEditor(menu->editor);
    }
    else if (choice == MENU_DISPLAY) {
        showText(menu);
    }
    else if (choice == MENU_EXIT) {
        exitProgram();
    }
}


// Main menu loop
void runMenu(MenuData* menu) {
    bool running = true;
    menu->selectedOption = 0;  // Start at first option

    while (running) {
        displayMenu(menu->selectedOption);

        char ch = getMenuChar();

        // Check for special keys
        if (ch == 27) {  // ESC sequence (arrow keys)
            ch = getMenuChar();
            if (ch == '[') {
                ch = getMenuChar();
                if (ch == 'A') {        // Up arrow
                    menu->selectedOption--;
                    if (menu->selectedOption < 0) {
                        menu->selectedOption = 2;  // Wrap to bottom
                    }
                } else if (ch == 'B') { // Down arrow
                    menu->selectedOption++;
                    if (menu->selectedOption > 2) {
                        menu->selectedOption = 0;  // Wrap to top
                    }
                }
            }
        } else if (ch == '\n' || ch == '\r') {  // Enter key
            if (menu->selectedOption == 2) {  // Exit option
                running = false;
            }
            handleChoice(menu);
        }
    }
}
