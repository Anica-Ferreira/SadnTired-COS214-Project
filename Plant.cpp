#include "Plant.h"

Plant::Plant(std::string name) : name_(name) {
    std::cout << "Plant created: " << name_ << std::endl;
}//set name and print creation

void Plant::Attach(IObserver* observer) {
    observers_.push_back(observer);
}//add observer to list

void Plant::Detach(IObserver* observer) {
    observers_.remove(observer);
}//remove observer from list

void Plant::Notify() {
    for (auto* o : observers_) {
        o->Update(current_need_ + " for plant " + name_);
    }
}//loop through observers and update on all

void Plant::signalNeed(std::string need) {
    current_need_ = need;
    Notify();
}//set need and call notify, extension