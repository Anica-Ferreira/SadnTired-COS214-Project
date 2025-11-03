#ifndef WEB_API_ADAPTER_H
#define WEB_API_ADAPTER_H

#include <string>
#include <vector>
using namespace std;

class InventoryManager;
class Plant;
class NurserySystemFacade;
class ShoppingCart;
class Product;

class WebAPIAdapter {
private:
    NurserySystemFacade* nurseryFacade;
    InventoryManager* inventoryManager;

public:
    WebAPIAdapter(NurserySystemFacade* facade, InventoryManager* invManager);
    ~WebAPIAdapter();

    // Inventory endpoints
    string getShopProducts();
    string getNurseryPlants();
    string getRandomPlants();

    // Plant management endpoints
    string waterPlant(const string& plantName);
    string waterAllPlants();
    string movePlantToShop(const string& plantName);
    string moveReadyPlantsToShop();
    string passTimeForAllPlants();

    // Plant search and browsing
    string searchPlants(const string& keyword);
    string getPlantInfo(const string& plantName);
    string getPlantsByKeyword(const string& keyword);

    // Customer support endpoints
    string checkPlantStock(const string& plantName);
    string getPlantAdvice(const string& plantName, const string& question);
    string getPlantRecommendation(const string& sunlight, const string& space, const string& experience);

    // Shopping cart endpoints
    string addToCart(const string& plantName);
    string addCustomizedToCart(const string& plantName, int potType, int wrapType);
    string viewCart();
    string removeFromCart(int itemIndex);
    string checkout();
    string getCartSummary();

    // Special bundles
    string getSpecialBundles();
    string addBundleToCart(int bundleIndex);

    // Order customization
    string startNewOrder();
    string setOrderPlant(const string& plantName);
    string addOrderPot(int potType);
    string addOrderWrapping(int wrapType);
    string finalizeOrder();

    // Staff operations
    string getStaff();
    string getNotifications();
    string finishTask(int taskId);

    // Customer management
    string createCustomer(const string& name, const string& email);
    string executeCustomerCommand(const string& commandType, const string& plantName,
                                     const string& sunlight = "", const string& space = "",
                                     const string& experience = "", const string& question = "");
    string getCustomerCart(int customerId);

private:
    string inventoryToJSON(const vector<Plant*>& plants);
    string cartToJSON(ShoppingCart* cart);
    string productsToJSON(const vector<Product*>& products);
    string plantToJSON(Plant* plant);
};

#endif