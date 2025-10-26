#ifndef STAFFSALESMAN_H
#define STAFFSALESMAN_H

#include "StaffMember.h"
#include <string>

class StaffSalesman : public StaffMember {
public:
    StaffSalesman(std::string name) : StaffMember(name, "Salesman") {}

    std::string processRequest(std::string request) override {
        // Extension: Handle more request types
        if (request.find("advice") != std::string::npos) {
            return "Here's some sales advice!";
        }
        return "Sales advice for: " + request;
    }

    void mainDuty() override {
        std::cout << "  [Main] " << name_ << ": Greeting customers" << std::endl;
    }

    void workDuty() override {
        std::cout << "  [Work] " << name_ << ": Selling plants" << std::endl;
    }

    void subDuty() override {
        std::cout << "  [Sub] " << name_ << ": Stocking shelves" << std::endl;
    }
};

#endif // STAFFSALESMAN_H