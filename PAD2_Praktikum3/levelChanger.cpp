#include "levelChanger.h"
#include"DungeonCrawler.h"

Level* levelChanger::getConnectingLevel() const
{
    return connectingLevel;
}
levelChanger::levelChanger(Level* stage, int r, int c, DungeonCrawler* spiel) : Tile(stage, row , col){
    pCharacter = nullptr;
    game = spiel;
    pLevel = stage;
    connectingChanger = nullptr;
    texture = ">";
    row = r;
    col = c;
    renderedTexture = QPixmap(":/textures/levelchanger.png");

}
levelChanger *levelChanger::getConnectingChanger() const
{
    return connectingChanger;
}

void levelChanger::setConnectingChanger(levelChanger *newConnectingChanger)
{
    connectingChanger = newConnectingChanger;
}

Tile* levelChanger::onEnter(Tile* fromTile, Character* who) {

    for(int i =0; i < game->getCurrentLevel()->characterVector.size(); i ++) {
        if( game->getCurrentLevel()->characterVector.at(i) == who) {
            game->getCurrentLevel()->characterVector.erase(game->getCurrentLevel()->characterVector.begin()+i);
        }
    }

    game->setCurrentLevel(connectingChanger->pLevel);
    who->setLevel(game->getCurrentLevel());
    game->getCurrentLevel()->characterVector.push_back(who);
    for(game->iterator = game->getLevelList()->begin(); *game->iterator != this->connectingChanger->pLevel; ++game->iterator) {}
    who->setCurrentTile(game->getCurrentLevel()->getTile(connectingChanger->getRow(), connectingChanger->getCol()));
    game->getCurrentLevel()->stage[connectingChanger->getRow()][connectingChanger->getCol()]->pCharacter = who;
    return connectingChanger;
}

Tile* levelChanger::onLeave(Tile* fromTile, Character* who) {
    return this;
}
void levelChanger::connectLevelChanger(levelChanger *connectingLevelChanger) {
    connectingChanger = connectingLevelChanger;
    connectingLevelChanger->setConnectingChanger(this);
}
