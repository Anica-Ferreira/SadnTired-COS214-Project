#ifndef STAFFSALESMAN_H
#define STAFFSALESMAN_H

#include "StaffMember.h"
#include <string>
#include <istream>

using namespace std;

class StaffSalesman : public StaffMember {
public:
    StaffSalesman(string name);
    string processRequest(string request) override;

    void mainDuty() override;
    void workDuty() override;
    void subDuty() override;
};

#endif