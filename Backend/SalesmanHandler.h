#ifndef SALESMANHANDLER_H
#define SALESMANHANDLER_H

#include "StaffHandler.h"
#include "Customer.h"

class SalesmanHandler : public StaffHandler {
public:
    SalesmanHandler(const string& name);
    bool canHandle(const string& requestType) override;
    void processRequest(Customer* customer, const string& details) override;
};

#endif