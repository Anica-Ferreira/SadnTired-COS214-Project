#include "ProductBundle.h"

ProductBundle::ProductBundle(string name)
    : name(name) {}

ProductBundle::ProductBundle(const ProductBundle& other)
    : name(other.name) {
    
    //deep copy contained item
    for (int i = 0; i < (int)other.items.size(); i++){
        items.push_back(other.items[i]->clone());
    }
}

ProductBundle::~ProductBundle() {
    for (int i = 0; i < (int)items.size(); i++){
        delete items[i];
    }
}

void ProductBundle::add(Product* item) {
    items.push_back(item);
}

string ProductBundle::getName() const {
    string result = name + " (";
    for (int i = 0; i < (int)items.size(); i++) {
        result += items[i]->getName();
        if (i != (int)items.size() - 1)
            result += ", ";
    }
    result += ")";
    return result;
}

double ProductBundle::getPrice() const {
    double total = 0.0;
    for (int i = 0; i < (int)items.size(); i++) {
        total += items[i]->getPrice();
    }
    return total;
}

Product* ProductBundle::clone() const {
    return new ProductBundle(*this);
}

void ProductBundle::printProduct() const {
    cout << "Bundle: " << getName() << endl;
    cout << "Total Price: R" << getPrice() << endl;
}