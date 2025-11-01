#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

#include "StaffMember.h"
#include <string>

class StaffManager : public StaffMember {
public:
    StaffManager(std::string name);

    std::string processRequest(std::string request) override;

    void mainDuty() override ;

    void workDuty() override;

    void subDuty() override;
};

#endif // STAFFMANAGER_H