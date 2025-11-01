/**
 * @class [ConcreteOrderBuilder]
 * @brief [Implementation of the ConcreteOrderBuilder class for building plant orders]
 * @details [Implements the Builder pattern for creating complex plant product orders]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "ConcreteOrderBuilder.h"

/**
 * @brief [Constructs a new ConcreteOrderBuilder object]
 */
ConcreteOrderBuilder::ConcreteOrderBuilder() : product(NULL) {}

/**
 * @brief [Destroys the ConcreteOrderBuilder object]
 */
ConcreteOrderBuilder::~ConcreteOrderBuilder() {}

/**
 * @brief [Sets the base plant for the order]
 * @param[in] name [Plant name]
 * @param[in] price [Plant price]
 */
void ConcreteOrderBuilder::setPlant(string name, double price) {
    if(product){
        delete product;
    }

    product = new ProductItem(name, price);
}

/**
 * @brief [Adds a decorative pot to the order]
 * @param[in] type [Type of decorative pot to add]
 */
void ConcreteOrderBuilder::addPot(DecorativePot::PotType type) {
    if(product){
        product = new DecorativePot(product, type);
    }
}

/**
 * @brief [Adds gift wrapping to the order]
 * @param[in] type [Type of gift wrapping to add]
 */
void ConcreteOrderBuilder::addWrapping(GiftWrapping::WrappingType type) {
    if(product){
        product = new GiftWrapping(product, type);
    }
}

/**
 * @brief [Adds the current product to a bundle]
 * @param[in] bundle [Pointer to the product bundle]
 */
void ConcreteOrderBuilder::addToBundle(ProductBundle* bundle) {
    if(product && bundle) {
        bundle->add(product);
        product = NULL;
    }
}

/**
 * @brief [Retrieves the built product]
 * @return [Pointer to the constructed Product object]
 */
Product* ConcreteOrderBuilder::getProduct() {
    return product;
}
