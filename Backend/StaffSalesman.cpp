#include "StaffSalesman.h"

StaffSalesman::StaffSalesman(string name, Customer& customer): StaffMember(name, "Manager", customer) {}

void StaffSalesman::mainDuty() {
    cout << "Salesman " << this->getName() << " has helped sell another plant" << endl;
}

void StaffSalesman::subDuty() {
    cout << "Salesman: " << getName() << " helped stock inventory" << endl;
}

void StaffSalesman::workDuty() {
    cout << "Salesman: " << getName() << " has helped Customers buy and help with Customer requests" << endl;
}