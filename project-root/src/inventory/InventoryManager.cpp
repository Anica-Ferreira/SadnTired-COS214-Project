/**
 * @class [InventoryManager]
 * @brief [Implementation of the InventoryManager class for inventory operations]
 * @details [Handles inventory management including search, filtering, and plant operations]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "InventoryManager.h"
 
#include <iostream>
#include <sstream>

/**
 * @brief [Constructs a new InventoryManager object]
 * @param[in] adapter [Pointer to the WebAPIAdapter for system communication]
 * @param[in] nurseryInv [Pointer to the nursery inventory]
 * @param[in] shopInv [Pointer to the shop inventory]
 */
InventoryManager::InventoryManager(WebAPIAdapter* adapter, Inventory* nurseryInv, Inventory* shopInv)
    : apiAdapter(adapter), nurseryInventory(nurseryInv), shopInventory(shopInv) {
    //cout << "Inventory Manager initialized with real inventory data" << endl;
}

/**
 * @brief [Destroys the InventoryManager object]
 */
InventoryManager::~InventoryManager() {
    //cout << "Inventory Manager destroyed" << endl;
    // Don't delete inventories here - they're managed elsewhere
}

/**
 * @brief [Searches plants by keyword]
 * @param[in,out] keyword [Search keyword]
 * @return [JSON string containing search results]
 */
vector<Plant*> InventoryManager::searchPlantsByKeyword(const string& keyword) {
    vector<Plant*> allPlants = shopInventory->getAll();
    vector<Plant*> results;

    string lowerKeyword = keyword;
    for (char &c : lowerKeyword) c = tolower(c);

    for (Plant* plant : allPlants) {
        string lowerName = plant->getName();
        for (char &c : lowerName) c = tolower(c);
        if (lowerName.find(lowerKeyword) != string::npos) {
            results.push_back(plant);
        }
    }

    return results;
}

/**
 * @brief [Filters plants by type]
 * @param[in,out] plantType [Type of plants to filter by]
 * @return [JSON string containing filtered results]
 */
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

/**
 * @brief [Gets detailed information about a specific plant]
 * @param[in,out] plantName [Name of the plant to get details for]
 * @return [JSON string containing plant details]
 */
string InventoryManager::getPlantDetails(const string& plantName) {
    cout << "InventoryManager: Getting details for plant: " << plantName << endl;

    Plant* plant = findPlantByName(plantName);
    if (!plant) {
        return "{\"error\": \"Plant not found: " + plantName + "\"}";
    }

    return plantToJSON(plant);
}

/**
 * @brief [Checks stock availability for a specific plant]
 * @param[in,out] plantName [Name of the plant to check stock for]
 * @return [JSON string containing stock information]
 */

string InventoryManager::checkStock(const string& plantName) {
    cout << "\033[1;32m\nInventoryManager: Checking stock for plant: " << plantName << "\033[0m" << endl;

    vector<Plant*> shopPlants = shopInventory->getAll();
    int count = 0;

    for (Plant* plant : shopPlants) {
        if (plant->getName() == plantName && plant->getStateName() == "Ready for Sale") {
            count++;
        }
    }

    if (count > 0) {
        return "Hello! I just checked for you and we currently have " + 
               to_string(count) + " '" + plantName + "' available in the shop.";
    }else {
        return "Sorry but I'm afraid '" + plantName + "' is currently out of stock. Would you like me to recommend something similar?";
    }
}

/**
 * @brief [Moves a plant from nursery to shop inventory]
 * @param[in,out] plantName [Name of the plant to move]
 * @return [JSON string indicating move result]
 */
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

/**
 * @brief [Waters a specific plant]
 * @param[in,out] plantName [Name of the plant to water]
 * @return [JSON string indicating watering result]
 */
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

/**
 * @brief [Finds a plant by name in either inventory]
 * @param[in] plantName [Name of the plant to find]
 * @return [Pointer to the found plant, or nullptr if not found]
 */
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

/**
 * @brief [Converts a plant object to JSON format]
 * @param[in] plant [Pointer to the plant to convert]
 * @return [JSON string representation of the plant]
 */
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

/**
 * @brief [Converts a vector of plants to JSON format]
 * @param[in] plants [Vector of plant pointers to convert]
 * @return [JSON string representation of the plants]
 */
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

/**
 * @brief [Gets plant recommendations based on user conditions]
 * @param[in] sunlight [Sunlight condition]
 * @param[in] space [Space availability]
 * @param[in] experience [User experience level]
 * @return [JSON string containing plant recommendations]
 */
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