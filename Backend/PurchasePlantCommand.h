#ifndef BACKEND_PURCHASEPLANTCOMMAND_H
#define BACKEND_PURCHASEPLANTCOMMAND_H

using namespace std;
#include "CustomerCommand.h"
#include <iostream>
#include <string>

class PurchasePlantCommand : public CustomerCommand {
private:
    string plantName;
    int quantity;
public:
    PurchasePlantCommand(Customer* cust, const string& plant, int qty = 1);
    void execute() override;
    string getDescription() const override;
};

#endif //BACKEND_PURCHASEPLANTCOMMAND_H