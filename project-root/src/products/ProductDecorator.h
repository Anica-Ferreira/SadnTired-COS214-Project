// Abstract Decorator class.

#ifndef PRODUCTDECORATOR_H
#define PRODUCTDECORATOR_H

#include "Product.h"

class ProductDecorator : public Product {
    public:
        ProductDecorator(Product* product);
        virtual ~ProductDecorator();

    protected:
        Product* product;
};

#endif