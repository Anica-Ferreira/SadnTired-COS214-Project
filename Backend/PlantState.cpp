#include "PlantState.h"
#include "Plant.h"
#include "WateringStrategy.h"

void PlantedState::handleWatering(Plant *plant)
{
    plant->getStrategy()->water(plant);
    plant->increaseWateringCount();
    if (plant->isReadyForSale())
    {
        plant->setState(new ReadyForSaleState());
    }
    else
    {
        plant->setState(new WateredState());
    }
}

void PlantedState::handlePassTime(Plant *plant)
{
    plant->setWaterLevel(plant->getWaterLevel() - 2.0);
    if (plant->getWaterLevel() <= 0.0)
    {
        plant->setState(new DryState());
    }
}

string PlantedState::getStateName() const
{
    return "Planted";
}

void WateredState::handleWatering(Plant *plant)
{
    plant->getStrategy()->water(plant);
    plant->increaseWateringCount();
    if (plant->isReadyForSale())
    {
        plant->setState(new ReadyForSaleState());
    }
}

void WateredState::handlePassTime(Plant *plant)
{
    double newLevel = plant->getWaterLevel() - 2.0;
    plant->setWaterLevel(newLevel < 0 ? 0 : newLevel); //for safety so that water level doesn't go under and cause bugs
    if (plant->getWaterLevel() <= 0.0)
    {
        plant->setState(new DryState());
    }
}

string WateredState::getStateName() const
{
    return "Watered";
}

void DryState::handleWatering(Plant *plant)
{
    plant->getStrategy()->water(plant);
    plant->increaseWateringCount();
    if (plant->isReadyForSale())
    {
        plant->setState(new ReadyForSaleState());
    }
    else
    {
        plant->setState(new WateredState());
    }
}

void DryState::handlePassTime(Plant *plant)
{
    plant->setWaterLevel(0.0);
}

string DryState::getStateName() const
{
    return "Dry";
}

//???
void ReadyForSaleState::handleWatering(Plant *plant)
{
    // No effect
}

void ReadyForSaleState::handlePassTime(Plant *plant)
{
    // No effect
}

string ReadyForSaleState::getStateName() const
{
    return "Ready for Sale";
}