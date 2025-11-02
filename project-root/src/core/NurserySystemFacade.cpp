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
#include "../orders/ConcreteOrderBuilder.h"
#include "../products/Product.h"
#include "../customer/ShoppingCart.h"
#include "../orders/OrderDirector.h"


#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

/**
 * @brief [Constructs a new NurserySystemFacade object]
 * @details [Initializes all subsystem components and sample data]
 */
NurserySystemFacade::NurserySystemFacade()
    : currentCustomer(nullptr), currentCart(nullptr),
      inventoryManager(nullptr), staffCoordinator(nullptr),
      plantNursery(nullptr), nurseryInventory(nullptr), shopInventory(nullptr) {

    srand((unsigned int)time(nullptr));

    initializeSubsystems();
    //cout << "Nursery System Facade initialized with real data backend" << endl;
}

/**
 * @brief [Destroys the NurserySystemFacade object]
 * @details [Cleans up all subsystem components]
 */
NurserySystemFacade::~NurserySystemFacade() {
    cleanupSubsystems();
    //cout << "Nursery System Facade destroyed" << endl;
}

/**
 * @brief [Initializes all subsystem components]
 */
void NurserySystemFacade::initializeSubsystems() {
    // Create real inventory objects
    nurseryInventory = new Inventory();
    shopInventory = new Inventory();

    builder = new ConcreteOrderBuilder();
    director = new OrderDirector();

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
    delete builder;
}

/**
 * @brief [Populates the system with random sample plant data]
 */
void NurserySystemFacade::populateSampleData() {
    // Create factories
    SucculentFactory succulentFactory;
    FlowerFactory flowerFactory;
    TreeFactory treeFactory;

    struct PlantType {
        string name;
        string description;
        string category;
    };

    vector<PlantType> plantOptions = {
        {"Rose", "Beautiful red roses", "Flower"},
        {"Tulip", "Colorful spring tulips", "Flower"},
        {"Lavender", "Fragrant purple lavender", "Flower"},
        {"Cactus", "Low maintenance cactus", "Succulent"},
        {"Aloe Vera", "Healing aloe plant", "Succulent"},
        {"Bonsai", "Miniature bonsai tree", "Tree"},
        {"Maple Tree", "Beautiful maple tree", "Tree"},
        {"Sunflower", "Bright sunflowers", "Flower"},
        {"Snake Plant", "Air purifying snake plant", "Succulent"},
        {"Oak", "Strong oak tree", "Tree"}
    };

    int totalPlants = 10 + rand() % 11;

    for (int i = 0; i < totalPlants; ++i) {
    int idx = rand() % plantOptions.size();
    PlantType p = plantOptions[idx];

    Plant* plant = nullptr;
    if (p.category == "Flower") {
        plant = flowerFactory.createPlant(p.name, 5 + rand() % 15, p.description);
    } else if (p.category == "Succulent") {
        plant = succulentFactory.createPlant(p.name, 5 + rand() % 15, p.description);
    } else if (p.category == "Tree") {
        plant = treeFactory.createPlant(p.name, 20 + rand() % 40, p.description);
    }

    if (rand() % 2 == 0) {
        int randState = rand() % 3;
        switch (randState) {
            case 0:
                plant->setWaterLevel(0.0);
                plant->setState(new DryState());
                break;
            case 1:
                plant->setWaterLevel(5.0 + rand() % 6);
                plant->setState(new WateredState());
                break;
            case 2:
                plant->setWaterLevel(1.0 + rand() % 3);
                plant->setState(new PlantedState());
                break;
        }
        nurseryInventory->addPlant(plant);
        } else {
            plant->setState(new ReadyForSaleState());
            shopInventory->addPlant(plant);
        }
    }


    createSpecialBundles();

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
vector<Plant*> NurserySystemFacade::getPlantsByKeyword(const string& keyword) {
    return inventoryManager->searchPlantsByKeyword(keyword);
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

void NurserySystemFacade::addToCart(Product* product) {
    //build the product and convert from plant to an actual product
    if (!currentCart) return;
    currentCart->addProduct(product);
    Plant* basePlant = product->getBasePlant();
    if (basePlant) {
        shopInventory->removePlant(basePlant);
    }
}

/**
 * @brief [Removes a plant from the shopping cart]
 * @param[in,out] plantName [Name of the plant to remove]
 * @return [JSON string indicating success or failure]
 */

 
string NurserySystemFacade::removeFromCart(int itemNumber) {
    if (!validateCustomer()) {
        return "No customer set.";
    }

    if (!currentCart) {
        return "Cart not available.";
    }

    // Remove the product from the cart
    Product* removedProduct = currentCart->removeProduct(itemNumber);
    if (!removedProduct) {
        return "Invalid item number. No product removed.";
    }

    // Return the plant to the shop if it exists
    Plant* basePlant = removedProduct->getBasePlant();
    if (basePlant) {
        getShopInventory()->addPlant(basePlant);
    }

    delete removedProduct; // Delete the product wrapper, not the plant
    return "Removed " + basePlant->getName() + " from cart.";
}

/**
 * @brief [Views the current shopping cart contents]
 * @return [JSON string containing cart contents]
 */

string NurserySystemFacade::viewCart() {
    if (!validateCustomer()) {
        cout << "\033[1;31mError: No customer set.\033[0m\n";
        return "";
    }

    if (!currentCart) {
        cout << "\033[1;31mError: No shopping cart available.\033[0m\n";
        return "";
    }

    currentCart->viewCart();
    return "";
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
    //currentCart->clear();

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

string NurserySystemFacade::executeCustomerCommand(
    const string& commandType,
    const string& plantName,
    int quantity,
    const string& question,
    const string& sunlight,
    const string& space,
    const string& experience,
    DecorativePot::PotType pot,
    GiftWrapping::WrappingType wrap
) {
    if (!validateCustomer()) {
        return "Please set customer information first";
    }

    CustomerCommand* command = nullptr;

    if (commandType == "purchase" && !plantName.empty()) {
        Plant* plant = shopInventory->get(plantName);
        if (!plant) return "Plant not found in shop";

        command = new PurchasePlantCommand(plant, pot, wrap, quantity, this);
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
        return "Invalid command or missing parameters";
    }

    string result = command ? command->execute(currentCustomer) : "Failed to create command";
    delete command;
    return result;
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
        //currentCart->clear();
    }
}

ShoppingCart* NurserySystemFacade::getCart() const {
    return currentCart;
}

Inventory* NurserySystemFacade::getNurseryInventory() { 
    return nurseryInventory; 
}

Inventory* NurserySystemFacade::getShopInventory() { 
    return shopInventory; 
}

void NurserySystemFacade::startNewOrder() {
    delete builder;
    builder = new ConcreteOrderBuilder();
}

void NurserySystemFacade::setOrderPlant(Plant* plant) {
    builder->setPlant(plant);
}

void NurserySystemFacade::addOrderPot(DecorativePot::PotType type) {
    builder->addPot(type);
}

void NurserySystemFacade::addOrderWrapping(GiftWrapping::WrappingType type) {
    builder->addWrapping(type);
}

Product* NurserySystemFacade::finalizeOrder() {
    return builder->getProduct();
}

void NurserySystemFacade::createSpecialBundles() {
    specialBundles.clear();

    ProductBundle* valentines = director->makeValentinesBundle(*builder);
    ProductBundle* succulent = director->makeSucculentBundle(*builder);
    ProductBundle* spring = director->makeSpringBundle(*builder);

    specialBundles.push_back(valentines);
    specialBundles.push_back(succulent);
    specialBundles.push_back(spring);
}