#ifndef STAFFGARDENER_H
#define STAFFGARDENER_H

#include "StaffMember.h"
#include <string>

class StaffGardener : public StaffMember {
public:
    StaffGardener(std::string name);

    std::string processRequest(std::string request) override;

    void mainDuty() override;

    void workDuty() override;

    void subDuty() override;
};

#endif // STAFFGARDENER_H