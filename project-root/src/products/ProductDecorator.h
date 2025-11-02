// Abstract Decorator class.

#ifndef PRODUCTDECORATOR_H
#define PRODUCTDECORATOR_H

#include "Product.h"

class ProductDecorator : public Product {
    public:
        ProductDecorator(Product* product);
        virtual ~ProductDecorator();

        virtual double getPrice() const = 0;
        virtual string getName() const = 0;
        virtual string getDescription() const = 0;
        virtual Product* clone() const = 0;

    protected:
        Product* product;
};

#endif