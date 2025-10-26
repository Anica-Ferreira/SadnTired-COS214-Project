#ifndef STAFFGARDENER_H
#define STAFFGARDENER_H

#include "StaffMember.h"
#include <string>

class StaffGardener : public StaffMember {
public:
    StaffGardener(std::string name) : StaffMember(name, "Gardener") {}

    std::string processRequest(std::string request) override {
        return "Gardening tip for: " + request;
    }

    void mainDuty() override {
        std::cout << "  [Main] " << name_ << ": Checking plants" << std::endl;
    }

    void workDuty() override {
        std::cout << "  [Work] " << name_ << ": Watering and feeding" << std::endl;
    }

    void subDuty() override {
        std::cout << "  [Sub] " << name_ << ": Pruning" << std::endl;
    }

};

#endif // STAFFGARDENER_H