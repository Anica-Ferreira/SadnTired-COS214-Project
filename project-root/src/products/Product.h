// Component interface for both Decorator and Composite.
// Represents the common interface for all products, individual or bundled.

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
using namespace std;

class Product {
    public:
        virtual ~Product() {}

        virtual double getPrice() const = 0;
        virtual std::string getName() const = 0;
        virtual std::string getDescription() const = 0;
        virtual Product* clone() const = 0;

        virtual void printProduct() const;

    private:
        
};

#endif