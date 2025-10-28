#include "crow.h"
#include "NurserySystemFacade.h"
#include "WebAPIAdapter.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// CORS Middleware
struct CORSMiddleware {
    struct context {};
    void before_handle(crow::request&, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    }
    void after_handle(crow::request&, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
    }
};

int main() {
    cout << "🌱 Starting Plant Nursery Management System..." << endl;

    // Initialize the complete backend system
    NurserySystemFacade* nurserySystem = new NurserySystemFacade();
    WebAPIAdapter* apiAdapter = new WebAPIAdapter(nurserySystem);

    crow::App<CORSMiddleware> app;
    srand(time(nullptr));

    // OPTIONS catch-all for preflight
    CROW_ROUTE(app, "/<path>")
    .methods(crow::HTTPMethod::Options)
    ([](const crow::request&, crow::response& res, std::string){
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.code = 200;
        res.end();
    });

    // SHOP ENDPOINTS
    CROW_ROUTE(app, "/shop").methods(crow::HTTPMethod::GET)([apiAdapter](){
        try {
            string result = apiAdapter->getShopProducts();
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    CROW_ROUTE(app, "/randomShop").methods(crow::HTTPMethod::GET)([apiAdapter](){
        try {
            string result = apiAdapter->getRandomPlants();
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    // NURSERY ENDPOINTS
    CROW_ROUTE(app, "/nursery").methods(crow::HTTPMethod::GET)([apiAdapter](){
        try {
            string result = apiAdapter->getNurseryPlants();
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    CROW_ROUTE(app, "/waterPlant/<string>").methods(crow::HTTPMethod::POST)([apiAdapter](const string& plantName){
        try {
            string result = apiAdapter->waterPlant(plantName);
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    CROW_ROUTE(app, "/movePlantOut/<string>").methods(crow::HTTPMethod::POST)([apiAdapter](const string& plantName){
        try {
            string result = apiAdapter->movePlantToShop(plantName);
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    // STAFF ENDPOINTS
    CROW_ROUTE(app, "/staff").methods(crow::HTTPMethod::GET)([apiAdapter](){
        try {
            string result = apiAdapter->getStaff();
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    // NOTIFICATIONS ENDPOINTS
    CROW_ROUTE(app, "/notifications").methods(crow::HTTPMethod::GET)([apiAdapter](){
        try {
            string result = apiAdapter->getNotifications();
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    CROW_ROUTE(app, "/finishTask/<int>").methods(crow::HTTPMethod::POST)([apiAdapter](int taskId){
        try {
            string result = apiAdapter->finishTask(taskId);
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    // BUNDLES ENDPOINTS
    CROW_ROUTE(app, "/bundle").methods(crow::HTTPMethod::GET)([apiAdapter](){
        try {
            string result = apiAdapter->getRandomBundle();
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    // CUSTOMER ENDPOINTS
    CROW_ROUTE(app, "/customer").methods("POST")([apiAdapter](const crow::request& req){
        try {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            string name = body["name"].s();
            string email = body["email"].s();

            string result = apiAdapter->createCustomer(name, email);
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    // SYSTEM STATUS ENDPOINT
    CROW_ROUTE(app, "/system/status").methods(crow::HTTPMethod::GET)([nurserySystem](){
        try {
            string result = nurserySystem->getStockCounts();
            return crow::response(result);
        } catch (const exception& e) {
            return crow::response(500, string("Error: ") + e.what());
        }
    });

    cout << "🚀 Nursery System Backend running on http://localhost:8080" << endl;
    cout << "Available endpoints:" << endl;
    cout << "  GET  /shop           - Browse shop plants" << endl;
    cout << "  GET  /nursery        - View nursery plants" << endl;
    cout << "  POST /waterPlant/{name} - Water a plant" << endl;
    cout << "  POST /movePlantOut/{name} - Move plant to shop" << endl;
    cout << "  GET  /staff          - Get staff info" << endl;
    cout << "  GET  /notifications  - Get pending tasks" << endl;
    cout << "  POST /finishTask/{id} - Complete a task" << endl;
    cout << "  GET  /bundle         - Get random bundle" << endl;
    cout << "  GET  /system/status  - Get system status" << endl;

    app.port(8080).multithreaded().run();

    // Cleanup
    delete apiAdapter;
    delete nurserySystem;

    return 0;
}