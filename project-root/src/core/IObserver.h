#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <string>
#include <iostream>

using namespace std;

class IObserver {
public:
    virtual void Update(string message) = 0;//when subject notifies, handle update message
    virtual ~IObserver() {}
};

#endif // IOBSERVER_H