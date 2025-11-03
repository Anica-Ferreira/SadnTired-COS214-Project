/**
 * @class [StaffManager]
 * @brief [Implementation of the StaffManager class for management staff operations]
 * @details [Handles management-level staff duties and administrative tasks]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "StaffManager.h"

/**
 * @brief [Constructs a new StaffManager object]
 * @param[in] name [The name of the management staff member]
 */
StaffManager::StaffManager(std::string name) : StaffMember(name, "Manager") {}

/**
 * @brief [Processes customer requests for management staff]
 * @param[in,out] request [The customer request to process]
 * @return [Response string for the customer request]
 */
std::string StaffManager::processRequest(std::string request)  {
    return "Manager handling: " + request;
}

/**
 * @brief [Performs the main duty of management staff]
 */
void StaffManager::mainDuty()  {
    std::cout << "  [Main] " << name_ << ": Overseeing operations" << std::endl;
}

/**
 * @brief [Performs the work duty of management staff]
 */
void StaffManager::workDuty()  {
    std::cout << "  [Work] " << name_ << ": Managing team" << std::endl;
}

/**
 * @brief [Performs the sub duty of management staff]
 */
void StaffManager::subDuty()  {
    std::cout << "  [Sub] " << name_ << ": Administrative tasks" << std::endl;
}