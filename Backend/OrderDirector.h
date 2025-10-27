// Order Director
// Calls Builder methods to produce predefined products.
#ifndef ORDERDIRECTOR_H
#define ORDERDIRECTOR_H

#include "ConcreteOrderBuilder.h"
#include "OrderBuilder.h"

class OrderDirector {
    public:
        void makeValentinesBundle(ConcreteOrderBuilder& builder);
        void makeSpringBundle(ConcreteOrderBuilder& builder, ProductBundle* bundle);
    private:
        OrderBuilder* builder;
};

#endif