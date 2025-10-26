#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "IColleague.h"
#include "IMediator.h"
#include <iostream>
#include <string>

class Customer : public IColleague {//customer is a colleague
private:
    std::string name_;//name of customer
    IMediator* mediator_;//mediator customer goes to

public:
    Customer(std::string name) ;//init name and mediator to null

    void setMediator(IMediator* mediator) override;

    void sendRequest(std::string request) override; //check if mediator exists, if yes, print send message and call mediator's notify with self and request, else error.

    std::string getName() const override;
};

#endif // CUSTOMER_H