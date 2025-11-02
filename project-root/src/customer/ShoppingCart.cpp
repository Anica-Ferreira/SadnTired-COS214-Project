/**
 * @class [ShoppingCart]
 * @brief [Implementation of the ShoppingCart class for cart management]
 * @details [Handles shopping cart operations and item management]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "ShoppingCart.h"
#include <iomanip>

ShoppingCart::ShoppingCart() {}

ShoppingCart::~ShoppingCart() {
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    items.clear();
}

void ShoppingCart::addProduct(Product* product) {
    if (product) {
        items.push_back(product->clone());
        cout << "\033[1;32mProduct added to cart successfully!\033[0m\n";
    } else {
        cout << "\033[1;31mError: Cannot add an empty product to the cart.\033[0m\n";
    }
}

void ShoppingCart::removeProduct(int index) {
    if (index >= 0 && index < (int)items.size()) {
        delete items[index];
        items.erase(items.begin() + index);
        cout << "\033[1;33mProduct removed from cart.\033[0m\n";
    } else {
        cout << "\033[1;31mInvalid index.\033[0m\n";
    }
}

void ShoppingCart::viewCart() const {
    cout << "\033[1;36m\n--- Shopping Cart ---\n\033[0m";
    if (items.empty()) {
        cout << "Your cart is empty.\n";
        return;
    }

    double total = 0.0;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i]->getDescription()
             << " - R" << fixed << setprecision(2) << items[i]->getPrice() << "\n";
        total += items[i]->getPrice();
    }

    cout << "\nTotal: R" << fixed << setprecision(2) << total << "\n";
}

void ShoppingCart::clear() {
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    items.clear();
}

bool ShoppingCart::isEmpty() const {
    return items.empty();
}

vector<Product*> ShoppingCart::getItems() const {
    return items;
}