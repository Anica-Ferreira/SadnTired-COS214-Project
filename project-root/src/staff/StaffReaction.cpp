/**
 * @class [StaffReaction]
 * @brief [Implementation of the StaffReaction class for staff command execution]
 * @details [Handles specific staff reactions and command execution]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "StaffReaction.h"

/**
 * @brief [Constructs a new StaffReaction object]
 * @param[in] action [The action to be executed by staff]
 */
StaffReaction::StaffReaction(std::string action) : action_(action) {}

/**
 * @brief [Executes the staff reaction command]
 * @param[in,out] type [The type of action to execute]
 */
void StaffReaction::execute(std::string type) {
    std::cout << "Executing " << action_ << " for " << type << std::endl;
}