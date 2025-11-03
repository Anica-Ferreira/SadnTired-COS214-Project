#ifndef STAFFSALESMAN_H
#define STAFFSALESMAN_H

#include "StaffMember.h"
#include <string>

class StaffSalesman : public StaffMember {
public:
    StaffSalesman(std::string name);

    std::string processRequest(std::string request) override;

    void mainDuty() override;

    void workDuty() override;

    void subDuty() override;
};

#endif // STAFFSALESMAN_H