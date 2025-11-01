/**
 * @class [DecorativePot]
 * @brief [Implementation of the DecorativePot decorator class]
 * @details [Adds decorative pot functionality to plant products using the Decorator pattern]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "DecorativePot.h"

/**
 * @brief [Constructs a new DecorativePot decorator]
 * @param[in] product [Pointer to the product to decorate]
 * @param[in] type [Type of decorative pot]
 */
DecorativePot::DecorativePot(Product* product, PotType type)
    : ProductDecorator(product), type(type) {}

/**
 * @brief [Destroys the DecorativePot object]
 */    
DecorativePot::~DecorativePot() {}

/**
 * @brief [Calculates the total price including the pot]
 * @return [Total price of product plus pot]
 */
double DecorativePot::getPrice() const {
    return product->getPrice() + getPotPrice();
}

/**
 * @brief [Gets the combined name of product and pot]
 * @return [Combined name string]
 */
std::string DecorativePot::getName() const {
    return product->getName() + " + " + getPotName();
}

/**
 * @brief [Creates a deep copy of the DecorativePot object]
 * @return [Pointer to the cloned DecorativePot object]
 */
Product* DecorativePot::clone() const {
    return new DecorativePot(product->clone(), type);
}

/**
 * @brief [Gets the name of the pot type]
 * @return [Pot type name string]
 */
std::string DecorativePot::getPotName() const {
    switch (type) {
        case CLASSIC: return "Classic Pot";
        case ROTUND: return "Rotund Pot";
        case SQUARE: return "Square Pot";
        case VASE: return "Vase Pot";
        default: return "Unknown Pot";
    }
}

/**
 * @brief [Gets the price of the pot type]
 * @return [Pot price]
 */
double DecorativePot::getPotPrice() const {
    switch (type) {
        case CLASSIC: return 12.00;
        case ROTUND: return 21.00;
        case SQUARE: return 15.00;
        case VASE: return 28;
        default: return 0.0;
    }
}
