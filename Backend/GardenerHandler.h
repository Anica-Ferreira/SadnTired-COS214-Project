#ifndef GARDENERHANDLER_H
#define GARDENERHANDLER_H

#include "StaffHandler.h"
#include "Customer.h"

class GardenerHandler : public StaffHandler {
public:
    GardenerHandler(const string& name);
    bool canHandle(const string& requestType) override;
    void processRequest(Customer* customer, const string& details) override;
};

#endif