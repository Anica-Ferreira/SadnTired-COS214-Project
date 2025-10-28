// WebAPIAdapter.cpp - UPDATED
#include "WebAPIAdapter.h"
#include "InventoryManager.h"
#include <sstream>

WebAPIAdapter::WebAPIAdapter(InventoryManager* invManager) : inventoryManager(invManager) {
    cout << "WebAPIAdapter initialized with real data backend" << endl;
}

WebAPIAdapter::~WebAPIAdapter() {
    cout << "WebAPIAdapter destroyed" << endl;
}

std::string WebAPIAdapter::getShopProducts() {
    // Get REAL data from inventory manager
    std::vector<Plant*> shopPlants = inventoryManager->getShopPlants();
    return inventoryToJSON(shopPlants);
}

std::string WebAPIAdapter::getNurseryPlants() {
    // Get REAL data from inventory manager
    std::vector<Plant*> nurseryPlants = inventoryManager->getNurseryPlants();
    return inventoryToJSON(nurseryPlants);
}

std::string WebAPIAdapter::waterPlant(const std::string& plantName) {
    // Actually water the plant in the backend
    return inventoryManager->waterPlant(plantName);
}

std::string WebAPIAdapter::movePlantToShop(const std::string& plantName) {
    // Actually move the plant in the backend
    return inventoryManager->movePlantToShop(plantName);
}

std::string WebAPIAdapter::inventoryToJSON(const std::vector<Plant*>& plants) {
    std::stringstream json;
    json << "[";

    for (size_t i = 0; i < plants.size(); i++) {
        Plant* plant = plants[i];
        json << "{"
             << "\"name\": \"" << plant->getName() << "\", "
             << "\"type\": \"" << plant->getType() << "\", "
             << "\"state\": \"" << plant->getStateName() << "\", "
             << "\"water_level\": " << plant->getWaterLevel();

        // Add shop-specific or nursery-specific fields
        if (plant->getStateName() == "Ready for Sale") {
            json << ", \"price\": 19.99";  // Example price
        }

        json << "}";

        if (i < plants.size() - 1) {
            json << ", ";
        }
    }

    json << "]";
    return json.str();
}

// Keep other methods but they can remain as stubs for now
std::string WebAPIAdapter::getStaff() {
    return "{\"staff\": [{\"name\": \"Mr. Green\", \"role\": \"Gardener\"}]}";
}

std::string WebAPIAdapter::getNotifications() {
    return "{\"notifications\": []}";
}

std::string WebAPIAdapter::finishTask(int taskId) {
    return "{\"status\": \"completed\", \"task_id\": " + std::to_string(taskId) + "}";
}

std::string WebAPIAdapter::createCustomer(const std::string& name, const std::string& email) {
    return "{\"status\": \"created\", \"customer_name\": \"" + name + "\"}";
}

std::string WebAPIAdapter::executeCustomerCommand(const std::string& commandType, const std::string& params) {
    return "{\"status\": \"executed\", \"command\": \"" + commandType + "\"}";
}

std::string WebAPIAdapter::getCustomerCart(int customerId) {
    return "{\"cart\": []}";
}

std::string WebAPIAdapter::getRandomPlants() {
    return getShopProducts();  // Use real data
}

std::string WebAPIAdapter::getRandomBundle() {
    return "{\"bundle\": {\"name\": \"Spring Collection\", \"plants\": 3}}";
}