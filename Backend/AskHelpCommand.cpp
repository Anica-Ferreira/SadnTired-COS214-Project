#include "AskHelpCommand.h"

AskHelpCommand::AskHelpCommand(Customer* cust, const string& query)
    : CustomerCommand(cust, "AskHelp"), helpQuery(query) {}

void AskHelpCommand::execute() {
    cout << "Customer is asking for help: " << helpQuery << endl;
    // Notify staff through mediator
    if (customer) {
        customer->doA();  // Use existing mediator pattern
    }
}

string AskHelpCommand::getDescription() const {
    return "AskHelp: " + helpQuery;
}