#include<Character.h>
#include<Tile.h>
#include<Level.h>
#include<QMessageBox>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include"levelChanger.h"
#include<QApplication>
/* int move():
 * 1 = links unten
 * 2 = unten
 * 3 = rechts unten
 * 4 = links
 * 5 = bleiben
 * 6 = rechts
 * 7 = links oben
 * 8 = oben
 * 9 = rechts oben
 * 0 = quit
 */
#define numRows 15
#define numColumns 15
int Character::characterID = 1;
const QPixmap Character::getCharacterTexture() const
{
    return renderedTexture;
}

void Character::moveToTile(int row, int col) {
    QMessageBox msgBox;
    if(row < numRows && col < numColumns  && row>= 0  && col >=0) {
        if(!this->currentTile->moveTo(this->level->getTile(row, col), this))
        {          
            msgBox.setText(QString("You cannot move here"));
            msgBox.exec();
            return;
        }
        if(typeid (*this->currentTile) == typeid (levelChanger)) {
            msgBox.setText(QString("moved to new level"));
            msgBox.exec();
            setCoord(this->currentTile->getRow(), this->currentTile->getCol());
            return;
        }
        else {
            setCoord(this->level->getTile(row, col)->onEnter(this->level->getTile(row, col), this)->getRow(),
                     this->level->getTile(row, col)->onEnter(this->level->getTile(row, col), this)->getCol());
            return;
        }
    }
    else {
        msgBox.setText(QString("you can't move outside of the map"));
        msgBox.exec();
        return;
    }
}

int Character::getRow() const
{
    return row;
}

int Character::getCol() const
{
    return col;
}

void Character::setCoord(int r, int c) {
    this->row = r;
    this->col = c;
}

int Character::getHitpoint() const
{
    return Hitpoint;
}

int Character::getStrength() const
{
    return Strength;
}

int Character::getStamina() const
{
    return Stamina;
}
int Character::getMaxHP() {
    return 20+(Stamina*5);
}

CharacterStatus Character::getStatus() const
{
    return status;
}
std::string Character::getCharacterString() const {
    return characterString;
}

void Character::setStatus()
{
    if(this->getHitpoint() > 0) {
        this->status = alive;
    }
    else
        this->status = dead;
}

CharacterType Character::getCharacterType() const
{
    return characterType;
}

Tile *Character::getCurrentTile() const
{
    return currentTile;
}

void Character::setCurrentTile(Tile *newCurrentTile)
{
    currentTile = newCurrentTile;
}

Level *Character::getLevel() const
{
    return level;
}

void Character::setLevel(Level *newLevel)
{
    level = newLevel;
}

int Character::move(Input input) {
    QMessageBox msgBox;
    if(input!= skip){
        moveDirection = input;
    }

    switch (input) {
        case down:
        moveToTile(row+1, col);
        //msgBox.setText(QString("down"));
        //msgBox.exec();
        break;
    case down_left:
        moveToTile(row+1, col-1);
        //msgBox.setText(QString("down_left"));
        //msgBox.exec();
        break;
    case down_right:
        moveToTile(row+1, col+1);
        //msgBox.setText(QString("down_right"));
        //msgBox.exec();
        break;
    case right:
        moveToTile(row, col+1);
        //msgBox.setText(QString("right"));
        //msgBox.exec();
        break;
    case left:
        moveToTile(row, col-1);
        //msgBox.setText(QString("left"));
        //msgBox.exec();
        break;
    case skip:
        //this->level->distanceViaPortal(this->currentTile, this->getLevel()->getTile(4, 5));  //lootchest
        this->getLevel()->aStar(this->currentTile, this->getLevel()->getTile(4, 5));
        //hasEnemyAround();
        //QApplication::quit();
        //msgBox.setText(QString("skip"));
        //msgBox.exec();
        break;
    case up_left:
        moveToTile(row-1, col-1);
        //msgBox.setText(QString("up_left"));
        //msgBox.exec();
        break;
    case up:
        moveToTile(row-1, col);
        //msgBox.setText(QString("up"));
        //msgBox.exec();
        break;
    case up_right:
        moveToTile(row-1, col+1);
        //msgBox.setText(QString("up_right"));
        //msgBox.exec();
        break;
        default:
        //msgBox.setText(QString("Default"));
        //msgBox.exec();
        break;
    }
    setRenderedTexture();
    return 1;

}
void Character::setRenderedTexture() {
    int random;
    switch (moveDirection) {
        case down :case down_left: case down_right:
        random = rand()%3+1;
        switch (random) {
            case 1:
            renderedTexture = QPixmap(":/textures/char/front/char_front_1.png");
            break;
            case 2:
            renderedTexture = QPixmap(":/textures/char/front/char_front_2.png");
            break;
            case 3:
            renderedTexture = QPixmap(":/textures/char/front/char_front_3.png");
            break;
        default:
            renderedTexture = QPixmap(":/textures/char/front/char_front_1.png");
            break;
        }
        break;
    case left:
        random = rand()%3+1;
        switch (random) {
            case 1:
            renderedTexture = QPixmap(":/textures/char/left/char_left_1.png");
            break;
            case 2:
            renderedTexture = QPixmap(":/textures/char/left/char_left_2.png");
            break;
            case 3:
            renderedTexture = QPixmap(":/textures/char/left/char_left_3.png");
            break;
        default:
            renderedTexture = QPixmap(":/textures/char/left/char_left_1.png");
            break;
        }
        break;
    case right:
        random = rand()%3+1;
        switch (random) {
            case 1:
            renderedTexture = QPixmap(":/textures/char/right/char_right_1.png");
            break;
            case 2:
            renderedTexture = QPixmap(":/textures/char/right/char_right_2.png");
            break;
            case 3:
            renderedTexture = QPixmap(":/textures/char/right/char_right_3.png");
            break;
        default:
            renderedTexture = QPixmap(":/textures/char/right/char_right_1.png");
            break;
        }
        break;
    case up: case up_left: case up_right:
        random = rand()%3+1;
        switch (random) {
            case 1:
            renderedTexture = QPixmap(":/textures/char/back/char_back_1.png");
            break;
            case 2:
            renderedTexture = QPixmap(":/textures/char/back/char_back_2.png");
            break;
            case 3:
            renderedTexture = QPixmap(":/textures/char/back/char_back_3.png");
            break;
        default:
            renderedTexture = QPixmap(":/textures/char/back/char_back_1.png");
            break;
        }
        break;
    default:
        renderedTexture = QPixmap(":/textures/char/front/char_front_2.png");
        break;


    }
}

Input Character::getMoveDirection() const
{
    return moveDirection;
}

void Character::setMoveDirection(Input newMoveDirection)
{
    moveDirection = newMoveDirection;
}

Tile *Character::getOldTile() const
{
    return oldTile;
}

void Character::setOldTile(Tile *newOldTile)
{
    oldTile = newOldTile;
}

Controller *Character::getPController() const
{
    return pController;
}

void Character::setPController(Controller *newPController)
{
    pController = newPController;
}

bool Character::hasEnemyFront() {
    QMessageBox message;
    switch(moveDirection) {
    case down :case down_left: case down_right:   //case down in general
            for(int i = this->getCol()-1; i < this->getCol()+1; i++) {
                if(this->getRow()+1 < numRows && (i < numColumns && i >= 0))
                {
                    if(this->getLevel()->getTile(this->getRow()+1, i)->hasCharacter()) {
                        message.setText( QString("enemy"));
                        message.exec();
                        return true;
                    }
                }
            }
        break;
        case left:
            for(int i = this->getRow()-1; i < this->getRow()+1; i++) {
                if(this->getCol()-1 >= 0 && (i < numRows && i >= 0))
                {
                    if(this->getLevel()->getTile(i, this->getCol()-1)->hasCharacter()) {
                        message.setText( QString("enemy"));
                        message.exec();
                        return true;
                    }
                }
            }
        break;
        case right:
            for(int i = this->getRow()-1; i < this->getRow()+1; i++) {
                if(this->getCol()+1 < numColumns && (i < numRows && i >= 0))
                {
                    if(this->getLevel()->getTile(i, getCol()+1)->hasCharacter()) {
                        message.setText( QString("enemy"));
                        message.exec();
                        return true;
                    }
                }
            }
        break;
        case up: case up_left: case up_right:
            for(int i = this->getCol()-1; i < this->getCol()+1; i++) {
                if(this->getRow()-1 <= 0 && (i < numColumns && i >= 0))
                {
                    if(this->getLevel()->getTile(this->getRow()-1, i)->hasCharacter()) {
                        message.setText( QString("enemy"));
                        message.exec();
                        return true;
                    }
                }
            }
        break;
        default:
        break;
    }
    return false;
}
bool Character::hasEnemyAround() {
    QMessageBox msg;
    for(int i = this->getRow()-1; i <= this->getRow()+1; i++) {
        for(int z = this->getCol()-1; z <= this->getCol()+1; z++) {
            if(i < numRows && z < numColumns && i >=0 && z >= 0) {
                if(this->level->getTile(i, z)->hasCharacter()) {
                    if(this->level->getTile(i, z)->pCharacter->getCharacterType() != this->getCharacterType()) {
                        msg.setText(QString("has Enemy"));
                        msg.exec();
                        this->fight(this->level->getTile(i, z)->pCharacter);
                        return true;
                    }
                }
            }
        }
    }
    msg.setText(QString("No Enemy"));
    msg.exec();
    return false;
}
bool Character::fight(Character *other) {
    other->Hitpoint -= this->Strength;
    this->Hitpoint -= other->getStrength();
    this->setStatus();
    other->setStatus();
    return true;
}
