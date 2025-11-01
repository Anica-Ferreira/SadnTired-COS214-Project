/**
 * @class [StaffAction]
 * @brief [Implementation of the StaffAction class for staff command sequences]
 * @details [Manages command execution sequences for staff actions with start/finish hooks]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "StaffAction.h"

/**
 * @brief [Sets the command to execute at the start of the action]
 * @param[in] cmd [Pointer to the start command]
 */
void StaffAction::setOnStart(StaffCommand* cmd) {
    onStart_ = cmd;
}

/**
 * @brief [Sets the command to execute at the finish of the action]
 * @param[in] cmd [Pointer to the finish command]
 */
void StaffAction::setOnFinish(StaffCommand* cmd) {
    onFinish_ = cmd;
}

/**
 * @brief [Executes the complete command sequence]
 * @param[in] type [The type of action to perform]
 */
void StaffAction::doCommand(std::string type) {
    if (onStart_) onStart_->execute(type);
    std::cout << "Performing main action..." << std::endl;//can be removed and replaced with onStart only
    if (onFinish_) onFinish_->execute(type);
}

/**
 * @brief [Destroys the StaffAction object and cleans up commands]
 */
StaffAction::~StaffAction() {
    delete onStart_;
    delete onFinish_;
}