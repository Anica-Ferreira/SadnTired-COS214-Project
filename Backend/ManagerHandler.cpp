#include "ManagerHandler.h"

ManagerHandler::ManagerHandler(const string& name) 
        : StaffHandler(name, "Manager") {}
    
bool ManagerHandler::canHandle(const string& requestType){
    return requestType == "Complaint" || 
           requestType == "Escalation" ||
           requestType == "ComplexIssue" ||
           requestType == "PolicyException";
}
    
void ManagerHandler::processRequest(Customer* customer, const string& details){
    cout << "Manager " << handlerName << " handling escalated request: " << details << endl;
        
    if (customer) {
        customer->CreateMessage("Manager " + handlerName + " is resolving: " + details);
        customer->doB();
    }
        
    cout << "Manager resolved the escalated issue." << endl;
}