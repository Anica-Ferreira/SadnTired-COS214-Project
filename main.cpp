#include <iostream>
#include "Plant.h"
#include "PlantFactory.h"
#include "WateringStrategy.h"

int main() {
    // Create watering strategies
    WateringStrategy* lightWatering = new LightWatering();
    WateringStrategy* regularWatering = new RegularWatering();
    WateringStrategy* heavyWatering = new HeavyWatering();

    // Create factories
    PlantFactory* succulentFactory = new SucculentFactory();
    PlantFactory* flowerFactory = new FlowerFactory();
    PlantFactory* treeFactory = new TreeFactory();

    // Create plants using factory method
    Plant* aloe = succulentFactory->createPlant("Aloe Vera", 10.0, lightWatering);
    Plant* rose = flowerFactory->createPlant("Rose", 15.0, regularWatering);
    Plant* oak = treeFactory->createPlant("Oak Tree", 50.0, heavyWatering);

    // Test scenario: Simulate nursery operations
    std::cout << "Initial states:\n";
    std::cout << aloe->getName() << " (" << aloe->getType() << "): State = " << aloe->getStateName()
              << ", Water Level = " << aloe->getWaterLevel() << "\n";
    std::cout << rose->getName() << " (" << rose->getType() << "): State = " << rose->getStateName()
              << ", Water Level = " << rose->getWaterLevel() << "\n";
    std::cout << oak->getName() << " (" << oak->getType() << "): State = " << oak->getStateName()
              << ", Water Level = " << oak->getWaterLevel() << "\n";

    // Cycle 1: Water all plants
    std::cout << "\nCycle 1: Water all plants\n";
    aloe->water();
    rose->water();
    oak->water();
    std::cout << aloe->getName() << ": State = " << aloe->getStateName()
              << ", Water Level = " << aloe->getWaterLevel() << "\n";
    std::cout << rose->getName() << ": State = " << rose->getStateName()
              << ", Water Level = " << rose->getWaterLevel() << "\n";
    std::cout << oak->getName() << ": State = " << oak->getStateName()
              << ", Water Level = " << oak->getWaterLevel() << "\n";

    // Cycle 2: Time passes
    std::cout << "\nCycle 2: Time passes (water level decreases)\n";
    aloe->passTime();
    rose->passTime();
    oak->passTime();
    std::cout << aloe->getName() << ": State = " << aloe->getStateName()
              << ", Water Level = " << aloe->getWaterLevel() << "\n";
    std::cout << rose->getName() << ": State = " << rose->getStateName()
              << ", Water Level = " << rose->getWaterLevel() << "\n";
    std::cout << oak->getName() << ": State = " << oak->getStateName()
              << ", Water Level = " << oak->getWaterLevel() << "\n";

    // Simulate enough waterings for Aloe to reach ReadyForSale (needs 5 waterings)
    std::cout << "\nWatering Aloe multiple times to reach ReadyForSale\n";
    for (int i = 0; i < 4; ++i) { // Already watered once
        aloe->water();
        std::cout << aloe->getName() << ": State = " << aloe->getStateName()
                  << ", Water Level = " << aloe->getWaterLevel() << "\n";
    }

    // Test Rose in Dry state
    std::cout << "\nLetting Rose dry out\n";
    while (rose->getStateName() != "Dry") {
        rose->passTime();
    }
    std::cout << rose->getName() << ": State = " << rose->getStateName()
              << ", Water Level = " << rose->getWaterLevel() << "\n";
    rose->water();
    std::cout << rose->getName() << ": State = " << rose->getStateName()
              << ", Water Level = " << rose->getWaterLevel() << "\n";

    // Clean up
    delete aloe;
    delete rose;
    delete oak;
    delete succulentFactory;
    delete flowerFactory;
    delete treeFactory;

    std::cout << "\nTest completed.\n";
    return 0;
}