/**
 * @class [Api]
 * @brief [The API backend to connect with our frontend]
 * @details [Sets up HTTP routes and handles API requests using Crow framework]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
*/

#include "crow.h"
#include <asio.hpp>
#include "../core/NurserySystemFacade.h"
#include "../core/WebAPIAdapter.h"
#include "../inventory/Inventory.h"
#include "../inventory/InventoryManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * @brief [CORS middleware for handling cross-origin requests]
 */
struct CORSMiddleware {
    struct context {};

    /**
     * @brief [Handles pre-flight CORS headers]
     */
    void before_handle(crow::request& req, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    }

    /**
     * @brief [Adds CORS headers to responses]
     */
    void after_handle(crow::request& req, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
    }
};


/**
 * @brief [Main entry point for the Nursery Management System web server]
 * @return [Exit status code]
 */
int main() {
    cout << "🌱 Starting Plant Nursery Management System..." << endl;

    // Create the main system facade first
    NurserySystemFacade* nurserySystem = new NurserySystemFacade();

    // Get inventory manager and inventories from facade
    InventoryManager* inventoryManager = nullptr; // This will be created internally by facade
    Inventory* nurseryInventory = nurserySystem->getNurseryInventory();
    Inventory* shopInventory = nurserySystem->getShopInventory();

    // FIX: Use the correct WebAPIAdapter constructor with both parameters
    WebAPIAdapter* apiAdapter = new WebAPIAdapter(nurserySystem, inventoryManager);

    crow::App<CORSMiddleware> app;
    srand(time(nullptr));

    // OPTIONS catch-all for preflight
    CROW_CATCHALL_ROUTE(app)([](const crow::request& req, crow::response& res){
        if (req.method == crow::HTTPMethod::Options) {
            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            res.add_header("Access-Control-Allow-Headers", "Content-Type");
            res.code = 200;
            res.end();
            return;
        }
        // Let other routes handle non-OPTIONS requests
        res.code = 404;
        res.end();
    });

    // --- ROOT ENDPOINT ---
    CROW_ROUTE(app, "/")([](){
        string html = R"(
<!DOCTYPE html>
<html>
<head>
    <title>Nursery API</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; }
        .endpoint { background: #f5f5f5; padding: 10px; margin: 5px 0; border-radius: 5px; }
        a { color: #0066cc; text-decoration: none; }
        a:hover { text-decoration: underline; }
    </style>
</head>
<body>
    <h1>🌿 Nursery Management System API</h1>
    <p>API is running successfully! Use the following endpoints:</p>

    <div class="endpoint"><strong>GET</strong> <a href="/health" target="_blank">/health</a> - Health check</div>
    <div class="endpoint"><strong>GET</strong> <a href="/shop" target="_blank">/shop</a> - Browse shop plants</div>
    <div class="endpoint"><strong>GET</strong> <a href="/nursery" target="_blank">/nursery</a> - View nursery plants</div>
    <div class="endpoint"><strong>GET</strong> <a href="/staff" target="_blank">/staff</a> - Get staff info</div>
    <div class="endpoint"><strong>GET</strong> <a href="/notifications" target="_blank">/notifications</a> - Get pending tasks</div>
    <div class="endpoint"><strong>GET</strong> <a href="/bundles" target="_blank">/bundles</a> - Get special bundles</div>
    <div class="endpoint"><strong>GET</strong> <a href="/system/status" target="_blank">/system/status</a> - Get system status</div>
    <div class="endpoint"><strong>GET</strong> <a href="/random-plants" target="_blank">/random-plants</a> - Get random plants</div>

    <h3>Action Endpoints (use curl or Postman):</h3>
    <div class="endpoint"><strong>POST</strong> /nursery/water - Water all plants</div>
    <div class="endpoint"><strong>POST</strong> /nursery/pass-time - Pass time for plants</div>
    <div class="endpoint"><strong>POST</strong> /nursery/move-ready - Move ready plants to shop</div>

    <p>Test the API by clicking the links above or using curl commands.</p>
</body>
</html>
        )";
        crow::response res(html);
        res.add_header("Content-Type", "text/html");
        return res;
    });

    // --- FAVICON ENDPOINT ---
    CROW_ROUTE(app, "/favicon.ico")([](){
        crow::response res;
        res.code = 204; // No content
        return res;
    });

    // --- HEALTH ENDPOINT ---
    CROW_ROUTE(app, "/health")([](){
        crow::response res("{\"status\": \"healthy\", \"service\": \"Nursery API\"}");
        res.add_header("Content-Type", "application/json");
        return res;
    });

    // --- SHOP ENDPOINT ---
    CROW_ROUTE(app, "/shop")([apiAdapter](){
        try {
            string result = apiAdapter->getShopProducts();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // --- NURSERY ENDPOINT ---
    CROW_ROUTE(app, "/nursery")([apiAdapter](){
        try {
            string result = apiAdapter->getNurseryPlants();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // --- RANDOM PLANTS ENDPOINT ---
    CROW_ROUTE(app, "/random-plants")([apiAdapter](){
        try {
            string result = apiAdapter->getRandomPlants();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // --- STAFF ENDPOINT ---
    CROW_ROUTE(app, "/staff")([apiAdapter](){
        try {
            string result = apiAdapter->getStaff();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // --- NOTIFICATIONS ENDPOINT ---
    CROW_ROUTE(app, "/notifications")([apiAdapter](){
        try {
            string result = apiAdapter->getNotifications();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // --- BUNDLES ENDPOINT ---
    CROW_ROUTE(app, "/bundles")([apiAdapter](){
        try {
            string result = apiAdapter->getSpecialBundles();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // --- SYSTEM STATUS ENDPOINT ---
    CROW_ROUTE(app, "/system/status")([nurserySystem](){
        try {
            string result = nurserySystem->getStockCounts();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // --- ACTION ENDPOINTS ---

    // Water all plants
    CROW_ROUTE(app, "/nursery/water")
        .methods("POST"_method)
    ([apiAdapter](){
        try {
            string result = apiAdapter->waterAllPlants();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // Pass time for all plants
    CROW_ROUTE(app, "/nursery/pass-time")
        .methods("POST"_method)
    ([apiAdapter](){
        try {
            string result = apiAdapter->passTimeForAllPlants();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // Move ready plants to shop
    CROW_ROUTE(app, "/nursery/move-ready")
        .methods("POST"_method)
    ([apiAdapter](){
        try {
            string result = apiAdapter->moveReadyPlantsToShop();
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // Water specific plant
    CROW_ROUTE(app, "/nursery/water/<string>")
        .methods("POST"_method)
    ([apiAdapter](const string& plantName){
        try {
            string result = apiAdapter->waterPlant(plantName);
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // Check plant stock
    CROW_ROUTE(app, "/shop/check-stock/<string>")([apiAdapter](const string& plantName){
        try {
            string result = apiAdapter->checkPlantStock(plantName);
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    // Get plant info
    CROW_ROUTE(app, "/plants/<string>")([apiAdapter](const string& plantName){
        try {
            string result = apiAdapter->getPlantInfo(plantName);
            crow::response res(result);
            res.add_header("Content-Type", "application/json");
            return res;
        } catch (const exception& e) {
            return crow::response(500, string("{\"error\": \"") + e.what() + "\"}");
        }
    });

    cout << "🚀 Nursery System Backend running on:" << endl;
    cout << "   http://localhost:8080" << endl;
    cout << "   http://127.0.0.1:8080" << endl;
    cout << endl;
    cout << "Available endpoints:" << endl;
    cout << "  GET  /shop              - Browse shop plants" << endl;
    cout << "  GET  /nursery           - View nursery plants" << endl;
    cout << "  GET  /bundles           - View special bundles" << endl;
    cout << "  POST /nursery/water     - Water all plants" << endl;
    cout << "  POST /nursery/pass-time - Pass time for plants" << endl;

    app.port(8080).multithreaded().run();

    delete apiAdapter;
    delete nurserySystem;

    return 0;
}