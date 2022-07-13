#include<Level.h>
#include<Factory.h>
#include<math.h>
#include<cmath>
#include"Tile.h"
#include<QMessageBox>
void printQMessage(std::string text) {
    QMessageBox msg;
    msg.setText(QString::fromStdString(text));
    msg.exec();

}
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
        for(uint y{}; y < level1.characterVector.size(); y++) {
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
    for(uint i{}; i < level1.characterVector.size(); i++) {
        characterVector.at(i) = new Character(level1.characterVector.at(i)->getStrength(),
                                              level1.characterVector.at(i)->getStamina(),
                                              level1.characterVector.at(i)->getCharacterType());
        *characterVector.at(i) = *level1.characterVector.at(i);
    }
    return *this;
}
int Level::distanceOnFoot(Tile *from, Tile *to) {
    int rowDistance  = std::max(from->getRow(), to->getRow()) - std::min(from->getRow(), to->getRow());
    int colDistance = std::max(from->getCol(), to->getCol()) - std::min(from->getCol(), to->getCol());
    int distance = pow(rowDistance, 2) + pow(colDistance, 2);
    /*QMessageBox msg;
    msg.setText(QString("Row: ")+ QString::number(rowDistance) + QString(" Col: ")+ QString::number(colDistance)
                + QString(" \nDistance: ")+ QString::number(distance));
    msg.exec();*/
    return 10*sqrt(distance);
}
//calculate distance from e.g a npc to a player
int Level::distanceViaPortal(Tile* from, Tile* to) {
    //a number so big that no distance can be compared
    int distance = 999;
    Tile* tempPort;
    for(uint i{}; i < numRows; i ++) {
        for(uint z{}; z < numColumns; z++) {
            if(typeid(*this->getTile(i, z)).name() == typeid (Portal).name()) {
                //we're finding the shortest distance here
                if(distance > distanceOnFoot(from, this->getTile(i, z))) {
                    distance = distanceOnFoot(from, this->getTile(i, z));
                    tempPort = this->getTile(i, z);

                }
            }
        }
    }
    //tempPort->onEnter return connecting port
    QMessageBox msg;
    distance += distanceOnFoot(to, tempPort->onEnter(nullptr, nullptr));
    msg.setText(QString("distance via Portal: ")+ QString::number(distance));
    msg.exec();
    return distance;

}

void sortPath(std::vector<std::vector<std::tuple<int, int, int>>>& allPath) {
    std::sort(allPath.begin(), allPath.end(), [](const std::vector<std::tuple<int, int ,int>>& a, const std::vector<std::tuple<int, int ,int>>& b)
    {
        return std::get<0>(a.at(a.size()-1)) < std::get<0>(b.at(b.size()-1));  //sort according to distance of last element of vector
    });
}
//get normal path and get path via portal separately
std::vector<std::tuple<int, int, int>> Level::getPath(Tile *from, Tile *to) {
    std::vector<std::vector<std::tuple<int, int, int>>> allPath;
    for(int i = from->getRow()-1; i <= from->getRow()+1; i++) {
        for(int z = from->getCol()-1; z <= from->getCol()+1; z++) {
            if(i == from->getRow() && i == from->getCol() ) {
                continue;
            }
            else {
                std::vector<std::tuple<int, int, int>> tmp;
                tmp.push_back(std::make_tuple(distanceOnFoot(this->getTile(i, z) + distanceOnFoot(this->getTile(i, z), to), to), i, z));    //step 1 for all => initializing
                allPath.push_back(tmp);
            }

        }
    }
    //the flooding path begin here
    sortPath(allPath);
    return allPath.at(0);
}
