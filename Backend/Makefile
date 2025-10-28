filesToDelete = main api
filesToCompile = Product.cpp ProductItem.cpp ProductDecorator.cpp DecorativePot.cpp GiftWrapping.cpp ProductBundle.cpp TestingMain.cpp OrderDirector.cpp OrderBuilder.cpp ConcreteOrderBuilder.cpp Api.cpp

# API specific files - UPDATED with missing files
apiFiles = Api.cpp \
          WebAPIAdapter.cpp \
          NurserySystemFacade.cpp \
          StaffMember.cpp \
          StaffCoordinator.cpp \
          Customer.cpp \
          InventoryManager.cpp \
          PlantNursery.cpp \
          CustomerCommand.cpp \
          Inventory.cpp \
          Plant.cpp \
          PlantFactory.cpp \
          ShoppingCart.cpp \
          WateringStrategy.cpp \
          PlantState.cpp \
          StaffReaction.cpp \
          StaffAction.cpp

filesInCoverageReport = main

main:
	g++ -g -std=c++17 ${filesToCompile} -o main

api:
	g++ -g -std=c++17 -I ../crow/include -I ../asio/include ${apiFiles} -o api -pthread

run: main
	./main

runapi: api
	./api

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.gz *.json *.html *.css output.txt coverage.txt valgrind.txt ${filesToDelete}

coverage:
	make clean
	g++ -g --coverage ${filesToCompile} -o main
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