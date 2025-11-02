/**
 * @class [ProductBundle]
 * @brief [Implementation of the ProductBundle class for product bundle management]
 * @details [Handles creation and management of product bundles with deep copying]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "ProductBundle.h"

/**
 * @brief [Constructs a new ProductBundle object]
 * @param[in] name [The name of the product bundle]
 */
ProductBundle::ProductBundle(string name)
    : name(name) {}

/**    
 * @brief [Copy constructor for ProductBundle]
 * @param[in] other [The ProductBundle to copy from]
 */    
ProductBundle::ProductBundle(const ProductBundle& other)
    : name(other.name) {
    
    //deep copy contained item
    for (int i = 0; i < (int)other.items.size(); i++){
        items.push_back(other.items[i]->clone());
    }
}

/**
 * @brief [Destroys the ProductBundle object and cleans up resources]
 */
ProductBundle::~ProductBundle() {
    for (int i = 0; i < (int)items.size(); i++){
        delete items[i];
    }
}

/**
 * @brief [Adds a product to the bundle]
 * @param[in] item [Pointer to the product to add]
 */
void ProductBundle::add(Product* item) {
    items.push_back(item);
}

/**
 * @brief [Gets the name of the product bundle]
 * @return [The bundle name with included items]
 */
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

/**
 * @brief [Gets the total price of the product bundle]
 * @return [The sum of all item prices in the bundle]
 */
double ProductBundle::getPrice() const {
    double total = 0.0;
    for (int i = 0; i < (int)items.size(); i++) {
        total += items[i]->getPrice();
    }
    return total;
}

/**
 * @brief [Gets the bundle title only, without listing contents]
 * @return [The bundle name]
 */
string ProductBundle::getTitle() const {
    return name;
}

string ProductBundle::getDescription() const {
    string desc;
    for (size_t i = 0; i < items.size(); i++) {
        
        desc += "  - " + items[i]->getDescription() + "\n";
    }

    stringstream priceStream;
    priceStream << fixed << setprecision(2) << getPrice();

    desc += "\033[38;5;215m\nTotal Price: R" + priceStream.str() + "\033[0m";
    return desc;
}

/**
 * @brief [Creates a deep copy of the ProductBundle]
 * @return [Pointer to the cloned ProductBundle object]
 */
Product* ProductBundle::clone() const {
    return new ProductBundle(*this);
}

/**
 * @brief [Prints bundle information to console]
 */
void ProductBundle::printProduct() const {
    cout << "Bundle: " << getName() << endl;
    cout << "Total Price: R" << getPrice() << endl;
}

Plant* ProductBundle::getBasePlant() const {
    if (!items.empty()) {
        return items.front()->getBasePlant();
    }
    return nullptr;
}