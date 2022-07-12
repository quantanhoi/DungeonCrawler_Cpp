#include"Factory.h"
Tile* Factory::createTile(const Tile* x, Level* level, int r, int c) {
    if(typeid(*x) == typeid (Floor))
    {
        return new Floor(level, r, c);
    }
    if(typeid(*x) == typeid (Wall))
    {
        return new Wall(level, r, c);
    }
    if(typeid(*x) == typeid (Portal))
    {
        return new Portal(level, r, c, nullptr);
    }
    if(typeid(*x) == typeid (Pit))
    {
        return new Floor(level, r, c);
    }
    if(typeid(*x) == typeid (Ramp))
    {
        return new Floor(level, r, c);
    }
    if(typeid(*x) == typeid (Switch))
    {
        return new Floor(level, r, c);
    }
    if(typeid(*x) == typeid (Door))
    {
        return new Floor(level, r, c);
    }
    else return 0;
}
