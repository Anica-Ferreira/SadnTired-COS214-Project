// Composite 

#ifndef PRODUCTBUNDLE_H
#define PRODUCTBUNDLE_H

#include "Product.h"
#include <vector>

using namespace std;

class ProductBundle : public Product {
    public:
        ProductBundle(string name = "");
        ProductBundle(const ProductBundle& other);
        ~ProductBundle();

        void add(Product* item);
        string getName() const override;
        double getPrice() const override;
        Product* clone() const override;
        void printProduct() const override;

    private:
        vector<Product*> items;
        string name;
};

#endif