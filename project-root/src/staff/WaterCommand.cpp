/**
 * @class [WaterCommand]
 * @brief [Implementation of the WaterCommand class for plant watering operations]
 * @details [Handles execution of plant watering commands]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "WaterCommand.h"

/**
 * @brief [Executes the plant watering command]
 * @param[in,out] type [The type of plant to water]
 */
void execute(std::string type) {
    std::cout << "Watering plant (" << type << ")..." << std::endl;
}