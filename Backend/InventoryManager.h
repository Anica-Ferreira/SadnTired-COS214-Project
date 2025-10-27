// InventoryManager.h
#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

using namespace std;
#include <string>
#include <vector>

class WebAPIAdapter;

class InventoryManager {
private:
    WebAPIAdapter* apiAdapter;
    
public:
    InventoryManager(WebAPIAdapter* adapter);
    ~InventoryManager();
    
    // Plant search and filtering
    string searchPlants(const string& keyword);
    string filterPlantsByType(const string& plantType);
    string filterPlantsByCareLevel(const string& careLevel);
    string getPlantsByStatus(const string& status);
    
    // Plant information
    string getPlantDetails(int plantName);
    string checkStock(int plantName);
    
    // Recommendations
    string getRecommendations(const string& sunlight, 
                                 const string& space, 
                                 const string& experience);
    
    // Inventory operations
    string updateStock(int plantName, int quantity);
    
    // Bundle management
    string getAvailableBundles();
    string getBundleDetails(const string& bundleName);
    string createCustomBundle(const vector<int>& plantNames, const string& bundleName);
    
private:
    string parseAPIResponse(const string& apiResponse);
};

#endif