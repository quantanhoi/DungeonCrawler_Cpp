#include<Level.h>
#include<Factory.h>
Tile* Level::getTile(int row, int col) {
    return this->stage[row][col];
}
const Tile* Level::getTile(int row, int col) const {
    return this->stage[row][col];
}

void Level::placeCharacter(Character* c, int row, int col) {
    characterVector.push_back(c);
    c->setCurrentTile(this->getTile(row, col));
    c->setLevel(this);
    this->stage[row][col]->pCharacter = c;
}
void Level::placePlayer(int row, int col) {
    Character* char1 = new Character(10, 20, player);
    characterVector.push_back(char1);
    char1->setCurrentTile(this->getTile(row, col));
    char1->setLevel(this);
    char1->setCoord(row, col);
    this->stage[row][col]->pCharacter = char1;
}
void Level::placeNPC(int row, int col) {
    Character* char2 = new Character(60, 5, npc);
    npcVector.push_back(char2);
    char2->setCurrentTile(this->getTile(row, col));
    char2->setLevel(this);
    char2->setCoord(row, col);
    this->stage[row][col]->pCharacter = char2;
}
Level::Level(const Level& level1) {
    {
        for(int i{}; i < numRows; i++) {
            for(int z{}; z < numColumns; z++) {
                stage[i][z] = Factory::createTile(level1.stage[i][z], this, i, z);
                *stage[i][z] = *level1.stage[i][z];

            }
        }
        for(int y{}; y < level1.characterVector.size(); y++) {
            Character* char1 = new Character(level1.characterVector.at(y)->getStrength(),
                                             level1.characterVector.at(y)->getStamina(),
                                             level1.characterVector.at(y)->getCharacterType());
            characterVector.push_back(char1);
            *characterVector.at(y) = *level1.characterVector.at(y);
        }
    }
}
Level& Level::operator=(const Level &level1) {
    for(int i=0; i < numRows; i++) {
        for(int z{}; z < numColumns; z++) {
            stage[i][z] = Factory::createTile(level1.stage[i][z], this, i, z);
            *stage[i][z] = *level1.stage[i][z];

        }
    }
    for(int i{}; i < level1.characterVector.size(); i++) {
        characterVector.at(i) = new Character(level1.characterVector.at(i)->getStrength(),
                                              level1.characterVector.at(i)->getStamina(),
                                              level1.characterVector.at(i)->getCharacterType());
        *characterVector.at(i) = *level1.characterVector.at(i);
    }
    return *this;
}
/*Level::Level() {
    (for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           this->stage[i][z] = new Floor(this, i, z);
        }
    }
    delete stage[1][1];
    delete stage[3][3];
    this->stage[1][1] = new Portal(this, 1, 1, nullptr);
    //Portal* newPort = new Portal(this, 1, 1, nullptr);
    //newPort->connectPortal();
    //this->stage[1][1] = newPort;


    //test Portal
    Portal* newPort = dynamic_cast<Portal*>(this->stage[1][1]);

    this->stage[1][1]= newPort;
    this->stage[3][3] = new Portal(this, 3, 3, newPort);
    Portal* newPort2 = dynamic_cast<Portal*>(this->stage[3][3]);
    newPort2->connectPortal(newPort);
    this->stage[3][3] = newPort2;


    //test door and switch
    delete stage[6][4];
    delete stage[8][7];
    Door* door1 = new Door(this, 6, 4);
    this->stage[6][4] = door1;
    Switch* switch1 = new Switch(this, 8, 7);
    this->stage[8][7] = switch1;
    switch1->attach(door1);


    //test Pit and Ramp
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           if(i == 10 && z < 10 ) {
               this->stage[i][z] = new Pit(this, i, z);
           }
        }
    }
    this->stage[10][10] = new Ramp(this, 10, 10);

    //test Wall
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           if((i== 5 || i == 7) && z < 6 ) {
               this->stage[i][z] = new Wall(this, i, z);
           }
        }
    }
}*/


