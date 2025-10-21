#ifndef BACKEND_ASKHELPCOMMAND_H
#define BACKEND_ASKHELPCOMMAND_H

using namespace std;
#include "CustomerCommand.h"
#include <iostream>
#include <string>

class AskHelpCommand : public CustomerCommand{
private:
    string helpQuery;
public:
    AskHelpCommand(Customer* cust, const string& query);
    void execute() override;
    string getDescription() const override;
};

#endif //BACKEND_ASKHELPCOMMAND_H