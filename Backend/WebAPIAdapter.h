#ifndef WEB_API_ADAPTER_H
#define WEB_API_ADAPTER_H

using namespace std;
#include <string>

class NurserySystemFacade;

class WebAPIAdapter {
private:
    NurserySystemFacade* nurseryFacade;

public:
    WebAPIAdapter(NurserySystemFacade* facade);
    ~WebAPIAdapter();

    // Shop endpoints
    std::string getShopProducts();
    std::string getRandomPlants();

    // Nursery endpoints
    std::string getNurseryPlants();
    std::string waterPlant(const std::string& plantName);
    std::string movePlantToShop(const std::string& plantName);

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
};

#endif