// CustomerCommand.h - NEW FILE
#ifndef CUSTOMER_COMMAND_H
#define CUSTOMER_COMMAND_H

#include <string>
#include "../customer/Customer.h"
#include "../core/NurserySystemFacade.h"

using namespace std;

class Customer;
class NurserySystemFacade;

class CustomerCommand {
public:
    virtual ~CustomerCommand() {}
    virtual string execute(Customer* customer) = 0;
    virtual string getDescription() const = 0;
};

// Concrete Commands
class PurchasePlantCommand : public CustomerCommand {
private:
    string plantName;
    int quantity;
    NurserySystemFacade* facade;
    
public:
    PurchasePlantCommand(const string& plant, int qty, NurserySystemFacade* fac);
    string execute(Customer* customer) override;
    string getDescription() const override;
};

class CheckStockCommand : public CustomerCommand {
private:
    string plantName;
    NurserySystemFacade* facade;
    
public:
    CheckStockCommand(const string& plant, NurserySystemFacade* fac);
    string execute(Customer* customer) override;
    string getDescription() const override;
};

class GetPlantInfoCommand : public CustomerCommand {
private:
    string plantName;
    NurserySystemFacade* facade;
    
public:
    GetPlantInfoCommand(const string& plant, NurserySystemFacade* fac);
    string execute(Customer* customer) override;
    string getDescription() const override;
};

class AskQuestionCommand : public CustomerCommand {
private:
    string question;
    NurserySystemFacade* facade;
    
public:
    AskQuestionCommand(const string& quest, NurserySystemFacade* fac);
    string execute(Customer* customer) override;
    string getDescription() const override;
};

class RequestRecommendationCommand : public CustomerCommand {
private:
    string sunlight;
    string space;
    string experience;
    NurserySystemFacade* facade;
    
public:
    RequestRecommendationCommand(const string& sun, const string& sp, 
                               const string& exp, NurserySystemFacade* fac);
    string execute(Customer* customer) override;
    string getDescription() const override;
};

#endif