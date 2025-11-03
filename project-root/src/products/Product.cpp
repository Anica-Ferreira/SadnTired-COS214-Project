/**
 * @class [Product]
 * @brief [Implementation of the Product class for product management]
 * @details [Provides base functionality for product display and information]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "Product.h"

/**
 * @brief [Constructs a new Product object with default values]
 */
Product::Product() : name(""), price(0.0), description("") {}

/**
 * @brief [Constructs a new Product object with specified values]
 * @param[in] name [Name of the product]
 * @param[in] price [Price of the product]
 * @param[in] description [Description of the product]
 */
Product::Product(const string& name, double price, const string& description)
    : name(name), price(price), description(description) {}
Product::~Product() {}

/**
 * @brief [Gets the name of the product]
 * @return [Name string]
 */
string Product::getName() const { return name; }

/**
 * @brief [Gets the price of the product]
 * @return [Price value]
 */
double Product::getPrice() const { return price; }

/**
 * @brief [Gets the description of the product]
 * @return [Description string]
 */
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