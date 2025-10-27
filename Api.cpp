/* 

    Endpoints : 

    Shop:
        GET: Get all products in shop
        URL: http://localhost:8080/shop
        Returns 12 products in the format:
        {
            "name": "Rose Bouquet",
            "description": "Fresh red and pink roses",
            "shopStock": 10
        }

        GET: Get random plants
        URL: http://localhost:8080/randomShop
        Returns 1-12 random plants with their count:
        [
            {"name":"Rose","count":3},
            {"name":"Cactus","count":1},
            ...
        ]

    Nursery:
        GET: Get all plants in nursery
        URL: http://localhost:8080/nursery
        Returns 12 plants in the format:
        {
            "name": "Rose",
            "status": "Planted",
            "nurseryStock": 5
        }

        POST: Water a plant
        URL: http://localhost:8080/waterPlant/{id}
        Updates the status of the plant to "Watered"

        POST: Move a plant to shop
        URL: http://localhost:8080/movePlantOut/{id}
        Decreases nursery stock by 1, increases shop stock by 1

    
    Staff
        GET: Get a single staff member
        URL: http://localhost:8080/staff
        Returns:
        {
            "name": "Mr. Green",
            "role": "Gardener",
            "since": 1999
        }
    
    Notifications:
        GET: Get all notifications
        URL: http://localhost:8080/notifications
        Returns array of notifications:
        [
            {
                "id":1,
                "type":"Watering",
                "status":"Active",
                "description":"Rose needs watering"
            },
        ]

        POST: Finish a task
        URL: http://localhost:8080/finishTask/{id}
        Updates the notification's status to "Completed"

    Bundles:
        GET: Get a random bundle
        URL: http://localhost:8080/bundle
        Returns:
        {
            "name":"Valentines bundle",
            "count":2
        }
*/

#include "crow.h"
#include "crow/middlewares/cors.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Here are the structures for all the data - we can change it as needed...

//This refers to the plant in the nursery
struct Plant {
    int id;
    string name;
    string status;
    int nurseryStock;
};

//The final product ready to be sold in shop
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

/* Dummy data */

vector<Plant> nursery = {
    {1,"Rose","Planted",5},
    {2,"Lavender","Ready",3},
    {3,"Cactus","Ready",7},
    {4,"Tulip","Dry",6},
    {5,"Daisy","Planted",4},
    {6,"Orchid", "Dry",2},
    {7,"Sunflower","Ready",5},
    {8,"Succulent","Planted",3},
    {9,"Fern","Watered",8},
    {10,"Bonsai","Watered",1},
    {11,"Peace Lily","Ready",6},
    {12,"Aloe Vera","Dry",2}
};

vector<Product> shop = {
    {1, "Rose", "Fresh red and pink roses", 10},
    {2, "Lavender", "Potted lavender plant", 5},
    {3, "Cactus", "Small cactus in pot", 8},
    {4, "Tulip", "Colorful tulips", 6},
    {5, "Daisy", "White and yellow daisies", 7},
    {6, "Orchid", "Orchid with blooms", 4},
    {7, "Sunflower", "Sunflowers in vase", 5},
    {8, "Succulent", "Three small succulents", 6},
    {9, "Fern", "Indoor fern plant", 3},
    {10, "Bonsai", "Mini bonsai tree", 2},
    {11, "Peace Lily", "Potted peace lily", 8},
    {12, "Aloe Vera", "Aloe vera in pot", 3}
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
    {"Sptring bundle",3},
    {"Valentines bundle",2},
    {"Cactus Trio", 1}
};

struct CORSMiddleware {
    struct context {};

    void before_handle(crow::request& req, crow::response& res, context& ctx) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
    }

    void after_handle(crow::request& req, crow::response& res, context& ctx) {}
};

int main() {
    crow::App<CORSMiddleware> app;
    srand(time(nullptr));

    CROW_ROUTE(app, "/<path>").methods(crow::HTTPMethod::Options)
    ([](const crow::request&, crow::response& res, std::string path) {
        res.code = 200;
        res.end();
    });

    //SHOP

    //GET /shop
    CROW_ROUTE(app, "/shop").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        for (size_t i = 0; i < shop.size(); i++) {
            result[i]["name"] = shop[i].name;
            result[i]["description"] = shop[i].description;
            result[i]["shopStock"] = shop[i].shopStock;
        }
        return crow::response(result);
    });

    //NURSERY

    //GET /nursery
    CROW_ROUTE(app, "/nursery").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        for (size_t i = 0; i < nursery.size(); i++) {
            result[i]["name"] = nursery[i].name;
            result[i]["status"] = nursery[i].status;
            result[i]["nurseryStock"] = nursery[i].nurseryStock;
        }
        return crow::response(result);
    });

    //POST /waterPlant/{id}
    CROW_ROUTE(app, "/waterPlant/<int>").methods(crow::HTTPMethod::POST)([](int id){
        if (id < 1 || id > nursery.size())
            return crow::response(400, "Invalid id");

        nursery[id-1].status = "Watered";
        return crow::response("Plant watered successfully");
    });

    //POST /movePlantOut/{id}
    CROW_ROUTE(app, "/movePlantOut/<int>").methods(crow::HTTPMethod::POST)([](int id){
        if (id < 1 || id > nursery.size())
            return crow::response(400, "Invalid id");

        if (nursery[id-1].nurseryStock <= 0)
            return crow::response(400, "No stock in nursery");

        nursery[id-1].nurseryStock--;
        shop[id-1].shopStock++;
        return crow::response("Plant moved to shop");
    });

    //STAFF

    //GET /staff
    CROW_ROUTE(app, "/staff").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        Staff s = staffList[0];
        result["name"] = s.name;
        result["role"] = s.role;
        result["since"] = s.since;
        return crow::response(result);
    });

    //GET /notifications
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

    //POST /finishTask/{id}
    CROW_ROUTE(app, "/finishTask/<int>").methods(crow::HTTPMethod::POST)([](int id){
        bool found = false;
        for(size_t i=0;i<notifications.size();i++){
            if(notifications[i].id == id){
                notifications[i].status = "Completed";
                found = true;
                break;
            }
        }
        if(!found) return crow::response(400,"Invalid task id");
        return crow::response("Task marked as completed");
    });

    //SHOP

    //GET /randomShop
    CROW_ROUTE(app, "/randomShop").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        int n = 1 + rand()%12;

        for(int i=0; i<n; i++){
            int idx = rand() % nursery.size();
            result[i]["name"] = nursery[idx].name;
            result[i]["count"] = 1 + rand()%5;
        }
        return crow::response(result);
    });

    //GET /bundle
    CROW_ROUTE(app, "/bundle").methods(crow::HTTPMethod::GET)([](){
        crow::json::wvalue result;
        int idx = rand() % bundles.size();
        result["name"] = bundles[idx].name;
        result["count"] = bundles[idx].count;
        return crow::response(result);
    });

    app.port(8080).multithreaded().run();
}
