/**
 * @class [ShoppingCart]
 * @brief [Implementation of the ShoppingCart class for cart management]
 * @details [Handles shopping cart operations and item management]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "ShoppingCart.h"
#include <iomanip>

/**
 * @brief [Constructs a new ShoppingCart object]
 */
ShoppingCart::ShoppingCart() {}

/**
 * @brief [Destroys the ShoppingCart object and cleans up resources]
 */
ShoppingCart::~ShoppingCart() {
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    items.clear();
}

/**
 * @brief [Adds a product to the shopping cart]
 * @param[in] product [Pointer to the product to add]
 */
void ShoppingCart::addProduct(Product* product) {
    if (product) {
        items.push_back(product->clone());
        cout << "\033[1;32m\nProduct added to cart successfully!\033[0m\n";
    } else {
        cout << "\033[1;31mError: Cannot add an empty product to the cart.\033[0m\n";
    }
}

/**
 * @brief [Removes a product from the shopping cart by index]
 * @param[in] index [Index of the product to remove]
 * @return [Pointer to the removed product, or nullptr if index is invalid]
 */
Product* ShoppingCart::removeProduct(int index) {
    if (index < 0 || index >= items.size()) return nullptr;
    Product* p = items[index];
    items.erase(items.begin() + index);
    return p;
}

/**
 * @brief [Displays the contents of the shopping cart]
 */
void ShoppingCart::viewCart() const {
    const string indent = "\t";
    const int descWidth = 44;
    const int priceWidth = 12;

    const string pastelAmber = "\033[38;5;179m"; 
    const string green = "\033[1;32m";
    const string red = "\033[1;31m";
    const string reset = "\033[0m";

    cout << indent << pastelAmber << "=============================================================="
         << reset << "\n";
    cout << indent << "                      Shopping Cart\n";
    cout << indent << pastelAmber << "=============================================================="
         << reset << "\n";

    if (items.empty()) {
        cout << indent << red << "                    Your cart is empty." << reset << "\n";
        cout << indent << pastelAmber << "=============================================================="
             << reset << "\n";
        return;
    }

    double total = 0.0;

    cout << indent << left << setw(5) << "#"
         << setw(descWidth) << "Item"
         << right << setw(priceWidth) << "Price (R)" << "\n";
    cout << indent << pastelAmber << "--------------------------------------------------------------"
         << reset << "\n";

    for (size_t i = 0; i < items.size(); ++i) {
        Product* product = items[i];
        double price = product->getPrice();

        string name;
        ProductBundle* bundle = dynamic_cast<ProductBundle*>(product);
        if (bundle) {
            name = bundle->getName(); 
        } else {
            name = product->getName();
        }

        stringstream priceStream;
        priceStream << "R" << fixed << setprecision(2) << price;
        string priceStr = priceStream.str();

        size_t pos = 0;
        bool firstLine = true;
        while (pos < name.length()) {
            string line = name.substr(pos, descWidth);
            pos += descWidth;

            if (firstLine) {
                cout << indent << left << setw(5) << (i + 1)
                     << setw(descWidth) << line
                     << right << setw(priceWidth) << priceStr << "\n";
                firstLine = false;
            } else {
                cout << indent << left << setw(5) << ""
                     << setw(descWidth) << line << "\n";
            }
        }

        total += price;
    }

    cout << indent << pastelAmber << "--------------------------------------------------------------"
         << reset << "\n";

    // Total in green
    stringstream totalStream;
    totalStream << "R" << fixed << setprecision(2) << total;
    string totalStr = totalStream.str();

    cout << indent << left << setw(5) << ""
         << setw(descWidth) << green + string("Total:\t\t") + reset
         << right << setw(priceWidth) << totalStr << "\n";

    cout << indent << pastelAmber << "=============================================================="
         << reset << "\n";
}

/**
 * @brief [Clears all items from the shopping cart]
 */
void ShoppingCart::clear() {
    for (Product* p : items) {
        delete p;
    }

    items.clear();
}

/**
 * @brief [Checks if the shopping cart is empty]
 * @return [True if the cart is empty, false otherwise]
 */
bool ShoppingCart::isEmpty() const {
    return items.empty();
}

/**
 * @brief [Gets the list of items in the shopping cart]
 * @return [Vector of pointers to products in the cart]
 */
vector<Product*> ShoppingCart::getItems() const {
    return items;
}