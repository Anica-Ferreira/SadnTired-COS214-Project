// Builder
// Defines the interface for creating complex plant orders.

#ifndef ORDERBUILDER_H
#define ORDERBUILDER_H

#include <string>
#include <iostream>

#include "Product.h"
#include "DecorativePot.h"
#include "GiftWrapping.h"
#include "ProductBundle.h"
#include "ProductItem.h"

using namespace std;

class OrderBuilder{
    public:
        virtual ~OrderBuilder() {}

        virtual void setPlant(string name, double price) = 0;
        virtual void addPot(DecorativePot::PotType type) = 0;
        virtual void addWrapping(GiftWrapping::WrappingType type) = 0;
        virtual void addToBundle(ProductBundle* bundle) = 0;

        virtual Product* getProduct() = 0;
};

#endif