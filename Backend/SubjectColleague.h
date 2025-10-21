#ifndef SUBJECTCOLLEAGUE_H
#define SUBJECTCOLLEAGUE_H

#include <iostream>
using namespace std;

class ObserverMediator;

class SubjectColleague {
public:
    virtual ~SubjectColleague() = default;
    virtual void Attach(ObserverMediator* observer) = 0;
    virtual void Detach(ObserverMediator* observer) = 0;
    virtual void Notify() = 0;

    void setMediator(ObserverMediator* mediator) {
        this->mediator_ = mediator;
    }
protected:
    ObserverMediator* mediator_;
};


#endif //SUBJECTCOLLEAGUE_H