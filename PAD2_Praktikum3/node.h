#ifndef NODE_H
#define NODE_H
#include<iostream>
#include"Tile.h"
//https://dev.to/jansonsa/a-star-a-path-finding-c-4a4h

// G cost: distance from starting node
// H cost: distance to end node
// F cost: total distance
//We use H cost and F cost so we first check nodes that move towards our destination and only then the ones that move away from it.
struct Node
{
    Tile* tile;
    int x;
    int y;
    int parentX;
    int parentY;
    float gCost;
    float hCost;
    float fCost;
};

#endif // NODE_H
