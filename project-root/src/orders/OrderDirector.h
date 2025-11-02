// Order Director
// Calls Builder methods to produce predefined products.
#ifndef ORDERDIRECTOR_H
#define ORDERDIRECTOR_H

#include "ConcreteOrderBuilder.h"
#include "OrderBuilder.h"

class OrderDirector {
    public:
        ProductBundle* makeValentinesBundle(ConcreteOrderBuilder& builder);
        ProductBundle* makeSpringBundle(ConcreteOrderBuilder& builder);
        ProductBundle* makeSucculentBundle(ConcreteOrderBuilder& builder);
    private:
        OrderBuilder* builder;
};

#endif