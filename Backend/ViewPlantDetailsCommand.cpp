#include "ViewPlantDetailsCommand.h"

ViewPlantDetailsCommand::ViewPlantDetailsCommand(Customer* cust, const string& plant)
        : CustomerCommand(cust, "ViewPlantDetails"), plantName(plant) {}
    
void ViewPlantDetailsCommand::execute()  {
    cout << "Customer viewing details for: " << plantName << endl;
    // Fetch plant details from database
    if (customer) {
        customer->CreateMessage("Viewing details: " + plantName);
    }
}
    
string ViewPlantDetailsCommand::getDescription() const  {
    return "ViewPlantDetails: " + plantName;
}