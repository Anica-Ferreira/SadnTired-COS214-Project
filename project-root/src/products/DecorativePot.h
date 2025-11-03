// ConcreteDecorator
// Adds a decorative pot to product.
#ifndef DECORATIVEPOT_H
#define DECORATIVEPOT_H

#include "ProductDecorator.h"

class DecorativePot : public ProductDecorator {
    public:
        enum PotType { CLASSIC, ROTUND, SQUARE, VASE, NONE };

        DecorativePot(Product* product, PotType type);
        ~DecorativePot() override;

        double getPrice() const override;
        string getName() const override;
        string getDescription() const override;

        Product* clone() const override;

        static string getPotName(PotType type);
        static double getPotPrice(PotType type);

    private:
        PotType type;
};

#endif