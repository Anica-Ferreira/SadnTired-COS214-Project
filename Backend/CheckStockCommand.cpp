#include "CheckStockCommand.h"

CheckStockCommand::CheckStockCommand(Customer* cust, const string& plant)
    : CustomerCommand(cust, "CheckStock"), plantName(plant) {}

void CheckStockCommand::execute()  {
    cout << "Customer checking stock for: " << plantName << endl;
    //Query inventory system
    if (customer) {
        customer->CreateMessage("Stock check: " + plantName);
    }
}

string CheckStockCommand::getDescription() const  {
    return "CheckStock: " + plantName;
}