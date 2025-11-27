#include "utils.h"
#include <termios.h>
#include <unistd.h>

// Get single character without Enter
char getChar() {
    struct termios old, current;
    tcgetattr(STDIN_FILENO, &old);
    current = old;
    current.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &current);

    char ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return ch;
}
