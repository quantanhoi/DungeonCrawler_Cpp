#ifndef ACTIVE_H
#define ACTIVE_H
#include"iostream"
#include"vector"
class Passive;
class Active {
protected:
    std::vector<Passive*> passiveObjects;
public:
    int attach(Passive* pPassive);
    int detach(Passive* pPassive);
    void activate();
    Active() {};
    virtual ~Active() {};
    std::vector<Passive *> &getPassiveObjects();
};

#endif // ACTIVE_H
