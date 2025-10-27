#include "crow.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// --- Structures ---
struct Plant {
    int id;
    string name;
    string status;
    int nurseryStock;
};

struct Product {
    int id;
    string name;
    string description;
    int shopStock;
};

struct Staff {
    int id;
    string name;
    string role;
    int since;
};

struct Notification {
    int id;
    string type;
    string status;
    string description;
};

struct Bundle {
    string name;
    int count;
};

// --- Dummy Data ---
vector<Plant> nursery = {
    {1,"Rose","Planted",5}, {2,"Lavender","Ready",3}, {3,"Cactus","Ready",7},
    {4,"Tulip","Dry",6}, {5,"Daisy","Planted",4}, {6,"Orchid", "Dry",2},
    {7,"Sunflower","Ready",5}, {8,"Succulent","Planted",3}, {9,"Fern","Watered",8},
    {10,"Bonsai","Watered",1}, {11,"Peace Lily","Ready",6}, {12,"Aloe Vera","Dry",2}
};

vector<Product> shop = {
    {1, "Rose", "Fresh red and pink roses", 10}, {2, "Lavender", "Potted lavender plant", 5},
    {3, "Cactus", "Small cactus in pot", 8}, {4, "Tulip", "Colorful tulips", 6},
    {5, "Daisy", "White and yellow daisies", 7}, {6, "Orchid", "Orchid with blooms", 4},
    {7, "Sunflower", "Sunflowers in vase", 5}, {8, "Succulent", "Three small succulents", 6},
    {9, "Fern", "Indoor fern plant", 3}, {10, "Bonsai", "Mini bonsai tree", 2},
    {11, "Peace Lily", "Potted peace lily", 8}, {12, "Aloe Vera", "Aloe vera in pot", 3}
};

vector<Staff> staffList = {
    {1,"Mr. Green","Gardener",1999},
    {2,"Mr. Cash","Sales", 2018}
};

vector<Notification> notifications = {
    {1,"Watering","Active","Rose needs watering"},
    {2,"Check","Waiting","Check Lavender status"},
    {3,"Move","Active","Move Aloe Vera to shop"}
};

vector<Bundle> bundles = {
    {"Sptring bundle",3}, {"Valentines bundle",2}, {"Cactus Trio", 1}
};

// --- CORS Middleware ---
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
    crow::App<CORSMiddleware> app;
    srand(time(nullptr));

    // --- OPTIONS catch-all for preflight ---
    CROW_ROUTE(app, "/<path>")
    .methods(crow::HTTPMethod::Options)
    ([](const crow::request&, crow::response& res, std::string){
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.code = 200;
        res.end();
    });

    // --- SHOP ---
    CROW_ROUTE(app, "/shop").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        for(size_t i=0;i<shop.size();i++){
            result[i]["name"] = shop[i].name;
            result[i]["description"] = shop[i].description;
            result[i]["shopStock"] = shop[i].shopStock;
        }
        return crow::response(result);
    });

    CROW_ROUTE(app, "/randomShop").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        int n = 1 + rand()%12;
        for(int i=0;i<n;i++){
            int idx = rand()%nursery.size();
            result[i]["name"] = nursery[idx].name;
            result[i]["count"] = 1 + rand()%5;
        }
        return crow::response(result);
    });

    // --- NURSERY ---
    CROW_ROUTE(app, "/nursery").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        for(size_t i=0;i<nursery.size();i++){
            result[i]["name"] = nursery[i].name;
            result[i]["status"] = nursery[i].status;
            result[i]["nurseryStock"] = nursery[i].nurseryStock;
        }
        return crow::response(result);
    });

    CROW_ROUTE(app, "/waterPlant/<int>").methods(crow::HTTPMethod::POST)([](int id){
        if(id < 1 || id > (int)nursery.size())
            return crow::response(400,"Invalid id");
        nursery[id-1].status = "Watered";
        return crow::response("Plant watered successfully");
    });

    CROW_ROUTE(app, "/movePlantOut/<int>").methods(crow::HTTPMethod::POST)([](int id){
        if(id < 1 || id > (int)nursery.size())
            return crow::response(400,"Invalid id");
        if(nursery[id-1].nurseryStock <= 0)
            return crow::response(400,"No stock in nursery");
        nursery[id-1].nurseryStock--;
        shop[id-1].shopStock++;
        return crow::response("Plant moved to shop");
    });

    // --- STAFF ---
    CROW_ROUTE(app, "/staff").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        Staff s = staffList[0]; // return first staff member
        result["name"] = s.name;
        result["role"] = s.role;
        result["since"] = s.since;
        return crow::response(result);
    });

    // --- NOTIFICATIONS ---
    CROW_ROUTE(app, "/notifications").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        for(size_t i=0;i<notifications.size();i++){
            result[i]["id"] = notifications[i].id;
            result[i]["type"] = notifications[i].type;
            result[i]["status"] = notifications[i].status;
            result[i]["description"] = notifications[i].description;
        }
        return crow::response(result);
    });

    CROW_ROUTE(app, "/finishTask/<int>").methods(crow::HTTPMethod::POST)([](int id){
        for(auto &notif : notifications){
            if(notif.id == id){
                notif.status = "Completed";
                return crow::response("Task marked as completed");
            }
        }
        return crow::response(400,"Invalid task id");
    });

    // --- BUNDLES ---
    CROW_ROUTE(app, "/bundle").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        int idx = rand() % bundles.size();
        result["name"] = bundles[idx].name;
        result["count"] = bundles[idx].count;
        return crow::response(result);
    });

    // --- Run server ---
    app.port(8080).multithreaded().run();
}