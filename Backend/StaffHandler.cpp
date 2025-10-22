#include "StaffHandler.h"

StaffHandler::StaffHandler(const string& name, const string& staffRole) 
        : nextHandler(nullptr), handlerName(name), role(staffRole) {}
    
StaffHandler::~StaffHandler() {
    // Clean up next handler in the chain
    if (nextHandler) {
        delete nextHandler;
    }
}
    
void StaffHandler::setNext(StaffHandler* handler) {
    nextHandler = handler;
}
    
void StaffHandler::handleRequest(const string& requestType, Customer* customer, const string& details) {
    if (canHandle(requestType)) {
        processRequest(customer, details);
    } else if (nextHandler) {
        cout << handlerName << " cannot handle '" << requestType << "'. Passing to next handler." << endl;
        nextHandler->handleRequest(requestType, customer, details);
    } else {
        cout << "No handler available for: " << requestType << endl;
    }
}

string StaffHandler::getName() const { return handlerName; }

string StaffHandler::getRole() const { return role; }