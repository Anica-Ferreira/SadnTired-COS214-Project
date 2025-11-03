/**
 * @class [Inventory]
 * @brief [Implementation of the Inventory class for managing plant collections]
 * @details [Handles storage, retrieval, and management of plant objects in inventory]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "Inventory.h"
#include <iostream>

/**
 * @brief [Destroys the Inventory object and cleans up plant resources]
 */
Inventory::~Inventory() {
    for (auto plant : plants) {
        delete plant;
    }
    plants.clear();
}

/**
 * @brief [Adds a plant to the inventory]
 * @param[in] plant [Pointer to the plant to add]
 */
void Inventory::addPlant(Plant* plant) {
    plants.push_back(plant);
}

/**
 * @brief [Gets all plants in the inventory]
 * @return [Vector containing pointers to all plants]
 */
vector<Plant*> Inventory::getAll() const {
    return plants; // Returns a *copy* of the vector, but same Plant pointers
}

/**
 * @brief [Gets a plant by index]
 * @param[in] index [Index of the plant to retrieve]
 * @return [Pointer to the plant at specified index, or nullptr if invalid]
 */
Plant* Inventory::get(int index) const {
    if (index >= 0 && index < (int)plants.size()) {
        return plants[index];
    }
    return nullptr;
}

Plant* Inventory::get(const string& name) const {
    for (Plant* plant : plants) {
        if (plant->getName() == name) return plant;
    }
    return nullptr;
}

/**
 * @brief [Gets the number of plants in inventory]
 * @return [Number of plants in inventory]
 */
int Inventory::size() const {
    return plants.size();
}

/**
 * @brief [Waters all plants in the inventory]
 */
void Inventory::waterAll() {
    for (Plant* plant : plants) {
        plant->water();
        /*cout << plant->getName() 
                  << " watered. State: " << plant->getStateName() 
                  << ", Water Level: " << plant->getWaterLevel() << "\n";*/
    }
}

/**
 * @brief [Advances time for all plants in the inventory]
 */
void Inventory::passTimeAll() {
    for (Plant* plant : plants) {
        plant->passTime();
        /*cout << plant->getName() 
                  << " after time passes. State: " << plant->getStateName() 
                  << ", Water Level: " << plant->getWaterLevel() << "\n";*/
    }
}

/**
 * @brief [Prints stock counts by plant type]
 */
void Inventory::printStockCounts() const {
    int succulents = 0;
    int flowers = 0;
    int trees = 0;

    for (Plant* plant : plants) {
        string type = plant->getType();
        if (type == "Succulent") succulents++;
        else if (type == "Flower") flowers++;
        else if (type == "Tree") trees++;
    }

    cout << "\n Stock Counts:\n";
    cout << "Succulents: " << succulents << "\n";
    cout << "Flowers: " << flowers << "\n";
    cout << "Trees: " << trees << "\n";
}

/**
 * @brief [Removes a specific plant from inventory]
 * @param[in] plant [Pointer to the plant to remove]
 */
void Inventory::removePlant(Plant* plant) {
    for (auto it = plants.begin(); it != plants.end(); ++it) {
        if (*it == plant) {
            plants.erase(it);
            return;
        }
    }
}

/**
 * @brief [Moves ready plants from this inventory to another inventory]
 * @param[in] store [Reference to the destination inventory]
 */
void Inventory::moveReadyPlantsTo(Inventory* other){
    vector<Plant*> toMove;
    for (Plant* plant : plants) {
        if (plant->getStateName() == "Ready for Sale") {
            toMove.push_back(plant);
        }
    }

    // Move plants to other inventory
    for (Plant* plant : toMove) {
        removePlant(plant);       // remove from this inventory
        other->addPlant(plant);   // add to other inventory
    }
}

int Inventory::getQuantity(const std::string& plantName) const {
    int count = 0;
    for (Plant* plant : plants) {
        if (plant->getName() == plantName) {
            count++;
        }
    }
    return count;
}