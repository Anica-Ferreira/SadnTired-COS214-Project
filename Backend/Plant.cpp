#include "Plant.h"

Plant::Plant(const string& name, const string& type, double price, WateringStrategy* strategy, const string& description)
    : name(name), type(type), description(description), price(price),
      waterLevel(0.0), wateringStrategy(strategy), state(new PlantedState()), wateringCount(0) {}
      
Plant::~Plant() {
    delete state;
    delete wateringStrategy;
}

//Getters
string Plant::getStateName() const {
    return state->getStateName();
}

double Plant::getWaterLevel() const {
    return waterLevel;
}

string Plant::getName() const {
    return name;
}

string Plant::getType() const {
    return type;
}

double Plant::getPrice() const {
    return price;
}

string Plant::getDescription() const {
    return description;
}

WateringStrategy* Plant::getStrategy() const {
    return wateringStrategy;
}

//Setters
void Plant::setWaterLevel(double level) {
    waterLevel = level;
}

void Plant::setState(PlantState* newState) {
    if (state != newState) {
        delete state;
        state = newState;
    }
}

void Plant::water() {
    state->handleWatering(this);
}

void Plant::passTime() {
    state->handlePassTime(this);
}

void Plant::increaseWateringCount() {
    wateringCount++;
}

bool Plant::isReadyForSale() const {
    return wateringCount >= getRequiredWaterings();
}


// Succulent
Succulent::Succulent(const string& name, double price, WateringStrategy* strategy, const string& description)
    : Plant(name, "Succulent", price, strategy, description) {}

int Succulent::getRequiredWaterings() const {
    return 5;  // Succulents need fewer waterings
}

// Flower
Flower::Flower(const string& name, double price, WateringStrategy* strategy, const string& description)
    : Plant(name, "Flower", price, strategy, description) {}

int Flower::getRequiredWaterings() const {
    return 10;  // Flowers need moderate waterings
}

// Tree
Tree::Tree(const string& name, double price, WateringStrategy* strategy, const string& description)
    : Plant(name, "Tree", price, strategy, description) {}

int Tree::getRequiredWaterings() const {
    return 15;  // Trees need more waterings to mature
}

//Jordans
void Plant::Attach(IObserver* observer) {
    observers_.push_back(observer);
}//add observer to list

void Plant::Detach(IObserver* observer) {
    observers_.remove(observer);
}//remove observer from list

void Plant::Notify() {
    for (auto* o : observers_) {
        o->Update(current_need_ + " for plant " + name);
    }
}//loop through observers and update on all

void Plant::signalNeed(string need) {
    current_need_ = need;
    Notify();
}//set need and call notify, extension