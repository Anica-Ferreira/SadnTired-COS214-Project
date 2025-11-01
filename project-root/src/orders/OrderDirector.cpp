/**
 * @class [OrderDirector]
 * @brief [Implementation of the OrderDirector class for creating plant order bundles]
 * @details [Implements predefined bundle configurations using the Builder pattern]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "OrderDirector.h"

/**
 * @brief [Creates a Valentine's Day themed plant bundle]
 * @param[in] builder [Reference to the order builder to construct the bundle]
 */
void OrderDirector::makeValentinesBundle(ConcreteOrderBuilder& builder) {
    builder.setPlant("Rose", 25.0);
    builder.addPot(DecorativePot::VASE);
    builder.addWrapping(GiftWrapping::RED_BOW);
}

/**
 * @brief [Creates a Spring themed plant bundle]
 * @param[in] builder [Reference to the order builder to construct the bundle]
 * @param[in] bundle [Pointer to the product bundle to add plants to]
 */
void OrderDirector::makeSpringBundle(ConcreteOrderBuilder& builder, ProductBundle* bundle) {
    builder.setPlant("Cactus", 30.0);
    builder.addPot(DecorativePot::CLASSIC);
    builder.addToBundle(bundle);

    builder.setPlant("Lavender", 20.0);
    builder.addWrapping(GiftWrapping::FLORAL_WRAP);
    builder.addToBundle(bundle);
}