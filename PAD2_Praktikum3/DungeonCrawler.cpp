#include<DungeonCrawler.h>
#include<QMessageBox>
#include"mainwindow.h"
#include "passive.h"
Level *DungeonCrawler::getCurrentLevel() const
{
    return currentLevel;
}

myList *DungeonCrawler::getLevelList() const
{
    return levelList;
}

GraphicalUI *DungeonCrawler::getPGraphicalUI() const
{
    return pGraphicalUI;
}

void DungeonCrawler::setPGraphicalUI(GraphicalUI *newPGraphicalUI)
{
    pGraphicalUI = newPGraphicalUI;
}

void DungeonCrawler::setCurrentLevel(Level *newCurrentLevel)
{
    currentLevel = newCurrentLevel;
}

void DungeonCrawler::setGameEnd(bool newGameEnd)
{
    gameEnd = newGameEnd;
}

//void DungeonCrawler::writeLevel(std::string& level)
/*
 *
void DungeonCrawler::writeLevel()
{
    std::string path_ = "level1.txt";
    //std::string path = level + counter + ".txt";
    std::ofstream data(path_, std::ofstream::out | std::ofstream::trunc);

    if ( !data.good() )
    {
        throw ("file can not be opened");
    }

    //std::ofstream data ("file.txt");
    data << "row: " << numRows << std::endl;
    data << "col: " << numColumns << std::endl;
    //data << "name: " << level << std::endl;
//    for(auto& tile : allLevel)
//    {
//    }
    data << "tile" << std::endl;
    iterator = levelList->begin();
    currentLevel = *iterator;
    for(int i = 0; i < numRows; i ++ )
    {
        for(int z = 0; z < numColumns; z++)
        {
            data << "col: " << currentLevel->stage[i][z]->getCol() << " "
                 << "row: " << currentLevel->stage[i][z]->getRow() << " "
                 << "texture: " << currentLevel->stage[i][z]->getTexture() << " ";
            if (currentLevel->stage[i][z]->getTexture() == "O")//portal
            {
                data
                << "destCol " << dynamic_cast<Portal*>(currentLevel->stage[i][z])->getConnectingPortal()->getCol() << " "
                << "destRow " << dynamic_cast<Portal*>(currentLevel->stage[i][z])->getConnectingPortal()->getRow() << " ";
            }
            if (currentLevel->stage[i][z]->getTexture() == "-")//door
            {
                data << "is_open " << dynamic_cast<Door*>(currentLevel->stage[i][z])->getStatus() << " ";
            }
            if (currentLevel->stage[i][z]->getTexture() == "?")//switch
            {
                Switch* a = dynamic_cast<Switch*>(currentLevel->stage[i][z]);

                Tile* tile;
                for(size_t i = 0; i < a->getPassiveObjects().size(); i++)
                {
                     tile = dynamic_cast<Tile*>(a->getPassiveObjects().at(i));
                }

                data << "target "
                << "col_door: " << tile->getCol() << " "
                << "row_door: " << tile->getRow() << " ";
            }

            if (currentLevel->stage[i][z]->getTexture() == ">")//levelchange
            {
                int counter = 1;
                for( iterator = levelList->begin(); iterator != levelList->end(); ++iterator )
                {
                    if (dynamic_cast<levelChanger*>(currentLevel->stage[i][z])->getConnectingLevel() == *iterator)
                    {
                        data << "Level: " << counter;
                        break;
                    }
                    else
                        counter ++;
                }
            }
            //data << typeid( *(currentLevel->getTile(i,z)) ).name() << ";";
            if (currentLevel->getTile(i,z)->hasCharacter())
            {
                data << "character type: ";
                Character* tmpChar = currentLevel->getTile(i,z)->pCharacter;
                CharacterType temp = currentLevel->getTile(i,z)->pCharacter->getCharacterType();
                switch(temp)
                {
                case player:
                    data << "player ";
                    break;
                case npc:
                    data << "npc ";
                    break;
                default: break;
                }
                data << "Strength: " << std::to_string(tmpChar->getStrength()) << " ";
                data << "Stamina: " << std::to_string(tmpChar->getStamina())<< " ";
                data << "HP: " << std::to_string(tmpChar->getHitpoint());

            }


            data << ";" << std::endl;
        }
        //data << std::endl;
    }
}
*/

void DungeonCrawler::readLevel(std::fstream& path)
{
    Level* level1 = new Level;
    levelList->push_back(level1);
    this->currentLevel = level1;

    if ( !path.good() )
    {
        throw ("file can not be opened");
    }
    std::string name;
    path >> name;//ignore "col:"
    int numColumns; path >> numColumns;
    path >> name;//ignore "row:"
    int numRows; path >> numRows;
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           level1->stage[i][z] = new Floor(level1, i, z);
        }
    }

    getline(path, name);//ignore the whole line containing "tile"

//    std::vector<int> col_vector;
//    std::vector<int> row_vector;

    int count = -1;
    while (!path.eof())
    {
        int i = 0;
        int col{}, row{};
        path >> name; path >> col;
        path >> name; path >> row;
        level1->stage[row][col] = new Floor(level1, row, col);
        //getline(path, name, ';');//read the rest of line
//        std::cout << "col: " << col
//                  << "row: " << row;
        i++;


        std::string texture, tile;
        path >> name; path >> texture;
        if (texture == "#")
        {
            delete level1->stage[row][col];
            level1->stage[row][col] = new Wall(level1, row, col);
        }
        if (texture == "v")
        {
            delete level1->stage[row][col];
            level1->stage[row][col] = new Pit(level1, row, col);
        }
        if (texture == "=")
        {
            delete level1->stage[row][col];
            level1->stage[row][col] = new Ramp(level1, row, col);
        }
        if (texture == "$")
        {
            delete level1->stage[row][col];
            level1->stage[row][col] = new lootChest(level1, row, col, this);
        }
        if (texture == ">")
        {
            delete level1->stage[row][col];
            level1->stage[row][col] = new levelChanger(level1, row, col, this);
        }
        int destCol1{},destRow1{},destCol2{},destRow2{};
//        Portal* newPort;
//        Portal* newPort2;
        if (texture == "O")
        {
            if (count == -1)
            {
                count++;
                path >> name; path >> destCol1;
                path >> name; path >> destRow1;
                //newPort = new Portal(level1, destRow1, destCol1, nullptr);
//                std::cout << " dest " << " col 1 " << destCol1
//                          << " row 1 " << destRow1;

            }
            else {
            path >> name; path >> destCol2;
            path >> name; path >> destRow2;
            delete level1->stage[destRow2][destCol2];
            }
            //if path encounters "O" 2nd times

//            std::cout << " dest "
//                      << " col 2 " << destCol2
//                      << " row 2 " << destRow2;
            delete level1->stage[destRow1][destCol1];

            Portal* newPort = new Portal(level1, destRow1, destCol1, nullptr);
            level1->stage[destRow1][destCol1]= newPort;
            Portal* newPort2 = new Portal(level1, destRow2, destCol2, nullptr);
            newPort2->connectPortal(newPort);
            level1->stage[destRow2][destCol2] = newPort2;
        }


        int col_door{}, row_door{};
        int col_sw{}, row_sw{};
        if (texture == "?")
        {
            path >> name; path >> col_sw;
            path >> name; path >> row_sw;
            path >> name; // read "target"
            path >> name; path >> col_door;
            path >> name; path >> row_door;

//            std::cout << " door " << "col " << col_door << " row " << row_door
//                      << " switch " <<  "col " << col_sw  << " row "  << row_sw;
            //delete level1->stage[row_door][col_door];
            Door* door1 = new Door(level1, row_door, col_door);
            //delete level1->stage[row_sw][col_sw];
            Switch* switch1 = new Switch(level1, row_sw, col_sw);
            level1->stage[row_sw][col_sw] = switch1;
            switch1->attach(door1);

        }


//        int stamina{}, strength{}, hitpoint{};
        std::string characterType;
        if (texture == "|")
        {
            std::string tmpcharType;
            path >> name; path >> tmpcharType; characterType = tmpcharType;
//            path >> name; path >> tmpcharType; strength = std::stoi(tmpcharType);
//            path >> name; path >> tmpcharType; stamina = std::stoi(tmpcharType);
//            path >> name; path >> tmpcharType; hitpoint = std::stoi(tmpcharType);
//            std::cout << " characterType " << characterType
//                      << " strength " << strength
//                      << " stamina " << stamina
//                      << " hitpoint " << hitpoint;
            if (characterType == "player") {
                level1->placePlayer(row, col);
                pGraphicalUI->chooseCharacter(this->currentLevel);
            }
            else
            {
                level1->placeNPC(row, col);
            }
        }

        getline(path, name, ';');//read the rest of line till ";"
        std::cout << std::endl;
    }
}
/*
void DungeonCrawler::readLevel(std::fstream& path)
{

    if ( !path.good() )
    {
        throw ("file can not be opened");
    }
    std::string name;
    path >> name;//ignore "col:"
    int numColumns; path >> numColumns;
    path >> name;//ignore "row:"
    int numRows; path >> numRows;

    getline(path, name);//ignore the whole line containing "tile"

//    std::vector<int> col_vector;
//    std::vector<int> row_vector;
    Level* level1 = new Level;
    while (!path.eof())
    {
        int i = 0;
        int col{}, row{};
        path >> name; path >> col;
        path >> name; path >> row;
        getline(path, name, ';');//read the rest of line
        level1->stage[row][col] = new Floor(level1, row, col);
        i++;
    }
    while (!path.eof())
    {
        int count = 0;
        std::string texture, tile;
        path >> name; path >> texture;
        int destCol1{},destRow1{},destCol2{},destRow2{};;
//        Portal* newPort;
//        Portal* newPort2;
        if (texture == "O")
        {
            if (count == 0)
            {
                count++;
                path >> name; path >> destCol1;
                path >> name; path >> destRow1;
                //newPort = new Portal(level1, destRow1, destCol1, nullptr);

            }
            //if path encounters "O" 2nd times
            Portal* newPort = new Portal(level1, destRow1, destCol1, nullptr);
            level1->stage[destRow1][destCol1]= newPort;
            path >> name; path >> destCol2;
            path >> name; path >> destRow2;
            //newPort2 = new Portal(level1, destRow2, destCol2, nullptr);
            Portal* newPort2 = new Portal(level1, destRow2, destCol2, nullptr);
            newPort2->connectPortal(newPort);
            level1->stage[destRow2][destCol2] = newPort2;
        }
        int col_door{}, row_door{};
        int col_sw{}, row_sw{};
        if (texture == "?")
        {
            path >> name;
            path >> name; path >> col_door;
            path >> name; path >> row_door;

            delete level1->stage[row_door][col_door];
            Door* door1 = new Door(level1, row_door, col_door);
            level1->stage[row_door][col_door] = door1;

            // set cursor position to beginning of line in C++
            path.seekg (0, std::ios::end);
            delete level1->stage[row_sw][col_sw];
            Switch* switch1 = new Switch(level1, row_sw, col_sw);
            level1->stage[row_sw][col_sw] = switch1;
            switch1->attach(door1);
        }

        path >> name; path >> tile;

    }


}*/
void DungeonCrawler::initialisieren() {
    //level 1
    Level* level1 = new Level;
    levelList->push_back(level1);
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           level1->stage[i][z] = new Floor(level1, i, z);
        }
    }

    //test Portal
    delete level1->stage[3][1];
    delete level1->stage[6][2];
    Portal* newPort = new Portal(level1, 3, 1, nullptr);
    level1->stage[3][1]= newPort;

    Portal* newPort2 = new Portal(level1,6, 2, nullptr);
    newPort2->connectPortal(newPort);
    level1->stage[6][2] = newPort2;


    //test door and switch
    delete level1->stage[6][4];
    delete level1->stage[3][4];
    Door* door1 = new Door(level1, 6, 4);
    level1->stage[6][4] = door1;
    Switch* switch1 = new Switch(level1, 3, 4);
    level1->stage[3][4] = switch1;
    switch1->attach(door1);


    //test Pit and Ramp
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           if(i == 2 && z < 5 ) {
               level1->stage[i][z] = new Pit(level1, i, z);
           }
        }
    }
    level1->stage[2][5] = new Ramp(level1, 2, 5);

    //test Wall
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           if((i== 5 || i == 7) && z < 5 ) {
               level1->stage[i][z] = new Wall(level1, i, z);
           }
        }
    }
    //testing level changer
    delete level1->stage[3][2];
    levelChanger* changer1 = new levelChanger(level1, 3, 2, this);
    level1->stage[3][2] = changer1;

    //testing loot chest
    delete level1->stage[4][5];
    lootChest* loot1 = new lootChest(level1, 4, 5, this);
    level1->stage[4][5] = loot1;


    //level2
    Level* level2 = new Level;
    levelList->push_back(level2);
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           level2->stage[i][z] = new Floor(level2, i, z);
        }
    }
    iterator = levelList->begin();
    //++iterator;
    currentLevel = *iterator;
    this->currentLevel->placePlayer(3,3);
    this->currentLevel->placeNPC(4, 4);
    pGraphicalUI->chooseCharacter(this->currentLevel);    //choose the first character placed in the current level

    //level changer 2
    delete level2->stage[0][0];
    levelChanger* changer2 = new levelChanger(level2, 0, 0, this);
    level2->stage[0][0] = changer2;
    changer2->connectLevelChanger(changer1);

//3, 2
}
void DungeonCrawler::play() {
    //int i{0};
    //initialisieren();
    std::fstream path("level1.txt");
    readLevel(path);
    //writeLevel();

    //print out level
    Level* level1 = new Level;
    levelList->push_back(level1);
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           if((i== 5 || i == 7) && z < 5 ) {
               level1->stage[i][z] = new Wall(level1, i, z);
           }
        }
    }


    MainWindow* mainWindow = new MainWindow(this);
    mainWindow->show();
    GraphicalUI::draw(this->currentLevel, mainWindow);







    /*this->currentLevel->placeCharacterTest(1, 3);
    this->currentLevel->placeCharacterTest(2, 6);
    Level new_level = *this->currentLevel;    //test copy constructor
    this->allLevel[1] = &new_level;
    this->pTerminalUI->draw(this->currentLevel);
    this->pTerminalUI->chooseCharacter(this->currentLevel);
    while(true) {
        system("cls");      //clear console
        this->pTerminalUI->draw(this->currentLevel);
        this->pTerminalUI->move();
        i++;
        log(i);
        sif(i == 5) {
            this->pTerminalUI->draw(this->allLevel[1]);
            Sleep(10000);
        }

    }*/
}
bool DungeonCrawler::checkEndGame() {
    if(this->gameEnd) {
        return true;
    }
    else {
        for(int i = 0; i < this->currentLevel->characterVector.size(); i++) {
            if(this->currentLevel->characterVector.at(i)->getStatus() == alive) {
                this->gameEnd = false;
                return false;
            }
            else {
                this->gameEnd = true;
                return true;
            }
        }
    }
    return false;
}
