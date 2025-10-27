#ifndef SAD_TIRED_PLANTNURSERY_H
#define SAD_TIRED_PLANTNURSERY_H

#include <string>
using namespace std;

class WebAPIAdapter;

class PlantNursery {
private:
    WebAPIAdapter* apiAdapter;

public:
    PlantNursery(WebAPIAdapter* adapter);
    string getGrowthStatus();
    string getWateringSchedule();
    string getPlantHealthAlerts();
    string addNewPlant(const string& plantType, int quantity);
};

#endif //SAD_TIRED_PLANTNURSERY_H