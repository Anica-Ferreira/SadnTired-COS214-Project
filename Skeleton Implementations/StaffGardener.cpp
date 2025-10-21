#include "StaffGardener.h"

StaffGardener::StaffGardener(string name,Customer& customer): StaffMember(name, "Manager", customer) {}

void StaffGardener::mainDuty() {
    cout << "Gardener " << this->getName() << " has tended to plants in greenhouse" << endl;
}

void StaffGardener::subDuty() {
    cout << "Gardener: " << getName() << " does some tool maintenance" << endl;
}

void StaffGardener::workDuty() {
    cout << "Gardener: " << getName() << " has gone to help a plant that needed extra help after notified" << endl;
}