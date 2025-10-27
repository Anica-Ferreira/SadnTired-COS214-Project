// Customer.cpp - UPDATED
#include "Customer.h"
#include "CustomerCommand.h"
#include <iostream>

Customer::Customer() : name(""), surname(""), email(""), phoneNum("") {}

Customer::Customer(const string& customerName, const string& customerSurname,
                   const string& customerEmail, const string& customerPhone)
    : name(customerName), surname(customerSurname),
      email(customerEmail), phoneNum(customerPhone) {

    cout << "Customer created: " << getName() << " (" << email << ")" << endl;
}

Customer::~Customer() {
    cleanup();
}

void Customer::cleanup() {
    for (auto command : commandHistory) {
        delete command;
    }
    commandHistory.clear();
}

void Customer::executeCommand(CustomerCommand* command) {
    if (command) {
        commandHistory.push_back(command);
        command->execute(this);
        // Note: command is NOT deleted here - manager handles cleanup
    }
}

void Customer::showCommandHistory() const {
    cout << "=== Command History for " << getName() << " ===" << endl;
    for (size_t i = 0; i < commandHistory.size(); i++) {
        cout << i + 1 << ". " << commandHistory[i]->getDescription() << endl;
    }
}

// These methods will be called by commands
string Customer::purchasePlant(const string& plantName, int quantity) {
    return "Customer " + getName() + " purchasing " + to_string(quantity) + " of " + plantName;
}

string Customer::requestPlantCare(const string& plantName, const string& careType) {
    return "Customer " + getName() + " requesting " + careType + " for " + plantName;
}

string Customer::checkPlantStock(const string& plantName) {
    return "Customer " + getName() + " checking stock for " + plantName;
}

string Customer::requestRefund(const string& plantName, const string& reason) {
    return "Customer " + getName() + " requesting refund for " + plantName + " - Reason: " + reason;
}

string Customer::getPlantInfo(const string& plantName) {
    return "Customer " + getName() + " getting info for " + plantName;
}