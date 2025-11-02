/**
 * @class [ProductItem]
 * @brief [Implementation of the ProductItem class for individual product items]
 * @details [Handles basic product item functionality and cloning]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "ProductItem.h"

/**
 * @brief [Constructs a new ProductItem object]
 * @param[in] name [The name of the product item]
 * @param[in] price [The price of the product item]
 */
ProductItem::ProductItem(const string name, double price, const string description) {
    this->name = name;
    this->price = price;
    this->description = description;
}

/**
 * @brief [Destroys the ProductItem object]
 */
ProductItem::~ProductItem() {}

/**
 * @brief [Gets the price of the product item]
 * @return [The product price]
 */
double ProductItem::getPrice() const {
    return price;
}

/**
 * @brief [Gets the name of the product item]
 * @return [The product name]
 */
string ProductItem::getName() const {
    return name;
}

/**
 * @brief [Gets the description of the product item]
 * @return [The product name]
 */
string ProductItem::getDescription() const {
    return description;
}

/**
 * @brief [Creates a deep copy of the ProductItem]
 * @return [Pointer to the cloned ProductItem object]
 */
Product* ProductItem::clone() const {
    return new ProductItem(*this);
}