// Leaf class for Composite and ConcreteComponent for Decorator.
// Represents a single purchasable product.

#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include "Product.h"

class ProductItem : public Product {
    public:
        ProductItem(const string name, double price, const string description);
        ~ProductItem();

        double getPrice() const override;
        string getName() const override;
        string getDescription() const override;
        Product* clone() const override;

    private:
        string name;
        double price;
        string description;
};

#endif