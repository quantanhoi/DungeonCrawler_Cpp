#include "lootChest.h"
#include"DungeonCrawler.h"
#include<QMessageBox>
lootChest::lootChest(Level* stage, int r, int c, DungeonCrawler* gamePlay) : Tile(stage, row , col)
{
    pCharacter = nullptr;
    pLevel = stage;
    texture = "$";
    row = r;
    col = c;
    renderedTexture = QPixmap(":/textures/chest.png");
    found = false;
    game = gamePlay;

}
void lootChest::endgame() {
    if(this->hasCharacter()) {
        found = true;
    }
    game->setGameEnd(found);
}
Tile* lootChest::onEnter(Tile *fromTile, Character *who) {
    QMessageBox msg;
    msg.setText(QString("Found the chest"));
    msg.exec();
    return this;

}
Tile* lootChest::onLeave(Tile *destTile, Character *who) {
    return this;
}
