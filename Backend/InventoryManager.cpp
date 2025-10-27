// InventoryManager.cpp
#include "InventoryManager.h"
#include "WebAPIAdapter.h"
#include <iostream>
#include <sstream>

InventoryManager::InventoryManager(WebAPIAdapter* adapter) : apiAdapter(adapter) {
    cout << "Inventory Manager initialized" << endl;
}

InventoryManager::~InventoryManager() {
    cout << "Inventory Manager destroyed" << endl;
}

string InventoryManager::searchPlants(const string& keyword) {
    cout << "InventoryManager: Searching plants for keyword: " << keyword << endl;
    
    // Get all plants from API
    string allPlants = apiAdapter->getShopProducts();
    
    // In a real implementation, we would parse the JSON and filter
    // For now, return the API response directly
    return "{\"action\": \"search\", \"keyword\": \"" + keyword + 
           "\", \"results\": " + allPlants + "}";
}

string InventoryManager::filterPlantsByType(const string& plantType) {
    cout << "InventoryManager: Filtering plants by type: " << plantType << endl;
    
    string allPlants = apiAdapter->getShopProducts();
    return "{\"action\": \"filter_by_type\", \"type\": \"" + plantType + 
           "\", \"results\": " + allPlants + "}";
}

string InventoryManager::filterPlantsByCareLevel(const string& careLevel) {
    cout << "InventoryManager: Filtering plants by care level: " << careLevel << endl;
    
    string allPlants = apiAdapter->getShopProducts();
    return "{\"action\": \"filter_by_care\", \"care_level\": \"" + careLevel + 
           "\", \"results\": " + allPlants + "}";
}

string InventoryManager::getPlantDetails(int plantName) {  
    cout << "InventoryManager: Getting details for plant ID: " << plantName << endl;
    
    // Get all plants and find the specific one
    string allPlants = apiAdapter->getShopProducts();
    
    // In real implementation, parse JSON and find specific plant
    return "{\"action\": \"get_plant_details\", \"plant_id\": " + to_string(plantName) + 
           ", \"details\": {\"name\": \"Sample Plant\", \"price\": 19.99, \"care_level\": \"easy\"}}";
}

string InventoryManager::checkStock(int plantName) {
    if (!validateplantName(plantName)) {
        return "{\"error\": \"Invalid plant ID\"}";
    }
    
    cout << "InventoryManager: Checking stock for plant ID: " << plantName << endl;
    
    // Get nursery plants to check stock
    string nurseryPlants = apiAdapter->getNurseryPlants();
    
    // Simulate stock check - in real implementation, parse the JSON response
    int simulatedStock = (plantName % 5) + 1; // Random stock between 1-5
    bool inStock = simulatedStock > 0;
    
    stringstream response;
    response << "{\"plant_id\": " << plantName 
             << ", \"in_stock\": " << (inStock ? "true" : "false")
             << ", \"quantity\": " << simulatedStock
             << ", \"status\": \"" << (inStock ? "available" : "out_of_stock") << "\"}";
    
    return response.str();
}

string InventoryManager::getRecommendations(const string& sunlight, 
                                               const string& space, 
                                               const string& experience) {
    cout << "InventoryManager: Getting recommendations for sunlight=" << sunlight 
              << ", space=" << space << ", experience=" << experience << endl;
    
    // Get all plants from API
    string allPlants = apiAdapter->getShopProducts();
    
    // Simulate recommendation logic
    string recommendedType;
    if (sunlight == "low" && space == "small" && experience == "beginner") {
        recommendedType = "Succulents, Snake Plants, Pothos";
    } else if (sunlight == "high" && space == "large" && experience == "expert") {
        recommendedType = "Roses, Sunflowers, Fruit Trees";
    } else {
        recommendedType = "Mixed variety suitable for your conditions";
    }
    
    return "{\"recommendations\": \"" + recommendedType + 
           "\", \"parameters\": {\"sunlight\": \"" + sunlight + 
           "\", \"space\": \"" + space + 
           "\", \"experience\": \"" + experience + "\"}}";
}

string InventoryManager::updateStock(int plantName, int quantity) {
    if (!validateplantName(plantName)) {
        return "{\"error\": \"Invalid plant ID\"}";
    }
    
    if (quantity < 0) {
        return "{\"error\": \"Quantity cannot be negative\"}";
    }
    
    cout << "InventoryManager: Updating stock for plant ID " << plantName 
              << " to quantity " << quantity << endl;
    
    // In real implementation, this would call an API endpoint to update stock
    return "{\"action\": \"update_stock\", \"plant_id\": " + to_string(plantName) + 
           ", \"new_quantity\": " + to_string(quantity) + ", \"status\": \"success\"}";
}

string InventoryManager::getInventoryReport() {
    cout << "InventoryManager: Generating inventory report" << endl;
    
    string shopProducts = apiAdapter->getShopProducts();
    string nurseryPlants = apiAdapter->getNurseryPlants();
    
    return "{\"report_type\": \"inventory_report\", "
           "\"shop_products\": " + shopProducts + ", "
           "\"nursery_plants\": " + nurseryPlants + "}";
}

string InventoryManager::getAvailableBundles() {
    cout << "InventoryManager: Getting available bundles" << endl;
    
    string bundles = apiAdapter->getRandomBundle();
    return "{\"bundles\": " + bundles + "}";
}

string InventoryManager::getBundleDetails(const string& bundleName) {
    cout << "InventoryManager: Getting details for bundle: " << bundleName << endl;
    
    return "{\"bundle_name\": \"" + bundleName + 
           "\", \"plants\": [\"Rose\", \"Lavender\", \"Fern\"], "
           "\"price\": 49.99, \"description\": \"Beautiful mixed plant bundle\"}";
}

string InventoryManager::createCustomBundle(const vector<int>& plantNames, const string& bundleName) {
    cout << "InventoryManager: Creating custom bundle: " << bundleName << endl;
    
    string plantList = "[";
    for (int i = 0; i < plantNames.size(); i++) {
        plantList += to_string(plantNames[i]);
        if (i < plantNames.size() - 1) {
            plantList += ", ";
        }
    }
    plantList += "]";
    
    return "{\"action\": \"create_bundle\", \"bundle_name\": \"" + bundleName + 
           "\", \"plant_ids\": " + plantList + ", \"status\": \"created\"}";
}

// Private helper methods
string InventoryManager::parseAPIResponse(const string& apiResponse) {
    // In real implementation, this would parse JSON and extract relevant data
    return apiResponse;
}
