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
ProductBundle* OrderDirector::makeValentinesBundle(ConcreteOrderBuilder& builder) {
    ProductBundle* bundle = new ProductBundle("Valentine's Special");

    Plant* rose1 = new Flower("Red Rose", 52.0, nullptr, "Red romantic rose.");
    builder.setPlant(rose1);
    builder.addPot(DecorativePot::VASE);
    builder.addWrapping(GiftWrapping::RED_BOW);
    builder.addToBundle(bundle);

    Plant* rose2 = new Flower("Pink Rose", 48.0, nullptr, "Pink rose.");
    builder.setPlant(rose2);
    builder.addPot(DecorativePot::VASE);
    builder.addWrapping(GiftWrapping::RED_BOW);
    builder.addToBundle(bundle);

    return bundle;
}

/**
 * @brief [Creates a Spring themed plant bundle]
 * @param[in] builder [Reference to the order builder to construct the bundle]
 */

ProductBundle* OrderDirector::makeSpringBundle(ConcreteOrderBuilder& builder) {
    ProductBundle* bundle = new ProductBundle("Spring Collection");

    Plant* lavender = new Flower("Lavender", 45.0, nullptr, "Purple lavender.");
    builder.setPlant(lavender);
    builder.addPot(DecorativePot::CLASSIC);
    builder.addWrapping(GiftWrapping::FLORAL_WRAP);
    builder.addToBundle(bundle);

    Plant* daisy = new Flower("Daisy", 30.0, nullptr, "Bright white daisy.");
    builder.setPlant(daisy);
    builder.addPot(DecorativePot::CLASSIC);
    builder.addWrapping(GiftWrapping::FLORAL_WRAP);
    builder.addToBundle(bundle);

    return bundle;
}

/**
 * @brief [Creates a Succulent themed plant bundle]
 * @param[in] builder [Reference to the order builder to construct the bundle]
 */
ProductBundle* OrderDirector::makeSucculentBundle(ConcreteOrderBuilder& builder) {
    ProductBundle* bundle = new ProductBundle("Succulent Special");

    Plant* cactus = new Succulent("Mini Cactus", 35.0, nullptr, "Small desert cactus.");
    builder.setPlant(cactus);
    builder.addPot(DecorativePot::ROTUND);
    builder.addToBundle(bundle);

    Plant* aloe = new Succulent("Aloe Vera", 40.0, nullptr, "Medicinal succulent.");
    builder.setPlant(aloe);
    builder.addPot(DecorativePot::SQUARE);
    builder.addToBundle(bundle);

    Plant* echeveria = new Succulent("Echeveria", 38.0, nullptr, "Pretty rosette succulent.");
    builder.setPlant(echeveria);
    builder.addPot(DecorativePot::CLASSIC);
    builder.addToBundle(bundle);

    return bundle;
}