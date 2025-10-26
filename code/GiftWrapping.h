// ConcreteDecorator
// Adds gift wrapping to a product with selectable wrapping styles.

#ifndef GIFTWRAPPING_H
#define GIFTWRAPPING_H

#include "ProductDecorator.h"

class GiftWrapping : public ProductDecorator {
    public:
        enum WrappingType {
            RED_BOW,
            BROWN_PAPER,
            FLORAL_WRAP
        };

        GiftWrapping(Product* product, WrappingType type);
        ~GiftWrapping();

        double getPrice() const override;
        std::string getName() const override;
        Product* clone() const override;

    private:
        WrappingType type;
        string getWrappingName() const;
        double getWrappingPrice() const;
        
};

#endif