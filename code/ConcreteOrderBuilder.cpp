#include "ConcreteOrderBuilder.h"

ConcreteOrderBuilder::ConcreteOrderBuilder() : product(NULL) {}

ConcreteOrderBuilder::~ConcreteOrderBuilder() {}

void ConcreteOrderBuilder::setPlant(string name, double price) {
    if(product){
        delete product;
    }

    product = new ProductItem(name, price);
}

void ConcreteOrderBuilder::addPot(DecorativePot::PotType type) {
    if(product){
        product = new DecorativePot(product, type);
    }
}

void ConcreteOrderBuilder::addWrapping(GiftWrapping::WrappingType type) {
    if(product){
        product = new GiftWrapping(product, type);
    }
}

void ConcreteOrderBuilder::addToBundle(ProductBundle* bundle) {
    if(product && bundle) {
        bundle->add(product);
        product = NULL;
    }
}

Product* ConcreteOrderBuilder::getProduct() {
    return product;
}
