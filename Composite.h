//
// Created by User on 2025/10/20.
//

#ifndef SAD_TIRED_COMPOSITE_H
#define SAD_TIRED_COMPOSITE_H

#endif //SAD_TIRED_COMPOSITE_H

/*

    WHEN A CUSTOMER PURCHASES MULTIPLE PRODUCTS, SOME MAY BE BUNDLE PRODUCTS MADE OF MULTIPLE INDIVIDUAL PRODUCT COMPONENTS

add(product) {
    adds product to composite object
}

remove(product) {
    deletes product from bundle if it exists else error: product already removed or didn't exist
}

getChild(int) {
    return the child of composite object if it exists, else we're at the end of bundle, so stop
}

operation() {
    go through product branch by branch of composite tree and add to order/make order and return the full order including composites

    string result;
    for (const Component *c : children_) {
      if (c == children_.back()) {
        result += c->Operation();
      } else {
        result += c->Operation() + "+";
      }
    }
    return "Product(" + result + ")";
}

*/