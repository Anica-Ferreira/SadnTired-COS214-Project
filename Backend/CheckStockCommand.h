#ifndef BACKEND_CHECKSTOCKCOMMAND_H
#define BACKEND_CHECKSTOCKCOMMAND_H

using namespace std;
#include <iostream>
#include "CustomerCommand.h"
#include <string>

class CheckStockCommand : public CustomerCommand {
private:
    string plantName;
    
public:
    CheckStockCommand(Customer* cust, const string& plant);
    void execute() override;
    string getDescription() const override;
};

#endif //BACKEND_CHECKSTOCKCOMMAND_H