#ifndef PLANT_FACTORY_H
#define PLANT_FACTORY_H

#include "Plant.h"
#include "WateringStrategy.h"
#include <string>

class PlantFactory {
public:
    virtual ~PlantFactory() {}
    virtual Plant* createPlant(const std::string& name, double price, const std::string& description = "") = 0;
};

class SucculentFactory : public PlantFactory {
public:
    Plant* createPlant(const std::string& name, double price, const std::string& description = "") override;
};

class FlowerFactory : public PlantFactory {
public:
    Plant* createPlant(const std::string& name, double price, const std::string& description = "") override;
};

class TreeFactory : public PlantFactory {
public:
    Plant* createPlant(const std::string& name, double price, const std::string& description = "") override;
};

#endif // PLANT_FACTORY_H
