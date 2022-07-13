#include "active.h"
#include"Tile.h"
std::vector<Passive *> &Active::getPassiveObjects()
{
    return passiveObjects;
}

int Active::attach(Passive *pPassive) {
    for(int i{}; i < passiveObjects.size(); i ++) {
        if(passiveObjects.at(i) == pPassive) {
            return 0;
        }
    }
    this->passiveObjects.push_back(pPassive);
    pPassive->connectedSwitch = this;
    return 0;
}
int Active::detach(Passive *pPassive) {
    for(int i{}; i < passiveObjects.size(); i ++) {
        if(passiveObjects.at(i) == pPassive) {
            passiveObjects.erase(passiveObjects.begin()+i);
            return 0;
        }
    }
    return 0;
}
void Active::activate() {
    for(int i{}; i < passiveObjects.size(); i++) {
        passiveObjects.at(i)->notify(this);
        passiveObjects.at(i)->setTexture();
    }
}

Tile* Switch::onEnter(Tile *fromTile, Character *who) {
    this->activate();
    return this;
}
Tile* Switch::onLeave(Tile *destTile, Character *who) {
    return this;
}
