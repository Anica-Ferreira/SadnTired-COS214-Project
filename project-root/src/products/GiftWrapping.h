// ConcreteDecorator
// Adds gift wrapping to a product with selectable wrapping styles.
#ifndef GIFTWRAPPING_H
#define GIFTWRAPPING_H

#include "ProductDecorator.h"

class GiftWrapping : public ProductDecorator {
    public:
        enum WrappingType { RED_BOW, BROWN_PAPER, FLORAL_WRAP, NONE };

        GiftWrapping(Product* product, WrappingType type);
        ~GiftWrapping() override;

        double getPrice() const override;
        string getName() const override;
        string getDescription() const override;
        Product* clone() const override;

        static string getWrappingName(WrappingType type);
        static double getWrappingPrice(WrappingType type);

    private:
        WrappingType type;
};

#endif