#ifndef OBSERVERMEDIATOR_H
#define OBSERVERMEDIATOR_H
#include <string>

#include "SubjectColleague.h"

class ObserverMediator {
public:
    virtual void Update(const std::string &message_from_subject) = 0;
    virtual void notify(SubjectColleague* colleague, string event) = 0;
};


#endif //OBSERVERMEDIATOR_H