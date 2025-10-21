#include "Customer.h"

#include "ObserverMediator.h"

Customer::Customer() {
}


void Customer::Attach(ObserverMediator* observer) {
    list_observer_.push_back(observer);
}

void Customer::Detach(ObserverMediator* observer) {
    list_observer_.remove(observer);
}

void Customer::Notify() {
    list<ObserverMediator*>::iterator it = list_observer_.begin();

    while (it != list_observer_.end()) {
        (*it)->Update(message_);
        it++;
    }
}

void Customer::CreateMessage(std::string message) {
    this->message_ = message;
    Notify();
}