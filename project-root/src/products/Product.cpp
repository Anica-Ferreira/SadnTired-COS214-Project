/**
 * @class [Product]
 * @brief [Implementation of the Product class for product management]
 * @details [Provides base functionality for product display and information]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "Product.h"

/**
 * @brief [Prints product information to console]
 */
void Product::printProduct() const{
    cout << getName() << " - R" << getPrice() << endl;
}