#include "StaffGardener.h"

StaffGardener::StaffGardener(std::string name) : StaffMember(name, "Gardener") {}

std::string StaffGardener::processRequest(std::string request) {
    return "Gardening tip for: " + request;
}

void StaffGardener::mainDuty() {
    std::cout << "  [Main] " << name_ << ": Checking plants" << std::endl;
}

void StaffGardener::workDuty() {
    std::cout << "  [Work] " << name_ << ": Watering and feeding" << std::endl;
}

void StaffGardener::subDuty() {
    std::cout << "  [Sub] " << name_ << ": Pruning" << std::endl;
}