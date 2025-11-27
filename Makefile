# Simple Makefile for text editor

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executable
TARGET = editor

# Source files
SOURCES = main.cpp menu.cpp editor.cpp

# Object files
OBJECTS = main.o menu.o editor.o

# Build the program
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile main.cpp
main.o: main.cpp menu.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile menu.cpp
menu.o: menu.cpp menu.h editor.h
	$(CXX) $(CXXFLAGS) -c menu.cpp

# Compile editor.cpp
editor.o: editor.cpp editor.h
	$(CXX) $(CXXFLAGS) -c editor.cpp

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
