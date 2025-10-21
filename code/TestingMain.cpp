#include <iostream>
#include "ConcreteOrderBuilder.h"
#include "OrderDirector.h"
#include "ProductBundle.h"

using namespace std;

int main() {
    OrderDirector director;

    ConcreteOrderBuilder valentinesBuilder;
    ProductBundle* valentinesBundle = new ProductBundle("Valentine's Bundle");
    director.makeValentinesBundle(valentinesBuilder);
    valentinesBundle->add(valentinesBuilder.getProduct());

    ConcreteOrderBuilder springBuilder;
    ProductBundle* springBundle = new ProductBundle("Spring Bundle");
    director.makeSpringBundle(springBuilder, springBundle);

    cout << "Valentine's Bundle" << endl;
    valentinesBundle->printProduct();
    cout << endl;

    cout << "Spring Bundle" << endl;
    springBundle->printProduct();
    cout << endl;

    //create custom products
    ConcreteOrderBuilder customBuilder;
    customBuilder.setPlant("Orchid", 40.0);
    customBuilder.addPot(DecorativePot::ROTUND);
    customBuilder.addWrapping(GiftWrapping::FLORAL_WRAP);
    Product* customOrchid = customBuilder.getProduct();

    cout << "Custom Order" << endl;
    customOrchid->printProduct();
    cout << endl;

    delete valentinesBundle;
    delete springBundle;
    delete customOrchid;
    
    return 0;
}