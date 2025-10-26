#include "GiftWrapping.h"

GiftWrapping::GiftWrapping(Product* product, WrappingType type)
    : ProductDecorator(product), type(type) {}

GiftWrapping::~GiftWrapping() {}

double GiftWrapping::getPrice() const {
    return product->getPrice() + getWrappingPrice();
}

std::string GiftWrapping::getName() const {
    return product->getName() + " + " + getWrappingName();
}

Product* GiftWrapping::clone() const {
    return new GiftWrapping(product->clone(), type);
}

std::string GiftWrapping::getWrappingName() const {
    switch (type) {
        case RED_BOW: return "Red Bow Wrapping";
        case BROWN_PAPER: return "Parchment Paper Wrapping";
        case FLORAL_WRAP: return "Floral Wrap";
        default: return "Unknown Wrapping";
    }
}

double GiftWrapping::getWrappingPrice() const {
    switch (type) {
        case RED_BOW: return 12.00;
        case BROWN_PAPER: return 8.00;
        case FLORAL_WRAP: return 18.00;
        default: return 0.0;
    }
}