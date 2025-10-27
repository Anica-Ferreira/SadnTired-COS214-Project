#include "Product.h"

void Product::printProduct() const{
    cout << getName() << " - R" << getPrice() << endl;
}