/**
 * @class [StaffGardener]
 * @brief [Implementation of the StaffGardener class for gardening staff operations]
 * @details [Handles gardening-related staff duties and plant care tasks]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "StaffGardener.h"

/**
 * @brief [Constructs a new StaffGardener object]
 * @param[in] name [The name of the gardening staff member]
 */
StaffGardener::StaffGardener(std::string name) : StaffMember(name, "Gardener") {}

/**
 * @brief [Processes customer requests for gardening staff]
 * @param[in,out] request [The customer request to process]
 * @return [Response string for the customer request]
 */
std::string StaffGardener::processRequest(std::string request) {
    return "Gardening tip for: " + request;
}

/**
 * @brief [Performs the main duty of gardening staff]
 */
void StaffGardener::mainDuty() {
    std::cout << "  [Main] " << name_ << ": Checking plants" << std::endl;
}

/**
 * @brief [Performs the work duty of gardening staff]
 */
void StaffGardener::workDuty() {
    std::cout << "  [Work] " << name_ << ": Watering and feeding" << std::endl;
}

/**
 * @brief [Performs the sub duty of gardening staff]
 */
void StaffGardener::subDuty() {
    std::cout << "  [Sub] " << name_ << ": Pruning" << std::endl;
}