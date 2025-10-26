// ConcreteDecorator
// Adds a decorative pot to product.

#ifndef DECORATIVEPOT_H
#define DECORATIVEPOT_H

#include "ProductDecorator.h"

using namespace std;

class DecorativePot : public ProductDecorator {
    public:
        //These are based on the pots Ani drew I don't know the shapes names
        enum PotType {
            CLASSIC,
            ROTUND,
            SQUARE,
            VASE
        };

        DecorativePot(Product* product, PotType type);
        ~DecorativePot();

        double getPrice() const override;
        std::string getName() const override;
        Product* clone() const override;

    private:
        PotType type;
        string getPotName() const;
        double getPotPrice() const;
        
};

#endif