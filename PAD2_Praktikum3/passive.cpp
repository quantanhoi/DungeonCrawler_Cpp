#include "passive.h"
#include"Tile.h"
Tile* Door::onEnter(Tile *fromTile, Character *who) {
    if(this->status)        //if door is shut, can not enter
    {
        return this;
    }
    else return nullptr;
}
Tile* Door::onLeave(Tile *destTile, Character *who) {
    return this;
    //if we're already on the door, that means door is opened
}
void Door::notify(Active *source) {
    if(!this->status) {
        status = true;
        texture = "/";
    }
    else {
        status = false;
        texture = "-";
    }
}
