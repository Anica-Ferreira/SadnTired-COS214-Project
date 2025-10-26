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
    Customer(std::string name) : name_(name), mediator_(nullptr) {
        std::cout << "Customer created: " << name_ << std::endl;
    }//init name and mediator to null

    void setMediator(IMediator* mediator) override {
        mediator_ = mediator;
    }//set mediator pointer

    void sendRequest(std::string request) override {
        if (mediator_) {
            std::cout << name_ << " sends request: " << request << std::endl;
            mediator_->notify(this, request);
        } else {
            std::cout << name_ << ": No mediator set!" << std::endl;
        }
    }//check if mediator exists, if yes, print send message and call mediator's notify with self and request, else error.

    std::string getName() const override {
        return name_;
    }
};

#endif // CUSTOMER_H