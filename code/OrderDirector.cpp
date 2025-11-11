#include "OrderDirector.h"

void OrderDirector::makeValentinesBundle(ConcreteOrderBuilder& builder) {
    builder.setPlant("Rose", 25.0);
    builder.addPot(DecorativePot::VASE);
    builder.addWrapping(GiftWrapping::RED_BOW);
}

void OrderDirector::makeSpringBundle(ConcreteOrderBuilder& builder, ProductBundle* bundle) {
    builder.setPlant("Cactus", 30.0);
    builder.addPot(DecorativePot::CLASSIC);
    builder.addToBundle(bundle);

    builder.setPlant("Lavender", 20.0);
    builder.addWrapping(GiftWrapping::FLORAL_WRAP);
    builder.addToBundle(bundle);
}