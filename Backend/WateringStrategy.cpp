#include "WateringStrategy.h"
#include "Plant.h"

void HeavyWatering::water(Plant* plant) {
    plant->setWaterLevel(plant->getWaterLevel() + 10.0);
}

void RegularWatering::water(Plant* plant) {
    plant->setWaterLevel(plant->getWaterLevel() + 5.0);
}

void LightWatering::water(Plant* plant) {
    plant->setWaterLevel(plant->getWaterLevel() + 2.0);
}