#include "ProductItem.h"

ProductItem::ProductItem(const string& name, double price) {
    this->name = name;
    this->price = price;
}

ProductItem::~ProductItem() {}

double ProductItem::getPrice() const {
    return price;
}

std::string ProductItem::getName() const {
    return name;
}

Product* ProductItem::clone() const {
    return new ProductItem(*this);
}