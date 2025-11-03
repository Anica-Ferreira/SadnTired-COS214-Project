/**
 * @class [Product]
 * @brief [Implementation of the Product class for product management]
 * @details [Provides base functionality for product display and information]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "Product.h"

Product::Product() : name(""), price(0.0), description("") {}
Product::Product(const string& name, double price, const string& description)
    : name(name), price(price), description(description) {}
Product::~Product() {}

string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
string Product::getDescription() const { return description; }

/**
 * @brief [Prints product information to console]
 */
void Product::printProduct() const {
    cout << "Product: " << getName() 
         << ", Price: " << getPrice()
         << ", Description: " << getDescription()
         << endl;
}