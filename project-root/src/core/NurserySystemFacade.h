#ifndef NURSERY_SYSTEM_FACADE_H
#define NURSERY_SYSTEM_FACADE_H

#include <string>
#include <vector>
#include "../products/DecorativePot.h"
#include "../products/GiftWrapping.h"

using namespace std;

// Forward declarations
class WebAPIAdapter;
class Customer;
class ShoppingCart;
class InventoryManager;
class StaffCoordinator;
class PlantNursery;
class Inventory;
class ConcreteOrderBuilder;
class Plant;
class DecorativePot;
class GiftWrapping;
class Product;
class ProductBundle;
class OrderDirector;

class NurserySystemFacade {
private:
    WebAPIAdapter* apiAdapter;
    Customer* currentCustomer;
    ShoppingCart* currentCart;
    InventoryManager* inventoryManager;
    StaffCoordinator* staffCoordinator;
    PlantNursery* plantNursery;

    // Real inventory objects
    Inventory* nurseryInventory;
    Inventory* shopInventory;
    vector<Product*> specialBundles;

    ConcreteOrderBuilder* builder;
    OrderDirector* director;
public:
    NurserySystemFacade();
    ~NurserySystemFacade();

    // Customer Management (set at purchase time)
    bool setCustomer(const string& name, const string& surname,
                     const string& email, const string& phone = "");
    void resetCustomer();
    string getCurrentCustomerInfo() const;

    // Plant Shop Operations - USING REAL DATA
    string browseAllPlants();
    vector<Plant*> getPlantsByKeyword(const string& keyword);
    string filterPlantsByType(const string& plantType);
    string getPlantInfo(const string& plantName);
    string checkPlantStock(const string& plantName);

    // Shopping Cart Operations
    void addToCart(Product* product);
    string removeFromCart(int itemNumber);
    string updateCartQuantity(const string& plantName, int newQuantity);
    string viewCart();
    string getCartSummary();
    ShoppingCart* getCart() const;
    void clearCart();

    // Order Management
    string checkout();

    // Customer Support
    string askStaffQuestion(const string& question);
    string requestPlantRecommendation(const string& sunlight,
                                     const string& space,
                                     const string& experience);

    // Nursery Management - MODIFIES REAL DATA
    string viewNurseryStatus();
    string waterPlant(const string& plantName);
    string fertilizePlant(const string& plantName);
    string movePlantToShop(const string& plantName);
    string getPlantHealthReport();
    string waterAllPlants();
    string passTimeForAllPlants();

    // Staff Operations
    string viewStaffMembers();
    string assignStaffTask(int staffId, const string& task);
    string viewPendingTasks();
    string completeTask(int taskId);

    // Notifications & Alerts
    string getNotifications();
    string markNotificationRead(int notificationId);

    // Bundles & Special Offers
    string viewAvailableBundles();
    string addBundleToCart(const string& bundleName);

    // Inventory Reports
    string getStockCounts();

    // Command execution helper
    string executeCustomerCommand(
        const string& commandType,
        const string& plantName,
        int quantity,
        const string& question,
        const string& sunlight,
        const string& space,
        const string& experience,
        DecorativePot::PotType pot,
        GiftWrapping::WrappingType wrap
    );
    
    //Accessors for testing
    Inventory* getNurseryInventory();
    Inventory* getShopInventory();

    //Order builder
    void startNewOrder();
    void setOrderPlant(Plant* plant);
    void addOrderPot(DecorativePot::PotType type);
    void addOrderWrapping(GiftWrapping::WrappingType type);
    Product* finalizeOrder();

    //bundles
    void createSpecialBundles();
    vector<Product*> getSpecialBundles() const { return specialBundles; }

private:
    void initializeSubsystems();
    void cleanupSubsystems();
    bool validateCustomer() const;
    void populateSampleData(); // Add sample plants to inventories using Factory
};

#endif