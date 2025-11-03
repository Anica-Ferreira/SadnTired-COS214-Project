/**
 * @class [PlantFactory]
 * @brief [Implementation of plant factory classes]
 * @details [Implements the Factory Method pattern for creating different types of plants]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "PlantFactory.h"

/**
 * @brief [Creates a new succulent plant]
 * @param[in] name [Plant name]
 * @param[in] price [Plant price]
 * @param[in] description [Plant description]
 * @return [Pointer to the created succulent plant]
 */
Plant* SucculentFactory::createPlant(const string& name, double price, const string& description) {
    return new Succulent(name, price, new LightWatering(), description);
}

/**
 * @brief [Creates a new flower plant]
 * @param[in] name [Plant name]
 * @param[in] price [Plant price]
 * @param[in] description [Plant description]
 * @return [Pointer to the created flower plant]
 */
Plant* FlowerFactory::createPlant(const string& name, double price, const string& description) {
    return new Flower(name, price, new RegularWatering(), description);
}

/**
 * @brief [Creates a new tree plant]
 * @param[in] name [Plant name]
 * @param[in] price [Plant price]
 * @param[in] description [Plant description]
 * @return [Pointer to the created tree plant]
 */
Plant* TreeFactory::createPlant(const string& name, double price, const string& description) {
    return new Tree(name, price, new HeavyWatering(), description);
}
