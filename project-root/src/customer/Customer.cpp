/**
 * @class [Customer]
 * @brief [Implementation of the Customer class for managing customer data and actions]
 * @details [Handles customer operations including command execution and mediator communication]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "Customer.h"
#include "CustomerCommand.h"
#include <iostream>

/**
 * @brief [Constructs a new Customer object with default values]
 */
Customer::Customer() : name(""), surname(""), email(""), phoneNum("") {}

/**
 * @brief [Constructs a new Customer object with specified details]
 * @param[in] customerName [Customer's first name]
 * @param[in] customerSurname [Customer's last name]
 * @param[in] customerEmail [Customer's email address]
 * @param[in] customerPhone [Customer's phone number]
 */
Customer::Customer(const string& customerName, const string& customerSurname,
                   const string& customerEmail, const string& customerPhone)
    : name(customerName), surname(customerSurname),
      email(customerEmail), phoneNum(customerPhone) {

    //cout << "Customer created: " << getName() << " (" << email << ")" << endl;
}

/**
 * @brief [Destroys the Customer object and cleans up resources]
 */
Customer::~Customer() {
    cleanup();
}

/**
 * @brief [Cleans up command history and resources]
 */
void Customer::cleanup() {
    for (auto command : commandHistory) {
        delete command;
    }
    commandHistory.clear();
}

/**
 * @brief [Executes a customer command]
 * @param[in] command [Pointer to the command to execute]
 */
void Customer::executeCommand(CustomerCommand* command) {
    if (command) {
        commandHistory.push_back(command);
        command->execute(this);
        // Note: command is NOT deleted here - manager handles cleanup
    }
}

/**
 * @brief [Displays the command execution history]
 */
void Customer::showCommandHistory() const {
    cout << "=== Command History for " << getName() << " ===" << endl;
    for (size_t i = 0; i < commandHistory.size(); i++) {
        cout << i + 1 << ". " << commandHistory[i]->getDescription() << endl;
    }
}

// These methods will be called by commands

/**
 * @brief [Simulates purchasing a plant]
 * @param[in,out] plantName [Name of the plant to purchase]
 * @param[in,out] quantity [Number of plants to purchase]
 * @return [Status message about the purchase]
 */
string Customer::purchasePlant(const string& plantName, int quantity) {
    return "Customer " + getName() + " purchasing " + to_string(quantity) + " of " + plantName;
}

/**
 * @brief [Requests plant care services]
 * @param[in,out] plantName Name of the plant needing care
 * @param[in,out] careType [Type of care requested]
 * @return [Status message about the care request]
 */
string Customer::requestPlantCare(const string& plantName, const string& careType) {
    return "Customer " + getName() + " requesting " + careType + " for " + plantName;
}

/**
 * @brief [Checks stock for a specific plant]
 * @param[in,out] plantName [Name of the plant to check]
 * @return [Stock information message]
 */
string Customer::checkPlantStock(const string& plantName) {
    return "Customer " + getName() + " checking stock for " + plantName;
}

/**
 * @brief [Requests a refund for a plant]
 * @param[in,out] plantName [Name of the plant for refund]
 * @param[in,out] reason [Reason for the refund request]
 * @return [Refund request status message]
 */
string Customer::requestRefund(const string& plantName, const string& reason) {
    return "Customer " + getName() + " requesting refund for " + plantName + " - Reason: " + reason;
}

/**
 * @brief [Gets information about a specific plant]
 * @param[in,out] plantName [Name of the plant to get info for]
 * @return [Plant information message]
 */
string Customer::getPlantInfo(const string& plantName) {
    return "Customer " + getName() + " getting info for " + plantName;
}

/**
 * @brief [Sets the mediator for communication]
 * @param[in] mediator [Pointer to the mediator interface]
 */
void Customer::setMediator(IMediator* mediator) {
    mediator_ = mediator;
}//set mediator pointer

/**
 * @brief [Sends a request through the mediator]
 * @param [request The request message to send]
 */
void Customer::sendRequest(std::string request) {
    if (mediator_) {
        std::cout << name<< " sends request: " << request << std::endl;
        mediator_->notify(this, request);
    } else {
        std::cout << name<< ": No mediator set!" << std::endl;
    }
}//check if mediator exists, if yes, print send message and call mediator's notify with self and request, else error.