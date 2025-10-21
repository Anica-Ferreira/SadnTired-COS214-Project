#ifndef BACKEND_BROWSEPLANTSCOMMAND_H
#define BACKEND_BROWSEPLANTSCOMMAND_H

using namespace std;
#include "CustomerCommand.h"
#include <iostream>
#include <string>

class BrowsePlantsCommand : public CustomerCommand {
public:
    BrowsePlantsCommand(Customer* cust);
    void execute() override;
    string getDescription() const override;
};

#endif //BACKEND_BROWSEPLANTSCOMMAND_H