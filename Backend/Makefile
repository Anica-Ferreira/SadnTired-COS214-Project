# Universal C++ Makefile
# Compiler to use
CXX = g++
# Compiler flags (includes debugging symbols for Valgrind and GDB)
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -g
# Linker flags
LDFLAGS =

# Target executable name
TARGET = app

# Source files
SOURCES = $(wildcard *.cpp)
# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target: build the executable
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program with Valgrind to check for memory leaks
coverage: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Run the program with GDB for debugging
gdb: $(TARGET)
	gdb ./$(TARGET)

# Phony targets
.PHONY: all clean valgrind gdb

# Available commands:
# make          - Build the executable (same as 'make all')
# make all      - Build the executable
# make clean    - Remove object files and the executable
# make valgrind - Run the executable with Valgrind to check for memory leaks
# make gdb      - Run the executable with GDB for debugging
# make all && ./app - Build and run the executable