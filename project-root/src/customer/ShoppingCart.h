#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include <string>
#include <vector>
#include <iomanip>
#include "../products/Product.h"
#include "../products/ProductDecorator.h"
#include "../inventory/Inventory.h"

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
        Product* removeProduct(int index);
        void viewCart() const;
        void clear(Inventory* shopInventory);
        bool isEmpty() const;

        std::vector<Product*> getItems() const;
};

#endif