#ifndef LOOTCHEST_H
#define LOOTCHEST_H
#include<iostream>
#include"Tile.h"
class DungeonCrawler;
class lootChest : virtual public Tile
{
private:
    DungeonCrawler* game;
    bool found;
public:
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;
    lootChest(Level* stage, int r, int c, DungeonCrawler* gamePlay);
    ~lootChest() {};
    void endgame();
};

#endif // LOOTCHEST_H
