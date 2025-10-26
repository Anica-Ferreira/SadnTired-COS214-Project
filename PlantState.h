#ifndef PLANT_STATE_H
#define PLANT_STATE_H

#include <string>

class Plant;

class PlantState {
public:
    virtual ~PlantState() {}
    virtual void handleWatering(Plant* plant) = 0;
    virtual void handlePassTime(Plant* plant) = 0;
    virtual std::string getStateName() const = 0;
};

class PlantedState : public PlantState {
public:
    void handleWatering(Plant* plant) override;
    void handlePassTime(Plant* plant) override;
    std::string getStateName() const override;
};

class WateredState : public PlantState {
public:
    void handleWatering(Plant* plant) override;
    void handlePassTime(Plant* plant) override;
    std::string getStateName() const override;
};

class DryState : public PlantState {
public:
    void handleWatering(Plant* plant) override;
    void handlePassTime(Plant* plant) override;
    std::string getStateName() const override;
};

class ReadyForSaleState : public PlantState {
public:
    void handleWatering(Plant* plant) override;
    void handlePassTime(Plant* plant) override;
    std::string getStateName() const override;
};

#endif // PLANT_STATE_H