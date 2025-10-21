#ifndef BACKEND_REFUNDCOMMAND_H
#define BACKEND_REFUNDCOMMAND_H

using namespace std;
#include "CustomerCommand.h"
#include <iostream>
#include <string>

class RefundCommand : public CustomerCommand {
private:
    string reason;
    string plantName;
public:
    RefundCommand(Customer* cust, const string& plant, const string& refundReason);
    void execute() override;
    string getDescription() const override;

};
#endif //BACKEND_REFUNDCOMMAND_H