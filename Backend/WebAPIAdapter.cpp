// WebAPIAdapter.cpp
#include "WebAPIAdapter.h"
#include "APICommandHandler.h"
#include "json.hpp"
#include <sstream>

using json = nlohmann::json;

WebAPIAdapter::WebAPIAdapter() {
    inventoryFacade = new InventoryFacade();
    customerManager = CustomerManager::getInstance();
    staffMediator = new StaffMediator();
    plantMonitor = new PlantMonitor();
}

WebAPIAdapter::~WebAPIAdapter() {
    delete inventoryFacade;
    delete staffMediator;
    delete plantMonitor;
}

std::string WebAPIAdapter::getShopProducts() {
    std::vector<Product*> products = inventoryFacade->getAvailableProducts();

    json result = json::array();
    for (int i = 0; i < products.size(); i++) {
        json productJson;
        productJson["id"] = products[i]->getId();
        productJson["name"] = products[i]->getName();
        productJson["description"] = products[i]->getDescription();
        productJson["shopStock"] = products[i]->getStock();
        productJson["price"] = products[i]->getPrice();
        result.push_back(productJson);
    }

    return result.dump();
}

std::string WebAPIAdapter::createCustomer(const std::string& name, const std::string& email) {
    Customer* customer = customerManager->createCustomer(name, email);

    json response;
    response["status"] = "success";
    response["customerId"] = customer->getId();
    response["name"] = customer->getName();

    return response.dump();
}

std::string WebAPIAdapter::executeCustomerCommand(int customerId, const std::string& commandType, const std::string& params) {
    Customer* customer = customerManager->getCustomer(customerId);
    if (!customer) {
        return "{\"error\": \"Customer not found\"}";
    }

    APICommandHandler commandHandler(inventoryFacade, new OrderBuilder());
    return commandHandler.executeCommand(customer, commandType, params);
}

std::string WebAPIAdapter::getCustomerCart(int customerId) {
    Customer* customer = customerManager->getCustomer(customerId);
    if (!customer) {
        return "{\"error\": \"Customer not found\"}";
    }

    ShoppingCart* cart = customer->getShoppingCart();
    std::vector<CartItem> items = cart->getItems();

    json result;
    result["customerId"] = customerId;
    result["customerName"] = customer->getName();
    result["totalItems"] = cart->getItemCount();
    result["totalPrice"] = cart->calculateTotal();

    json itemsArray = json::array();
    for (int i = 0; i < items.size(); i++) {
        json itemJson;
        itemJson["plantId"] = items[i].plantId;
        itemJson["quantity"] = items[i].quantity;
        itemJson["unitPrice"] = items[i].unitPrice;
        itemsArray.push_back(itemJson);
    }
    result["items"] = itemsArray;

    return result.dump();
}