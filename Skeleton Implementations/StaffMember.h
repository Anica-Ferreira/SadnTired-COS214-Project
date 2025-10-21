#ifndef STAFFMEMBER_H
#define STAFFMEMBER_H

#include <string>
#include <iostream>

#include "Customer.h"
#include "ObserverMediator.h"

using namespace std;



class StaffMember : public ObserverMediator{//template method to specify which type of employee this is
protected:
    string name;
    string role;
    string message_from_subject_;
    Customer& customer_;
    Customer* component;

    virtual void mainDuty() = 0;
    virtual void workDuty() = 0;
    virtual void subDuty() = 0;
public:
    StaffMember(string name, string role, Customer& customer);
    ~StaffMember() = default;
    string getName();
    string getRole();
    void templateWorkCycle();

    void Update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        customer_.Detach(this);
        std::cout << "Observer: " << getName() << " removed from the list.\n";
    }

    void PrintInfo() {
        std::cout << "Observer: " << getName() << ", a new message is available --> " << this->message_from_subject_ << "\n";
    }

    void notify(SubjectColleague *colleague, string event) override;

    void action(string type);

};


#endif //STAFFMEMBER_H