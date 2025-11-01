// Concrete Builder
// Implements the steps defined by the Builder to create a concrete plant order
#ifndef CONCRETEORDERBUILDER_H
#define CONCRETEORDERBUILDER_H

#include "OrderBuilder.h"

class ConcreteOrderBuilder : public OrderBuilder {
public:
    ConcreteOrderBuilder();
    ~ConcreteOrderBuilder();

    void setPlant(string name, double price) override;
    void addPot(DecorativePot::PotType type) override;
    void addWrapping(GiftWrapping::WrappingType type) override;
    void addToBundle(ProductBundle* bundle) override;

    Product* getProduct() override;

    private:
    Product* product;
};

#endif