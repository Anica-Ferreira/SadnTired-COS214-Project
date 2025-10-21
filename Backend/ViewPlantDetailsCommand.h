#ifndef BACKEND_VIEWPLANTDETAILSCOMMAND_H
#define BACKEND_VIEWPLANTDETAILSCOMMAND_H

using namespace std;
#include <iostream>
#include "CustomerCommand.h"
#include <string>

class ViewPlantDetailsCommand : public CustomerCommand {
private:
    string plantName;
public:
    ViewPlantDetailsCommand(Customer* cust, const string& plant);
    void execute() override;
    string getDescription() const override;
};

#endif //BACKEND_VIEWPLANTDETAILSCOMMAND_H