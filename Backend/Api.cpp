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
    void before_handle(crow::request& req, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    }
    void after_handle(crow::request& req, crow::response& res, context&) {
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
    <div class="endpoint"><strong>GET</strong> <a href="/bundle" target="_blank">/bundle</a> - Get random bundle</div>
    <div class="endpoint"><strong>GET</strong> <a href="/system/status" target="_blank">/system/status</a> - Get system status</div>

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

    // --- BUNDLE ENDPOINT ---
    CROW_ROUTE(app, "/bundle")([apiAdapter](){
        try {
            string result = apiAdapter->getRandomBundle();
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

    app.port(8080).multithreaded().run();

    delete apiAdapter;
    delete nurserySystem;

    return 0;
}