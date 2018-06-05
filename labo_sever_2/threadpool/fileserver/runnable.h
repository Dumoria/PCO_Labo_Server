#ifndef RUNNABLE_H
#define RUNNABLE_H

class Runnable {
public:
    virtual ~Runnable() {}
    virtual void run() = 0;
    virtual QString id() = 0;
};


#endif // RUNNABLE_H
