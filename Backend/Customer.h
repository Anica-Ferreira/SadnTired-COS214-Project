#ifndef CUSTOMER_H
#define CUSTOMER_H

using namespace std;
#include <list>
#include <vector>
#include <string>
#include <iostream>

#include "ObserverMediator.h"
#include "SubjectColleague.h"
#include "Facade.h"

class RequestSystem;
class CustomerCommand;

class Customer : public SubjectColleague {
private:
    std::list<ObserverMediator*> list_observer_;
    std::string message_;
    std::vector<CustomerCommand*> commandHistory;
    RequestSystem* requestSystem;
    Facade* nurseryFacade;
public:
    Customer();
    ~Customer();

    void Attach(ObserverMediator* observer) override;
    void Detach(ObserverMediator* observer) override;
    void Notify() override;

    void CreateMessage(std::string message = "Default Message");

    // Command execution methods
    void executeCommand(CustomerCommand* command);
    void showCommandHistory() const;

    // Chain of Responsibility method
    void makeRequest(const std::string& requestType, const std::string& details);

    // Facade methods
    void useFacadePurchase(const std::string& plantName, int quantity, double price);
    void useFacadeCare(const std::string& plantName, const std::string& careType);
    void useFacadeCheckStock(const std::string& plantName);
    void useFacadeRefund(const std::string& plantName, const std::string& reason);
    void useFacadeGetInfo(const std::string& plantName);
    
    void doA();
    void doB();
};

#endif // CUSTOMER_H