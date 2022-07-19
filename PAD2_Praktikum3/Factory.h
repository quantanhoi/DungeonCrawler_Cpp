#ifndef FACTORY_H
#define FACTORY_H
#include"Tile.h"
class Level;
class Tile;
class Factory {
public:
    static Tile* createTile(const Tile* x, Level* level, int r, int c);
};
#endif // FACTORY_H
