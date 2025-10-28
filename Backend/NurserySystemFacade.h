#ifndef NURSERY_SYSTEM_FACADE_H
#define NURSERY_SYSTEM_FACADE_H

#include <string>
#include "Inventory.h"
#include "Customer.h"
#include "InventoryManager.h"
#include "StaffCoordinator.h"
#include "PlantNursery.h"
#include "ShoppingCart.h"
using namespace std;

class NurserySystemFacade {
private:
    Inventory* nurseryInventory;
    Inventory* shopInventory;
    Customer* currentCustomer;
    ShoppingCart* currentCart;
    InventoryManager* inventoryManager;
    StaffCoordinator* staffCoordinator;
    PlantNursery* plantNursery;

public:
    NurserySystemFacade();
    ~NurserySystemFacade();

    // Customer Management
    bool setCustomer(const string& name, const string& surname, const string& email, const string& phone = "");
    void resetCustomer();

    // Plant Shop Operations
    string browseAllPlants();
    string searchPlants(const string& keyword);
    string filterPlantsByType(const string& plantType);
    string getPlantInfo(const string& plantName);
    string checkPlantStock(const string& plantName);

    // Shopping Cart Operations
    string addToCart(const string& plantName, int quantity = 1);
    string removeFromCart(const string& plantName);
    string updateCartQuantity(const string& plantName, int newQuantity);
    string viewCart();
    string getCartSummary();
    void clearCart();

    // Order Management
    string checkout();

    // Customer Support
    string askStaffQuestion(const string& question);
    string requestPlantRecommendation(const string& sunlight, const string& space, const string& experience);

    // Nursery Management
    string viewNurseryStatus();
    string waterPlant(const string& plantName);
    string fertilizePlant(const string& plantName);
    string movePlantToShop(const string& plantName);
    string getPlantHealthReport();
    string waterAllPlants();
    string passTimeForAllPlants();

    // Staff Operations
    string assignStaffTask(int staffId, const string& task);

    // Notifications & Alerts
    string getNotifications();
    string markNotificationRead(int notificationId);

    // Bundles & Special Offers
    string viewAvailableBundles();
    string addBundleToCart(const string& bundleName);

    // System Information
    string getStockCounts();

private:
    void initializeSubsystems();
    void cleanupSubsystems();
    bool validateCustomer() const;
    void populateSampleData();
    string plantToJSON(Plant* plant);
    string plantsToJSON(vector<Plant*> plants);
};

#endif