// WebAPIAdapter.h - UPDATED
#ifndef WEB_API_ADAPTER_H
#define WEB_API_ADAPTER_H

#include <string>
#include "InventoryManager.h"  // Now includes Inventory

class WebAPIAdapter {
private:
    InventoryManager* inventoryManager;
    // Remove other managers if not needed

public:
    WebAPIAdapter(InventoryManager* invManager);  // Takes real inventory manager
    ~WebAPIAdapter();

    // Shop endpoints - SERVES REAL DATA
    std::string getShopProducts();
    std::string getRandomPlants();

    // Nursery endpoints - SERVES REAL DATA
    std::string getNurseryPlants();
    std::string waterPlant(const std::string& plantName);  // Changed to string
    std::string movePlantToShop(const std::string& plantName);  // Changed to string

    // Staff endpoints
    std::string getStaff();
    std::string getNotifications();
    std::string finishTask(int taskId);

    // Customer endpoints
    std::string createCustomer(const std::string& name, const std::string& email);
    std::string executeCustomerCommand(const std::string& commandType, const std::string& params);
    std::string getCustomerCart(int customerId);

    // Bundle endpoints
    std::string getRandomBundle();

private:
    std::string inventoryToJSON(const std::vector<Plant*>& plants);
};

#endif