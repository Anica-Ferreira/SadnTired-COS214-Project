#include "DecorativePot.h"

DecorativePot::DecorativePot(Product* product, PotType type)
    : ProductDecorator(product), type(type) {}

DecorativePot::~DecorativePot() {}

double DecorativePot::getPrice() const {
    return product->getPrice() + getPotPrice();
}

std::string DecorativePot::getName() const {
    return product->getName() + " + " + getPotName();
}

Product* DecorativePot::clone() const {
    return new DecorativePot(product->clone(), type);
}

std::string DecorativePot::getPotName() const {
    switch (type) {
        case CLASSIC: return "Classic Pot";
        case ROTUND: return "Rotund Pot";
        case SQUARE: return "Square Pot";
        case VASE: return "Vase Pot";
        default: return "Unknown Pot";
    }
}

double DecorativePot::getPotPrice() const {
    switch (type) {
        case CLASSIC: return 12.00;
        case ROTUND: return 21.00;
        case SQUARE: return 15.00;
        case VASE: return 28;
        default: return 0.0;
    }
}
