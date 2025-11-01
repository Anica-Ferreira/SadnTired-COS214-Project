filesToCompile := $(shell find src -name "*.cpp" ! -name "Api.cpp")
filesToDelete = main api
filesInCoverageReport = main

INCLUDE_PATHS := -I src

main:
	g++ -g -std=c++17 $(filesToCompile) $(INCLUDE_PATHS) -o main

api:
	g++ -g -std=c++17 \
	    -I src/api/crow/include \
	    -I src/api/asio/include \
	    -I src \
	    $(shell find src -name "*.cpp") \
	    -o api -pthread

run: main
	./main

runapi: api
	./api

runboth: main api
	# run API in background, then main program
	./api & ./main

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.gz *.json *.html *.css output.txt coverage.txt valgrind.txt $(filesToDelete)

coverage:
	make clean
	g++ -g --coverage $(filesToCompile) $(INCLUDE_PATHS) -o main
	./main
	gcov -f -m -r -j $(filesInCoverageReport) > coverage.txt
	gcovr --html-details output.html

valgrind:
	make clean
	make
	valgrind --track-origins=yes --leak-check=full --keep-stacktraces=alloc-and-free --error-exitcode=1 --log-file=valgrind.txt ./main > output.txt

gdb:
	make clean
	make
	gdb ./main

all:
	make clean
	make valgrind
	make coverage
	make gdb