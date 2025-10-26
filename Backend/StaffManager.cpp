#include "StaffManager.h"

StaffManager::StaffManager(std::string name) : StaffMember(name, "Manager") {}

std::string StaffManager::processRequest(std::string request)  {
    return "Manager handling: " + request;
}

void StaffManager::mainDuty()  {
    std::cout << "  [Main] " << name_ << ": Overseeing operations" << std::endl;
}

void StaffManager::workDuty()  {
    std::cout << "  [Work] " << name_ << ": Managing team" << std::endl;
}

void StaffManager::subDuty()  {
    std::cout << "  [Sub] " << name_ << ": Administrative tasks" << std::endl;
}