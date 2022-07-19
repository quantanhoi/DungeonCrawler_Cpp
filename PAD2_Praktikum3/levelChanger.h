#ifndef LEVELCHANGER_H
#define LEVELCHANGER_H
#include<iostream>

#include "Tile.h"
class DungeonCrawler;
class Level;
class levelChanger : virtual public Tile {
protected:
    Level* connectingLevel;
    levelChanger* connectingChanger;
    DungeonCrawler* game;
public:
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;
    void connectLevelChanger(levelChanger* connectingLevelChanger);
    levelChanger(Level* stage, int r, int c, DungeonCrawler* spiel);
    ~levelChanger() {};
    Level *getConnectingLevel() const;
    levelChanger *getConnectingChanger() const;
    void setConnectingChanger(levelChanger *newConnectingChanger);
};
#endif // LEVELCHANGER_H
