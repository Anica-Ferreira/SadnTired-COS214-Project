// CustomerCommand.cpp - NEW FILE
#include "CustomerCommand.h"
#include "Customer.h"
#include "NurserySystemFacade.h"
#include <iostream>

// PurchasePlantCommand Implementation
PurchasePlantCommand::PurchasePlantCommand(const string& plant, int qty, NurserySystemFacade* fac)
    : plantName(plant), quantity(qty), facade(fac) {}

string PurchasePlantCommand::execute(Customer* customer) {
    if (facade && customer) {
        return facade->addToCart(plantName, quantity);
    }
    return "Error: System not available";
}

string PurchasePlantCommand::getDescription() const {
    return "Purchase " + to_string(quantity) + " " + plantName + "(s)";
}

// CheckStockCommand Implementation
CheckStockCommand::CheckStockCommand(const string& plant, NurserySystemFacade* fac)
    : plantName(plant), facade(fac) {}

string CheckStockCommand::execute(Customer* customer) {
    if (facade) {
        return facade->checkPlantStock(plantName);
    }
    return "Error: System not available";
}

string CheckStockCommand::getDescription() const {
    return "Check stock for " + plantName;
}

// GetPlantInfoCommand Implementation
GetPlantInfoCommand::GetPlantInfoCommand(const string& plant, NurserySystemFacade* fac)
    : plantName(plant), facade(fac) {}

string GetPlantInfoCommand::execute(Customer* customer) {
    if (facade) {
        return facade->getPlantInfo(plantName);
    }
    return "Error: System not available";
}

string GetPlantInfoCommand::getDescription() const {
    return "Get information for " + plantName;
}

// AskQuestionCommand Implementation
AskQuestionCommand::AskQuestionCommand(const string& quest, NurserySystemFacade* fac)
    : question(quest), facade(fac) {}

string AskQuestionCommand::execute(Customer* customer) {
    if (facade && customer) {
        return facade->askStaffQuestion(question);
    }
    return "Error: System not available";
}

string AskQuestionCommand::getDescription() const {
    return "Ask question: " + question;
}

// RequestRecommendationCommand Implementation
RequestRecommendationCommand::RequestRecommendationCommand(const string& sun, const string& sp,
                                                         const string& exp, NurserySystemFacade* fac)
    : sunlight(sun), space(sp), experience(exp), facade(fac) {}

string RequestRecommendationCommand::execute(Customer* customer) {
    if (facade) {
        return facade->requestPlantRecommendation(sunlight, space, experience);
    }
    return "Error: System not available";
}

string RequestRecommendationCommand::getDescription() const {
    return "Request plant recommendation for conditions: " + sunlight + " light, " + space + " space, " + experience + " experience";
}