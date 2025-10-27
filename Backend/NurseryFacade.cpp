// NurserySystemFacade.cpp - UPDATED
#include "NurserySystemFacade.h"
#include "WebAPIAdapter.h"
#include "Customer.h"
#include "ShoppingCart.h"
#include "InventoryManager.h"
#include "StaffCoordinator.h"
#include "PlantNursery.h"
#include "CustomerCommand.h"
#include <iostream>
#include <map>

NurserySystemFacade::NurserySystemFacade()
    : currentCustomer(nullptr), currentCart(nullptr),
      inventoryManager(nullptr), staffCoordinator(nullptr),
      plantNursery(nullptr) {

    initializeSubsystems();
    cout << "Nursery System Facade initialized" << endl;
}

NurserySystemFacade::~NurserySystemFacade() {
    cleanupSubsystems();
    cout << "Nursery System Facade destroyed" << endl;
}

void NurserySystemFacade::initializeSubsystems() {
    apiAdapter = new WebAPIAdapter();
    inventoryManager = new InventoryManager(apiAdapter);
    staffCoordinator = new StaffCoordinator(apiAdapter);
    plantNursery = new PlantNursery(apiAdapter);

    // Initialize with empty customer
    currentCustomer = new Customer("", "", "", "");
    currentCart = new ShoppingCart(); // Assuming ShoppingCart doesn't need customer
}

void NurserySystemFacade::cleanupSubsystems() {
    delete currentCart;
    delete currentCustomer;
    delete plantNursery;
    delete staffCoordinator;
    delete inventoryManager;
    delete apiAdapter;
}

bool NurserySystemFacade::setCustomer(const string& name, const string& surname,
                                     const string& email, const string& phone) {
    if (!currentCustomer) {
        currentCustomer = new Customer(name, surname, email, phone);
    } else {
        currentCustomer->setName(name);
        currentCustomer->setSurname(surname);
        currentCustomer->setEmail(email);
        currentCustomer->setPhone(phone);
    }

    cout << "Customer set: " << currentCustomer->getName() << endl;
    return true;
}

void NurserySystemFacade::resetCustomer() {
    if (currentCustomer) {
        cout << "Customer reset: " << currentCustomer->getName() << endl;
        currentCustomer->setName("");
        currentCustomer->setSurname("");
        currentCustomer->setEmail("");
        currentCustomer->setPhone("");
    }
    if (currentCart) {
        currentCart->clear();
    }
}

// Plant Name to ID mapping helper
int NurserySystemFacade::plantNameToId(const string& plantName) {
    // Simple mapping - in real system, this would query the API
    map<string, int> plantMap = {
        {"Rose", 1}, {"Lavender", 2}, {"Cactus", 3}, {"Tulip", 4},
        {"Daisy", 5}, {"Orchid", 6}, {"Sunflower", 7}, {"Succulent", 8},
        {"Fern", 9}, {"Bonsai", 10}, {"Peace Lily", 11}, {"Aloe Vera", 12}
    };

    if (plantMap.find(plantName) != plantMap.end()) {
        return plantMap[plantName];
    }
    return 1; // Default to Rose if not found
}

// Updated methods using plant names
string NurserySystemFacade::addToCart(const string& plantName, int quantity) {
    int plantId = plantNameToId(plantName);
    // Implementation would call API through inventoryManager
    return "Added " + to_string(quantity) + " " + plantName + " to cart";
}

string NurserySystemFacade::checkPlantStock(const string& plantName) {
    int plantId = plantNameToId(plantName);
    return inventoryManager->checkStock(plantId);
}

string NurserySystemFacade::getPlantInfo(const string& plantName) {
    int plantId = plantNameToId(plantName);
    return inventoryManager->getPlantDetails(plantId);
}

string NurserySystemFacade::waterPlant(const string& plantName) {
    int plantId = plantNameToId(plantName);
    return apiAdapter->waterPlant(plantId);
}

string NurserySystemFacade::movePlantToShop(const string& plantName) {
    int plantId = plantNameToId(plantName);
    return apiAdapter->movePlantToShop(plantId);
}

// Command execution helper
string NurserySystemFacade::executeCustomerCommand(const string& commandType,
                                                 const string& plantName,
                                                 int quantity,
                                                 const string& question,
                                                 const string& sunlight,
                                                 const string& space,
                                                 const string& experience) {

    CustomerCommand* command = nullptr;

    if (commandType == "purchase" && !plantName.empty()) {
        command = new PurchasePlantCommand(plantName, quantity, this);
    }
    else if (commandType == "check_stock" && !plantName.empty()) {
        command = new CheckStockCommand(plantName, this);
    }
    else if (commandType == "get_info" && !plantName.empty()) {
        command = new GetPlantInfoCommand(plantName, this);
    }
    else if (commandType == "ask_question" && !question.empty()) {
        command = new AskQuestionCommand(question, this);
    }
    else if (commandType == "get_recommendation") {
        command = new RequestRecommendationCommand(sunlight, space, experience, this);
    }

    if (command && currentCustomer) {
        string result = command->execute(currentCustomer);
        delete command;
        return result;
    }

    delete command;
    return "Error: Invalid command or no customer set";
}

// Other methods remain similar but use plant names instead of IDs
string NurserySystemFacade::browseAllPlants() {
    return apiAdapter->getShopProducts();
}

string NurserySystemFacade::askStaffQuestion(const string& question) {
    // Since we don't have customer IDs, use a default or handle differently
    return staffCoordinator->handleCustomerQuestion(0, question);
}

string NurserySystemFacade::requestPlantRecommendation(const string& sunlight,
                                                     const string& space,
                                                     const string& experience) {
    return inventoryManager->getRecommendations(sunlight, space, experience);
}

bool NurserySystemFacade::validateCustomer() const {
    return currentCustomer && !currentCustomer->getName().empty();
}

// Add missing method implementations
string NurserySystemFacade::searchPlants(const string& keyword) {
    return inventoryManager->searchPlants(keyword);
}

string NurserySystemFacade::filterPlantsByType(const string& plantType) {
    return inventoryManager->filterPlantsByType(plantType);
}

string NurserySystemFacade::filterPlantsByCareLevel(const string& careLevel) {
    return inventoryManager->filterPlantsByCareLevel(careLevel);
}

string NurserySystemFacade::viewNurseryStatus() {
    return apiAdapter->getNurseryPlants();
}

string NurserySystemFacade::viewStaffMembers() {
    return apiAdapter->getStaff();
}

string NurserySystemFacade::viewPendingTasks() {
    return apiAdapter->getNotifications();
}

string NurserySystemFacade::completeTask(int taskId) {
    return apiAdapter->finishTask(taskId);
}

string NurserySystemFacade::getNotifications() {
    return apiAdapter->getNotifications();
}

string NurserySystemFacade::viewAvailableBundles() {
    return inventoryManager->getAvailableBundles();
}

string NurserySystemFacade::checkout() {
    if (!validateCustomer()) {
        return "Error: No customer information set";
    }
    if (!currentCart || currentCart->isEmpty()) {
        return "Error: Cart is empty";
    }
    return "Checkout completed for " + currentCustomer->getName();
}

// Stub implementations for unimplemented methods
string NurserySystemFacade::removeFromCart(const string& plantName) {
    return "Remove from cart: " + plantName;
}

string NurserySystemFacade::updateCartQuantity(const string& plantName, int newQuantity) {
    return "Update cart quantity: " + plantName + " to " + to_string(newQuantity);
}

string NurserySystemFacade::viewCart() {
    return "Cart contents";
}

string NurserySystemFacade::getCartSummary() {
    return "Cart summary";
}

void NurserySystemFacade::clearCart() {
    if (currentCart) {
        currentCart->clear();
    }
}