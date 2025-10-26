#include "StaffSalesman.h"

StaffSalesman::StaffSalesman(std::string name) : StaffMember(name, "Salesman") {}

std::string StaffSalesman::processRequest(std::string request) {
    // Extension: Handle more request types
    if (request.find("advice") != std::string::npos) {
        return "Here's some sales advice!";
    }
    return "Sales advice for: " + request;
}

void StaffSalesman::mainDuty() {
    std::cout << "  [Main] " << name_ << ": Greeting customers" << std::endl;
}

void StaffSalesman::workDuty() {
    std::cout << "  [Work] " << name_ << ": Selling plants" << std::endl;
}

void StaffSalesman::subDuty() {
    std::cout << "  [Sub] " << name_ << ": Stocking shelves" << std::endl;
}