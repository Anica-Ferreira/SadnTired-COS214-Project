// Builder
// Defines the interface for creating complex plant orders.

#ifndef ORDERBUILDER_H
#define ORDERBUILDER_H

#include <string>
#include <iostream>

#include "../products/Product.h"
#include "../products/DecorativePot.h"
#include "../products/GiftWrapping.h"
#include "../products/ProductBundle.h"
#include "../products/ProductItem.h"
#include "../greenhouse/Plant.h"

using namespace std;

class OrderBuilder{
    public:
        virtual ~OrderBuilder() {}

        virtual void setPlant(Plant* plant) = 0;
        virtual void addPot(DecorativePot::PotType type) = 0;
        virtual void addWrapping(GiftWrapping::WrappingType type) = 0;
        virtual void addToBundle(ProductBundle* bundle) = 0;

        virtual Product* getProduct() = 0;
};

#endif