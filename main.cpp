#include "menu.h"
#include <cstdlib>

int main() {
    // Create menu on heap
    MenuData* menu = createMenu();

    // Run the program
    runMenu(menu);

    // Clean up memory
    destroyMenu(menu);

    return 0;
}
