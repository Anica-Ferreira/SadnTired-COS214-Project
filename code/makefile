filesToDelete = main
filesToCompile = Product.cpp ProductItem.cpp ProductDecorator.cpp DecorativePot.cpp GiftWrapping.cpp ProductBundle.cpp TestingMain.cpp
filesInCoverageReport = main

main: 
		g++ -g -std=c++11 ${filesToCompile}  -o main

run: main
		./main

clean:
	rm *.o *.gcov *.gcda *.gcno *.gz *.json *.html *.css output.txt coverage.txt valgrind.txt -f ${filesToDelete}

coverage:
	make clean
	g++ -g --coverage -dumpbase '' ${filesToCompile} -o main
	./main 
	gcov -f -m -r -j ${filesInCoverageReport} > coverage.txt 
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