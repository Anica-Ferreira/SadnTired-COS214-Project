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
#include "../greenhouse/PlantState.h"
#include "../staff/StaffSalesman.h"
#include "../staff/StaffGardener.h"
#include "../staff/StaffManager.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * @brief [Constructs a new NurserySystemFacade object]
 * @details [Initializes all subsystem components and sample data]
 */
NurserySystemFacade::NurserySystemFacade()
    : apiAdapter(nullptr), currentCustomer(nullptr), currentCart(nullptr),
      inventoryManager(nullptr), staffCoordinator(nullptr),
      plantNursery(nullptr), nurseryInventory(nullptr), shopInventory(nullptr),
      builder(nullptr), director(nullptr), salesman(nullptr), gardener(nullptr), manager(nullptr) {

    srand((unsigned int)time(nullptr));
    initializeSubsystems();
}

/**
 * @brief [Destroys the NurserySystemFacade object]
 * @details [Cleans up all subsystem components]
 */
NurserySystemFacade::~NurserySystemFacade() {
    cleanupSubsystems();
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

    // Create API adapter with both facade and inventory manager
    apiAdapter = new WebAPIAdapter(this, inventoryManager);

    // FIXED: Pass apiAdapter to StaffCoordinator and PlantNursery
    staffCoordinator = new StaffCoordinator(apiAdapter);
    plantNursery = new PlantNursery(apiAdapter);

    // Initialize staff members
    gardener = new StaffGardener("Mr. Green");
    salesman = new StaffSalesman("Plant Expert");
    manager = new StaffManager("Nursery Manager");

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
    delete director;
    delete gardener;
    delete salesman;
    delete manager;

    // Clear special bundles
    for (Product* bundle : specialBundles) {
        delete bundle;
    }
    specialBundles.clear();
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

        if (plant) {
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
    vector<Plant*> shopPlants = shopInventory->getAll();
    vector<Plant*> results;

    for (Plant* plant : shopPlants) {
        if (plant->getName().find(keyword) != string::npos ||
            plant->getDescription().find(keyword) != string::npos ||
            plant->getType().find(keyword) != string::npos) {
            results.push_back(plant);
        }
    }
    return results;
}

/**
 * @brief [Filters plants by type]
 * @param[in] plantType [Type of plant to filter by]
 * @return [JSON string containing filtered plants]
 */
string NurserySystemFacade::filterPlantsByType(const string& plantType) {
    vector<Plant*> shopPlants = shopInventory->getAll();
    vector<Plant*> filtered;

    for (Plant* plant : shopPlants) {
        if (plant->getType() == plantType) {
            filtered.push_back(plant);
        }
    }

    stringstream result;
    result << "[";
    for (size_t i = 0; i < filtered.size(); i++) {
        result << "{\"name\": \"" << filtered[i]->getName()
               << "\", \"type\": \"" << filtered[i]->getType()
               << "\", \"price\": " << filtered[i]->getPrice() << "}";
        if (i < filtered.size() - 1) result << ", ";
    }
    result << "]";
    return result.str();
}

/**
 * @brief [Gets detailed information about a specific plant]
 * @param[in] plantName [Name of the plant]
 * @return [JSON string containing plant details]
 */
string NurserySystemFacade::getPlantInfo(const string& plantName) {
    Plant* plant = shopInventory->get(plantName);
    if (!plant) {
        plant = nurseryInventory->get(plantName);
    }

    if (plant) {
        stringstream result;
        result << "{\"name\": \"" << plant->getName()
               << "\", \"type\": \"" << plant->getType()
               << "\", \"description\": \"" << plant->getDescription()
               << "\", \"price\": " << plant->getPrice()
               << ", \"state\": \"" << plant->getStateName()
               << "\", \"water_level\": " << plant->getWaterLevel() << "}";
        return result.str();
    }
    return "{\"error\": \"Plant not found\"}";
}

/**
 * @brief [Checks stock availability for a specific plant]
 * @param[in] plantName [Name of the plant]
 * @return [JSON string containing stock information]
 */
string NurserySystemFacade::checkPlantStock(const string& plantName) {
    Plant* plant = shopInventory->get(plantName);
    if (plant) {
        stringstream result;
        result << "{\"status\": \"available\", \"plant\": \"" << plantName
               << "\", \"price\": " << plant->getPrice()
               << ", \"message\": \"" << plantName << " is available in the shop for R"
               << plant->getPrice() << "\"}";
        return result.str();
    }
    return "{\"status\": \"unavailable\", \"plant\": \"" + plantName + "\", \"message\": \"" + plantName + " is not available in the shop.\"}";
}

// Shopping Cart Operations

/**
 * @brief [Adds a product to the shopping cart]
 * @param[in] product [Pointer to the product to add]
 */
void NurserySystemFacade::addToCart(Product* product) {
    if (!currentCart) return;
    currentCart->addProduct(product);
    Plant* basePlant = product->getBasePlant();
    if (basePlant) {
        shopInventory->removePlant(basePlant);
    }
}

/**
 * @brief [Removes a product from the shopping cart]
 * @param[in] itemNumber [Item number in the cart to remove]
 * @return [Confirmation message]
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

    delete removedProduct;
    return "Removed " + basePlant->getName() + " from cart.";
}

/**
 * @brief [Views the contents of the shopping cart]
 * @return [String representation of the cart contents]
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
 * @brief [Processes the checkout of the shopping cart]
 * @return [JSON string containing checkout confirmation]
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
    double total = 0.0;
    for (Product* p : currentCart->getItems()) {
        total += p->getPrice();
    }

    currentCart->clear();

    return "{\"status\": \"success\", \"message\": \"Checkout completed for " +
           customerName + "\", \"total\": " + to_string(total) + ", \"order_id\": " + to_string(rand() % 1000) + "}";
}

// Nursery Management - MODIFIES REAL DATA

/**
 * @brief [Views the status of all plants in the nursery]
 * @return [JSON string containing nursery plant statuses]
 */
string NurserySystemFacade::viewNurseryStatus() {
    return apiAdapter->getNurseryPlants();
}

/**
 * @brief [Waters a specific plant in the nursery]
 * @param[in] plantName [Name of the plant to water]
 * @return [JSON string confirming watering action]
 */
string NurserySystemFacade::waterPlant(const string& plantName) {
    vector<Plant*> nurseryPlants = nurseryInventory->getAll();
    for (Plant* plant : nurseryPlants) {
        if (plant->getName() == plantName) {
            plant->water();
            stringstream result;
            result << "{\"status\": \"success\", \"message\": \"Plant watered\", \"plant\": \""
                   << plantName << "\", \"new_water_level\": " << plant->getWaterLevel() << "}";
            return result.str();
        }
    }
    return "{\"error\": \"Plant not found in nursery\"}";
}

/**
 * @brief [Moves a plant from the nursery to the shop if ready for sale]
 * @param[in] plantName [Name of the plant to move]
 * @return [JSON string confirming the move action]
 */
string NurserySystemFacade::movePlantToShop(const string& plantName) {
    Plant* plant = nurseryInventory->get(plantName);
    if (plant && plant->getStateName() == "Ready for Sale") {
        nurseryInventory->removePlant(plant);
        plant->setState(new ReadyForSaleState());
        shopInventory->addPlant(plant);
        return "{\"status\": \"success\", \"message\": \"Plant moved to shop\", \"plant\": \"" + plantName + "\"}";
    }
    return "{\"status\": \"error\", \"message\": \"Plant not ready or not found\"}";
}

/**
 * @brief [Waters all plants in the nursery]
 * @return [JSON string confirming watering action]
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
 * @return [JSON string confirming time passage]
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
 * @brief [Allows customers to ask questions to staff]
 * @param[in] question [Customer's question]
 * @return [JSON string containing staff response]
 */
string NurserySystemFacade::askStaffQuestion(const string& question) {
    if (!validateCustomer()) {
        return "{\"error\": \"Please set customer information first\"}";
    }

    // Simple response simulation
    return "{\"response\": \"Thank you for your question: " + question + ". Our plant experts recommend regular watering and adequate sunlight for most plants.\"}";
}

/**
 * @brief [Provides plant recommendations based on customer preferences]
 * @param[in] sunlight [Preferred sunlight level]
 * @param[in] space [Available space]
 * @param[in] experience [Gardening experience level]
 * @return [JSON string containing plant recommendations]
 */
string NurserySystemFacade::requestPlantRecommendation(const string& sunlight,
                                                     const string& space,
                                                     const string& experience) {
    string recommendation;

    if (sunlight == "low" && space == "small" && experience == "beginner") {
        recommendation = "Snake Plant, ZZ Plant - Perfect for low light and small spaces";
    } else if (sunlight == "medium" && space == "medium") {
        recommendation = "Monstera, Peace Lily - Great for medium light conditions";
    } else if (sunlight == "high") {
        recommendation = "Succulents, Cacti - Require plenty of sunlight";
    } else {
        recommendation = "Snake Plant, Pothos, Spider Plant - Versatile plants";
    }

    return "{\"recommendations\": \"" + recommendation + "\"}";
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
 * @brief [Views all pending tasks assigned to staff]
 * @return [JSON string containing pending tasks]
 */
string NurserySystemFacade::viewPendingTasks() {
    return apiAdapter->getNotifications();
}

/**
 * @brief [Completes a specific staff task]
 * @param[in] taskId [ID of the task to complete]
 * @return [JSON string confirming task completion]
 */
string NurserySystemFacade::completeTask(int taskId) {
    return apiAdapter->finishTask(taskId);
}

/**
 * @brief [Gets current stock counts for nursery and shop]
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
 * @param[in] quantity [Quantity for stock check (if applicable)]
 * @param[in] question [Customer question (if applicable)]
 * @param[in] sunlight [Preferred sunlight level (if applicable)]
 * @param[in] space [Available space (if applicable)]
 * @param[in] experience [Gardening experience level (if applicable)]
 * @param[in] pot [Type of decorative pot (if applicable)]
 * @param[in] wrap [Type of gift wrapping (if applicable)]
 * @return [JSON string containing command result]
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

    if (commandType == "check_stock" && !plantName.empty()) {
        return checkPlantStock(plantName);
    }
    else if (commandType == "ask_question" && !question.empty()) {
        return askStaffQuestion(question);
    }
    else if (commandType == "get_recommendation") {
        return requestPlantRecommendation(sunlight, space, experience);
    }
    else {
        return "Invalid command or missing parameters";
    }
}

/**
 * @brief [Validates that a customer is set]
 * @return [True if a valid customer is set, false otherwise]
 */
bool NurserySystemFacade::validateCustomer() const {
    return currentCustomer && !currentCustomer->getName().empty();
}

// Additional Methods

/**
 * @brief [Fertilizes a specific plant in the nursery]
 * @param[in] plantName [Name of the plant to fertilize]
 * @return [JSON string confirming fertilization action]
 */
string NurserySystemFacade::fertilizePlant(const string& plantName) {
    return "{\"status\": \"success\", \"message\": \"Plant fertilized: " + plantName + "\"}";
}

/**
 * @brief [Generates a health report for all plants in the nursery]
 * @return [JSON string containing plant health report]
 */
string NurserySystemFacade::getPlantHealthReport() {
    return "{\"health_report\": \"All plants are healthy\"}";
}

/**
 * @brief [Assigns a task to a staff member]
 * @param[in] staffId [ID of the staff member]
 * @param[in] task [Task description]
 * @return [JSON string confirming task assignment]
 */
string NurserySystemFacade::assignStaffTask(int staffId, const string& task) {
    return "{\"status\": \"assigned\", \"staff_id\": " + to_string(staffId) + ", \"task\": \"" + task + "\"}";
}

/**
 * @brief [Retrieves notifications for staff members]
 * @return [JSON string containing notifications]
 */
string NurserySystemFacade::getNotifications() {
    return apiAdapter->getNotifications();
}

/**
 * @brief [Marks a notification as read]
 * @param[in] notificationId [ID of the notification to mark as read]
 * @return [JSON string confirming notification is read]
 */
string NurserySystemFacade::markNotificationRead(int notificationId) {
    return "{\"status\": \"read\", \"notification_id\": " + to_string(notificationId) + "}";
}

/**
 * @brief [Views available special product bundles]
 * @return [JSON string containing special bundles]
 */
string NurserySystemFacade::viewAvailableBundles() {
    stringstream result;
    result << "[";
    for (size_t i = 0; i < specialBundles.size(); i++) {
        result << "{\"title\": \"" << specialBundles[i]->getTitle()
               << "\", \"description\": \"" << specialBundles[i]->getDescription()
               << "\", \"price\": " << specialBundles[i]->getPrice() << "}";
        if (i < specialBundles.size() - 1) result << ", ";
    }
    result << "]";
    return result.str();
}

/**
 * @brief [Adds a special bundle to the shopping cart]
 * @param[in] bundleName [Name of the bundle to add]
 * @return [JSON string confirming addition to cart]
 */
string NurserySystemFacade::addBundleToCart(const string& bundleName) {
    for (Product* bundle : specialBundles) {
        if (bundle->getTitle() == bundleName) {
            currentCart->addProduct(bundle);
            return "{\"status\": \"success\", \"message\": \"Bundle added to cart: " + bundleName + "\"}";
        }
    }
    return "{\"error\": \"Bundle not found\"}";
}

/**
 * @brief [Updates the quantity of a specific item in the cart]
 * @param[in] plantName [Name of the plant in the cart]
 * @param[in] newQuantity [New quantity to set]
 * @return [JSON string confirming quantity update]
 */
string NurserySystemFacade::updateCartQuantity(const string& plantName, int newQuantity) {
    return "{\"status\": \"success\", \"message\": \"Updated quantity for " + plantName + " to " + to_string(newQuantity) + "\"}";
}

/**
 * @brief [Gets a summary of the shopping cart]
 * @return [JSON string containing cart summary]
 */
string NurserySystemFacade::getCartSummary() {
    if (!currentCart) return "{\"item_count\": 0, \"total_price\": 0}";

    double total = 0.0;
    for (Product* p : currentCart->getItems()) {
        total += p->getPrice();
    }

    stringstream result;
    result << "{\"item_count\": " << currentCart->getItems().size()
           << ", \"total_price\": " << total << "}";
    return result.str();
}

/**
 * @brief [Clears all items from the shopping cart]
 */
void NurserySystemFacade::clearCart() {
    if (currentCart) {
        currentCart->clear();
    }
}

/**
 * @brief [Gets the current shopping cart]
 * @return [Pointer to the current ShoppingCart object]
 */
ShoppingCart* NurserySystemFacade::getCart() const {
    return currentCart;
}

/**
 * @brief [Gets the nursery inventory]
 * @return [Pointer to the nursery Inventory object]
 */
Inventory* NurserySystemFacade::getNurseryInventory() { 
    return nurseryInventory; 
}

/**
 * @brief [Gets the shop inventory]
 * @return [Pointer to the shop Inventory object]
 */
Inventory* NurserySystemFacade::getShopInventory() { 
    return shopInventory; 
}

/**
 * @brief [Starts a new order using the builder pattern]
 */
void NurserySystemFacade::startNewOrder() {
    delete builder;
    builder = new ConcreteOrderBuilder();
}

/**
 * @brief [Sets the plant for the current order]
 * @param[in] plant [Pointer to the Plant object]
 */
void NurserySystemFacade::setOrderPlant(Plant* plant) {
    builder->setPlant(plant);
}

/**
 * @brief [Adds a decorative pot to the current order]
 * @param[in] type [Type of decorative pot]
 */
void NurserySystemFacade::addOrderPot(DecorativePot::PotType type) {
    builder->addPot(type);
}

/**
 * @brief [Adds gift wrapping to the current order]
 * @param[in] type [Type of gift wrapping]
 */
void NurserySystemFacade::addOrderWrapping(GiftWrapping::WrappingType type) {
    builder->addWrapping(type);
}

/**
 * @brief [Finalizes the current order and retrieves the product]
 * @return [Pointer to the finalized Product object]
 */
Product* NurserySystemFacade::finalizeOrder() {
    return builder->getProduct();
}

/**
 * @brief [Creates special product bundles using the builder and director]
 */
void NurserySystemFacade::createSpecialBundles() {
    specialBundles.clear();

    ProductBundle* valentines = director->makeValentinesBundle(*builder);
    ProductBundle* succulent = director->makeSucculentBundle(*builder);
    ProductBundle* spring = director->makeSpringBundle(*builder);

    specialBundles.push_back(valentines);
    specialBundles.push_back(succulent);
    specialBundles.push_back(spring);
}