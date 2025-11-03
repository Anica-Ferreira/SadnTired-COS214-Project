// Component interface for both Decorator and Composite.
// Represents the common interface for all products, individual or bundled.

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include "../greenhouse/Plant.h"

using namespace std;

class Product {
    protected:
        string name;
        double price;
        string description;

    public:
        Product();
        Product(const string& name, double price, const string& description);
        virtual ~Product();

        virtual Product* clone() const = 0;
        virtual Plant* getBasePlant() const { return NULL; }

        virtual string getName() const;
        virtual double getPrice() const;
        virtual string getDescription() const;
        virtual string getTitle() const {
            return getName();
        }

        virtual void printProduct() const;
};

#endif