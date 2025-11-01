/**
 * @class [WebAPIAdapter]
 * @brief [The implementation of the WebAPIAdapter class for handling HTTP API requests]
 * @details [Acts as an adapter between the web API and the nursery system facade]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
*/

#include "WebAPIAdapter.h"
#include "../inventory/InventoryManager.h"
#include <sstream>
#include <iostream>

using namespace std;

/**
 * @brief [Constructs a new WebAPIAdapter object]
 * @param[in] invManager [Pointer to the InventoryManager instance]
 */
WebAPIAdapter::WebAPIAdapter(InventoryManager* invManager) : inventoryManager(invManager) {
    cout << "WebAPIAdapter initialized with real data backend" << endl;
}

/**
 * @brief [Destroys the WebAPIAdapter object]
 */
WebAPIAdapter::~WebAPIAdapter() {
    cout << "WebAPIAdapter destroyed" << endl;
}

/**
 * @brief [Retrieves all shop products]
 * @return [JSON string containing shop products or error message]
 */
string WebAPIAdapter::getShopProducts() {
    // Get REAL data from inventory manager
    vector<Plant*> shopPlants = inventoryManager->getShopPlants();
    return inventoryToJSON(shopPlants);
}

/**
 * @brief [Retrieves all nursery plants]
 * @return [JSON string containing nursery plants or error message]
 */
string WebAPIAdapter::getNurseryPlants() {
    // Get REAL data from inventory manager
    vector<Plant*> nurseryPlants = inventoryManager->getNurseryPlants();
    return inventoryToJSON(nurseryPlants);
}

/**
 * @brief [Waters a specific plant]
 * @param[in] plantName [Name of the plant to water]
 * @return [JSON string indicating watering result or error]
 */
string WebAPIAdapter::waterPlant(const string& plantName) {
    // Actually water the plant in the backend
    return inventoryManager->waterPlant(plantName);
}

/**
 * @brief [Moves a plant from nursery to shop]
 * @param[in] plantName [Name of the plant to move]
 * @return [JSON string indicating move result or error]
 */
string WebAPIAdapter::movePlantToShop(const string& plantName) {
    // Actually move the plant in the backend
    return inventoryManager->movePlantToShop(plantName);
}

/**
 * @brief [Converts a list of Plant objects to a JSON string]
 * @param[in] plants [Vector of Plant pointers]
 * @return [JSON string representation of the plant list]
 */
string WebAPIAdapter::inventoryToJSON(const vector<Plant*>& plants) {
    stringstream json;
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
//STUBS://

/**
 * @brief [Retrieves all tasks]
 * @return [JSON string containing tasks or error message]
 */
string WebAPIAdapter::getStaff() {
    return "{\"staff\": [{\"name\": \"Mr. Green\", \"role\": \"Gardener\"}]}";
}

/**
 * @brief [Retrieves all notifications]
 * @return [JSON string containing notifications or error message]
 */
string WebAPIAdapter::getNotifications() {
    return "{\"notifications\": []}";
}

/**
 * @brief [Finishes a specific task]
 * @param[in,out] taskId [ID of the task to finish]
 * @return [JSON string indicating task completion or error]
 */
string WebAPIAdapter::finishTask(int taskId) {
    return "{\"status\": \"completed\", \"task_id\": " + to_string(taskId) + "}";
}

/**
 * @brief [Creates a new customer]
 * @param[in,out] name [Customer name]
 * @param[in,out] email [Customer email]
 * @return [JSON string with customer creation status]
 */
string WebAPIAdapter::createCustomer(const string& name, const string& email) {
    return "{\"status\": \"created\", \"customer_name\": \"" + name + "\"}";
}

/**
 * @brief [Executes a customer command]
 * @param[in,out] commandType [Type of command to execute]
 * @param[in] params [Parameters for the command]
 * @return [JSON string indicating command execution result]
 */
string WebAPIAdapter::executeCustomerCommand(const string& commandType, const string& params) {
    return "{\"status\": \"executed\", \"command\": \"" + commandType + "\"}";
}

/**
 * @brief [Retrieves the cart for a specific customer]
 * @param[in] customerId [ID of the customer]
 * @return [JSON string containing cart details or error]
 */
string WebAPIAdapter::getCustomerCart(int customerId) {
    return "{\"cart\": []}";
}

/**
 * @brief [Retrieves random plants from shop]
 * @return [JSON string containing random plants or error]
 */
string WebAPIAdapter::getRandomPlants() {
    return getShopProducts();  // Use real data
}

/**
 * @brief [Retrieves a random plant bundle]
 * @return [JSON string containing bundle information or error]
 */
string WebAPIAdapter::getRandomBundle() {
    return "{\"bundle\": {\"name\": \"Spring Collection\", \"plants\": 3}}";
}