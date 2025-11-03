#include "WebAPIAdapter.h"
#include "../core/NurserySystemFacade.h"
#include "../inventory/InventoryManager.h"
#include "../inventory/Inventory.h"
#include "../customer/ShoppingCart.h"
#include "../products/DecorativePot.h"
#include "../products/GiftWrapping.h"
#include "../customer/CustomerCommand.h"
#include "../products/ProductBundle.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

WebAPIAdapter::WebAPIAdapter(NurserySystemFacade* facade, InventoryManager* invManager)
    : nurseryFacade(facade), inventoryManager(invManager) {
    cout << "WebAPIAdapter initialized with NurserySystemFacade backend" << endl;
}

WebAPIAdapter::~WebAPIAdapter() {
    cout << "WebAPIAdapter destroyed" << endl;
}

// Inventory endpoints
string WebAPIAdapter::getShopProducts() {
    vector<Plant*> shopPlants = nurseryFacade->getShopInventory()->getAll();
    return inventoryToJSON(shopPlants);
}

string WebAPIAdapter::getNurseryPlants() {
    vector<Plant*> nurseryPlants = nurseryFacade->getNurseryInventory()->getAll();
    return inventoryToJSON(nurseryPlants);
}

string WebAPIAdapter::getRandomPlants() {
    // Return a subset of shop plants as "random"
    vector<Plant*> shopPlants = nurseryFacade->getShopInventory()->getAll();
    if (shopPlants.size() > 5) {
        vector<Plant*> randomPlants(shopPlants.begin(), shopPlants.begin() + 5);
        return inventoryToJSON(randomPlants);
    }
    return inventoryToJSON(shopPlants);
}

// Plant management endpoints
string WebAPIAdapter::waterPlant(const string& plantName) {
    vector<Plant*> nurseryPlants = nurseryFacade->getNurseryInventory()->getAll();
    for (Plant* plant : nurseryPlants) {
        if (plant->getName() == plantName) {
            plant->water();
            stringstream json;
            json << "{\"status\": \"success\", \"message\": \"Plant watered\", \"plant\": \""
                 << plantName << "\", \"new_water_level\": " << plant->getWaterLevel() << "}";
            return json.str();
        }
    }
    return "{\"status\": \"error\", \"message\": \"Plant not found in nursery\"}";
}

string WebAPIAdapter::waterAllPlants() {
    nurseryFacade->getNurseryInventory()->waterAll();
    return "{\"status\": \"success\", \"message\": \"All plants watered\"}";
}

string WebAPIAdapter::movePlantToShop(const string& plantName) {
    // This would need to be implemented in NurserySystemFacade
    // For now, return success if plant exists in nursery
    vector<Plant*> nurseryPlants = nurseryFacade->getNurseryInventory()->getAll();
    for (Plant* plant : nurseryPlants) {
        if (plant->getName() == plantName && plant->getStateName() == "Ready for Sale") {
            // Simulate moving to shop
            nurseryFacade->getShopInventory()->addPlant(plant);
            return "{\"status\": \"success\", \"message\": \"Plant moved to shop\", \"plant\": \"" + plantName + "\"}";
        }
    }
    return "{\"status\": \"error\", \"message\": \"Plant not ready or not found\"}";
}

string WebAPIAdapter::moveReadyPlantsToShop() {
    nurseryFacade->getNurseryInventory()->moveReadyPlantsTo(nurseryFacade->getShopInventory());
    return "{\"status\": \"success\", \"message\": \"Ready plants moved to shop\"}";
}

string WebAPIAdapter::passTimeForAllPlants() {
    nurseryFacade->getNurseryInventory()->passTimeAll();
    return "{\"status\": \"success\", \"message\": \"Time passed for all plants\"}";
}

// Plant search and browsing
string WebAPIAdapter::searchPlants(const string& keyword) {
    vector<Plant*> results = nurseryFacade->getPlantsByKeyword(keyword);
    return inventoryToJSON(results);
}

string WebAPIAdapter::getPlantInfo(const string& plantName) {
    Plant* plant = nurseryFacade->getShopInventory()->get(plantName);
    if (!plant) {
        plant = nurseryFacade->getNurseryInventory()->get(plantName);
    }

    if (plant) {
        return plantToJSON(plant);
    }
    return "{\"status\": \"error\", \"message\": \"Plant not found\"}";
}

string WebAPIAdapter::getPlantsByKeyword(const string& keyword) {
    vector<Plant*> results = nurseryFacade->getPlantsByKeyword(keyword);
    return inventoryToJSON(results);
}

// Customer support endpoints
string WebAPIAdapter::checkPlantStock(const string& plantName) {
    Plant* plant = nurseryFacade->getShopInventory()->get(plantName);
    if (plant) {
        stringstream json;
        json << "{\"status\": \"available\", \"plant\": \"" << plantName
             << "\", \"price\": " << plant->getPrice()
             << ", \"message\": \"" << plantName << " is available in the shop for R"
             << plant->getPrice() << "\"}";
        return json.str();
    }
    return "{\"status\": \"unavailable\", \"plant\": \"" + plantName + "\", \"message\": \"" + plantName + " is not available in the shop.\"}";
}

string WebAPIAdapter::getPlantAdvice(const string& plantName, const string& question) {
    // Simulate plant advice - in real implementation, this would use expert system
    stringstream json;
    json << "{\"advice\": \"For " << plantName << ": " << question
         << " - Based on our expertise, this plant requires regular watering and moderate sunlight. Make sure to check soil moisture regularly.\"}";
    return json.str();
}

string WebAPIAdapter::getPlantRecommendation(const string& sunlight, const string& space, const string& experience) {
    // Simulate recommendation logic based on demo
    string recommendation;

    if (sunlight == "low" && space == "small" && experience == "beginner") {
        recommendation = "Snake Plant, ZZ Plant - Perfect for low light and small spaces, very low maintenance";
    } else if (sunlight == "medium" && space == "medium" && experience == "intermediate") {
        recommendation = "Monstera, Peace Lily - Great for medium light conditions, moderate care required";
    } else if (sunlight == "high" && experience == "expert") {
        recommendation = "Succulents, Cacti, Orchids - Require plenty of sunlight and expert care";
    } else {
        recommendation = "Snake Plant, Pothos, Spider Plant - Versatile plants suitable for various conditions";
    }

    stringstream json;
    json << "{\"recommendations\": \"" << recommendation << "\", \"criteria\": {"
         << "\"sunlight\": \"" << sunlight << "\", "
         << "\"space\": \"" << space << "\", "
         << "\"experience\": \"" << experience << "\"}}";
    return json.str();
}

// Shopping cart endpoints
string WebAPIAdapter::addToCart(const string& plantName) {
    Plant* plant = nurseryFacade->getShopInventory()->get(plantName);
    if (plant) {
        // Create a basic product (no customization)
        nurseryFacade->startNewOrder();
        nurseryFacade->setOrderPlant(plant);
        Product* product = nurseryFacade->finalizeOrder();
        nurseryFacade->addToCart(product);

        stringstream json;
        json << "{\"status\": \"success\", \"message\": \"Added to cart\", \"plant\": \""
             << plantName << "\", \"price\": " << product->getPrice() << "}";
        return json.str();
    }
    return "{\"status\": \"error\", \"message\": \"Plant not available\"}";
}

string WebAPIAdapter::addCustomizedToCart(const string& plantName, int potType, int wrapType) {
    Plant* plant = nurseryFacade->getShopInventory()->get(plantName);
    if (plant) {
        nurseryFacade->startNewOrder();
        nurseryFacade->setOrderPlant(plant);
        nurseryFacade->addOrderPot(static_cast<DecorativePot::PotType>(potType));
        nurseryFacade->addOrderWrapping(static_cast<GiftWrapping::WrappingType>(wrapType));
        Product* product = nurseryFacade->finalizeOrder();
        nurseryFacade->addToCart(product);

        stringstream json;
        json << "{\"status\": \"success\", \"message\": \"Customized plant added to cart\", \"plant\": \""
             << plantName << "\", \"total_price\": " << product->getPrice() << "}";
        return json.str();
    }
    return "{\"status\": \"error\", \"message\": \"Plant not available\"}";
}

string WebAPIAdapter::viewCart() {
    ShoppingCart* cart = nurseryFacade->getCart();
    if (cart) {
        return cartToJSON(cart);
    }
    return "{\"status\": \"error\", \"message\": \"Cart not available\"}";
}

string WebAPIAdapter::removeFromCart(int itemIndex) {
    ShoppingCart* cart = nurseryFacade->getCart();
    if (cart && itemIndex > 0 && itemIndex <= cart->getItems().size()) {
        Product* removed = cart->removeProduct(itemIndex - 1);
        if (removed) {
            Plant* basePlant = removed->getBasePlant();
            if (basePlant) {
                nurseryFacade->getShopInventory()->addPlant(basePlant);
            }
            delete removed;
            return "{\"status\": \"success\", \"message\": \"Item removed from cart\"}";
        }
    }
    return "{\"status\": \"error\", \"message\": \"Failed to remove item\"}";
}

string WebAPIAdapter::checkout() {
    ShoppingCart* cart = nurseryFacade->getCart();
    if (cart && !cart->getItems().empty()) {
        double total = 0.0;
        for (Product* p : cart->getItems()) {
            total += p->getPrice();
        }
        cart->clear();

        stringstream json;
        json << "{\"status\": \"success\", \"message\": \"Purchase completed\", \"total\": "
             << total << ", \"items_purchased\": " << cart->getItems().size() << "}";
        return json.str();
    }
    return "{\"status\": \"error\", \"message\": \"Cart is empty\"}";
}

string WebAPIAdapter::getCartSummary() {
    ShoppingCart* cart = nurseryFacade->getCart();
    if (cart) {
        double total = 0.0;
        for (Product* p : cart->getItems()) {
            total += p->getPrice();
        }

        stringstream json;
        json << "{\"item_count\": " << cart->getItems().size()
             << ", \"total_price\": " << total << "}";
        return json.str();
    }
    return "{\"item_count\": 0, \"total_price\": 0}";
}

// Special bundles
string WebAPIAdapter::getSpecialBundles() {
    vector<Product*> bundles = nurseryFacade->getSpecialBundles();
    return productsToJSON(bundles);
}

string WebAPIAdapter::addBundleToCart(int bundleIndex) {
    vector<Product*> bundles = nurseryFacade->getSpecialBundles();
    if (bundleIndex > 0 && bundleIndex <= bundles.size()) {
        Product* selected = bundles[bundleIndex - 1];
        nurseryFacade->getCart()->addProduct(selected);

        stringstream json;
        json << "{\"status\": \"success\", \"message\": \"Bundle added to cart\", \"bundle\": \""
             << selected->getTitle() << "\", \"price\": " << selected->getPrice() << "}";
        return json.str();
    }
    return "{\"status\": \"error\", \"message\": \"Invalid bundle selection\"}";
}

// Order customization
string WebAPIAdapter::startNewOrder() {
    nurseryFacade->startNewOrder();
    return "{\"status\": \"success\", \"message\": \"New order started\"}";
}

string WebAPIAdapter::setOrderPlant(const string& plantName) {
    Plant* plant = nurseryFacade->getShopInventory()->get(plantName);
    if (plant) {
        nurseryFacade->setOrderPlant(plant);
        return "{\"status\": \"success\", \"message\": \"Plant set for order\"}";
    }
    return "{\"status\": \"error\", \"message\": \"Plant not found\"}";
}

string WebAPIAdapter::addOrderPot(int potType) {
    nurseryFacade->addOrderPot(static_cast<DecorativePot::PotType>(potType));
    return "{\"status\": \"success\", \"message\": \"Pot added to order\"}";
}

string WebAPIAdapter::addOrderWrapping(int wrapType) {
    nurseryFacade->addOrderWrapping(static_cast<GiftWrapping::WrappingType>(wrapType));
    return "{\"status\": \"success\", \"message\": \"Wrapping added to order\"}";
}

string WebAPIAdapter::finalizeOrder() {
    Product* product = nurseryFacade->finalizeOrder();
    if (product) {
        stringstream json;
        json << "{\"status\": \"success\", \"product\": {"
             << "\"name\": \"" << product->getName() << "\", "
             << "\"description\": \"" << product->getDescription() << "\", "
             << "\"price\": " << product->getPrice() << "}}";
        return json.str();
    }
    return "{\"status\": \"error\", \"message\": \"Failed to create product\"}";
}

// Staff operations (stubs - would need Staff system implementation)
string WebAPIAdapter::getStaff() {
    return "{\"staff\": [{\"name\": \"Mr. Green\", \"role\": \"Gardener\"}]}";
}

string WebAPIAdapter::getNotifications() {
    return "{\"notifications\": []}";
}

string WebAPIAdapter::finishTask(int taskId) {
    return "{\"status\": \"completed\", \"task_id\": " + to_string(taskId) + "}";
}

// Customer management
string WebAPIAdapter::createCustomer(const string& name, const string& email) {
    return "{\"status\": \"created\", \"customer_name\": \"" + name + "\"}";
}

string WebAPIAdapter::executeCustomerCommand(const string& commandType, const string& plantName,
                                           const string& sunlight, const string& space,
                                           const string& experience, const string& question) {
    // This would interface with the CustomerCommand system
    if (commandType == "check_stock") {
        return checkPlantStock(plantName);
    } else if (commandType == "ask_question") {
        return getPlantAdvice(plantName, question);
    } else if (commandType == "get_recommendation") {
        return getPlantRecommendation(sunlight, space, experience);
    }

    return "{\"status\": \"error\", \"message\": \"Unknown command type\"}";
}

string WebAPIAdapter::getCustomerCart(int customerId) {
    // In a real system, this would get cart for specific customer
    return viewCart();
}

// Private helper methods
string WebAPIAdapter::inventoryToJSON(const vector<Plant*>& plants) {
    stringstream json;
    json << "[";

    for (size_t i = 0; i < plants.size(); i++) {
        Plant* plant = plants[i];
        json << plantToJSON(plant);

        if (i < plants.size() - 1) {
            json << ", ";
        }
    }

    json << "]";
    return json.str();
}

string WebAPIAdapter::cartToJSON(ShoppingCart* cart) {
    stringstream json;
    json << "{\"items\": [";

    const vector<Product*>& items = cart->getItems();
    for (size_t i = 0; i < items.size(); i++) {
        Product* product = items[i];
        json << "{"
             << "\"name\": \"" << product->getName() << "\", "
             << "\"description\": \"" << product->getDescription() << "\", "
             << "\"price\": " << product->getPrice() << "}";

        if (i < items.size() - 1) {
            json << ", ";
        }
    }

    json << "], \"item_count\": " << items.size() << "}";
    return json.str();
}

string WebAPIAdapter::productsToJSON(const vector<Product*>& products) {
    stringstream json;
    json << "[";

    for (size_t i = 0; i < products.size(); i++) {
        Product* product = products[i];
        json << "{"
             << "\"title\": \"" << product->getTitle() << "\", "
             << "\"description\": \"" << product->getDescription() << "\", "
             << "\"price\": " << product->getPrice() << "}";

        if (i < products.size() - 1) {
            json << ", ";
        }
    }

    json << "]";
    return json.str();
}

string WebAPIAdapter::plantToJSON(Plant* plant) {
    stringstream json;
    json << "{"
         << "\"name\": \"" << plant->getName() << "\", "
         << "\"type\": \"" << plant->getType() << "\", "
         << "\"state\": \"" << plant->getStateName() << "\", "
         << "\"water_level\": " << plant->getWaterLevel() << ", "
         << "\"price\": " << plant->getPrice() << "}";
    return json.str();
}