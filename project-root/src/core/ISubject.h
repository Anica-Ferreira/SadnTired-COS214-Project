#ifndef ISUBJECT_H
#define ISUBJECT_H

class IObserver;  // Forward declaration

class ISubject {
public:
    virtual void Attach(IObserver* observer) = 0;//add observer
    virtual void Detach(IObserver* observer) = 0;//remove observer
    virtual void Notify() = 0;//notify all attached observers
    virtual ~ISubject() {}
};

#endif // ISUBJECT_H