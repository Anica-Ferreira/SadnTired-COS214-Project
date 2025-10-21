#include "StaffMember.h"

StaffMember::StaffMember(string name, string role, Customer& customer) : customer_(customer) {
    this->name = name;
    this->role = role;
    this->customer_.Attach(this);
    this->customer_.setMediator(this);
}

string StaffMember::getName() {
    return name;
}

string StaffMember::getRole() {
    return role;
}

void StaffMember::templateWorkCycle() {
    cout << "StaffMember now working:" << endl;
    this->mainDuty();
    this->workDuty();
    this->subDuty();
    cout << endl;
}

void StaffMember::notify(SubjectColleague *colleague, string event) {
    if (event == "Customer Interaction A") {
        cout << "Staff Member interacts with Customer in a specific way" << endl;
    }
    else if (event == "Customer Interaction B") {
        cout << "Staff Member interacts with Customer in another type of way" << endl;
    }
}

void StaffMember::action(string type) {

}