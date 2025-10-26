#ifndef PLANT_H
#define PLANT_H

#include "ISubject.h"
#include "IObserver.h"
#include <list>
#include <string>
#include <iostream>

class Plant : public ISubject {
private:
    std::list<IObserver*> observers_;//list of pointers
    std::string name_;//name of plant
    std::string current_need_;

public:
    Plant(std::string name) : name_(name) {
        std::cout << "Plant created: " << name_ << std::endl;
    }//set name and print creation

    void Attach(IObserver* observer) override {
        observers_.push_back(observer);
    }//add observer to list

    void Detach(IObserver* observer) override {
        observers_.remove(observer);
    }//remove observer from list

    void Notify() override {
        for (auto* o : observers_) {
            o->Update(current_need_ + " for plant " + name_);
        }
    }//loop through observers and update on all

    void signalNeed(std::string need) {
        current_need_ = need;
        Notify();
    }//set need and call notify, extension
};

#endif // PLANT_H