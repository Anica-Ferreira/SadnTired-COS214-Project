#ifndef STAFFMEMBER_H
#define STAFFMEMBER_H

#include "IMediator.h"
#include "IObserver.h"
#include "IColleague.h"
#include "StaffCommand.h"  // For command integration
#include <iostream>
#include <string>
#include <vector>

#include "StaffAction.h"
#include "StaffReaction.h"

// Forward declaration for commands
class StaffAction;

class StaffMember : public IMediator, public IObserver {
protected:
    std::string name_;
    std::string role_;
    // Extension: Add state to StaffMember
    bool is_busy_ = false;
    std::vector<std::string> current_tasks_;//vector for queueing

public:
    StaffMember(std::string name, std::string role) : name_(name), role_(role) {
        std::cout << "StaffMember created: " << name_ << " (" << role_ << ")" << std::endl;
    }//init name and role

    virtual std::string processRequest(std::string request) = 0;//method for handling requests

    void notify(IColleague* sender, std::string request) override {//For Mediator
        if (is_busy_) {
            std::cout << getName() << ": I'm busy, please wait..." << std::endl;
            current_tasks_.push_back(request);  // Queue task
            return;
        }
        is_busy_ = true;
        std::string response = processRequest(request);
        std::cout << name_ << " processes request and sends response back to " << sender->getName() << ": " << response << std::endl;
        is_busy_ = false;
    }//checks busy, if not set to busy and process request

    void Update(std::string message) override {//For Observer
        std::cout << name_ << " received notification: " << message << std::endl;
        // Extension: Execute a command for plant need
        StaffAction* action = new StaffAction();
        action->setOnStart(new StaffReaction("handle_plant_need"));
        action->doCommand("plant");
        delete action;
    }

    virtual void templateWorkCycle() {
        std::cout << "=== " << name_ << " (" << role_ << ") Work Cycle ===" << std::endl;
        mainDuty();
        workDuty();
        subDuty();
        std::cout << "=== Work Cycle Complete ===" << std::endl;
    }

    virtual void mainDuty() = 0;
    virtual void workDuty() = 0;
    virtual void subDuty() = 0;

    std::string getName() const { return name_; }
    bool isBusy() const { return is_busy_; }
};

#endif // STAFFMEMBER_H