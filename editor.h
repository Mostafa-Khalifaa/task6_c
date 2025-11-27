#ifndef EDITOR_H
#define EDITOR_H

// Structure to hold editor data
struct EditorData {
    char* buffer;      // Store text here (dynamic array)
    int bufferSize;    // Current buffer size
    int textLength;    // Length of text
    int cursorPos;     // Current cursor position
};

// Function declarations
EditorData* createEditor();
void clearEditor(EditorData* editor);
void destroyEditor(EditorData* editor);
void runEditor(EditorData* editor);
void addChar(EditorData* editor, char c);
void deleteChar(EditorData* editor);
void moveCursorLeft(EditorData* editor);
void moveCursorRight(EditorData* editor);
void displayEditor(EditorData* editor);
char* getText(EditorData* editor);

#endif
