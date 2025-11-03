#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <string>

class IObserver {
public:
    virtual void Update(std::string message) = 0;//when subject notifies, handle update message
    virtual ~IObserver() {}
};

#endif // IOBSERVER_H