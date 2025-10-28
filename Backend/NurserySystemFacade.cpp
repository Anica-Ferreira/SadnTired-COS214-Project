#include "NurserySystemFacade.h"
#include "WebAPIAdapter.h"
#include "PlantFactory.h"
#include "Plant.h"
#include <iostream>
#include <sstream>

using namespace std;

NurserySystemFacade::NurserySystemFacade()
    : nurseryInventory(nullptr), shopInventory(nullptr), currentCustomer(nullptr),
      currentCart(nullptr), inventoryManager(nullptr), staffCoordinator(nullptr),
      plantNursery(nullptr) {

    initializeSubsystems();
    cout << "Nursery System Facade initialized with real classes" << endl;
}

NurserySystemFacade::~NurserySystemFacade() {
    cleanupSubsystems();
    cout << "Nursery System Facade destroyed" << endl;
}

void NurserySystemFacade::initializeSubsystems() {
    // Create real inventory objects
    nurseryInventory = new Inventory();
    shopInventory = new Inventory();

    // Create other subsystems
    inventoryManager = new InventoryManager(nullptr, nurseryInventory, shopInventory);
    staffCoordinator = new StaffCoordinator("Coordinator", nullptr);
    plantNursery = new PlantNursery(nullptr);

    // Initialize customer and cart
    currentCustomer = new Customer("", "", "", "");
    currentCart = new ShoppingCart();

    // Populate with sample data
    populateSampleData();
}

void NurserySystemFacade::cleanupSubsystems() {
    delete currentCart;
    delete currentCustomer;
    delete plantNursery;
    delete staffCoordinator;
    delete inventoryManager;
    delete shopInventory;
    delete nurseryInventory;
}

void NurserySystemFacade::populateSampleData() {
    // Create factories
    SucculentFactory succulentFactory;
    FlowerFactory flowerFactory;
    TreeFactory treeFactory;

    // Add sample plants to nursery
    nurseryInventory->addPlant(flowerFactory.createPlant("Rose", 12.99, "Beautiful red roses"));
    nurseryInventory->addPlant(flowerFactory.createPlant("Tulip", 8.99, "Colorful spring tulips"));
    nurseryInventory->addPlant(flowerFactory.createPlant("Lavender", 10.99, "Fragrant purple lavender"));
    nurseryInventory->addPlant(succulentFactory.createPlant("Cactus", 6.99, "Low maintenance cactus"));
    nurseryInventory->addPlant(succulentFactory.createPlant("Aloe Vera", 9.99, "Healing aloe plant"));
    nurseryInventory->addPlant(treeFactory.createPlant("Bonsai", 49.99, "Miniature bonsai tree"));

    // Add some plants to shop
    shopInventory->addPlant(flowerFactory.createPlant("Sunflower", 14.99, "Bright sunflowers"));
    shopInventory->addPlant(succulentFactory.createPlant("Snake Plant", 18.99, "Air purifying snake plant"));
    shopInventory->addPlant(treeFactory.createPlant("Oak", 39.99, "Strong oak tree"));

    cout << "Sample data populated: " << nurseryInventory->size()
         << " plants in nursery, " << shopInventory->size()
         << " plants in shop" << endl;
}

// Plant Shop Operations - USING REAL CLASSES
string NurserySystemFacade::browseAllPlants() {
    vector<Plant*> shopPlants = shopInventory->getAll();
    return plantsToJSON(shopPlants);
}

string NurserySystemFacade::viewNurseryStatus() {
    vector<Plant*> nurseryPlants = nurseryInventory->getAll();
    return plantsToJSON(nurseryPlants);
}

string NurserySystemFacade::waterPlant(const string& plantName) {
    // Find plant in nursery
    vector<Plant*> plants = nurseryInventory->getAll();
    for (Plant* plant : plants) {
        if (plant->getName() == plantName) {
            plant->water();

            stringstream result;
            result << "{\"action\": \"watered\", \"plant\": \"" << plantName
                   << "\", \"new_state\": \"" << plant->getStateName()
                   << "\", \"water_level\": " << plant->getWaterLevel() << "}";
            return result.str();
        }
    }
    return "{\"error\": \"Plant not found in nursery: " + plantName + "\"}";
}

string NurserySystemFacade::movePlantToShop(const string& plantName) {
    // Find ready plant in nursery
    vector<Plant*> plants = nurseryInventory->getAll();
    Plant* plantToMove = nullptr;

    for (Plant* plant : plants) {
        if (plant->getName() == plantName && plant->getStateName() == "Ready for Sale") {
            plantToMove = plant;
            break;
        }
    }

    if (plantToMove) {
        nurseryInventory->removePlant(plantToMove);
        shopInventory->addPlant(plantToMove);
        return "{\"action\": \"moved\", \"plant\": \"" + plantName + "\", \"message\": \"Plant moved to shop successfully\"}";
    }

    return "{\"error\": \"No ready plant found in nursery: " + plantName + "\"}";
}

string NurserySystemFacade::waterAllPlants() {
    nurseryInventory->waterAll();
    return "{\"action\": \"watered_all\", \"message\": \"All nursery plants watered\"}";
}

string NurserySystemFacade::passTimeForAllPlants() {
    nurseryInventory->passTimeAll();
    return "{\"action\": \"time_passed\", \"message\": \"Time passed for all plants\"}";
}

// Shopping Cart Operations
string NurserySystemFacade::addToCart(const string& plantName, int quantity) {
    if (!validateCustomer()) {
        return "{\"error\": \"Please set customer information first\"}";
    }

    // Check if plant is available
    vector<Plant*> shopPlants = shopInventory->getAll();
    bool found = false;
    for (Plant* plant : shopPlants) {
        if (plant->getName() == plantName) {
            found = true;
            break;
        }
    }

    if (!found) {
        return "{\"error\": \"Plant not available: " + plantName + "\"}";
    }

    currentCart->addItem(plantName, quantity);
    return "{\"action\": \"added_to_cart\", \"plant\": \"" + plantName + "\", \"quantity\": " + to_string(quantity) + "}";
}

string NurserySystemFacade::viewCart() {
    if (!validateCustomer()) {
        return "{\"error\": \"No customer set\"}";
    }

    // Simple cart representation - you would enhance this with actual cart items
    stringstream cartJson;
    cartJson << "{\"customer\": \"" << currentCustomer->getName() << "\", \"items\": [";
    cartJson << "{\"plant\": \"Rose\", \"quantity\": 2, \"price\": 19.99}";
    cartJson << "], \"total\": 39.98}";

    return cartJson.str();
}

string NurserySystemFacade::checkout() {
    if (!validateCustomer()) {
        return "{\"error\": \"Please set customer information first\"}";
    }

    if (currentCart->isEmpty()) {
        return "{\"error\": \"Cart is empty\"}";
    }

    string customerName = currentCustomer->getName();
    currentCart->clear();

    return "{\"status\": \"success\", \"message\": \"Checkout completed for " + customerName + "\"}";
}

// Customer Management
bool NurserySystemFacade::setCustomer(const string& name, const string& surname, const string& email, const string& phone) {
    if (!currentCustomer) {
        currentCustomer = new Customer(name, surname, email, phone);
    } else {
        currentCustomer->setName(name);
        currentCustomer->setSurname(surname);
        currentCustomer->setEmail(email);
        currentCustomer->setPhone(phone);
    }
    return true;
}

void NurserySystemFacade::resetCustomer() {
    if (currentCustomer) {
        currentCustomer->setName("");
        currentCustomer->setSurname("");
        currentCustomer->setEmail("");
        currentCustomer->setPhone("");
    }
    if (currentCart) {
        currentCart->clear();
    }
}

// Helper methods
string NurserySystemFacade::plantToJSON(Plant* plant) {
    if (!plant) return "{}";

    stringstream json;
    json << "{"
         << "\"name\": \"" << plant->getName() << "\", "
         << "\"type\": \"" << plant->getType() << "\", "
         << "\"state\": \"" << plant->getStateName() << "\", "
         << "\"water_level\": " << plant->getWaterLevel() << ", "
         << "\"price\": " << plant->getPrice()
         << "}";

    return json.str();
}

string NurserySystemFacade::plantsToJSON(vector<Plant*> plants) {
    stringstream json;
    json << "[";

    for (size_t i = 0; i < plants.size(); i++) {
        json << plantToJSON(plants[i]);
        if (i < plants.size() - 1) {
            json << ", ";
        }
    }

    json << "]";
    return json.str();
}

bool NurserySystemFacade::validateCustomer() const {
    return currentCustomer && !currentCustomer->getName().empty();
}

// Other methods with real implementations
string NurserySystemFacade::getStockCounts() {
    stringstream result;
    result << "{\"nursery_count\": " << nurseryInventory->size()
           << ", \"shop_count\": " << shopInventory->size() << "}";
    return result.str();
}

string NurserySystemFacade::checkPlantStock(const string& plantName) {
    vector<Plant*> shopPlants = shopInventory->getAll();
    int count = 0;

    for (Plant* plant : shopPlants) {
        if (plant->getName() == plantName) {
            count++;
        }
    }

    stringstream result;
    result << "{\"plant\": \"" << plantName << "\", \"in_stock\": " << (count > 0 ? "true" : "false")
           << ", \"quantity\": " << count << "}";
    return result.str();
}

// Stub implementations for other methods
string NurserySystemFacade::askStaffQuestion(const string& question) {
    return "{\"question\": \"" + question + "\", \"answer\": \"Our staff will get back to you soon\"}";
}

string NurserySystemFacade::requestPlantRecommendation(const string& sunlight, const string& space, const string& experience) {
    return "{\"recommendation\": \"Based on your preferences: " + sunlight + " light, " + space + " space, " + experience + " experience\"}";
}

string NurserySystemFacade::getPlantInfo(const string& plantName) {
    return "{\"plant\": \"" + plantName + "\", \"info\": \"Beautiful plant\"}";
}

// Add other stub implementations as needed...
string NurserySystemFacade::searchPlants(const string& keyword) { return "{\"results\": []}"; }
string NurserySystemFacade::filterPlantsByType(const string& plantType) { return "{\"results\": []}"; }
string NurserySystemFacade::removeFromCart(const string& plantName) { return "{\"status\": \"removed\"}"; }
string NurserySystemFacade::updateCartQuantity(const string& plantName, int newQuantity) { return "{\"status\": \"updated\"}"; }
string NurserySystemFacade::getCartSummary() { return "{\"summary\": \"2 items\"}"; }
void NurserySystemFacade::clearCart() { if (currentCart) currentCart->clear(); }
string NurserySystemFacade::fertilizePlant(const string& plantName) { return "{\"status\": \"fertilized\"}"; }
string NurserySystemFacade::getPlantHealthReport() { return "{\"report\": \"All plants healthy\"}"; }
string NurserySystemFacade::assignStaffTask(int staffId, const string& task) { return "{\"status\": \"assigned\"}"; }
string NurserySystemFacade::markNotificationRead(int notificationId) { return "{\"status\": \"read\"}"; }
string NurserySystemFacade::viewAvailableBundles() { return "{\"bundles\": []}"; }
string NurserySystemFacade::addBundleToCart(const string& bundleName) { return "{\"status\": \"added\"}"; }