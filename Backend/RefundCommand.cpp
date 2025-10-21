#include "RefundCommand.h"

RefundCommand::RefundCommand(Customer* cust, const string& plant, const string& refundReason)
        : CustomerCommand(cust, "Refund"), plantName(plant), reason(refundReason) {}
    
void RefundCommand::execute()  {
    cout << "Customer requesting refund for " << plantName << ": " << reason << endl;
    //Integrate with refund processing
    if (customer) {
        customer->CreateMessage("Refund requested for: " + plantName);
    }
}
    
string RefundCommand::getDescription() const  {
    return "Refund: " + plantName + " - " + reason;
}