#ifndef STAFFHANDLER_H
#define STAFFHANDLER_H

using namespace std;
#include <string>
#include <iostream>

class Customer;
class CustomerCommand;

class StaffHandler {
protected:
    StaffHandler* nextHandler;
    string handlerName;
    string role;
public:
    StaffHandler(const string& name, const string& staffRole);
    virtual ~StaffHandler();
    void setNext(StaffHandler* handler);
    virtual void handleRequest(const string& requestType, Customer* customer, const string& details);
    virtual bool canHandle(const string& requestType) = 0;
    virtual void processRequest(Customer* customer, const string& details) = 0;
    string getName() const ;
    string getRole() const ;
};

#endif