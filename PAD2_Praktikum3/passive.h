#ifndef PASSIVE_H
#define PASSIVE_H

#include"active.h"
class Active;
class Passive{
protected:

public:
    Active* connectedSwitch;
    virtual void notify(Active* source) = 0 ;
    virtual void setTexture() = 0;
    Passive() {};
    virtual ~Passive() {};
};

#endif // PASSIVE_H
