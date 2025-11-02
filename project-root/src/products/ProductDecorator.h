// Abstract Decorator class.

#ifndef PRODUCTDECORATOR_H
#define PRODUCTDECORATOR_H

#include "Product.h"

class ProductDecorator : public Product {
    protected:
        Product* product;

    public:
        ProductDecorator(Product* product);
        virtual ~ProductDecorator();
};

#endif