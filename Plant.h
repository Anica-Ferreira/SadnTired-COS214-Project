#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "WateringStrategy.h"
#include "PlantState.h"

class Plant {
protected:
    std::string name;
    std::string type;
    std::string description;
    double price;
    double waterLevel;
    WateringStrategy* wateringStrategy;
    PlantState* state;
    int wateringCount;
    virtual int getRequiredWaterings() const = 0;

    void increaseWateringCount();
    bool isReadyForSale() const;

public:
    Plant(const std::string& name, const std::string& type, double price, WateringStrategy* strategy,const std::string& description = "");
    virtual ~Plant();

    void water();
    void passTime();  // Simulates time passing, decreasing water level
    std::string getStateName() const;
    double getWaterLevel() const;
    void setWaterLevel(double level);
    std::string getName() const;
    std::string getType() const;
    double getPrice() const;
    std::string getDescription() const;
    WateringStrategy* getStrategy() const; // Declared here
    void setState(PlantState* newState);

    // Allow PlantState classes to access protected members
    friend class PlantState;
    friend class PlantedState;
    friend class WateredState;
    friend class DryState;
    friend class ReadyForSaleState;
};

class Succulent : public Plant {
protected:
    int getRequiredWaterings() const override;

public:
    Succulent(const std::string& name, double price, WateringStrategy* strategy, const std::string& description = "");
};

class Flower : public Plant {
protected:
    int getRequiredWaterings() const override;

public:
    Flower(const std::string& name, double price, WateringStrategy* strategy, const std::string& description = "");
};

class Tree : public Plant {
protected:
    int getRequiredWaterings() const override;

public:
    Tree(const std::string& name, double price, WateringStrategy* strategy, const std::string& description = "");
};

#endif // PLANT_H