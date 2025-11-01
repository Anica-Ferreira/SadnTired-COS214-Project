/**
 * @class [StaffSalesman]
 * @brief [Implementation of the StaffSalesman class for sales staff operations]
 * @details [Handles sales-related staff duties and customer interactions]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "StaffSalesman.h"

/**
 * @brief [Constructs a new StaffSalesman object]
 * @param[in] name [The name of the sales staff member]
 */
StaffSalesman::StaffSalesman(std::string name) : StaffMember(name, "Salesman") {}

/**
 * @brief [Processes customer requests for sales staff]
 * @param[in,out] request [The customer request to process]
 * @return [Response string for the customer request]
 */
std::string StaffSalesman::processRequest(std::string request) {
    // Extension: Handle more request types
    if (request.find("advice") != std::string::npos) {
        return "Here's some sales advice!";
    }
    return "Sales advice for: " + request;
}

/**
 * @brief [Performs the main duty of sales staff]
 */
void StaffSalesman::mainDuty() {
    std::cout << "  [Main] " << name_ << ": Greeting customers" << std::endl;
}

/**
 * @brief [Performs the work duty of sales staff]
 */
void StaffSalesman::workDuty() {
    std::cout << "  [Work] " << name_ << ": Selling plants" << std::endl;
}

/**
 * @brief [Performs the sub duty of sales staff]
 */
void StaffSalesman::subDuty() {
    std::cout << "  [Sub] " << name_ << ": Stocking shelves" << std::endl;
}