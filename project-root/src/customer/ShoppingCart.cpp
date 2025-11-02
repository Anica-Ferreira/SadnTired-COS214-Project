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

Product* ShoppingCart::removeProduct(int index) {
    if (index < 0 || index >= items.size()) return nullptr;
    Product* p = items[index];
    items.erase(items.begin() + index);
    return p;
}

void ShoppingCart::viewCart() const {
    const string indent = "\t";
    const int descWidth = 40;
    const int priceWidth = 12;

    cout << indent << "\033[1;36m==============================================================\033[0m\n";
    cout << indent << "                      Shopping Cart\n";
    cout << indent << "\033[1;36m==============================================================\033[0m\n";

    if (items.empty()) {
        cout << indent << "\033[1;31m                    Your cart is empty.\033[0m\n";
        cout << indent << "\033[1;36m==============================================================\033[0m\n";
        return;
    }

    double total = 0.0;

    // Header
    cout << indent << left << setw(5) << "#" 
         << setw(descWidth) << "Item Description" 
         << right << setw(priceWidth) << "Price (R)" << "\n";
    cout << indent << "\033[1;36m--------------------------------------------------------------\033[0m\n";

    for (size_t i = 0; i < items.size(); ++i) {
        string desc = items[i]->getDescription();
        double price = items[i]->getPrice();

        stringstream priceStream;
        priceStream << "R" << fixed << setprecision(2) << price;
        string priceStr = priceStream.str();

        size_t pos = 0;
        bool firstLine = true;
        while (pos < desc.length()) {
            string line = desc.substr(pos, descWidth);
            pos += descWidth;

            if (firstLine) {
                cout << indent << left << setw(5) << (i + 1)
                     << setw(descWidth) << line
                     << right << setw(priceWidth) << priceStr << "\n";
                firstLine = false;
            } else {
                cout << indent << left << setw(5) << ""
                     << setw(descWidth) << line
                     << "\n";
            }
        }

        total += price;
    }

    cout << indent << "\033[1;36m--------------------------------------------------------------\033[0m\n";

    stringstream totalStream;
    totalStream << "R" << fixed << setprecision(2) << total;
    string totalStr = totalStream.str();

    cout << indent << left << setw(descWidth + 5) << "\033[1;36mTotal:\033[0m"
         << right << setw(priceWidth) << "\t\t" << totalStr << "\n";

    cout << indent << "\033[1;36m==============================================================\033[0m\n";
}

void ShoppingCart::clear(Inventory* shopInventory) {
    for (Product* p : items) {
        Plant* basePlant = nullptr;

        if (auto decorator = dynamic_cast<ProductDecorator*>(p)) {
            basePlant = decorator->getBasePlant();
        } else {
            basePlant = dynamic_cast<Plant*>(p);
        }

        if (basePlant && shopInventory) {
            shopInventory->addPlant(basePlant);
        }

        delete p;
    }

    items.clear();
}

bool ShoppingCart::isEmpty() const {
    return items.empty();
}

vector<Product*> ShoppingCart::getItems() const {
    return items;
}