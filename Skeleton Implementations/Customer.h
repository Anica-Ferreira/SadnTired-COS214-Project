#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <list>

#include "ObserverMediator.h"
#include "SubjectColleague.h"


class Customer : public SubjectColleague{
private:
    list<ObserverMediator*> list_observer_;
    string message_;
public:
    Customer();
    void Attach(ObserverMediator* observer) override;
    void Detach(ObserverMediator* observer) override;
    void Notify() override;

    void CreateMessage(string message = "Default Message");
    void doA() {
        cout << "Customer: 'Can you help do A?' " << endl;
        this->mediator_->notify(this,"Customer Interaction A");
    }
    void doB() {
        cout << "Customer: 'What about B?' " << endl;
        this->mediator_->notify(this,"Customer Interaction B");
    }
};


#endif //CUSTOMER_H