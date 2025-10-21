#include <iostream>
#include "ProductItem.h"
#include "DecorativePot.h"
#include "GiftWrapping.h"
#include "ProductBundle.h"

using namespace std;

int main() {

    //create products
    Product* cactus = new ProductItem("Cactus", 30.0);
    Product* rose = new ProductItem("Rose", 25.0);
    Product* lavender = new ProductItem("Lavender", 20.0);

    //decorate
    Product* cactusInPot = new DecorativePot(cactus, DecorativePot::CLASSIC);
    Product* roseWrapped = new GiftWrapping(rose, GiftWrapping::RED_BOW);
    Product* lavenderWrappedPot = new DecorativePot(
        new GiftWrapping(lavender, GiftWrapping::FLORAL_WRAP), 
        DecorativePot::ROTUND
    );

    //product bundles
    ProductBundle* springBundle = new ProductBundle("Spring Special Bundle");
    springBundle->add(cactusInPot);
    springBundle->add(roseWrapped);
    springBundle->add(lavenderWrappedPot);

    //print
    cout << "Individual Products:" << endl;
    cactusInPot->printProduct();
    roseWrapped->printProduct();
    lavenderWrappedPot->printProduct();
    cout << endl;

    cout << "Bundle Details:" << endl;
    springBundle->printProduct();
    cout << "Total Price of Bundle: R" << springBundle->getPrice() << endl;

    delete springBundle;

    return 0;
}