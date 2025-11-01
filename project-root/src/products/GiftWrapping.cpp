/**
 * @class [GiftWrapping]
 * @brief [Implementation of the GiftWrapping decorator class]
 * @details [Adds gift wrapping functionality to plant products using the Decorator pattern]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "GiftWrapping.h"

/**
 * @brief [Constructs a new GiftWrapping decorator]
 * @param[in] product [Pointer to the product to decorate]
 * @param[in] type [Type of gift wrapping]
 */
GiftWrapping::GiftWrapping(Product* product, WrappingType type)
    : ProductDecorator(product), type(type) {}

/**
 * @brief [Destroys the GiftWrapping object]
 */
GiftWrapping::~GiftWrapping() {}

/**
 * @brief [Calculates the total price including gift wrapping]
 * @return [Total price of product plus wrapping]
 */
double GiftWrapping::getPrice() const {
    return product->getPrice() + getWrappingPrice();
}

/**
 * @brief [Gets the combined name of product and wrapping]
 * @return [Combined name string]
 */
std::string GiftWrapping::getName() const {
    return product->getName() + " + " + getWrappingName();
}

/**
 * @brief [Creates a deep copy of the GiftWrapping object]
 * @return [Pointer to the cloned GiftWrapping object]
 */
Product* GiftWrapping::clone() const {
    return new GiftWrapping(product->clone(), type);
}

/**
 * @brief [Gets the name of the wrapping type]
 * @return [Wrapping type name string]
 */
std::string GiftWrapping::getWrappingName() const {
    switch (type) {
        case RED_BOW: return "Red Bow Wrapping";
        case BROWN_PAPER: return "Parchment Paper Wrapping";
        case FLORAL_WRAP: return "Floral Wrap";
        default: return "Unknown Wrapping";
    }
}

/**
 * @brief [Gets the price of the wrapping type]
 * @return [Wrapping price]
 */
double GiftWrapping::getWrappingPrice() const {
    switch (type) {
        case RED_BOW: return 12.00;
        case BROWN_PAPER: return 8.00;
        case FLORAL_WRAP: return 18.00;
        default: return 0.0;
    }
}