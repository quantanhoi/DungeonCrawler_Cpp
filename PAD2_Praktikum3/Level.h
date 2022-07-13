#ifndef LEVEL_H
#define LEVEL_H
#include<iostream>
#include<vector>
#include<array>
#include<string>
#include"Tile.h"
#include"Character.h"

const int numRows = 10;
const int numColumns = 10;

class Tile;
class Factory;
class Character;
class Level {
public:
    std::vector<Character*> characterVector;
    std::vector<Character*> npcVector;
    std::array<std::array<Tile*, numRows>, numColumns> stage;
    Tile* getTile(int row, int col);
    const Tile* getTile(int row, int col) const;
    void placeCharacter(Character* c, int row, int col);
    void placePlayer(int row, int col);
    void placeNPC(int row, int col);
    Level(const Level &level1);
    Level& operator=(const Level& level1);
    Level() {};
    ~Level() {
        for(int i{}; i < characterVector.size(); i++) {
            delete characterVector.at(i);
        }
        for(int z{}; z< numRows; z++ ) {
            for(int y{}; y < numColumns ; y++) {
                delete stage[z][y];
            }
        }
    }
    //prak5
    std::vector<std::tuple<int, int, int >> getPath(Tile* from, Tile* to);    //distance, row, col
    int distanceViaPortal(Tile* from, Tile* to);
    int distanceOnFoot(Tile* from, Tile* to);

};

#endif // LEVEL_H
