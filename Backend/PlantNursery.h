#ifndef PLANT_NURSERY_H
#define PLANT_NURSERY_H

#include <string>
using namespace std;

class WebAPIAdapter;

class PlantNursery {
private:
    WebAPIAdapter* apiAdapter;

public:
    PlantNursery(WebAPIAdapter* adapter);

    // Core nursery operations
    string getGrowthStatus();
    string getWateringSchedule();
    string getPlantHealthAlerts();
    string addNewPlant(const string& plantType, int quantity);

    // Additional nursery management methods
    string getPropagationReport();
    string getEnvironmentalConditions();
};

#endif