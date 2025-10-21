#ifndef BACKEND_CUSTOMERCOMMAND_H
#define BACKEND_CUSTOMERCOMMAND_H

using namespace std;
#include <string>
#include "Customer.h"

class Customer;  // Forward declaration

class CustomerCommand {
protected:
    Customer* customer;
    string commandType;

public:
    CustomerCommand(Customer* cust, const string& type)
        : customer(cust), commandType(type) {}
    virtual ~CustomerCommand() = default;
    virtual void execute() = 0;
    virtual string getDescription() const = 0;
    string getCommandType() const { return commandType; }
};

#endif //BACKEND_CUSTOMERCOMMAND_H