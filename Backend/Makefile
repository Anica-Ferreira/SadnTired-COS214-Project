filesToDelete = main api
filesToCompile = TestingMain.cpp ConcreteOrderBuilder.cpp Customer.cpp CustomerCommand.cpp DecorativePot.cpp GiftWrapping.cpp IColleague.cpp IMediator.cpp Inventory.cpp InventoryManager.cpp IObserver.cpp ISubject.cpp NurserySystemFacade.cpp OrderBuilder.cpp OrderDirector.cpp Plant.cpp PlantFactory.cpp PlantNursery.cpp PlantState.cpp Product.cpp ProductBundle.cpp ProductDecorator.cpp ProductItem.cpp ShoppingCart.cpp StaffAction.cpp StaffCommand.cpp StaffCoordinator.cpp StaffGardener.cpp StaffManager.cpp StaffMember.cpp StaffReaction.cpp StaffSalesman.cpp WaterCommand.cpp WateringStrategy.cpp WebAPIAdapter.cpp

filesInCoverageReport = main

main:
	g++ -g -std=c++17 ${filesToCompile} -o main

api:
	g++ -g -std=c++17 -I ../crow/include -I ../asio/include Api.cpp -o api -pthread

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