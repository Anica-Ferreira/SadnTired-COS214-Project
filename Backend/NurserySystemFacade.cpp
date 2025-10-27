#include "NurserySystemFacade.h"
#include "WebAPIAdapter.h"
#include "Customer.h"
#include "ShoppingCart.h"
#include "InventoryManager.h"
#include "StaffCoordinator.h"
#include "PlantNursery.h"
#include "Inventory.h"
#include "Plant.h"
#include "PlantFactory.h"  // Include the factory
#include "CustomerCommand.h"
#include <iostream>
#include <sstream>

NurserySystemFacade::NurserySystemFacade()
    : currentCustomer(nullptr), currentCart(nullptr),
      inventoryManager(nullptr), staffCoordinator(nullptr),
      plantNursery(nullptr), nurseryInventory(nullptr), shopInventory(nullptr) {

    initializeSubsystems();
    cout << "Nursery System Facade initialized with real data backend" << endl;
}

NurserySystemFacade::~NurserySystemFacade() {
    cleanupSubsystems();
    cout << "Nursery System Facade destroyed" << endl;
}

void NurserySystemFacade::initializeSubsystems() {
    // Create real inventory objects
    nurseryInventory = new Inventory();
    shopInventory = new Inventory();

    // Populate with sample data using factory
    populateSampleData();

    // Create inventory manager with real inventories
    inventoryManager = new InventoryManager(nullptr, nurseryInventory, shopInventory);

    // Create API adapter with inventory manager
    apiAdapter = new WebAPIAdapter(inventoryManager);

    staffCoordinator = new StaffCoordinator("test", apiAdapter);
    plantNursery = new PlantNursery(apiAdapter);

    // Initialize customer and cart
    currentCustomer = new Customer("", "", "", "");
    currentCart = new ShoppingCart();
}

void NurserySystemFacade::cleanupSubsystems() {
    delete currentCart;
    delete currentCustomer;
    delete plantNursery;
    delete staffCoordinator;
    delete inventoryManager;
    delete apiAdapter;
    delete nurseryInventory;
    delete shopInventory;
}

void NurserySystemFacade::populateSampleData() {
    // Create factories
    SucculentFactory succulentFactory;
    FlowerFactory flowerFactory;
    TreeFactory treeFactory;

    // Add sample plants to nursery using factory
    nurseryInventory->addPlant(flowerFactory.createPlant("Rose", 12.99, "Beautiful red roses"));
    nurseryInventory->addPlant(flowerFactory.createPlant("Tulip", 8.99, "Colorful spring tulips"));
    nurseryInventory->addPlant(flowerFactory.createPlant("Lavender", 10.99, "Fragrant purple lavender"));
    nurseryInventory->addPlant(succulentFactory.createPlant("Cactus", 6.99, "Low maintenance cactus"));
    nurseryInventory->addPlant(succulentFactory.createPlant("Aloe Vera", 9.99, "Healing aloe plant"));
    nurseryInventory->addPlant(treeFactory.createPlant("Bonsai", 49.99, "Miniature bonsai tree"));
    nurseryInventory->addPlant(treeFactory.createPlant("Maple", 29.99, "Beautiful maple tree"));

    // Add some plants to shop (ready for sale)
    Plant* sunflower = flowerFactory.createPlant("Sunflower", 14.99, "Bright sunflowers");
    // Set sunflower to ready state if needed
    shopInventory->addPlant(sunflower);

    Plant* snakePlant = succulentFactory.createPlant("Snake Plant", 18.99, "Air purifying snake plant");
    shopInventory->addPlant(snakePlant);

    Plant* oak = treeFactory.createPlant("Oak", 39.99, "Strong oak tree");
    shopInventory->addPlant(oak);

    cout << "Sample data populated: " << nurseryInventory->size()
         << " plants in nursery, " << shopInventory->size()
         << " plants in shop" << endl;
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

string NurserySystemFacade::getCurrentCustomerInfo() const {
    if (!validateCustomer()) {
        return "No customer set";
    }
    return "Customer: " + currentCustomer->getName() +
           ", Email: " + currentCustomer->getEmail();
}

// Plant Shop Operations - USING REAL DATA
string NurserySystemFacade::browseAllPlants() {
    return apiAdapter->getShopProducts();
}

string NurserySystemFacade::searchPlants(const string& keyword) {
    return inventoryManager->searchPlants(keyword);
}

string NurserySystemFacade::filterPlantsByType(const string& plantType) {
    return inventoryManager->filterPlantsByType(plantType);
}

string NurserySystemFacade::getPlantInfo(const string& plantName) {
    return inventoryManager->getPlantDetails(plantName);
}

string NurserySystemFacade::checkPlantStock(const string& plantName) {
    return inventoryManager->checkStock(plantName);
}

// Shopping Cart Operations
string NurserySystemFacade::addToCart(const string& plantName, int quantity) {
    if (!validateCustomer()) {
        return "{\"error\": \"Please set customer information first\"}";
    }

    // Check if plant is available
    string stockCheck = checkPlantStock(plantName);
    if (stockCheck.find("\"in_stock\": false") != string::npos) {
        return "{\"error\": \"Plant not available: " + plantName + "\"}";
    }

    // Add to cart
    if (currentCart) {
        currentCart->addItem(plantName, quantity);
        return "{\"status\": \"success\", \"message\": \"Added " + to_string(quantity) +
               " " + plantName + "(s) to cart\", \"customer\": \"" +
               currentCustomer->getName() + "\"}";
    }

    return "{\"error\": \"Cart not available\"}";
}

string NurserySystemFacade::removeFromCart(const string& plantName) {
    if (!validateCustomer()) {
        return "{\"error\": \"No customer set\"}";
    }

    if (currentCart) {
        currentCart->removeItem(plantName);
        return "{\"status\": \"success\", \"message\": \"Removed " + plantName + " from cart\"}";
    }

    return "{\"error\": \"Cart not available\"}";
}

string NurserySystemFacade::viewCart() {
    if (!validateCustomer()) {
        return "{\"error\": \"No customer set\"}";
    }

    if (!currentCart) {
        return "{\"error\": \"Cart not available\"}";
    }

    // Simple cart representation
    stringstream cartJson;
    cartJson << "{\"customer\": \"" << currentCustomer->getName() << "\", \"items\": [";

    // This would use actual cart items in a real implementation
    cartJson << "{\"plant\": \"Rose\", \"quantity\": 2, \"price\": 19.99}";
    cartJson << "], \"total\": 39.98}";

    return cartJson.str();
}

string NurserySystemFacade::checkout() {
    if (!validateCustomer()) {
        return "{\"error\": \"Please set customer information first\"}";
    }

    if (!currentCart || currentCart->isEmpty()) {
        return "{\"error\": \"Cart is empty\"}";
    }

    // Process checkout
    string customerName = currentCustomer->getName();
    currentCart->clear();

    return "{\"status\": \"success\", \"message\": \"Checkout completed for " +
           customerName + "\", \"order_id\": " + to_string(rand() % 1000) + "}";
}

// Nursery Management - MODIFIES REAL DATA
string NurserySystemFacade::viewNurseryStatus() {
    return apiAdapter->getNurseryPlants();
}

string NurserySystemFacade::waterPlant(const string& plantName) {
    return inventoryManager->waterPlant(plantName);
}

string NurserySystemFacade::movePlantToShop(const string& plantName) {
    return inventoryManager->movePlantToShop(plantName);
}

string NurserySystemFacade::waterAllPlants() {
    if (nurseryInventory) {
        nurseryInventory->waterAll();
        return "{\"status\": \"success\", \"message\": \"All nursery plants watered\"}";
    }
    return "{\"error\": \"Nursery inventory not available\"}";
}

string NurserySystemFacade::passTimeForAllPlants() {
    if (nurseryInventory) {
        nurseryInventory->passTimeAll();
        return "{\"status\": \"success\", \"message\": \"Time passed for all nursery plants\"}";
    }
    return "{\"error\": \"Nursery inventory not available\"}";
}

// Customer Support
string NurserySystemFacade::askStaffQuestion(const string& question) {
    if (!validateCustomer()) {
        return "{\"error\": \"Please set customer information first\"}";
    }

    return staffCoordinator->handleCustomerQuestion(0, question);
}

string NurserySystemFacade::requestPlantRecommendation(const string& sunlight,
                                                     const string& space,
                                                     const string& experience) {
    return inventoryManager->getRecommendations(sunlight, space, experience);
}

// Staff Operations
string NurserySystemFacade::viewStaffMembers() {
    return apiAdapter->getStaff();
}

string NurserySystemFacade::viewPendingTasks() {
    return apiAdapter->getNotifications();
}

string NurserySystemFacade::completeTask(int taskId) {
    return apiAdapter->finishTask(taskId);
}

// Inventory Reports - REMOVED getInventoryReport()
string NurserySystemFacade::getStockCounts() {
    if (nurseryInventory && shopInventory) {
        stringstream report;
        report << "{\"nursery_count\": " << nurseryInventory->size()
               << ", \"shop_count\": " << shopInventory->size() << "}";
        return report.str();
    }
    return "{\"error\": \"Inventories not available\"}";
}

// Command execution helper
string NurserySystemFacade::executeCustomerCommand(const string& commandType,
                                                 const string& plantName,
                                                 int quantity,
                                                 const string& question,
                                                 const string& sunlight,
                                                 const string& space,
                                                 const string& experience) {

    if (!validateCustomer()) {
        return "{\"error\": \"Please set customer information first\"}";
    }

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
    else {
        return "{\"error\": \"Invalid command or missing parameters\"}";
    }

    if (command) {
        string result = command->execute(currentCustomer);
        delete command;
        return result;
    }

    return "{\"error\": \"Failed to create command\"}";
}

bool NurserySystemFacade::validateCustomer() const {
    return currentCustomer && !currentCustomer->getName().empty();
}

// Stub implementations for methods that need them
string NurserySystemFacade::filterPlantsByCareLevel(const string& careLevel) {
    return inventoryManager->filterPlantsByCareLevel(careLevel);
}

string NurserySystemFacade::fertilizePlant(const string& plantName) {
    return "{\"status\": \"success\", \"message\": \"Plant fertilized: " + plantName + "\"}";
}

string NurserySystemFacade::getPlantHealthReport() {
    return "{\"health_report\": \"All plants are healthy\"}";
}

string NurserySystemFacade::assignStaffTask(int staffId, const string& task) {
    return staffCoordinator->assignTask(staffId, task);
}

string NurserySystemFacade::getNotifications() {
    return apiAdapter->getNotifications();
}

string NurserySystemFacade::markNotificationRead(int notificationId) {
    return "{\"status\": \"read\", \"notification_id\": " + to_string(notificationId) + "}";
}

string NurserySystemFacade::viewAvailableBundles() {
    return inventoryManager->getAvailableBundles();
}

string NurserySystemFacade::addBundleToCart(const string& bundleName) {
    return "{\"status\": \"success\", \"message\": \"Bundle added to cart: " + bundleName + "\"}";
}

string NurserySystemFacade::updateCartQuantity(const string& plantName, int newQuantity) {
    return "{\"status\": \"success\", \"message\": \"Updated quantity for " + plantName + " to " + to_string(newQuantity) + "\"}";
}

string NurserySystemFacade::getCartSummary() {
    return "{\"cart_summary\": \"2 items, Total: $39.98\"}";
}

void NurserySystemFacade::clearCart() {
    if (currentCart) {
        currentCart->clear();
    }
}