#ifndef ICOLLEAGUE_H
#define ICOLLEAGUE_H

#include <string>
#include "IMediator.h"  // For setMediator

class IColleague {
public:
    virtual void setMediator(IMediator* mediator) = 0;//set mediator for this colleague
    virtual void sendRequest(std::string request) = 0;//send request via mediator
    virtual std::string getName() const = 0;//get colleagues name
    virtual ~IColleague() {}
};

#endif // ICOLLEAGUE_H