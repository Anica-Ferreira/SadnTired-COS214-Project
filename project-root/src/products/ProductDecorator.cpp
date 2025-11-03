/**
 * @class [ProductDecorator]
 * @brief [Implementation of the ProductDecorator class for product decoration]
 * @details [Provides base functionality for decorating products with additional features]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "ProductDecorator.h"

/**
 * @brief [Constructs a new ProductDecorator object]
 * @param[in] product [Pointer to the product to decorate]
 */
ProductDecorator::ProductDecorator(Product* product) : product(product) {}


/**
 * @brief [Destroys the ProductDecorator object and cleans up resources]
 */
ProductDecorator::~ProductDecorator() { delete product; }