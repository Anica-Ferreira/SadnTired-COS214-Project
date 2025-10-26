#include "PlantFactory.h"

Plant* SucculentFactory::createPlant(const std::string& name, double price, const std::string& description) {
    return new Succulent(name, price, new LightWatering(), description);
}

Plant* FlowerFactory::createPlant(const std::string& name, double price, const std::string& description) {
    return new Flower(name, price, new RegularWatering(), description);
}

Plant* TreeFactory::createPlant(const std::string& name, double price, const std::string& description) {
    return new Tree(name, price, new HeavyWatering(), description);
}
