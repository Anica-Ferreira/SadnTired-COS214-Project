#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include <string>
#include <vector>
#include <iomanip>
#include "../products/Product.h"

using namespace std;

struct CartItem {
    string plantName;
    int quantity;
    double price;

    CartItem(const string& name, int qty, double pr) : plantName(name), quantity(qty), price(pr) {}
};

class ShoppingCart {
    private:
        std::vector<Product*> items;

    public:
        ShoppingCart();
        ~ShoppingCart();

        void addProduct(Product* product);
        void removeProduct(int index);
        void viewCart() const;
        void clear();
        bool isEmpty() const;

        std::vector<Product*> getItems() const;
};

#endif