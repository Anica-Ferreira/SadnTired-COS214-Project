// InventoryManager.cpp - UPDATED
#include "InventoryManager.h"
#include "WebAPIAdapter.h"
#include "Plant.h"  // Your Plant class
#include <iostream>
#include <sstream>

InventoryManager::InventoryManager(WebAPIAdapter* adapter, Inventory* nurseryInv, Inventory* shopInv)
    : apiAdapter(adapter), nurseryInventory(nurseryInv), shopInventory(shopInv) {
    cout << "Inventory Manager initialized with real inventory data" << endl;
}

InventoryManager::~InventoryManager() {
    cout << "Inventory Manager destroyed" << endl;
    // Don't delete inventories here - they're managed elsewhere
}

string InventoryManager::searchPlants(const string& keyword) {
    cout << "InventoryManager: Searching plants for keyword: " << keyword << endl;

    vector<Plant*> allPlants = shopInventory->getAll();
    vector<Plant*> results;

    for (Plant* plant : allPlants) {
        string name = plant->getName();
        // Simple case-insensitive search
        string lowerName = name;
        string lowerKeyword = keyword;
        for (char& c : lowerName) c = tolower(c);
        for (char& c : lowerKeyword) c = tolower(c);

        if (lowerName.find(lowerKeyword) != string::npos) {
            results.push_back(plant);
        }
    }

    return "{\"action\": \"search\", \"keyword\": \"" + keyword +
           "\", \"results\": " + plantsToJSON(results) + "}";
}

string InventoryManager::filterPlantsByType(const string& plantType) {
    cout << "InventoryManager: Filtering plants by type: " << plantType << endl;

    vector<Plant*> allPlants = shopInventory->getAll();
    vector<Plant*> filtered;

    for (Plant* plant : allPlants) {
        if (plant->getType() == plantType) {
            filtered.push_back(plant);
        }
    }

    return "{\"action\": \"filter_by_type\", \"type\": \"" + plantType +
           "\", \"results\": " + plantsToJSON(filtered) + "}";
}

string InventoryManager::getPlantDetails(const string& plantName) {
    cout << "InventoryManager: Getting details for plant: " << plantName << endl;

    Plant* plant = findPlantByName(plantName);
    if (!plant) {
        return "{\"error\": \"Plant not found: " + plantName + "\"}";
    }

    return plantToJSON(plant);
}

string InventoryManager::checkStock(const string& plantName) {
    cout << "InventoryManager: Checking stock for plant: " << plantName << endl;

    vector<Plant*> shopPlants = shopInventory->getAll();
    int count = 0;

    for (Plant* plant : shopPlants) {
        if (plant->getName() == plantName && plant->getStateName() == "Ready for Sale") {
            count++;
        }
    }

    stringstream response;
    response << "{\"plant_name\": \"" << plantName
             << "\", \"in_stock\": " << (count > 0 ? "true" : "false")
             << ", \"quantity\": " << count
             << ", \"status\": \"" << (count > 0 ? "available" : "out_of_stock") << "\"}";

    return response.str();
}

string InventoryManager::movePlantToShop(const string& plantName) {
    cout << "InventoryManager: Moving plant to shop: " << plantName << endl;

    // Find the plant in nursery
    vector<Plant*> nurseryPlants = nurseryInventory->getAll();
    Plant* plantToMove = nullptr;

    for (Plant* plant : nurseryPlants) {
        if (plant->getName() == plantName && plant->getStateName() == "Ready for Sale") {
            plantToMove = plant;
            break;
        }
    }

    if (!plantToMove) {
        return "{\"error\": \"No ready plant found in nursery: " + plantName + "\"}";
    }

    // Move from nursery to shop
    nurseryInventory->removePlant(plantToMove);
    shopInventory->addPlant(plantToMove);

    return "{\"action\": \"move_to_shop\", \"plant_name\": \"" + plantName +
           "\", \"status\": \"moved\"}";
}

string InventoryManager::waterPlant(const string& plantName) {
    cout << "InventoryManager: Watering plant: " << plantName << endl;

    Plant* plant = findPlantByName(plantName);
    if (!plant) {
        return "{\"error\": \"Plant not found: " + plantName + "\"}";
    }

    plant->water();

    return "{\"action\": \"water_plant\", \"plant_name\": \"" + plantName +
           "\", \"new_state\": \"" + plant->getStateName() +
           "\", \"water_level\": " + to_string(plant->getWaterLevel()) + "}";
}

// Helper methods
Plant* InventoryManager::findPlantByName(const string& plantName) {
    // Check shop first
    vector<Plant*> shopPlants = shopInventory->getAll();
    for (Plant* plant : shopPlants) {
        if (plant->getName() == plantName) {
            return plant;
        }
    }

    // Check nursery
    vector<Plant*> nurseryPlants = nurseryInventory->getAll();
    for (Plant* plant : nurseryPlants) {
        if (plant->getName() == plantName) {
            return plant;
        }
    }

    return nullptr;
}

string InventoryManager::plantToJSON(Plant* plant) {
    if (!plant) return "{}";

    stringstream json;
    json << "{"
         << "\"name\": \"" << plant->getName() << "\", "
         << "\"type\": \"" << plant->getType() << "\", "
         << "\"state\": \"" << plant->getStateName() << "\", "
         << "\"water_level\": " << plant->getWaterLevel() << ", "
         << "\"care_instructions\": \"Placeholder care instructions\""
         << "}";

    return json.str();
}

string InventoryManager::plantsToJSON(const vector<Plant*>& plants) {
    stringstream json;
    json << "[";

    for (size_t i = 0; i < plants.size(); i++) {
        json << plantToJSON(plants[i]);
        if (i < plants.size() - 1) {
            json << ", ";
        }
    }

    json << "]";
    return json.str();
}

// Keep other methods similar but update to use plant names
string InventoryManager::getRecommendations(const string& sunlight,
                                          const string& space,
                                          const string& experience) {
    // Implementation using real plant data
    vector<Plant*> allPlants = shopInventory->getAll();
    vector<Plant*> recommendations;

    for (Plant* plant : allPlants) {
        // Simple recommendation logic based on plant type
        if (sunlight == "low" && plant->getType() == "Succulent") {
            recommendations.push_back(plant);
        }
        // Add more sophisticated logic here
    }

    return "{\"recommendations\": " + plantsToJSON(recommendations) + "}";
}