#include "StaffManager.h"

StaffManager::StaffManager(string name, Customer& customer): StaffMember(name, "Manager", customer) {}

void StaffManager::mainDuty() {
    cout << "Manager " << this->getName() << " has led team of employees" << endl;
}

void StaffManager::subDuty() {
    cout << "Manager: " << getName() << " has made reports and budget" << endl;
}

void StaffManager::workDuty() {
    cout << "Manager: " << getName() << " has worked in Greenhouse and made sure all plants are healthy" << endl;
}
