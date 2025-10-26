#include "Customer.h"

Customer::Customer(std::string name) : name_(name), mediator_(nullptr) {
    std::cout << "Customer created: " << name_ << std::endl;
}//init name and mediator to null

void Customer::setMediator(IMediator* mediator) {
    mediator_ = mediator;
}//set mediator pointer

void Customer::sendRequest(std::string request) {
    if (mediator_) {
        std::cout << name_ << " sends request: " << request << std::endl;
        mediator_->notify(this, request);
    } else {
        std::cout << name_ << ": No mediator set!" << std::endl;
    }
}//check if mediator exists, if yes, print send message and call mediator's notify with self and request, else error.

std::string Customer::getName() const {
    return name_;
}