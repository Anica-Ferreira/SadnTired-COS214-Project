#include "Inventory.h"
#include <iostream>

Inventory::~Inventory() {
    for (auto plant : plants) {
        delete plant;
    }
    plants.clear();
}

void Inventory::addPlant(Plant* plant) {
    plants.push_back(plant);
}

std::vector<Plant*> Inventory::getAll() const {
    return plants; // Returns a *copy* of the vector, but same Plant pointers
}

Plant* Inventory::get(int index) const {
    if (index >= 0 && index < (int)plants.size()) {
        return plants[index];
    }
    return nullptr;
}

int Inventory::size() const {
    return plants.size();
}

void Inventory::waterAll() {
    for (Plant* plant : plants) {
        plant->water();
        std::cout << plant->getName() 
                  << " watered. State: " << plant->getStateName() 
                  << ", Water Level: " << plant->getWaterLevel() << "\n";
    }
}

void Inventory::passTimeAll() {
    for (Plant* plant : plants) {
        plant->passTime();
        std::cout << plant->getName() 
                  << " after time passes. State: " << plant->getStateName() 
                  << ", Water Level: " << plant->getWaterLevel() << "\n";
    }
}

void Inventory::printStockCounts() const {
    int succulents = 0;
    int flowers = 0;
    int trees = 0;

    for (Plant* plant : plants) {
        std::string type = plant->getType();
        if (type == "Succulent") succulents++;
        else if (type == "Flower") flowers++;
        else if (type == "Tree") trees++;
    }

    std::cout << "\n Stock Counts:\n";
    std::cout << "Succulents: " << succulents << "\n";
    std::cout << "Flowers: " << flowers << "\n";
    std::cout << "Trees: " << trees << "\n";
}

void Inventory::removePlant(Plant* plant) {
    for (auto it = plants.begin(); it != plants.end(); ++it) {
        if (*it == plant) {
            plants.erase(it);
            return;
        }
    }
}

void Inventory::moveReadyPlantsTo(Inventory& store) {
    std::vector<Plant*> toMove;

    // Collect ready plants
    for (Plant* plant : plants) {
        if (plant->getStateName() == "Ready for Sale") {
            toMove.push_back(plant);
        }
    }

    // Move plants to the store
    for (Plant* plant : toMove) {
        removePlant(plant);
        store.addPlant(plant);
        std::cout << "✅ " << plant->getName() << " moved to store inventory.\n";
    }
}