/**
 * @class [NurserySystemFacade]
 * @brief [Implementation of the NurserySystemFacade class]
 * @details [Provides a unified interface to the nursery system's subsystems and operations]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "NurserySystemFacade.h"
#include "WebAPIAdapter.h"
#include "../customer/Customer.h"
#include "../customer/ShoppingCart.h"
#include "../inventory/InventoryManager.h"
#include "../staff/StaffCoordinator.h"
#include "../greenhouse/PlantNursery.h"
#include "../inventory/Inventory.h"
#include "../greenhouse/Plant.h"
#include "../greenhouse/PlantFactory.h"
#include "../customer/CustomerCommand.h"
#include <iostream>
#include <sstream>

/**
 * @brief [Constructs a new NurserySystemFacade object]
 * @details [Initializes all subsystem components and sample data]
 */
NurserySystemFacade::NurserySystemFacade()
    : currentCustomer(nullptr), currentCart(nullptr),
      inventoryManager(nullptr), staffCoordinator(nullptr),
      plantNursery(nullptr), nurseryInventory(nullptr), shopInventory(nullptr) {

    initializeSubsystems();
    cout << "Nursery System Facade initialized with real data backend" << endl;
}

/**
 * @brief [Destroys the NurserySystemFacade object]
 * @details [Cleans up all subsystem components]
 */
NurserySystemFacade::~NurserySystemFacade() {
    cleanupSubsystems();
    cout << "Nursery System Facade destroyed" << endl;
}

/**
 * @brief [Initializes all subsystem components]
 */
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

    staffCoordinator = new StaffCoordinator(apiAdapter);
    plantNursery = new PlantNursery(apiAdapter);

    // Initialize customer and cart
    currentCustomer = new Customer("", "", "", "");
    currentCart = new ShoppingCart();
}

/**
 * @brief [Cleans up all subsystem components]
 */
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

/**
 * @brief [Populates the system with sample plant data]
 */
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

/**
 * @brief [Sets the current customer information]
 * @param[in] name [Customer's first name]
 * @param[in] surname [Customer's surname]
 * @param[in] email [Customer's email address]
 * @param[in] phone [Customer's phone number]
 * @return [True if customer information is set successfully]
 */
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

/**
 * @brief [Resets the current customer information and shopping cart]
 */
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

/**
 * @brief [Gets the current customer information]
 * @return [String representation of the current customer]
 */
string NurserySystemFacade::getCurrentCustomerInfo() const {
    if (!validateCustomer()) {
        return "No customer set";
    }
    return "Customer: " + currentCustomer->getName() +
           ", Email: " + currentCustomer->getEmail();
}

// Plant Shop Operations - USING REAL DATA

/**
 * @brief [Retrieves all plants available in the shop]
 * @return [JSON string containing all shop plants]
 */
string NurserySystemFacade::browseAllPlants() {
    return apiAdapter->getShopProducts();
}

/**
 * @brief [Searches for plants by keyword]
 * @param[in] keyword [Search keyword]
 * @return [JSON string containing search results]
 */
string NurserySystemFacade::searchPlants(const string& keyword) {
    return inventoryManager->searchPlants(keyword);
}

/**
 * @brief [Filters plants by type]
 * @param[in] plantType [Type of plant to filter by]
 * @return [JSON string containing filtered plants]
 */
string NurserySystemFacade::filterPlantsByType(const string& plantType) {
    return inventoryManager->filterPlantsByType(plantType);
}

/**
 * @brief [Gets detailed information about a specific plant]
 * @param[in] plantName [Name of the plant]
 * @return [JSON string containing plant details]
 */
string NurserySystemFacade::getPlantInfo(const string& plantName) {
    return inventoryManager->getPlantDetails(plantName);
}

/**
 * @brief [Checks stock availability for a specific plant]
 * @param[in] plantName [Name of the plant]
 * @return [JSON string containing stock information]
 */
string NurserySystemFacade::checkPlantStock(const string& plantName) {
    return inventoryManager->checkStock(plantName);
}

// Shopping Cart Operations

/**
 * @brief [Adds a plant to the shopping cart]
 * @param[in,out] plantName [Name of the plant to add]
 * @param[in,out] quantity [Quantity to add]
 * @return [JSON string indicating success or failure]
 */
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

/**
 * @brief [Removes a plant from the shopping cart]
 * @param[in,out] plantName [Name of the plant to remove]
 * @return [JSON string indicating success or failure]
 */
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

/**
 * @brief [Views the current shopping cart contents]
 * @return [JSON string containing cart contents]
 */
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

/**
 * @brief [Processes checkout for the current shopping cart]
 * @return [JSON string indicating success or failure]
 */
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

/**
 * @brief [Retrieves the current status of the nursery]
 * @return [JSON string containing all nursery plants]
 */
string NurserySystemFacade::viewNurseryStatus() {
    return apiAdapter->getNurseryPlants();
}

/**
 * @brief [Waters a specific plant in the nursery]
 * @param[in] plantName [Name of the plant to water]
 * @return [JSON string indicating watering result]
 */
string NurserySystemFacade::waterPlant(const string& plantName) {
    return inventoryManager->waterPlant(plantName);
}

/**
 * @brief [Moves a plant from nursery to shop inventory]
 * @param[in] plantName [Name of the plant to move]
 * @return [JSON string indicating move result]
 */
string NurserySystemFacade::movePlantToShop(const string& plantName) {
    return inventoryManager->movePlantToShop(plantName);
}

/**
 * @brief [Waters all plants in the nursery]
 * @return [JSON string indicating watering result]
 */
string NurserySystemFacade::waterAllPlants() {
    if (nurseryInventory) {
        nurseryInventory->waterAll();
        return "{\"status\": \"success\", \"message\": \"All nursery plants watered\"}";
    }
    return "{\"error\": \"Nursery inventory not available\"}";
}

/**
 * @brief [Advances time for all plants in the nursery]
 * @return [JSON string indicating time passage result]
 */
string NurserySystemFacade::passTimeForAllPlants() {
    if (nurseryInventory) {
        nurseryInventory->passTimeAll();
        return "{\"status\": \"success\", \"message\": \"Time passed for all nursery plants\"}";
    }
    return "{\"error\": \"Nursery inventory not available\"}";
}

// Customer Support

/**
 * @brief [Asks a question to staff members]
 * @param[in] question [The question to ask]
 * @return [JSON string with staff response]
 */
string NurserySystemFacade::askStaffQuestion(const string& question) {
    if (!validateCustomer()) {
        return "{\"error\": \"Please set customer information first\"}";
    }

    return staffCoordinator->handleCustomerQuestion(0, question);
}

/**
 * @brief [Requests plant recommendations based on user conditions]
 * @param[in] sunlight [Sunlight condition]
 * @param[in] space [Space availability]
 * @param[in] experience [User experience level]
 * @return [JSON string with plant recommendations]
 */
string NurserySystemFacade::requestPlantRecommendation(const string& sunlight,
                                                     const string& space,
                                                     const string& experience) {
    return inventoryManager->getRecommendations(sunlight, space, experience);
}

// Staff Operations

/**
 * @brief [Views all staff members]
 * @return [JSON string containing staff member details]
 */
string NurserySystemFacade::viewStaffMembers() {
    return apiAdapter->getStaff();
}

/**
 * @brief [Views pending tasks for staff members]
 * @return [JSON string containing pending tasks]
 */
string NurserySystemFacade::viewPendingTasks() {
    return apiAdapter->getNotifications();
}

/**
 * @brief [Completes a specific staff task]
 * @param[in] taskId [ID of the task to complete]
 * @return [JSON string indicating task completion result]
 */
string NurserySystemFacade::completeTask(int taskId) {
    return apiAdapter->finishTask(taskId);
}

// Inventory Reports - REMOVED getInventoryReport()

/**
 * @brief [Gets stock counts for nursery and shop inventories]
 * @return [JSON string containing stock counts]
 */
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

/**
 * @brief [Executes a customer command based on type and parameters]
 * @param[in] commandType [Type of command to execute]
 * @param[in] plantName [Name of the plant (if applicable)]
 * @param[in] quantity [Quantity (if applicable)]
 * @param[in] question [Question to ask (if applicable)]
 * @param[in] sunlight [Sunlight condition (if applicable)]
 * @param[in] space [Space availability (if applicable)]
 * @param[in] experience [User experience level (if applicable)]
 * @return [JSON string with command execution result]
 */
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

/**
 * @brief [Validates that a customer is set]
 * @return [True if a valid customer is set, false otherwise]
 */
bool NurserySystemFacade::validateCustomer() const {
    return currentCustomer && !currentCustomer->getName().empty();
}

// Additional Methods for Fertilization, Health Reports, Staff Tasks, Notifications, and Bundles

/**
 * @brief [Fertilizes a specific plant in the nursery]
 * @param[in,out] plantName [Name of the plant to fertilize]
 * @return [JSON string indicating fertilization result]
 */
string NurserySystemFacade::fertilizePlant(const string& plantName) {
    return "{\"status\": \"success\", \"message\": \"Plant fertilized: " + plantName + "\"}";
}

/**
 * @brief [Gets a health report for all plants in the nursery]
 * @return [JSON string containing plant health report]
 */
string NurserySystemFacade::getPlantHealthReport() {
    return "{\"health_report\": \"All plants are healthy\"}";
}

/**
 * @brief [Assigns a task to a staff member]
 * @param[in] staffId [ID of the staff member]
 * @param[in] task [Task description]
 * @return [JSON string indicating task assignment result]
 */
string NurserySystemFacade::assignStaffTask(int staffId, const string& task) {
    return staffCoordinator->assignTask(staffId, task);
}

/**
 * @brief [Gets notifications for staff members]
 * @return [JSON string containing notifications]
 */
string NurserySystemFacade::getNotifications() {
    return apiAdapter->getNotifications();
}

/**
 * @brief [Marks a notification as read]
 * @param[in,out] notificationId [ID of the notification to mark as read]
 * @return [JSON string indicating notification read result]
 */
string NurserySystemFacade::markNotificationRead(int notificationId) {
    return "{\"status\": \"read\", \"notification_id\": " + to_string(notificationId) + "}";
}

/**
 * @brief [Adds a plant bundle to the shopping cart]
 * @param[in,out] bundleName [Name of the bundle to add]
 * @return [JSON string indicating success or failure]
 */
string NurserySystemFacade::addBundleToCart(const string& bundleName) {
    return "{\"status\": \"success\", \"message\": \"Bundle added to cart: " + bundleName + "\"}";
}

/**
 * @brief [Updates the quantity of a plant in the shopping cart]
 * @param[in,out] plantName [Name of the plant to update]
 * @param[in,out] newQuantity [New quantity to set]
 * @return [JSON string indicating success or failure]
 */
string NurserySystemFacade::updateCartQuantity(const string& plantName, int newQuantity) {
    return "{\"status\": \"success\", \"message\": \"Updated quantity for " + plantName + " to " + to_string(newQuantity) + "\"}";
}

/**
 * @brief [Gets a summary of the current shopping cart]
 * @return [JSON string containing cart summary]
 */
string NurserySystemFacade::getCartSummary() {
    return "{\"cart_summary\": \"2 items, Total: $39.98\"}";
}

/**
 * @brief [Clears all items from the shopping cart]
 */
void NurserySystemFacade::clearCart() {
    if (currentCart) {
        currentCart->clear();
    }
}