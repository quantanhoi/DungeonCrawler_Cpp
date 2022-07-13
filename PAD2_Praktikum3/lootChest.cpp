#include "lootChest.h"
#include"DungeonCrawler.h"
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
Tile* lootChest::onEnter(Tile *fromTile, Character *who) {
    found = true;
    game->setGameEnd(found);
    return this;

}
Tile* lootChest::onLeave(Tile *destTile, Character *who) {
    return this;
}
