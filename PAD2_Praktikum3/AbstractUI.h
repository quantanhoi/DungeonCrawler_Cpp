#ifndef ABSTRACTUI_H
#define ABSTRACTUI_H
#include"Level.h"

class Level;
class Character;
class AbstractUI {
public:
    //virtual void draw(Level* level) = 0;
};
class Controller {
protected:
    Character* pCharacter;
public:
    virtual void chooseCharacter(Level* level) = 0;
    virtual int move(Input in) = 0;
    Character *getPCharacter() const;
};

class TerminalUI : virtual public AbstractUI, virtual public Controller {
public:
    Character* getpCharacter();
    void draw(Level* level) ;
    //int moveCharacter(Level* level, Character* c);
    int move(Input in) override;
    void chooseCharacter(Level* level) override;
    void moveToTile(int row, int col);
};

#endif // ABSTRACTUI_H
