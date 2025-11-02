#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

#include "StaffMember.h"
#include <iostream>
#include <string>

using namespace std;

class StaffManager : public StaffMember {
public:
    StaffManager(string name);

    string processRequest(string request) override;

    void mainDuty() override ;

    void workDuty() override;

    void subDuty() override;
};

#endif // STAFFMANAGER_H