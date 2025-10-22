#include "Customer.h"
#include "RequestSystem.h"
#include "CustomerCommand.h"
#include "Facade.h"      // if you call methods on nurseryFacade


Customer::Customer() : requestSystem(new RequestSystem()), nurseryFacade(new Facade()) {
    // Constructor implementation
}

Customer::~Customer() {
    // Clean up command history
    for (auto cmd : commandHistory) {
        delete cmd;
    }
    // Clean up systems
    delete requestSystem;
    delete nurseryFacade;
}

void Customer::Attach(ObserverMediator* observer) {
    list_observer_.push_back(observer);
}

void Customer::Detach(ObserverMediator* observer) {
    list_observer_.remove(observer);
}

void Customer::Notify() {
    std::list<ObserverMediator*>::iterator it = list_observer_.begin();
    while (it != list_observer_.end()) {
        (*it)->Update(message_);
        it++;
    }
}

void Customer::CreateMessage(std::string message) {
    this->message_ = message;
    Notify();
}

void Customer::executeCommand(CustomerCommand* command) {
    commandHistory.push_back(command);
    command->execute();
}

void Customer::showCommandHistory() const {
    std::cout << "Customer Command History:" << std::endl;
    for (const auto& cmd : commandHistory) {
        std::cout << " - " << cmd->getDescription() << std::endl;
    }
}

void Customer::makeRequest(const std::string& requestType, const std::string& details) {
    requestSystem->processCustomerRequest(requestType, this, details);
}

void Customer::doA() {
    std::cout << "Customer: 'Can you help do A?' " << std::endl;
    this->mediator_->notify(this, "Customer Interaction A");
}

void Customer::doB() {
    std::cout << "Customer: 'What about B?' " << std::endl;
    this->mediator_->notify(this, "Customer Interaction B");
}

void Customer::useFacadePurchase(const std::string& plantName, int quantity, double price) {
    std::cout << "Customer using facade to purchase plants..." << std::endl;
    nurseryFacade->purchasePlant(plantName, quantity, price);
}

void Customer::useFacadeCare(const std::string& plantName, const std::string& careType) {
    std::cout << "Customer using facade for plant care..." << std::endl;
    nurseryFacade->requestPlantCare(plantName, careType);
}

void Customer::useFacadeCheckStock(const std::string& plantName) {
    std::cout << "Customer using facade to check stock..." << std::endl;
    nurseryFacade->checkPlantStock(plantName);
}

void Customer::useFacadeRefund(const std::string& plantName, const std::string& reason) {
    std::cout << "Customer using facade for refund..." << std::endl;
    nurseryFacade->processRefund(plantName, reason);
}

void Customer::useFacadeGetInfo(const std::string& plantName) {
    std::cout << "Customer using facade to get plant info..." << std::endl;
    nurseryFacade->getPlantInfo(plantName);
}