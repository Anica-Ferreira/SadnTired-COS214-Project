#ifndef STAFFGARDENER_H
#define STAFFGARDENER_H
#include "StaffMember.h"


class StaffGardener : public StaffMember{
public:
    StaffGardener(string name, Customer& customer);

    void mainDuty() override;
    void subDuty() override;
    void workDuty() override;
};


#endif //STAFFGARDENER_H