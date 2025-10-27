#ifndef IMEDIATOR_H
#define IMEDIATOR_H

#include <string>

class IColleague;  // Forward declaration

class IMediator {
public:
    virtual void notify(IColleague* sender, std::string request) = 0;//handle notifications from customer requests
    virtual ~IMediator() {}
};

#endif // IMEDIATOR_H