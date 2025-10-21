//
// Created by User on 2025/10/20.
//

#ifndef SAD_TIRED_OBSERVERMEDIATOR_H
#define SAD_TIRED_OBSERVERMEDIATOR_H

#endif //SAD_TIRED_OBSERVERMEDIATOR_H

/*

    OBSERVER NOTIFIES THE RELEVANT STAFF MEMBER TO PERFORMA SPECIFIC ACTION ON A PLANT WHENEVER A PLANT NOTIFIES THAT THEIR STATE HAS CHANGED/PLANT CARE IS REQUIRED

Subject gets attached to a specific observer (staff member) when made and notifies observer based on state change or care needs

attach and detach = pushed/popped to observer list

notify() {
    go through observer list and when reaching a specific observer that can handle its need it notifies that observer to come and help
}

    MEDIATOR DIRECTS COORDINATION BETWEEN THE STAFF AND CUSTOMERS FOR ALL THEIR INTERACTIONS

customers and staff set mediator to Mediator class on initialisation

staffCustomerInteractionNotify(interaction between 2) {
    Depending on Interaction customer wants to do, it triggers interaction with corresponding/correct customer => Commands gets called too?
}

*/