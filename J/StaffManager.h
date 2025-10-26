#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

#include "StaffMember.h"
#include <string>

class StaffManager : public StaffMember {
public:
    StaffManager(std::string name) : StaffMember(name, "Manager") {}

    std::string processRequest(std::string request) override {
        return "Manager handling: " + request;
    }

    void mainDuty() override {
        std::cout << "  [Main] " << name_ << ": Overseeing operations" << std::endl;
    }

    void workDuty() override {
        std::cout << "  [Work] " << name_ << ": Managing team" << std::endl;
    }

    void subDuty() override {
        std::cout << "  [Sub] " << name_ << ": Administrative tasks" << std::endl;
    }
};

#endif // STAFFMANAGER_H