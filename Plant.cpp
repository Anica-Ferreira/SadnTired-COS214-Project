#include "Plant.h"

Plant::Plant(const std::string& name, const std::string& type, double price, WateringStrategy* strategy)
    : name(name), type(type), price(price), waterLevel(0.0), wateringStrategy(strategy), state(new PlantedState()), wateringCount(0) {}

Plant::~Plant() {
    delete state;
    delete wateringStrategy;
}

void Plant::water() {
    state->handleWatering(this);
}

void Plant::passTime() {
    state->handlePassTime(this);
}

std::string Plant::getStateName() const {
    return state->getStateName();
}

double Plant::getWaterLevel() const {
    return waterLevel;
}

void Plant::setWaterLevel(double level) {
    waterLevel = level;
}

std::string Plant::getName() const {
    return name;
}

std::string Plant::getType() const {
    return type;
}

double Plant::getPrice() const {
    return price;
}

WateringStrategy* Plant::getStrategy() const {
    return wateringStrategy;
}

void Plant::setState(PlantState* newState) {
    if (state != newState) {
        delete state;
        state = newState;
    }
}

void Plant::increaseWateringCount() {
    wateringCount++;
}

bool Plant::isReadyForSale() const {
    return wateringCount >= getRequiredWaterings();
}

// Succulent
Succulent::Succulent(const std::string& name, double price, WateringStrategy* strategy)
    : Plant(name, "Succulent", price, strategy) {}

int Succulent::getRequiredWaterings() const {
    return 5;  // Succulents need fewer waterings
}

// Flower
Flower::Flower(const std::string& name, double price, WateringStrategy* strategy)
    : Plant(name, "Flower", price, strategy) {}

int Flower::getRequiredWaterings() const {
    return 10;  // Flowers need moderate waterings
}

// Tree
Tree::Tree(const std::string& name, double price, WateringStrategy* strategy)
    : Plant(name, "Tree", price, strategy) {}

int Tree::getRequiredWaterings() const {
    return 15;  // Trees need more waterings to mature
}