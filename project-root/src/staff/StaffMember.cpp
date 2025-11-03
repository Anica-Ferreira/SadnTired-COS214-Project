/**
 * @class [StaffMember]
 * @brief [Implementation of the StaffMember base class for all staff types]
 * @details [Provides base functionality for staff operations including mediator and observer patterns]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "StaffMember.h"

/**
 * @brief [Constructs a new StaffMember object]
 * @param[in,out] name [The name of the staff member]
 * @param[in,out] role [The role of the staff member]
 */
StaffMember::StaffMember(std::string name, std::string role) : name_(name), role_(role) {
    std::cout << "StaffMember created: " << name_ << " (" << role_ << ")" << std::endl;
}//init name and role

/**
 * @brief [Handles notifications from the mediator pattern]
 * @param[in] sender [Pointer to the colleague sending the notification]
 * @param[in] request [The request message from the sender]
 */
void StaffMember::notify(IColleague* sender, std::string request) {//For Mediator
    std::string response = processRequest(request);
    std::cout << name_ << " processes request and sends response back to " << sender->getName() << ": " << response << std::endl;
}// process request

/**
 * @brief [Handles updates from the observer pattern]
 * @param[in,out] message [The update message from the subject]
 */
void StaffMember::Update(std::string message) {//For Observer
    std::cout << name_ << " received notification: " << message << std::endl;
    // Extension: Execute a command for plant need
    StaffAction* action = new StaffAction();
    action->setOnStart(new StaffReaction("handle_plant_need"));
    action->doCommand("plant");
    delete action;
}

/**
 * @brief [Executes the staff work cycle template method]
 */
void StaffMember::templateWorkCycle() {
    std::cout << "=== " << name_ << " (" << role_ << ") Work Cycle ===" << std::endl;
    mainDuty();
    workDuty();
    subDuty();
    std::cout << "=== Work Cycle Complete ===" << std::endl;
}

/**
 * @brief [Gets the name of the staff member]
 * @return [The staff member's name]
 */
std::string StaffMember::getName() const { return name_; }