// NurserySystemFacade.h - UPDATED
#ifndef NURSERY_SYSTEM_FACADE_H
#define NURSERY_SYSTEM_FACADE_H

#include <string>
using namespace std;

// Forward declarations
class WebAPIAdapter;
class Customer;
class ShoppingCart;
class InventoryManager;
class StaffCoordinator;
class PlantNursery;

class NurserySystemFacade {
private:
    WebAPIAdapter* apiAdapter;
    Customer* currentCustomer;
    ShoppingCart* currentCart;
    InventoryManager* inventoryManager;
    StaffCoordinator* staffCoordinator;
    PlantNursery* plantNursery;

public:
    NurserySystemFacade();
    ~NurserySystemFacade();

    // Customer Management (no login - set customer at purchase)
    bool setCustomer(const string& name, const string& surname,
                     const string& email, const string& phone = "");
    void resetCustomer();

    // Plant Shop Operations - USING PLANT NAMES
    string browseAllPlants();
    string searchPlants(const string& keyword);
    string filterPlantsByType(const string& plantType);
    string filterPlantsByCareLevel(const string& careLevel);
    string getPlantInfo(const string& plantName); // CHANGED from getPlantDetails
    string checkPlantStock(const string& plantName); // ADDED

    // Shopping Cart Operations - USING PLANT NAMES
    string addToCart(const string& plantName, int quantity = 1); // CHANGED
    string removeFromCart(const string& plantName); // CHANGED
    string updateCartQuantity(const string& plantName, int newQuantity); // CHANGED
    string viewCart();
    string getCartSummary();
    void clearCart();

    // Order Management
    string checkout();

    // Customer Support
    string askStaffQuestion(const string& question);
    string requestPlantRecommendation(const string& sunlight,
                                     const string& space,
                                     const string& experience);

    // Nursery Management
    string viewNurseryStatus();
    string waterPlant(const string& plantName); // CHANGED
    string movePlantToShop(const string& plantName); // CHANGED

    // Staff Operations
    string viewStaffMembers();
    string viewPendingTasks();
    string completeTask(int taskId);

    // Notifications & Alerts
    string getNotifications();

    // Bundles & Special Offers
    string viewAvailableBundles();

    // Command execution helper
    string executeCustomerCommand(const string& commandType,
                                 const string& plantName = "",
                                 int quantity = 0,
                                 const string& question = "",
                                 const string& sunlight = "",
                                 const string& space = "",
                                 const string& experience = "");

private:
    void initializeSubsystems();
    void cleanupSubsystems();
    bool validateCustomer() const;
    int plantNameToId(const string& plantName); // Helper to convert names to IDs for API
};

#endif