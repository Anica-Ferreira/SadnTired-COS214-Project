// Leaf class for Composite and ConcreteComponent for Decorator.
// Represents a single purchasable product.

#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include "Product.h"

class ProductItem : public Product {
    private:
        Plant* basePlant;

    public:
        ProductItem(Plant* plant);
        ~ProductItem() override;

        Product* clone() const override;

        string getName() const override;
        double getPrice() const override;
        string getDescription() const override;
        string getTitle() const {
            return getName();
        }


        Plant* getBasePlant() const override;
};

#endif