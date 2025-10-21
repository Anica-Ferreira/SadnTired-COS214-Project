#ifndef STAFFSALESMAN_H
#define STAFFSALESMAN_H
#include "StaffMember.h"


class StaffSalesman : public StaffMember {
public:
    StaffSalesman(string name, Customer& customer);

    void mainDuty() override;
    void subDuty() override;
    void workDuty() override;
};


#endif //STAFFSALESMAN_H