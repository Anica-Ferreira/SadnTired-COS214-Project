// InventoryManager.h - UPDATED
#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <string>
#include <vector>
#include "Inventory.h"  // Include your actual Inventory class
using namespace std;

class WebAPIAdapter;
class Plant;

class InventoryManager {
private:
    WebAPIAdapter* apiAdapter;
    Inventory* nurseryInventory;  // Your actual nursery inventory
    Inventory* shopInventory;     // Your actual shop inventory

public:
    InventoryManager(WebAPIAdapter* adapter, Inventory* nurseryInv, Inventory* shopInv);
    ~InventoryManager();

    // Plant search and filtering
    string searchPlants(const string& keyword);
    string filterPlantsByType(const string& plantType);
    string filterPlantsByCareLevel(const string& careLevel);
    string getPlantsByStatus(const string& status);

    // Plant information
    string getPlantDetails(const string& plantName);
    string checkStock(const string& plantName);
    string getPlantCareInstructions(const string& plantName);

    // Recommendations
    string getRecommendations(const string& sunlight,
                             const string& space,
                             const string& experience);

    // Inventory operations
    string updateStock(const string& plantName, int quantity);
    string movePlantToShop(const string& plantName);
    string waterPlant(const string& plantName);

    // Bundle management
    string getAvailableBundles();
    string getBundleDetails(const string& bundleName);
    string createCustomBundle(const vector<string>& plantNames, const string& bundleName);

    // Internal data access for API
    vector<Plant*> getNurseryPlants() const { return nurseryInventory->getAll(); }
    vector<Plant*> getShopPlants() const { return shopInventory->getAll(); }

private:
    Plant* findPlantByName(const string& plantName);
    string plantToJSON(Plant* plant);
    string plantsToJSON(const vector<Plant*>& plants);
};

#endif