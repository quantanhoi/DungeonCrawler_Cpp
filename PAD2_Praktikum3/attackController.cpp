#include "attackController.h"
#include"Character.h"
attackController::attackController()
{

}
void attackController::chooseCharacter(Level *level) {
    if(level->npcVector.size() == 0) {
        return;
    }
    else {
        pCharacter = level->npcVector.at(0);
    }
}
int attackController::move(Input in) {    //find and attack closest character

    return 1;

}
Character* attackController::chooseTarget() {
    int distance;
    std::vector<std::pair<int, Character*>> targetList;
    for(auto char1 : pCharacter->getLevel()->characterVector) {         //choose target
        distance = (std::max(pCharacter->getRow(), char1->getRow()) - std::min(pCharacter->getRow(), char1->getRow()))
                +(std::max(pCharacter->getCol(), char1->getCol()) - std::min(pCharacter->getCol(), char1->getCol()));
        targetList.push_back(std::make_pair(distance, char1));
    }
    std::sort(targetList.begin(), targetList.end());
    return targetList.at(0).second;     //aka the closest character due to distance
}
