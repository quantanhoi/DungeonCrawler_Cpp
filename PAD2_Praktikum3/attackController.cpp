#include "attackController.h"
#include"Character.h"
#include"QMessageBox"
#include"graph.h"
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
    Character* target = chooseTarget();
    QMessageBox msg;
    std::vector<Node> path = this->pCharacter->getLevel()->aStar(this->pCharacter->getCurrentTile(), target->getCurrentTile());
    std::vector<Node> path_viaPortal = this->pCharacter->getLevel()->makePathViaPortal(this->pCharacter->getCurrentTile(), target->getCurrentTile());
    if(path.size() > path_viaPortal.size() || path.size() == 0) {
        if(path_viaPortal.size() != 0) {
            path = path_viaPortal;
        }
    }
    if( path.size() == 0 || (path.at(path.size()-1).x != target->getRow() && path.at(path.size()-1).y != target->getCol()) ) {
        msg.setText(QString("Can't find path to player"));
        msg.exec();
        return 0;
    }
    this->pCharacter->moveToTile(path.at(1).x, path.at(1).y);
    Graph::drawGraph(path);
    //now somehow we could choose an input to move
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
