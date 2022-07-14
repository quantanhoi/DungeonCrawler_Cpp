#include<Level.h>
#include<Factory.h>
#include<math.h>
#include<cmath>
#include"Tile.h"
#include<QMessageBox>
#include"node.h"
#include"float.h"
#include<stack>
#include<map>
#include"levelChanger.h"

void printQMessage(std::string text) {
    QMessageBox msg;
    msg.setText(QString::fromStdString(text));
    msg.exec();

}
bool Level::isValidNode(int x, int y) {     //only wall return nullptr
    if(typeid (*this->getTile(x, y)).name() == typeid (levelChanger).name()
            || typeid (*this->getTile(x, y)).name() == typeid (Portal).name()) {
        std::cout << "shitttttt" << std::endl;
        return false;
    }
    if(this->getTile(x, y)->hasCharacter()) {
        return false;
    }
    if(this->getTile(x, y)->onEnter(this->getTile(x, y), nullptr) != nullptr) {
        return true;
    }
    return false;
}
bool Level::isDestination(int x, int y, Tile *to) {
    if(x == to->getRow() && y == to->getCol()) {
        return true;
    }
    return false;
}

std::vector<Node> Level::aStar(Tile *player, Tile *dest)
{
    std::vector<Node> empty;
    if (isValidNode(dest->getRow(), dest->getCol()) == false) {
        std::cout << "Destination is an obstacle" << std::endl;
        return empty;
        //Destination is invalid
    }
    if (isDestination(player->getRow(), player->getCol(), dest)) {
        std::cout << "You are the destination" << std::endl;
        return empty;
        //You clicked on yourself
    }

    bool closedList[numRows][numColumns];
    //Initialize whole map AGAIN
    std::array<std::array<Node, numRows>, numColumns> allMap;
    for (int x = 0; x < numRows; x++) {
        for (int y = 0; y < numColumns; y++) {
            allMap[x][y].fCost = FLT_MAX;
            allMap[x][y].gCost = FLT_MAX;
            allMap[x][y].hCost = FLT_MAX;
            allMap[x][y].parentX = -1;
            allMap[x][y].parentY = -1;
            allMap[x][y].tile = this->getTile(x, y);
            allMap[x][y].x = x;
            allMap[x][y].y = y;
            closedList[x][y] = false;
        }
    }

    Node destination = allMap[dest->getRow()][dest->getCol()];
    Node Start = allMap[player->getRow()][player->getCol()];
    //Initialize our starting list
    int x = Start.x;
    int y = Start.y;
    allMap[x][y].fCost = 0.0;
    allMap[x][y].gCost = 0.0;
    allMap[x][y].hCost = 0.0;
    allMap[x][y].parentX = x;
    allMap[x][y].parentY = y;

    std::vector<Node> openList;
    openList.emplace_back(allMap[x][y]);
    bool destinationFound = false;

    while (!openList.empty() && openList.size() < numRows*numColumns) {
        Node node;
        do {
            //This do-while loop could be replaced with extracting the first
            //element from a set, but you'd have to make the openList a set.
            //To be completely honest, I don't remember the reason why I do
            //it with a vector, but for now it's still an option, although
            //not as good as a set performance wise.
            float temp = FLT_MAX;
            std::vector<Node>::iterator itNode;
            for (std::vector<Node>::iterator it = openList.begin();
                it != openList.end(); it = next(it)) {
                Node n = *it;
                if (n.fCost < temp) {
                    temp = n.fCost;
                    itNode = it;
                }
            }
            node = *itNode;
            openList.erase(itNode);
        } while (isValidNode(node.x, node.y) == false);

        x = node.x;
        y = node.y;
        closedList[x][y] = true;

        //For each neighbour starting from North-West to South-East
        for (int newX = -1; newX <= 1; newX++) {
            for (int newY = -1; newY <= 1; newY++) {
                double gNew, hNew, fNew;
                if (isValidNode(x + newX, y + newY)) {
                    if (isDestination(x + newX, y + newY, dest))
                    {
                        //Destination found - make path
                        allMap[x + newX][y + newY].parentX = x;
                        allMap[x + newX][y + newY].parentY = y;
                        destinationFound = true;
                        return makePath(allMap, destination);
                    }
                    else if (closedList[x + newX][y + newY] == false)
                    {
                        gNew = node.gCost + 1.0;
                        hNew = calculateH(x + newX, y + newY, dest);
                        fNew = gNew + hNew;
                        // Check if this path is better than the one already present
                        if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
                            allMap[x + newX][y + newY].fCost > fNew)
                        {
                            // Update the details of this neighbour node
                            allMap[x + newX][y + newY].fCost = fNew;
                            allMap[x + newX][y + newY].gCost = gNew;
                            allMap[x + newX][y + newY].hCost = hNew;
                            allMap[x + newX][y + newY].parentX = x;
                            allMap[x + newX][y + newY].parentY = y;
                            openList.emplace_back(allMap[x + newX][y + newY]);
                        }
                    }
                }
            }
        }
    }
    if (!destinationFound) {
        std::cout << "Destination not found" << std::endl;
        return empty;
    }
}

float Level::calculateH(int x, int y, Tile * dest)
{
    return distanceOnFoot(this->getTile(x, y), dest);
}

std::vector<Node> Level::makePath(std::array<std::array<Node, numRows>, numColumns> map, Node dest)
{
    try {
        QMessageBox msg;
        msg.setText(QString("Found a path"));
        msg.exec();
        std::cout << "Found a path" << std::endl;
        int x = dest.x;
        int y = dest.y;
        std::stack<Node> path;
        std::vector<Node> usablePath;
        while (!(map[x][y].parentX == x && map[x][y].parentY == y)
            && map[x][y].x != -1 && map[x][y].y != -1)
        {
            path.push(map[x][y]);
            int tempX = map[x][y].parentX;
            int tempY = map[x][y].parentY;
            x = tempX;
            y = tempY;

        }
        path.push(map[x][y]);


        while (!path.empty()) {
            Node top = path.top();
            path.pop();
            usablePath.emplace_back(top);
        }
        for(Node x : usablePath) {
            std::cout << x.x << " " << x.y << std::endl;
        }
        return usablePath;
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }

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
float Level::distanceOnFoot(Tile *from, Tile *to) {
    int rowDistance  = std::max(from->getRow(), to->getRow()) - std::min(from->getRow(), to->getRow());
    int colDistance = std::max(from->getCol(), to->getCol()) - std::min(from->getCol(), to->getCol());
    int distance = pow(rowDistance, 2) + pow(colDistance, 2);
    /*QMessageBox msg;
    msg.setText(QString("Row: ")+ QString::number(rowDistance) + QString(" Col: ")+ QString::number(colDistance)
                + QString(" \nDistance: ")+ QString::number(distance));
    msg.exec();*/
    return sqrt(distance);
}
//calculate distance from e.g a npc to a player
float Level::distanceViaPortal(Tile* from, Tile* to) {
    //a number so big that no distance can be compared
    float distance = FLT_MAX;
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
            if(!from->moveTo(this->getTile(i, z), nullptr)) {
                continue;
            }
            else {
                float fcost = distanceOnFoot(from, this->getTile(i, z))  + distanceOnFoot(this->getTile(i, z), to);
                std::vector<std::tuple<int, int, int>> tmp;
                tmp.push_back(std::make_tuple(fcost, i, z));    //step 1 for all => initializing
                allPath.push_back(tmp);
            }

        }
    }
    //the flooding path begin here
    sortPath(allPath);

    return allPath.at(0);
}
void Level::pathFlooding(std::vector<std::vector<std::tuple<int, int, int>>> &allPath, Tile *from, Tile *to) {
    while(std::get<0>(allPath.at(0).at(allPath.at(0).size()-1)) < std::get<0>(allPath.at(1).at(allPath.at(1).size()-1))) {

    }
}

