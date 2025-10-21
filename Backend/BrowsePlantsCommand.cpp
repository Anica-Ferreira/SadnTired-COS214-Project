#include "BrowsePlantsCommand.h"
#include <iostream>
using namespace std;

BrowsePlantsCommand::BrowsePlantsCommand(Customer* cust) : CustomerCommand(cust, "BrowsePlants") {}
    
void BrowsePlantsCommand::execute()  {
    cout << "Customer is browsing available plants" << endl;
    //Integrate with inventory system
    if (customer) {
        customer->CreateMessage("Customer browsing plants");
    }
}
    
string BrowsePlantsCommand::getDescription() const  {
    return "BrowsePlants: Viewing available plants";
}