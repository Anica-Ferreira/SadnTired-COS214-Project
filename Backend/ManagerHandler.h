#ifndef MANAGERHANDLER_H
#define MANAGERHANDLER_H

#include "StaffHandler.h"
#include "Customer.h"

class ManagerHandler : public StaffHandler {
public:
    ManagerHandler(const string& name);
    bool canHandle(const string& requestType) override;
    void processRequest(Customer* customer, const string& details) override;
};

#endif