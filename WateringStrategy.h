#ifndef WATERING_STRATEGY_H
#define WATERING_STRATEGY_H

class Plant;

class WateringStrategy {
public:
    virtual ~WateringStrategy() {}
    virtual void water(Plant* plant) = 0;
};

class HeavyWatering : public WateringStrategy {
public:
    void water(Plant* plant) override;
};  

class RegularWatering : public WateringStrategy {
public:
    void water(Plant* plant) override;
};

class LightWatering : public WateringStrategy {
public:
    void water(Plant* plant) override;
};

#endif // WATERING_STRATEGY_H