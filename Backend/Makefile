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
	rm -f *.o *.gcov *.gcda *.gcno *.gz *.json *.html *.css output.txt coverage.txt valgrind.txt main api

# Run the program with Valgrind to check for memory leaks
coverage: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Run the program with GDB for debugging
gdb: $(TARGET)
	gdb ./$(TARGET)

# --- API Specific Build Targets ---
filesToDelete = main api
filesToCompile = Product.cpp ProductItem.cpp ProductDecorator.cpp DecorativePot.cpp GiftWrapping.cpp ProductBundle.cpp TestingMain.cpp OrderDirector.cpp OrderBuilder.cpp ConcreteOrderBuilder.cpp Api.cpp
filesInCoverageReport = main

main: 
	g++ -g -std=c++17 ${filesToCompile} -o main

api:
	g++ -g -std=c++17 -I ../crow/include -I ../asio/include Api.cpp -o api -pthread

run: main
	./main

runapi: api
	./api

coverage-api:
	make clean
	g++ -g --coverage ${filesToCompile} -o api
	./api
	gcov -f -m -r -j ${filesInCoverageReport} > coverage.txt
	gcovr --html-details output.html

valgrind-main:
	make clean
	make
	valgrind --track-origins=yes --leak-check=full --keep-stacktraces=alloc-and-free --error-exitcode=1 --log-file=valgrind.txt ./main > output.txt

gdb-main:
	make clean
	make
	gdb ./main

# Phony targets
.PHONY: all clean valgrind gdb run runapi main api coverage coverage-api valgrind-main gdb-main

# Available commands:
# make          - Build the main executable
# make all      - Build the main executable
# make clean    - Remove object files, coverage, valgrind logs, and built executables
# make valgrind - Run main executable with Valgrind
# make gdb      - Debug main executable with GDB
# make run      - Run main executable
# make api      - Build the API executable
# make runapi   - Run the API executable
# make coverage-api - Run API executable with coverage
# make valgrind-main - Run main with Valgrind
# make gdb-main - Debug main with GDB