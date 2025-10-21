#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H
#include "StaffMember.h"
#include "Customer.h"


class StaffManager : public StaffMember {
public:
    StaffManager(string name, Customer& customer);

    void mainDuty() override;
    void subDuty() override;
    void workDuty() override;
};


#endif //STAFFMANAGER_H