#ifndef WEB_API_ADAPTER_H
#define WEB_API_ADAPTER_H

#include "InventoryFacade.h"
#include "CustomerManager.h"
#include "StaffMediator.h"
#include "PlantMonitor.h"
#include <string>

class WebAPIAdapter {
private:
    InventoryFacade* inventoryFacade;
    CustomerManager* customerManager;
    StaffMediator* staffMediator;
    PlantMonitor* plantMonitor;

public:
    WebAPIAdapter();
    ~WebAPIAdapter();

    // Shop endpoints
    std::string getShopProducts();
    std::string getRandomPlants();

    // Nursery endpoints
    std::string getNurseryPlants();
    std::string waterPlant(int plantId);
    std::string movePlantToShop(int plantId);

    // Staff endpoints
    std::string getStaff();
    std::string getNotifications();
    std::string finishTask(int taskId);

    // Customer endpoints (new)
    std::string createCustomer(const std::string& name, const std::string& email);
    std::string executeCustomerCommand(int customerId, const std::string& commandType, const std::string& params);
    std::string getCustomerCart(int customerId);

    // Bundle endpoints
    std::string getRandomBundle();
};

#endif