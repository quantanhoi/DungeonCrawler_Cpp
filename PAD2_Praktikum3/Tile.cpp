#include"Tile.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<Character.h>
#include<QMessageBox>
#include "levelChanger.h"
#include"lootChest.h"
Tile::Tile(Level* stage, int r, int c){
    pCharacter = nullptr;
    pLevel = stage;
    row = r;
    col = c;
}
Tile::Tile(const Tile &tile1) {
    texture = tile1.texture;
    row = tile1.row;
    col = tile1.col;
    pLevel = tile1.pLevel;
    pCharacter = tile1.pCharacter;
}
std::string Tile::getCharacterTexture() {
    if(hasCharacter()) {
        return this->pCharacter->getCharacterString();
    }
    else return getTexture();
}
const QPixmap &Tile::getRenderedTexture() const
{
    return renderedTexture;
}

std::string Tile::getTexture() {
    return texture;
}

bool Tile::hasCharacter() {
    if(pCharacter != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

bool Tile::moveTo(Tile* destTile, Character* who) {
    if(destTile->hasCharacter()) {
        if(destTile->pCharacter->getCharacterType() != who->getCharacterType()) {
            log("A character is already here");
            who->fight(destTile->pCharacter);
        }
        return false;
    }
    if(this->onLeave(destTile, who)!= nullptr) {
        if(destTile->onEnter(destTile, who)!= nullptr) {
            who->setOldTile(this);
            //save this address oldTile address
            who->setCurrentTile(destTile->onEnter(destTile,who));
            //move to new tiles, or to the next Portal
            this->pCharacter= nullptr;
            //delete the old tile's pCharacter
            destTile->pCharacter = who;
            //character who moved to new Tile

            if(typeid (*destTile).name() == typeid (Portal).name()) {   //portal
                //if the character move into a portal, delete pCharacter in the first Portal
                //instead move it to 2nd portal instead
                destTile->pCharacter = nullptr;
                destTile->onEnter(destTile, who)->pCharacter = who;

                return true;
            }
            if(typeid (*destTile).name() == typeid (Switch).name()) {  //switch
                destTile->onEnter(destTile, who);
                return true;
            }
            if(typeid (*destTile).name() == typeid (levelChanger).name()) {
                destTile->pCharacter = nullptr;
                destTile->pCharacter = who;
            }
            if(typeid (*destTile).name() == typeid (lootChest).name()) {
                dynamic_cast<lootChest*>(destTile)->endgame();
        }
            return true;
        }
        else {
            log("Unable to Enter here");
            return false;
        }
    return true;
    }
    else {
        log("Unable to leave");
        return false;
    }
}



int Tile::getRow() const {
    return row;
}
int Tile::getCol() const {
    return col;
}

Floor::Floor(Level* stage, int r, int c)  : Tile(stage, r, c){
    pCharacter = nullptr;
    pLevel = stage;
    texture = ".";
    row = r;
    col = c;
    int random;
    random = rand()% 5 +1;
    switch(random) {
        case 1:
        renderedTexture = QPixmap(":/textures/floor/floor1.png");
        break;
        case 2:
        renderedTexture = QPixmap(":/textures/floor/floor2.png");
        break;
        case 3:
        renderedTexture = QPixmap(":/textures/floor/floor3.png");
        break;
        case 4:
        renderedTexture = QPixmap(":/textures/floor/floor4.png");
        break;
        default:
        renderedTexture = QPixmap(":/textures/floor/floor5.png");
        break;
    }
}
Wall::Wall(Level* stage, int r, int c) : Tile(stage, row, col){
    pCharacter = nullptr;
    pLevel = stage;
    texture = "#";
    row = r;
    col = c;
    renderedTexture = QPixmap(":/textures/wall/wall1.png");

}
Portal::Portal(Level* stage, int r, int c, Portal* port) : Tile(stage, row , col){
    pCharacter = nullptr;
    pLevel = stage;
    connectingPortal = port;
    texture = "O";
    row = r;
    col = c;
    renderedTexture = QPixmap(":/textures/portal/portal1.png");

}
Door::Door(Level* stage, int r, int c) : Tile(stage, r, c){
    texture = "-";
    pCharacter = nullptr;
    connectedSwitch = nullptr;
    pLevel = stage;
    row = r;
    col = c;
    setDoorTexture();
    
}
Switch::Switch(Level* stage, int r, int c): Tile(stage, r, c) {
    texture = "?";
    pCharacter = nullptr;
    pLevel = stage;
    row = r;
    col = c;
    renderedTexture = QPixmap(":/textures/switch.png");
}

Tile* Floor::onEnter(Tile *fromTile, Character *who) {
    return this;
}
Tile* Floor::onLeave(Tile *destTile, Character *who) {
    return this;
}

Tile* Wall::onEnter(Tile *fromTile, Character *who) {
    return nullptr;
}
Tile* Wall::onLeave(Tile *destTile, Character *who) {
    return this;
}



//Portal
Portal *Portal::getConnectingPortal() const
{
    return connectingPortal;
}

Tile* Portal::onEnter(Tile *fromTile, Character *who) {
    return this->connectingPortal;
}
Tile* Portal::onLeave(Tile *destTile, Character *who) {
    return this;
}
void Portal::connectPortal(Portal *secondPort) {
    connectingPortal = secondPort;
    secondPort->connectingPortal = this;
}


//Pit
Tile* Pit::onEnter(Tile *fromTile, Character *who) {
    return this;
}
Tile* Pit::onLeave(Tile *destTile, Character *who) {
    if(typeid(*destTile).name() == typeid(Pit).name()
        || typeid(*destTile).name() == typeid(Ramp).name()) {
        return this;
    }
    else {
        return nullptr;
    }
}
//

Tile* Ramp::onEnter(Tile *fromTile, Character *who) {
    return this;
}
Tile* Ramp::onLeave(Tile *destTile, Character *who) {
    return this;
}
void Door::setTexture() {
    setDoorTexture();
}
bool Door::getStatus() const
{
    return status;
}

void Door::setDoorTexture() {
    if(status) {
        renderedTexture = QPixmap(":/textures/doors/door2.png");
    }
    else {
        renderedTexture = QPixmap(":/textures/doors/door1.png");
    }
}





