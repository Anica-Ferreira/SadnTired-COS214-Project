#include "SalesmanHandler.h"

SalesmanHandler::SalesmanHandler(const string& name) 
        : StaffHandler(name, "Salesman") {}
    
bool SalesmanHandler::canHandle(const string& requestType) {
    return requestType == "Purchase" || 
           requestType == "ProductInfo" || 
           requestType == "Pricing" ||
           requestType == "StockQuery" ||
           requestType == "Refund";
}
    
void SalesmanHandler::processRequest(Customer* customer, const string& details) {
    cout << "Salesman " << handlerName << " handling request: " << details << endl;
        
    if (customer) {
        customer->CreateMessage("Salesman " + handlerName + " is assisting with: " + details);
        customer->doA();
    }
        
    cout << "Salesman completed the transaction." << endl;
}