/* please add description here  and at the top of each file :( */

#include "ProductDecorator.h"

ProductDecorator::ProductDecorator(Product* product) : product(product) {}

ProductDecorator::~ProductDecorator() {
    delete product;
}