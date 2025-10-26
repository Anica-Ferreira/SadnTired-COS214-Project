#include "StaffMember.h"

StaffMember::StaffMember(std::string name, std::string role) : name_(name), role_(role) {
    std::cout << "StaffMember created: " << name_ << " (" << role_ << ")" << std::endl;
}//init name and role

void StaffMember::notify(IColleague* sender, std::string request) {//For Mediator
    std::string response = processRequest(request);
    std::cout << name_ << " processes request and sends response back to " << sender->getName() << ": " << response << std::endl;
}// process request

void StaffMember::Update(std::string message) {//For Observer
    std::cout << name_ << " received notification: " << message << std::endl;
    // Extension: Execute a command for plant need
    StaffAction* action = new StaffAction();
    action->setOnStart(new StaffReaction("handle_plant_need"));
    action->doCommand("plant");
    delete action;
}

void StaffMember::templateWorkCycle() {
    std::cout << "=== " << name_ << " (" << role_ << ") Work Cycle ===" << std::endl;
    mainDuty();
    workDuty();
    subDuty();
    std::cout << "=== Work Cycle Complete ===" << std::endl;
}

std::string StaffMember::getName() const { return name_; }