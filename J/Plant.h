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
    Plant(std::string name);//set name and print creation

    void Attach(IObserver* observer) override; //add observer to list

    void Detach(IObserver* observer) override; //remove observer from list

    void Notify() override;//loop through observers and update on all

    void signalNeed(std::string need);//set need and call notify, extension
};

#endif // PLANT_H