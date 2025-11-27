#include "editor.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
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

void clearEditor(EditorData* editor) {
    editor->buffer[0] = '\0';
    editor->textLength = 0;
    editor->cursorPos = 0;
}

// Create editor in heap
EditorData* createEditor() {
    EditorData* editor = (EditorData*)malloc(sizeof(EditorData));
    editor->bufferSize = 100;
    editor->buffer = (char*)malloc(editor->bufferSize);
    editor->buffer[0] = '\0';
    editor->textLength = 0;
    editor->cursorPos = 0;
    return editor;
}

// Free memory
void destroyEditor(EditorData* editor) {
    free(editor->buffer);
    free(editor);
}

// Add character at cursor position
void addChar(EditorData* editor, char c) {
    // Resize buffer if needed
    if (editor->textLength + 1 >= editor->bufferSize) {
        editor->bufferSize *= 2;
        editor->buffer = (char*)realloc(editor->buffer, editor->bufferSize);
    }

    // Shift characters to the right
    for (int i = editor->textLength; i > editor->cursorPos; i--) {
        editor->buffer[i] = editor->buffer[i - 1];
    }

    editor->buffer[editor->cursorPos] = c;
    editor->cursorPos++;
    editor->textLength++;
    editor->buffer[editor->textLength] = '\0';
}

// Delete character before cursor
void deleteChar(EditorData* editor) {
    if (editor->cursorPos > 0) {
        // Shift characters to the left
        for (int i = editor->cursorPos - 1; i < editor->textLength - 1; i++) {
            editor->buffer[i] = editor->buffer[i + 1];
        }
        editor->cursorPos--;
        editor->textLength--;
        editor->buffer[editor->textLength] = '\0';
    }
}

// Move cursor left
void moveCursorLeft(EditorData* editor) {
    if (editor->cursorPos > 0) {
        editor->cursorPos--;
    }
}

// Move cursor right
void moveCursorRight(EditorData* editor) {
    if (editor->cursorPos < editor->textLength) {
        editor->cursorPos++;
    }
}

// Display editor screen
void displayEditor(EditorData* editor) {
    system("clear");
    std::cout << "=== TEXT EDITOR ===\n";
    std::cout << "Text: " << editor->buffer << "\n";
    std::cout << "      ";
    for (int i = 0; i < editor->cursorPos; i++) {
        std::cout << " ";
    }
    std::cout << "^\n\n";
    std::cout << "  Tab for new line\n";
    std::cout << "  Press Enter to Save & Exit to Menu\n";
}

// Main editor loop
void runEditor(EditorData* editor) {
    bool running = true;

    while (running) {
        displayEditor(editor);

        char ch = getChar();

        // Check for Tab first (new line)
        if (ch == 9) {  // Tab key
            addChar(editor, '\n');
        }
        // Check for Enter (save and exit)
        else if (ch == 10 || ch == 13) {  // Enter key
            running = false;
        }
        // Arrow keys
        else if (ch == 27) {  // ESC sequence
            ch = getChar();
            if (ch == '[') {
                ch = getChar();
                if (ch == 'D') {
                    moveCursorLeft(editor);
                } else if (ch == 'C') {
                    moveCursorRight(editor);
                }
            }
        }
        // Backspace
        else if (ch == 127 || ch == 8) {
            deleteChar(editor);
        }
        // Normal characters
        else if (ch >= 32 && ch <= 126) {
            addChar(editor, ch);
        }
    }

    // Show save message after loop
    system("clear");
    std::cout << "Text saved! Returning to menu...\n";
    sleep(1);
}

// Get text from buffer
char* getText(EditorData* editor) {
    return editor->buffer;
}
