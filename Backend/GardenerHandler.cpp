#include "GardenerHandler.h"

GardenerHandler::GardenerHandler(const string& name) 
        : StaffHandler(name, "Gardener") {}
    
bool GardenerHandler::canHandle(const string& requestType) {
    return requestType == "PlantCare" || 
           requestType == "PlantHealth" || 
           requestType == "WateringIssue" ||
           requestType == "GrowthProblem";
}
    
void GardenerHandler::processRequest(Customer* customer, const string& details) {
    cout << "Gardener " << handlerName << " handling request: " << details << endl;
        
    if (customer) {
        customer->CreateMessage("Gardener " + handlerName + " is handling: " + details);
    }
        
    cout << "Gardener resolved the plant issue." << endl;
}