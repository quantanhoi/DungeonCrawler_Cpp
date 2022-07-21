#ifndef TILE_H
#define TILE_H
#include<iostream>
#include<vector>
#include<array>
#include<string>
#include"passive.h"
#include"active.h"
#include<QPixmap>
#include<QGraphicsPixmapItem>
#define log(x) std::cout << x << std::endl;
class Level;
class Character;
class Active;
class Passive;
class Floor;
class Tile {
protected:
    std::string texture;
    int row;
    int col;
    Level* pLevel;
    QPixmap renderedTexture;
public:  
    Character* pCharacter;
    std::string getTexture();
    std::string getCharacterTexture();
    int getRow() const;
    int getCol() const;
    bool hasCharacter();
    bool moveTo(Tile* destTile, Character* who) ;
    virtual Tile* onEnter(Tile* fromTile, Character* who) = 0;          //Betreten einer kachel
    virtual Tile* onLeave(Tile* destTile, Character* who) = 0;          //Verlassen der kachel
    //onEnter and onLeave sind Bewegungsablauf
    //Passive and Active
    virtual ~Tile() {};
    Tile(Level* stage, int r, int c);
    Tile(const Tile &tile1);

    const QPixmap &getRenderedTexture() const;
    Level *getPLevel() const;
};

class Floor :  virtual public Tile {
public:
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;
    Floor(Level* stage, int r, int c);
    ~Floor() {};

};


class Wall : virtual public Tile {
public:
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;
    Wall(Level* stage, int r, int c);
    ~Wall() {
    };
};


class Portal : virtual public Tile {
protected:
    Portal* connectingPortal;
public:
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;
    void connectPortal(Portal* secondPort);
    Portal(Level* stage, int r, int c, Portal* port);
    ~Portal() {};
    Portal *getConnectingPortal() const;
};



class Door :  virtual public Passive, virtual public Tile {
protected:
    bool status = false;
public:
    void notify(Active* source) override;
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;
    void setDoorTexture();
    void setTexture() override;
    Door(Level* stage, int r, int c);
    ~Door(){};
    bool getStatus() const;
    void setStatus(bool newStatus);
};

class Switch : public Active, virtual public Tile {
public:
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;
    Switch(Level* stage, int r, int c);
    ~Switch(){};

};
class Pit: virtual public Tile {
public:
    Pit(Level* stage, int r, int c): Tile(stage, r, c) {
        texture = "v";
        pCharacter = nullptr;
        pLevel = stage;
        row = r;
        col = c;
        renderedTexture = QPixmap(":/textures/pit.png");
    }
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;

};
class Ramp : virtual public Tile {
public:
    Ramp(Level* stage, int r, int c): Tile(stage, r, c) {
        texture = "=";
        pCharacter = nullptr;
        pLevel = stage;
        row = r;
        col = c;
        renderedTexture = QPixmap(":/textures/ramp.png");
    }
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;
};



#endif // TILE_H
