// WebAPIAdapter.h - UPDATED
#ifndef WEB_API_ADAPTER_H
#define WEB_API_ADAPTER_H

#include <string>
#include <vector>
#include <iostream>
 
#include "../greenhouse/Plant.h"

using namespace std;

class InventoryManager;

class WebAPIAdapter {
    private:
        InventoryManager* inventoryManager;
        

    public:
        WebAPIAdapter(InventoryManager* invManager);
        ~WebAPIAdapter();

        // Shop endpoints - SERVES REAL DATA
        string getShopProducts();
        string getRandomPlants();

        // Nursery endpoints - SERVES REAL DATA
        string getNurseryPlants();
        string waterPlant(const string& plantName);
        string movePlantToShop(const string& plantName);

        // Staff endpoints
        string getStaff();
        string getNotifications();
        string finishTask(int taskId);

        // Customer endpoints
        string createCustomer(const string& name, const string& email);
        string executeCustomerCommand(const string& commandType, const string& params);
        string getCustomerCart(int customerId);

        // Bundle endpoints
        string getRandomBundle();

    private:
        string inventoryToJSON(const vector<Plant*>& plants);
};

#endif