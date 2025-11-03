/**
 * @class [CustomerCommand]
 * @brief [Implementation of customer command classes]
 * @details [Implements various command patterns for customer operations in the nursery system]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "CustomerCommand.h"
#include <iostream>

// PurchasePlantCommand Implementation

/**
 * @brief [Constructs a new PurchasePlantCommand object]
 * @param[in] plant [Name of the plant to purchase]
 * @param[in] qty [Quantity to purchase]
 * @param[in] fac [Pointer to the nursery system facade]
 */
PurchasePlantCommand::PurchasePlantCommand(Plant* p, DecorativePot::PotType pt, GiftWrapping::WrappingType w, int qty, NurserySystemFacade* f)
        : plant(p), pot(pt), wrap(w), quantity(qty), facade(f) {}

/**
 * @brief [Executes the plant purchase command]
 * @param[in] customer [Pointer to the customer executing the command]
 * @return [Result message of the purchase operation]
 */

string PurchasePlantCommand::execute(Customer* customer) {
    if (!facade || !customer) {
        return "Error: System not available.";
    }

    ShoppingCart* cart = facade->getCart();
    if (!cart || cart->getItems().empty()) {
        return "Your cart is empty. Nothing to purchase.";
    }

    double total = 0.0;
    for (Product* product : cart->getItems()) {
        if (product) total += product->getPrice();
    }

    cout << "\033[1;32m--- Thank you for your purchase! ---\n\033[0m";
    cout << "Total amount paid: R" << fixed << setprecision(2) << total << "\n\n";

    cart->clear();

    return "Purchase completed successfully.";
}

/**
 * @brief [Gets the purchase description of this command]
 * @return [Command description string]
 */
string PurchasePlantCommand::getDescription() const {
    return "Purchase " + to_string(quantity) + " " + plant->getName() + "(s)";
}

// CheckStockCommand Implementation

/**
 * @brief [Constructs a new CheckStockCommand object]
 * @param[in] plant [Name of the plant to check stock for]
 * @param[in] fac [Pointer to the nursery system facade]
 */
CheckStockCommand::CheckStockCommand(const string& plant, NurserySystemFacade* fac)
    : plantName(plant), facade(fac) {}

/**
 * @brief [Executes the stock check command]
 * @param[in] customer [Pointer to the customer executing the command]
 * @return [Stock information message]
 */
string CheckStockCommand::execute(Customer* customer) {
    if (facade) {
        return facade->checkPlantStock(plantName);
    }
    return "Error: System not available";
}

/**
 * @brief [Gets the stock description of this command]
 * @return [Command description string]
 */
string CheckStockCommand::getDescription() const {
    return "Check stock for " + plantName;
}

// GetPlantInfoCommand Implementation

/**
 * @brief [Constructs a new GetPlantInfoCommand object]
 * @param[in] plant [Name of the plant to get information for]
 * @param[in] fac [Pointer to the nursery system facade]
 */
GetPlantInfoCommand::GetPlantInfoCommand(const string& plant, NurserySystemFacade* fac)
    : plantName(plant), facade(fac) {}

/**
 * @brief [Executes the plant information retrieval command]
 * @param[in] customer [Pointer to the customer executing the command]
 * @return [Plant information message]
 */
string GetPlantInfoCommand::execute(Customer* customer) {
    Plant* plant = facade->getShopInventory()->get(plantName);
    if(!plant) {
        cout << "Plant not found.\n";
        return "";
    }

    int stock = facade->getShopInventory()->getQuantity(plant->getName());
    plant->printSummary(stock);

    return "";
}

/**
 * @brief [Gets the information information of this command]
 * @return [Command description string]
 */
string GetPlantInfoCommand::getDescription() const {
    return "Get information for " + plantName;
}

// AskQuestionCommand Implementation

/**
 * @brief [Constructs a new AskQuestionCommand object]
 * @param[in] quest [The question to ask staff]
 * @param[in] fac [Pointer to the nursery system facade]
 */
AskQuestionCommand::AskQuestionCommand(const string& quest, NurserySystemFacade* fac)
    : question(quest), facade(fac) {}

/**
 * @brief [Executes the staff question command]
 * @param[in] customer [Pointer to the customer executing the command]
 * @return [Response message from staff]
 */
string AskQuestionCommand::execute(Customer* customer) {
    if (facade && customer) {
        return facade->askStaffQuestion(question);
    }
    return "Error: System not available";
}

/**
 * @brief [Gets the question description of this command]
 * @return [Command description string]
 */
string AskQuestionCommand::getDescription() const {
    return "Ask question: " + question;
}

// RequestRecommendationCommand Implementation

/**
 * @brief [Constructs a new RequestRecommendationCommand object]
 * @param[in] sun [Sunlight condition for recommendation]
 * @param[in] sp [Space availability for recommendation]
 * @param[in] exp [User experience level for recommendation]
 * @param[in] fac [Pointer to the nursery system facade]
 */
RequestRecommendationCommand::RequestRecommendationCommand(const string& sun, const string& sp,
                                                         const string& exp, NurserySystemFacade* fac)
    : sunlight(sun), space(sp), experience(exp), facade(fac) {}

/**
 * @brief [Executes the plant recommendation command]
 * @param[in] customer [Pointer to the customer executing the command]
 * @return [Plant recommendation message]
 */
string RequestRecommendationCommand::execute(Customer* customer) {
    if (facade) {
        return facade->requestPlantRecommendation(sunlight, space, experience);
    }
    return "Error: System not available";
}

/**
 * @brief [Gets the recommendation description of this command]
 * @return [Command description string]
 */
string RequestRecommendationCommand::getDescription() const {
    return "Request plant recommendation for conditions: " + sunlight + " light, " + space + " space, " + experience + " experience";
}