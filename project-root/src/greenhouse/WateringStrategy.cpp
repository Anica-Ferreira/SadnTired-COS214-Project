/**
 * @class [WateringStrategy]
 * @brief [Implementation of watering strategy classes for different plant types]
 * @details [Implements various watering strategies based on plant requirements]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "WateringStrategy.h"
#include "Plant.h"

/**
 * @brief [Waters a plant using heavy watering strategy]
 * @param[in,out] plant [Pointer to the plant to water]
 */
void HeavyWatering::water(Plant* plant) {
    plant->setWaterLevel(plant->getWaterLevel() + 10.0);
}

/**
 * @brief [Waters a plant using regular watering strategy]
 * @param[in,out] plant [Pointer to the plant to water]
 */
void RegularWatering::water(Plant* plant) {
    plant->setWaterLevel(plant->getWaterLevel() + 5.0);
}

/**
 * @brief [Waters a plant using light watering strategy]
 * @param[in,out] plant [Pointer to the plant to water]
 */
void LightWatering::water(Plant* plant) {
    plant->setWaterLevel(plant->getWaterLevel() + 2.0);
}