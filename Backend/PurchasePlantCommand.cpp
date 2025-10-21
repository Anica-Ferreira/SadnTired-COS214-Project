#include "PurchasePlantCommand.h"
using namespace std;

PurchasePlantCommand::PurchasePlantCommand(Customer* cust, const string& plant, int qty)
    : CustomerCommand(cust, "PurchasePlant"), plantName(plant), quantity(qty) {}

void PurchasePlantCommand::execute()  {
    cout << "Customer purchasing " << quantity << " " << plantName << "(s)" << endl;
    // Integrate with payment and inventory systems
    if (customer) {
        customer->CreateMessage("Purchase: " + plantName);
        customer->doB();  // Trigger staff interaction
    }
}

string PurchasePlantCommand::getDescription() const  {
    return "PurchasePlant: " + plantName + " x" + to_string(quantity);
}