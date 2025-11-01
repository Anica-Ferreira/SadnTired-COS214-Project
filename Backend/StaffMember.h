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
    std::vector<std::string> current_tasks_;//vector for queueing

public:
    StaffMember(std::string name, std::string role);//init name and role

    virtual std::string processRequest(std::string request) = 0;//method for handling requests

    void notify(IColleague* sender, std::string request) override; //checks busy, if not set to busy and process request

    void Update(std::string message) override;

    virtual void templateWorkCycle();

    virtual void mainDuty() = 0;
    virtual void workDuty() = 0;
    virtual void subDuty() = 0;

    std::string getName() const;
};

#endif // STAFFMEMBER_H