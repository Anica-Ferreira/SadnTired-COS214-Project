// ShoppingCart.h - NEW FILE (if needed)
#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include <string>
#include <vector>
using namespace std;

struct CartItem {
    string plantName;
    int quantity;
    double price;

    CartItem(const string& name, int qty, double pr) : plantName(name), quantity(qty), price(pr) {}
};

class ShoppingCart {
private:
    vector<CartItem> items;

public:
    ShoppingCart() {}

    void addItem(const string& plantName, int quantity) {
        // Simple implementation
        items.push_back(CartItem(plantName, quantity, 19.99));
    }

    void removeItem(const string& plantName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->plantName == plantName) {
                items.erase(it);
                break;
            }
        }
    }

    void clear() {
        items.clear();
    }

    bool isEmpty() const {
        return items.empty();
    }

    vector<CartItem> getItems() const {
        return items;
    }
};

#endif