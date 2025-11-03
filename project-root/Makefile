# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -pthread
INCLUDE_PATHS := -I src

# Source files
CORE_SRC := $(shell find src/core -name "*.cpp")
CUSTOMER_SRC := $(shell find src/customer -name "*.cpp")
GREENHOUSE_SRC := $(shell find src/greenhouse -name "*.cpp")
INVENTORY_SRC := $(shell find src/inventory -name "*.cpp")
ORDERS_SRC := $(shell find src/orders -name "*.cpp")
PRODUCTS_SRC := $(shell find src/products -name "*.cpp")
STAFF_SRC := $(shell find src/staff -name "*.cpp")

# Combine all source files except main files
ALL_SRC := $(CORE_SRC) $(CUSTOMER_SRC) $(GREENHOUSE_SRC) $(INVENTORY_SRC) $(ORDERS_SRC) $(PRODUCTS_SRC) $(STAFF_SRC)

# Output files
filesToDelete := main api test demo

# Default target
all: demo

# Test target
test: $(ALL_SRC) src/TestingMain.cpp
	$(CXX) $(CXXFLAGS) $(ALL_SRC) src/TestingMain.cpp $(INCLUDE_PATHS) -o test

# Demo target
demo: $(ALL_SRC) src/DemoMain.cpp
	$(CXX) $(CXXFLAGS) $(ALL_SRC) src/DemoMain.cpp $(INCLUDE_PATHS) -o demo

# API target - Try multiple ASIO locations
api: $(ALL_SRC) src/api/Api.cpp
	@echo "Building API..."
	@if pkg-config --exists asio; then \
		echo "Using system ASIO..."; \
		$(CXX) $(CXXFLAGS) \
			-I src/api/crow/include \
			`pkg-config --cflags asio` \
			$(INCLUDE_PATHS) \
			$(ALL_SRC) src/api/Api.cpp \
			-o api -pthread -DASIO_STANDALONE; \
	elif [ -d "/usr/include/asio" ]; then \
		echo "Using /usr/include/asio..."; \
		$(CXX) $(CXXFLAGS) \
			-I src/api/crow/include \
			-I /usr/include/asio \
			$(INCLUDE_PATHS) \
			$(ALL_SRC) src/api/Api.cpp \
			-o api -pthread -DASIO_STANDALONE; \
	elif [ -d "src/api/asio/include" ]; then \
		echo "Using local ASIO..."; \
		$(CXX) $(CXXFLAGS) \
			-I src/api/crow/include \
			-I src/api/asio/include \
			$(INCLUDE_PATHS) \
			$(ALL_SRC) src/api/Api.cpp \
			-o api -pthread -DASIO_STANDALONE; \
	else \
		echo "ASIO not found. Installing dependencies..."; \
		make install-deps; \
		make api; \
	fi

# Alternative simple API without Crow/ASIO dependencies
simpleapi: $(ALL_SRC) src/api/SimpleApi.cpp
	$(CXX) $(CXXFLAGS) $(ALL_SRC) src/api/SimpleApi.cpp $(INCLUDE_PATHS) -o simpleapi

# Install dependencies
install-deps:
	@echo "Installing dependencies..."
	@if command -v apt-get >/dev/null 2>&1; then \
		sudo apt-get update && sudo apt-get install -y libasio-dev; \
	elif command -v brew >/dev/null 2>&1; then \
		brew install asio; \
	elif command -v pacman >/dev/null 2>&1; then \
		sudo pacman -S asio; \
	else \
		echo "Please install ASIO manually: https://think-async.com/Asio/"; \
		exit 1; \
	fi

# Download ASIO locally
download-asio:
	@echo "Downloading ASIO locally..."
	@mkdir -p src/api/asio/include
	@cd src/api/asio/include && \
	wget -q https://sourceforge.net/projects/asio/files/latest/download -O asio.tar.gz && \
	tar -xzf asio.tar.gz --strip-components=1 && \
	rm asio.tar.gz
	@echo "ASIO downloaded to src/api/asio/include/"

# Run targets
runtest: test
	./test

run: demo
	./demo

runapi: api
	./api

runsimple: simpleapi
	./simpleapi

# Clean target
clean:
	rm -f *.o *.gcov *.gcda *.gcno *.gz *.json *.html *.css output.txt coverage.txt valgrind.txt $(filesToDelete) simpleapi

# Coverage target
coverage:
	make clean
	$(CXX) -g --coverage $(ALL_SRC) src/DemoMain.cpp $(INCLUDE_PATHS) -o main
	./main
	gcov -f -m -r -j $(ALL_SRC) > coverage.txt 2>/dev/null || true
	gcovr --html-details output.html

# Valgrind target
valgrind:
	make clean
	make demo
	valgrind --track-origins=yes --leak-check=full --keep-stacktraces=alloc-and-free --error-exitcode=1 --log-file=valgrind.txt ./demo > output.txt

# GDB target
gdb:
	make clean
	make demo
	gdb ./demo

# Help target
help:
	@echo "Available targets:"
	@echo "  all        - Build demo (default)"
	@echo "  demo       - Build demo application"
	@echo "  test       - Build test application"
	@echo "  api        - Build API server (requires ASIO)"
	@echo "  simpleapi  - Build simple API without dependencies"
	@echo "  run        - Run demo application"
	@echo "  runtest    - Run test application"
	@echo "  runapi     - Run API server"
	@echo "  runsimple  - Run simple API"
	@echo "  install-deps - Install ASIO dependency"
	@echo "  download-asio - Download ASIO locally"
	@echo "  clean      - Clean build files"
	@echo "  coverage   - Generate coverage report"
	@echo "  valgrind   - Run valgrind memory check"
	@echo "  gdb        - Run with GDB debugger"

.PHONY: all test demo api simpleapi install-deps download-asio runtest run runapi runsimple clean coverage valgrind gdb help