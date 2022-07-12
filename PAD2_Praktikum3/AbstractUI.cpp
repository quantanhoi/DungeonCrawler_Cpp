#include<AbstractUI.h>
#include<iostream>
void TerminalUI::draw(Level *level) {
    for(int i{}; i < numRows; i++) {
        for(int z{}; z < numColumns; z++) {
            std::cout << level->getTile(i, z)->getCharacterTexture();
        }
        std::cout << "\n";
    }

}

void TerminalUI::chooseCharacter(Level *level) {
    int choice;
    std::cout << "Choose a Character: " << std::endl;
    for(int i{}; i < level->characterVector.size(); i++) {
        log("Character number:" << i+1);
    }
    std::cout << "Choice: ";
    std::cin >> choice;
    if(choice <= level->characterVector.size() && choice > 0) {
        pCharacter = level->characterVector.at(choice-1);
    }
    else {
        log("There's no character like that!");
        chooseCharacter(level);
    }
}
Character* TerminalUI::getpCharacter() {
    return this->pCharacter;
}

void TerminalUI::moveToTile(int row, int col) {
    if(row <= numRows-1 && col <= numColumns -1 && row>= 0  && col >=0) {
        if(!this->pCharacter->getCurrentTile()->moveTo(this->pCharacter->getLevel()->getTile(row, col), this->getpCharacter()))
        {
        }
    }
    else {
        log("you can't move outside of the map");
    }
}
int TerminalUI::move(Input in) {
    int choice{}, row{}, col{};

    row = this->pCharacter->getCurrentTile()->getRow();
    col = this->pCharacter->getCurrentTile()->getCol();
    log("Row: " << row << " \nCol: " << col);
    std::cout << "Input: ";
    std::cin >> choice;
    switch (choice) {
        case 1:
        this->moveToTile(row+1, col-1);
        break;
        case 2:
        this->moveToTile(row+1, col);
        break;
        case 3:
        this->moveToTile(row+1, col+1);
        break;
        case 4:
        this->moveToTile(row, col-1);
        break;
        case 5:
        break;
        case 6:
        this->moveToTile(row, col+1);
        break;
        case 7:
        this->moveToTile(row-1, col-1);
        break;
        case 8:
        this->moveToTile(row-1, col);
        break;
        case 9:
        this->moveToTile(row-1, col+1);
        break;
        case 0:
        return 1;
        break;
        default:
            log("Invalid Input!!");
            move(in);
            break;
            return 0;
    }
    return 1;
}

Character *Controller::getPCharacter() const
{
    return pCharacter;
}
