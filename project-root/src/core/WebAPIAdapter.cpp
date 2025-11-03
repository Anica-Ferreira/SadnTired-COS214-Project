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

/**
 * @brief [Constructs a new WebAPIAdapter object]
 * @param[in] facade [Pointer to the NurserySystemFacade backend]
 * @param[in] invManager [Pointer to the InventoryManager]
 */
WebAPIAdapter::WebAPIAdapter(NurserySystemFacade* facade, InventoryManager* invManager)
    : nurseryFacade(facade), inventoryManager(invManager) {
    cout << "WebAPIAdapter initialized with NurserySystemFacade backend" << endl;
}

/**
 * @brief [Destroys the WebAPIAdapter object]
 */
WebAPIAdapter::~WebAPIAdapter() {
    cout << "WebAPIAdapter destroyed" << endl;
}

// Inventory endpoints

/**
 * @brief [Gets all products available in the shop]
 * @return [JSON string of shop products]
 */
string WebAPIAdapter::getShopProducts() {
    vector<Plant*> shopPlants = nurseryFacade->getShopInventory()->getAll();
    return inventoryToJSON(shopPlants);
}

/**
 * @brief [Gets all plants in the nursery]
 * @return [JSON string of nursery plants]
 */
string WebAPIAdapter::getNurseryPlants() {
    vector<Plant*> nurseryPlants = nurseryFacade->getNurseryInventory()->getAll();
    return inventoryToJSON(nurseryPlants);
}

/**
 * @brief [Gets a selection of random plants from the shop]
 * @return [JSON string of random shop plants]
 */
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

/**
 * @brief [Waters a specific plant in the nursery]
 * @param[in] plantName [Name of the plant to water]
 * @return [JSON string with watering result]
 */
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

/**
 * @brief [Waters all plants in the nursery]
 * @return [JSON string with watering result]
 */
string WebAPIAdapter::waterAllPlants() {
    nurseryFacade->getNurseryInventory()->waterAll();
    return "{\"status\": \"success\", \"message\": \"All plants watered\"}";
}

/**
 * @brief [Moves a plant from the nursery to the shop if ready for sale]
 * @param[in] plantName [Name of the plant to move]
 * @return [JSON string with move result]
 */
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

/**
 * @brief [Moves all ready plants from nursery to shop]
 * @return [JSON string with move result]
 */
string WebAPIAdapter::moveReadyPlantsToShop() {
    nurseryFacade->getNurseryInventory()->moveReadyPlantsTo(nurseryFacade->getShopInventory());
    return "{\"status\": \"success\", \"message\": \"Ready plants moved to shop\"}";
}

/**
 * @brief [Advances time for all plants in the nursery]
 * @return [JSON string with time passage result]
 */
string WebAPIAdapter::passTimeForAllPlants() {
    nurseryFacade->getNurseryInventory()->passTimeAll();
    return "{\"status\": \"success\", \"message\": \"Time passed for all plants\"}";
}

// Plant search and browsing

/**
 * @brief [Searches for plants by keyword in name or type]
 * @param[in] keyword [Keyword to search for]
 * @return [JSON string of matching plants]
 */
string WebAPIAdapter::searchPlants(const string& keyword) {
    vector<Plant*> results = nurseryFacade->getPlantsByKeyword(keyword);
    return inventoryToJSON(results);
}

/**
 * @brief [Gets detailed information about a specific plant]
 * @param[in] plantName [Name of the plant]
 * @return [JSON string with plant details]
 */
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

/**
 * @brief [Gets plants matching a keyword]
 * @param[in] keyword [Search keyword]
 * @return [JSON string of matching plants]
 */
string WebAPIAdapter::getPlantsByKeyword(const string& keyword) {
    vector<Plant*> results = nurseryFacade->getPlantsByKeyword(keyword);
    return inventoryToJSON(results);
}

// Customer support endpoints

/**
 * @brief [Checks stock availability for a specific plant]
 * @param[in] plantName [Name of the plant]
 * @return [JSON string with stock information]
 */
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

/**
 * @brief [Provides expert advice for a specific plant and question]
 * @param[in] plantName [Name of the plant]
 * @param[in] question [Customer question]
 * @return [JSON string with expert advice]
 */
string WebAPIAdapter::getPlantAdvice(const string& plantName, const string& question) {
    // Simulate plant advice - in real implementation, this would use expert system
    stringstream json;
    json << "{\"advice\": \"For " << plantName << ": " << question
         << " - Based on our expertise, this plant requires regular watering and moderate sunlight. Make sure to check soil moisture regularly.\"}";
    return json.str();
}

/**
 * @brief [Provides plant recommendations based on customer criteria]
 * @param[in] sunlight [Preferred sunlight level]
 * @param[in] space [Available space]
 * @param[in] experience [Gardening experience level]
 * @return [JSON string with plant recommendations]
 */
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

/**
 * @brief [Adds a plant to the shopping cart]
 * @param[in] plantName [Name of the plant to add]
 * @return [JSON string with add to cart result]
 */
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

/**
 * @brief [Adds a customized plant to the shopping cart]
 * @param[in] plantName [Name of the plant to customize]
 * @param[in] potType [Type of decorative pot]
 * @param[in] wrapType [Type of gift wrapping]
 * @return [JSON string with add to cart result]
 */
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

/**
 * @brief [Views the current shopping cart]
 * @return [JSON string of cart contents]
 */
string WebAPIAdapter::viewCart() {
    ShoppingCart* cart = nurseryFacade->getCart();
    if (cart) {
        return cartToJSON(cart);
    }
    return "{\"status\": \"error\", \"message\": \"Cart not available\"}";
}

/**
 * @brief [Removes an item from the shopping cart]
 * @param[in] itemIndex [Index of the item to remove (1-based)]
 * @return [JSON string with removal result]
 */
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

/**
 * @brief [Checks out the shopping cart and completes the purchase]
 * @return [JSON string with checkout result]
 */
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

/**
 * @brief [Gets a summary of the shopping cart]
 * @return [JSON string containing cart summary]
 */
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

/**
 * @brief [Gets the list of special product bundles]
 * @return [JSON string of special bundles]
 */
string WebAPIAdapter::getSpecialBundles() {
    vector<Product*> bundles = nurseryFacade->getSpecialBundles();
    return productsToJSON(bundles);
}

/**
 * @brief [Adds a special product bundle to the shopping cart]
 * @param[in] bundleIndex [Index of the bundle to add (1-based)]
 * @return [JSON string with add to cart result]
 */
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

/**
 * @brief [Starts a new order using the builder pattern]
 * @return [JSON string confirming new order]
 */
string WebAPIAdapter::startNewOrder() {
    nurseryFacade->startNewOrder();
    return "{\"status\": \"success\", \"message\": \"New order started\"}";
}

/**
 * @brief [Sets the plant for the current order]
 * @param[in] plantName [Name of the plant]
 * @return [JSON string confirming plant set]
 */
string WebAPIAdapter::setOrderPlant(const string& plantName) {
    Plant* plant = nurseryFacade->getShopInventory()->get(plantName);
    if (plant) {
        nurseryFacade->setOrderPlant(plant);
        return "{\"status\": \"success\", \"message\": \"Plant set for order\"}";
    }
    return "{\"status\": \"error\", \"message\": \"Plant not found\"}";
}

/**
 * @brief [Adds a decorative pot to the current order]
 * @param[in] potType [Type of decorative pot]
 * @return [JSON string confirming pot addition]
 */
string WebAPIAdapter::addOrderPot(int potType) {
    nurseryFacade->addOrderPot(static_cast<DecorativePot::PotType>(potType));
    return "{\"status\": \"success\", \"message\": \"Pot added to order\"}";
}

/**
 * @brief [Adds gift wrapping to the current order]
 * @param[in] wrapType [Type of gift wrapping]
 * @return [JSON string confirming wrapping addition]
 */
string WebAPIAdapter::addOrderWrapping(int wrapType) {
    nurseryFacade->addOrderWrapping(static_cast<GiftWrapping::WrappingType>(wrapType));
    return "{\"status\": \"success\", \"message\": \"Wrapping added to order\"}";
}

/**
 * @brief [Finalizes the current order and retrieves the product]
 * @return [JSON string with finalized product details]
 */
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

/**
 * @brief [Gets the list of staff members]
 * @return [JSON string of staff members]
 */
string WebAPIAdapter::getStaff() {
    return "{\"staff\": [{\"name\": \"Mr. Green\", \"role\": \"Gardener\"}]}";
}

/**
 * @brief [Gets notifications for staff members]
 * @return [JSON string containing notifications]
 */
string WebAPIAdapter::getNotifications() {
    return "{\"notifications\": []}";
}

/**
 * @brief [Assigns a task to a staff member]
 * @param[in] staffId [ID of the staff member]
 * @param[in] task [Task description]
 * @return [JSON string confirming task assignment]
 */
string WebAPIAdapter::finishTask(int taskId) {
    return "{\"status\": \"completed\", \"task_id\": " + to_string(taskId) + "}";
}

// Customer management

/**
 * @brief [Creates a new customer profile]
 * @param[in] name [Customer name]
 * @param[in] email [Customer email]
 * @return [JSON string confirming customer creation]
 */
string WebAPIAdapter::createCustomer(const string& name, const string& email) {
    return "{\"status\": \"created\", \"customer_name\": \"" + name + "\"}";
}

/**
 * @brief [Executes a customer command based on type and parameters]
 * @param[in] commandType [Type of command to execute]
 * @param[in] plantName [Name of the plant (if applicable)]
 * @param[in] sunlight [Preferred sunlight level (if applicable)]
 * @param[in] space [Available space (if applicable)]
 * @param[in] experience [Gardening experience level (if applicable)]
 * @param[in] question [Customer question (if applicable)]
 * @return [JSON string containing command result]
 */
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

/**
 * @brief [Gets the shopping cart for a specific customer]
 * @param[in] customerId [ID of the customer]
 * @return [JSON string of the customer's cart]
 */
string WebAPIAdapter::getCustomerCart(int customerId) {
    // In a real system, this would get cart for specific customer
    return viewCart();
}

// Private helper methods

/**
 * @brief [Converts a list of Plant objects to a JSON string]
 * @param[in] plants [Vector of Plant pointers]
 * @return [JSON string representing the list of plants]
 */
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

/**
 * @brief [Converts a ShoppingCart object to a JSON string]
 * @param[in] cart [Pointer to the ShoppingCart object]
 * @return [JSON string representing the shopping cart]
 */
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

/**
 * @brief [Converts a list of Product objects to a JSON string]
 * @param[in] products [Vector of Product pointers]
 * @return [JSON string representing the list of products]
 */
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

/**
 * @brief [Converts a Plant object to a JSON string]
 * @param[in] plant [Pointer to the Plant object]
 * @return [JSON string representing the plant]
 */
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