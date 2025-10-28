#include "PlantNursery.h"
#include "WebAPIAdapter.h"
#include "InventoryManager.h"
#include "PlantFactory.h"
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

PlantNursery::PlantNursery(WebAPIAdapter* adapter) : apiAdapter(adapter) {
    cout << "Plant Nursery initialized" << endl;
}

string PlantNursery::getGrowthStatus() {
    cout << "PlantNursery: Getting growth status" << endl;

    // Get nursery plants from API to analyze growth status
    string nurseryData = apiAdapter->getNurseryPlants();

    // Simulate growth status analysis based on plant states
    // In a real implementation, this would parse the JSON and analyze each plant
    stringstream status;
    status << "{\"growth_report\": {"
           << "\"timestamp\": \"" << time(nullptr) << "\", "
           << "\"summary\": {"
           << "\"total_plants\": 15, "
           << "\"healthy\": 12, "
           << "\"needs_water\": 2, "
           << "\"needs_attention\": 1, "
           << "\"ready_for_sale\": 5"
           << "}, "
           << "\"details\": ["
           << "{\"plant\": \"Rose\", \"status\": \"Growing\", \"progress\": \"75%\", \"health\": \"Good\"}, "
           << "{\"plant\": \"Cactus\", \"status\": \"Ready\", \"progress\": \"100%\", \"health\": \"Excellent\"}, "
           << "{\"plant\": \"Tulip\", \"status\": \"Seedling\", \"progress\": \"25%\", \"health\": \"Good\"}"
           << "]"
           << "}}";

    return status.str();
}

string PlantNursery::getWateringSchedule() {
    cout << "PlantNursery: Getting watering schedule" << endl;

    // Simulate intelligent watering schedule based on plant types
    stringstream schedule;
    schedule << "{\"watering_schedule\": {"
             << "\"week\": \"" << "2024-11-11 to 2024-11-17" << "\", "
             << "\"schedule\": ["
             << "{\"day\": \"Monday\", \"tasks\": ["
             << "{\"time\": \"08:00\", \"area\": \"Greenhouse A\", \"plants\": \"Roses, Tulips\", \"water_amount\": \"2L\"}, "
             << "{\"time\": \"14:00\", \"area\": \"Greenhouse B\", \"plants\": \"Succulents\", \"water_amount\": \"0.5L\"}"
             << "]}, "
             << "{\"day\": \"Tuesday\", \"tasks\": ["
             << "{\"time\": \"09:00\", \"area\": \"Outdoor Beds\", \"plants\": \"Trees, Shrubs\", \"water_amount\": \"5L\"}"
             << "]}, "
             << "{\"day\": \"Wednesday\", \"tasks\": ["
             << "{\"time\": \"08:00\", \"area\": \"Greenhouse A\", \"plants\": \"Roses, Tulips\", \"water_amount\": \"2L\"}"
             << "]}, "
             << "{\"day\": \"Thursday\", \"tasks\": ["
             << "{\"time\": \"10:00\", \"area\": \"Propagation Room\", \"plants\": \"Seedlings\", \"water_amount\": \"1L\"}"
             << "]}, "
             << "{\"day\": \"Friday\", \"tasks\": ["
             << "{\"time\": \"08:00\", \"area\": \"All Areas\", \"plants\": \"All Plants\", \"water_amount\": \"Varies\"}"
             << "]}"
             << "], "
             << "\"notes\": \"Adjust watering based on weather conditions and soil moisture\""
             << "}}";

    return schedule.str();
}

string PlantNursery::getPlantHealthAlerts() {
    cout << "PlantNursery: Checking for plant health alerts" << endl;

    // Get nursery status to check for health issues
    string nurseryStatus = apiAdapter->getNurseryPlants();

    // Simulate health monitoring system
    stringstream alerts;
    alerts << "{\"health_alerts\": {"
           << "\"timestamp\": \"" << time(nullptr) << "\", "
           << "\"critical_alerts\": 1, "
           << "\"warning_alerts\": 2, "
           << "\"alerts\": ["
           << "{\"level\": \"critical\", "
           << "\"plant\": \"Orchid\", "
           << "\"issue\": \"Root rot detected\", "
           << "\"location\": \"Greenhouse B, Shelf 3\", "
           << "\"action_required\": \"Immediate treatment needed\", "
           << "\"suggested_action\": \"Remove from soil, trim affected roots, repot with fresh medium\""
           << "}, "
           << "{\"level\": \"warning\", "
           << "\"plant\": \"Rose\", "
           << "\"issue\": \"Powdery mildew signs\", "
           << "\"location\": \"Greenhouse A, Row 2\", "
           << "\"action_required\": \"Treatment within 48 hours\", "
           << "\"suggested_action\": \"Apply fungicide and improve air circulation\""
           << "}, "
           << "{\"level\": \"warning\", "
           << "\"plant\": \"Fern\", "
           << "\"issue\": \"Low humidity stress\", "
           << "\"location\": \"Shade House\", "
           << "\"action_required\": \"Monitor closely\", "
           << "\"suggested_action\": \"Increase misting frequency to 3 times daily\""
           << "}"
           << "], "
           << "\"preventative_measures\": ["
           << "\"Check soil moisture levels daily\", "
           << "\"Monitor temperature and humidity in all greenhouses\", "
           << "\"Inspect for pests during morning rounds\""
           << "]"
           << "}}";

    return alerts.str();
}

string PlantNursery::addNewPlant(const string& plantType, int quantity) {
    cout << "PlantNursery: Adding " << quantity << " new " << plantType << "(s)" << endl;

    if (quantity <= 0) {
        return "{\"error\": \"Quantity must be positive\"}";
    }

    // Use PlantFactory to create new plants based on type
    string createdPlants;

    if (plantType == "Rose" || plantType == "Flower") {
        FlowerFactory factory;
        for (int i = 0; i < quantity; i++) {
            // In real implementation, this would add to inventory
            // For now, simulate the creation
            createdPlants += "Flower (" + plantType + "), ";
        }
    }
    else if (plantType == "Cactus" || plantType == "Succulent") {
        SucculentFactory factory;
        for (int i = 0; i < quantity; i++) {
            createdPlants += "Succulent (" + plantType + "), ";
        }
    }
    else if (plantType == "Tree" || plantType == "Bonsai") {
        TreeFactory factory;
        for (int i = 0; i < quantity; i++) {
            createdPlants += "Tree (" + plantType + "), ";
        }
    }
    else {
        return "{\"error\": \"Unknown plant type: " + plantType + "\"}";
    }

    // Remove trailing comma and space
    if (!createdPlants.empty()) {
        createdPlants = createdPlants.substr(0, createdPlants.length() - 2);
    }

    stringstream result;
    result << "{\"action\": \"add_plants\", "
           << "\"plant_type\": \"" << plantType << "\", "
           << "\"quantity\": " << quantity << ", "
           << "\"status\": \"created\", "
           << "\"plants_created\": \"" << createdPlants << "\", "
           << "\"next_steps\": \"Place in appropriate growing area and begin care routine\""
           << "}";

    return result.str();
}

string PlantNursery::getPropagationReport() {
    cout << "PlantNursery: Generating propagation report" << endl;

    stringstream report;
    report << "{\"propagation_report\": {"
           << "\"period\": \"Current Month\", "
           << "\"summary\": {"
           << "\"cuttings_taken\": 45, "
           << "\"successful_rootings\": 38, "
           << "\"success_rate\": \"84%\", "
           << "\"ready_for_potting\": 25"
           << "}, "
           << "\"by_plant_type\": ["
           << "{\"type\": \"Succulents\", \"taken\": 15, \"rooted\": 14, \"rate\": \"93%\"}, "
           << "{\"type\": \"Flowers\", \"taken\": 20, \"rooted\": 16, \"rate\": \"80%\"}, "
           << "{\"type\": \"Trees\", \"taken\": 10, \"rooted\": 8, \"rate\": \"80%\"}"
           << "], "
           << "\"recommendations\": ["
           << "\"Increase humidity for flower cuttings\", "
           << "\"Consider using rooting hormone for tree cuttings\", "
           << "\"Monitor succulent cuttings for overwatering\""
           << "]"
           << "}}";

    return report.str();
}

string PlantNursery::getEnvironmentalConditions() {
    cout << "PlantNursery: Checking environmental conditions" << endl;

    // Simulate environmental monitoring system
    stringstream conditions;
    conditions << "{\"environmental_conditions\": {"
               << "\"timestamp\": \"" << time(nullptr) << "\", "
               << "\"greenhouse_a\": {"
               << "\"temperature\": \"22.5°C\", "
               << "\"humidity\": \"65%\", "
               << "\"light_level\": \"8500 lux\", "
               << "\"soil_moisture\": \"Optimal\""
               << "}, "
               << "\"greenhouse_b\": {"
               << "\"temperature\": \"25.1°C\", "
               << "\"humidity\": \"45%\", "
               << "\"light_level\": \"12000 lux\", "
               << "\"soil_moisture\": \"Dry\""
               << "}, "
               << "\"shade_house\": {"
               << "\"temperature\": \"19.8°C\", "
               << "\"humidity\": \"75%\", "
               << "\"light_level\": \"3500 lux\", "
               << "\"soil_moisture\": \"Wet\""
               << "}, "
               << "\"alerts\": ["
               << "{\"location\": \"Greenhouse B\", \"issue\": \"Low humidity\", \"suggestion\": \"Increase misting\"}, "
               << "{\"location\": \"Shade House\", \"issue\": \"High soil moisture\", \"suggestion\": \"Reduce watering frequency\"}"
               << "]"
               << "}}";

    return conditions.str();
}