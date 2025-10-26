#include "PlantFactory.h"

Plant* SucculentFactory::createPlant(const std::string& name, double price, WateringStrategy* strategy) {
    return new Succulent(name, price, strategy);
}

Plant* FlowerFactory::createPlant(const std::string& name, double price, WateringStrategy* strategy) {
    return new Flower(name, price, strategy);
}

Plant* TreeFactory::createPlant(const std::string& name, double price, WateringStrategy* strategy) {
    return new Tree(name, price, strategy);
}