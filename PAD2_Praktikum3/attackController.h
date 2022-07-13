#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H

#include"AbstractUI.h"
class attackController : virtual public Controller
{
public:
    Character* chooseTarget();
    attackController();
    void chooseCharacter(Level* level) override;
    int move(Input in) override;
};

#endif // ATTACKCONTROLLER_H
