/**
 * @class [PlantState]
 * @brief [Implementation of plant state classes for state management]
 * @details [Handles plant state transitions and behavior based on current state]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "PlantState.h"
#include "Plant.h"
#include "WateringStrategy.h"

/**
 * @brief [Handles watering in the planted state]
 * @param[in] plant [Pointer to the plant being watered]
 */
void PlantedState::handleWatering(Plant *plant)
{
    plant->getStrategy()->water(plant);
    if (plant->isReadyForSale()) {
        plant->setState(new ReadyForSaleState());
    } else {
        plant->setState(new WateredState());
    }
}

/**
 * @brief [Handles time passage in the planted state]
 * @param[in] plant [Pointer to the plant affected by time]
 */
void PlantedState::handlePassTime(Plant *plant)
{
    double newLevel = plant->getWaterLevel() - 2.0;
    plant->setWaterLevel(newLevel < 0 ? 0 : newLevel);
    if (plant->getWaterLevel() <= 0.0) {
        plant->setState(new DryState());
    }
}

/**
 * @brief [Gets the name of the current state]
 * @return [Name of the planted state]
 */
string PlantedState::getStateName() const
{
    return "Planted";
}

/**
 * @brief [Handles watering in the watered state]
 * @param[in] plant [Pointer to the plant being watered]
 */
void WateredState::handleWatering(Plant *plant)
{
    plant->getStrategy()->water(plant);
    if (plant->isReadyForSale()) {
        plant->setState(new ReadyForSaleState());
    } else {
        plant->setState(new WateredState());
    }
}

/**
 * @brief [Handles time passage in the watered state]
 * @param[in] plant [Pointer to the plant affected by time]
 */
void WateredState::handlePassTime(Plant *plant)
{
    double newLevel = plant->getWaterLevel() - 2.0;
    plant->setWaterLevel(newLevel < 0 ? 0 : newLevel);
    if (plant->getWaterLevel() <= 0.0) {
        plant->setState(new DryState());
    }
}

/**
 * @brief [Gets the name of the current state]
 * @return [Name of the watered state]
 */
string WateredState::getStateName() const
{
    return "Watered";
}

/**
 * @brief [Handles watering in the dry state]
 * @param[in] plant [Pointer to the plant being watered]
 */
void DryState::handleWatering(Plant *plant)
{
    plant->getStrategy()->water(plant);
    if (plant->isReadyForSale()) {
        plant->setState(new ReadyForSaleState());
    } else if (plant->getWaterLevel() > 0) {
        plant->setState(new WateredState());
    }
}

/**
 * @brief [Handles time passage in the dry state]
 * @param[in] plant [Pointer to the plant affected by time]
 */
void DryState::handlePassTime(Plant *plant)
{
    plant->setWaterLevel(0.0);
}

/**
 * @brief [Gets the name of the current state]
 * @return [Name of the dry state]
 */
string DryState::getStateName() const
{
    return "Dry";
}

//???

/**
 * @brief [Handles watering in the ready for sale state]
 * @param[in] plant [Pointer to the plant being watered]
 */
void ReadyForSaleState::handleWatering(Plant *plant)
{
    // No effect
}

/**
 * @brief [Handles time passage in the ready for sale state]
 * @param[in] plant [Pointer to the plant affected by time]
 */
void ReadyForSaleState::handlePassTime(Plant *plant)
{
    // No effect
}

/**
 * @brief [Gets the name of the current state]
 * @return [Name of the ready for sale state]
 */
string ReadyForSaleState::getStateName() const
{
    return "Ready for Sale";
}