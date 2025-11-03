#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <string>
#include <vector>
#include "Inventory.h"
#include "../core/WebAPIAdapter.h"
#include "../greenhouse/Plant.h"
using namespace std;

class WebAPIAdapter;
class Plant;

class InventoryManager {
private:
    WebAPIAdapter* apiAdapter;
    Inventory* nurseryInventory;
    Inventory* shopInventory;

public:
    InventoryManager(WebAPIAdapter* adapter, Inventory* nurseryInv, Inventory* shopInv);
    ~InventoryManager();

    // Plant search and filtering
    vector<Plant*> searchPlantsByKeyword(const string& keyword);
    string filterPlantsByType(const string& plantType);
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