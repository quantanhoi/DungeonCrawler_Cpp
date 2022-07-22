#ifndef CHARACTER_H
#define CHARACTER_H
#include<iostream>
#include<vector>
#include<array>
#include<string>
#include <chrono>
#include <thread>
#include<string>
#include<QGraphicsPixmapItem>
#include"Button.h"
class Level;
class Tile;
class Controller;
enum CharacterType {
    player, npc
};
enum CharacterStatus {
    dead, alive
};

class Character {
protected:
    static int characterID;
    QPixmap renderedTexture;
    int row, col;
    int Strength, Stamina, Hitpoint;
    CharacterStatus status;
    CharacterType characterType;
    Tile* currentTile;
    Level* level;
    std::string characterString;
    Input moveDirection;
    Tile* oldTile;
    Controller* pController;
public:
    bool hasEnemyFront();
    bool hasEnemyAround();



    int move(Input input);
    void setRenderedTexture();
    void setCoord(int row, int col);
    void moveToTile(int row, int nums);
    Character(int Str, int Stam, CharacterType type) {
        //characterString = std::to_string(characterID);
        characterString = "|";
        characterID++;
        oldTile = NULL;
        pController = nullptr;
        characterType = type;
        Strength = Str;
        Stamina = Stam;
        Hitpoint = getMaxHP();
        if(characterType == player){
            renderedTexture = QPixmap(":/textures/char/front/char_front_2.png");
        }
        else {
            renderedTexture = QPixmap(":/textures/zombie.png");
        }
        setStatus();


    }
    const QPixmap getCharacterTexture() const;
    int getRow() const;
    int getCol() const;
    int getHitpoint() const;
    int getStrength() const;
    int getStamina() const;
    int getMaxHP();
    std::string getCharacterString() const;
    bool fight(Character* other);

    CharacterStatus getStatus() const;
    void setStatus();
    CharacterType getCharacterType() const;
    Tile *getCurrentTile() const;
    void setCurrentTile(Tile *newCurrentTile);
    Level *getLevel() const;
    void setLevel(Level *newLevel);

    Input getMoveDirection() const;
    void setMoveDirection(Input newMoveDirection);
    Tile *getOldTile() const;
    void setOldTile(Tile *newOldTile);
    Controller *getPController() const;
    void setPController(Controller *newPController);
    void movePath(Tile* from, Tile* to);
};



#endif // CHARACTER_H
