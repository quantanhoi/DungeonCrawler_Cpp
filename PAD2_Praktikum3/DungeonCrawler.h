#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H
#include<AbstractUI.h>
#include"mainwindow.h"
#include"Tile.h"
#include"AbstractUI.h"
#include"active.h"
#include"Character.h"
#include"Factory.h"
#include"Level.h"
#include"passive.h"
#include"Graphicalui.h"
#include"list.h"
#include"levelChanger.h"
#include"lootChest.h"
#include <fstream>
#include <sstream>
#include <algorithm>

#define NUMBER_OF_LEVEL_TEST 2
class DungeonCrawler {
private:
    myList* levelList;
    Level* currentLevel;
    GraphicalUI* pGraphicalUI;
    bool gameEnd;

public:

    myList::iterator iterator;
    //std::array<Level*, NUMBER_OF_LEVEL_TEST> allLevel;
    void initialisieren();
    void play();
    void goToNextLevel();
    void goToPreviousLevel();
    DungeonCrawler() {
        /*for(int i{}; i  < NUMBER_OF_LEVEL_TEST; i++ ) {
            allLevel[i] = new Level;
        }
        currentLevel = allLevel[0];*/
        levelList = new myList;
        pGraphicalUI = new GraphicalUI;
        gameEnd = false;
    }
    ~DungeonCrawler();
    bool checkEndGame();     // either found the treasure, or all player is dead
    Level *getCurrentLevel() const;
    myList *getLevelList() const;
    GraphicalUI *getPGraphicalUI() const;
    void setPGraphicalUI(GraphicalUI *newPGraphicalUI);
    void setCurrentLevel(Level *newCurrentLevel);
    void setGameEnd(bool newGameEnd);

    void readLevel(std::fstream& path);
    void writeLevel();
    void writeLevel(std::string& level);//Level in einer Datei abspeichern
};

#endif // DUNGEONCRAWLER_H
