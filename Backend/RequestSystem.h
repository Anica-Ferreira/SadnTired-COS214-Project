#ifndef REQUESTSYSTEM_H
#define REQUESTSYSTEM_H

using namespace std;
#include <string>
#include "GardenerHandler.h"
#include "SalesmanHandler.h"
#include "ManagerHandler.h"

class RequestSystem {
private:
    StaffHandler* chainRoot;
public:
    RequestSystem();
    ~RequestSystem();
    void processCustomerRequest(const string& requestType, Customer* customer, const string& details);
    static void demonstrateChain();
};

#endif