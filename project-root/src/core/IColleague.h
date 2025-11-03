#ifndef ICOLLEAGUE_H
#define ICOLLEAGUE_H

#include <string>
#include <iostream>
#include "IMediator.h"  // For setMediator

using namespace std;

class IColleague {
public:
    virtual void setMediator(IMediator* mediator) = 0;//set mediator for this colleague
    virtual void sendRequest(string request) = 0;//send request via mediator
    virtual string getName() const = 0;//get colleagues name
    virtual ~IColleague() {}
};

#endif // ICOLLEAGUE_H