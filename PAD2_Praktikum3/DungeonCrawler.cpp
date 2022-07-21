#include<DungeonCrawler.h>
#include<QMessageBox>
#include<fstream>
#include"mainwindow.h"

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

attackController *DungeonCrawler::getPAttackController() const
{
    return pAttackController;
}

void DungeonCrawler::loadGame()
{
    std::fstream path("level.txt");
    readFile(path);
    MainWindow* mainWindow = new MainWindow(this);
    mainWindow->show();
    GraphicalUI::draw(getCurrentLevel(), mainWindow);
}



void DungeonCrawler::initialisieren() {
    //level 1
    Level* level1 = new Level;
    levelList->push_back(level1);
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
            if( i == 0 || z == 0 || i == numRows-1 || z == numColumns -1) {
                level1->stage[i][z] = new Wall(level1, i, z);
            }
            else {
                level1->stage[i][z] = new Floor(level1, i, z);
            }
        }
    }

    //test Portal
    delete level1->stage[3][1];
    delete level1->stage[6][3];
    Portal* newPort = new Portal(level1, 3, 1, nullptr);
    level1->stage[3][1]= newPort;

    Portal* newPort2 = new Portal(level1,6, 3, nullptr);
    newPort2->connectPortal(newPort);
    level1->stage[6][3] = newPort2;


    //test door and switch
    delete level1->stage[6][4];
    delete level1->stage[3][8];
    Door* door1 = new Door(level1, 6, 4);
    level1->stage[6][4] = door1;
    Switch* switch1 = new Switch(level1, 3, 8);
    level1->stage[3][8] = switch1;
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
    delete level1->stage[8][8];
    levelChanger* changer1 = new levelChanger(level1, 8, 8, this);
    level1->stage[8][8] = changer1;

    //testing loot chest
    delete level1->stage[6][1];
    lootChest* loot1 = new lootChest(level1, 6, 1, this);
    level1->stage[6][1] = loot1;


    //level2
    Level* level2 = new Level;
    levelList->push_back(level2);
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           level2->stage[i][z] = new Floor(level2, i, z);
        }
    }


    //level changer 2
    delete level2->stage[0][0];
    levelChanger* changer2 = new levelChanger(level2, 0, 0, this);
    level2->stage[0][0] = changer2;
    changer2->connectLevelChanger(changer1);

    //test Level3
    Level* level3 = new Level;
    levelList->push_back(level3);
    for(int i = 0; i < numRows; i ++ ) {
        for(int z = 0; z < numColumns; z++){
           level3->stage[i][z] = new Floor(level3, i, z);
        }
    }


    iterator = levelList->end();
    iterator = levelList->begin();
    //++iterator;
    /*while(iterator!= levelList->end()) {
        ++iterator;
    }*/
    currentLevel = *iterator;
    this->currentLevel->placePlayer(3,3);
    this->currentLevel->placeNPC(4, 4);
    pGraphicalUI->chooseCharacter(this->currentLevel);    //choose the first character placed in the current level
    pAttackController->chooseCharacter(this->currentLevel);


//3, 2
}
void DungeonCrawler::writeFile()
{
    std::string path_ = "level.txt";
    //std::string path = level + counter + ".txt";
    std::ofstream data(path_, std::ofstream::out | std::ofstream::trunc);

    if ( !data.good() )
    {
        throw ("file can not be opened");
    }
    //std::ofstream data ("file.txt");
    data << "row: " << numRows << std::endl;
    data << "col: " << numColumns << std::endl;
    myList::iterator ite;
    Level* temp = currentLevel;
    for(ite = levelList->begin(); ite != levelList->end(); ++ite) {
        currentLevel = *ite;
        writeLevel(data);
        data << "level" << std::endl;
    }
    ite = levelList->end();
    currentLevel = *ite;
    writeLevel(data);
    currentLevel = temp;

}
void DungeonCrawler::writeLevel(std::ofstream& data)
{
    /*std::string path_ = path;
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
    */
    for(int i = 0; i < numRows; i ++ )
    {
        for(int z = 0; z < numColumns; z++)
        {
            if(currentLevel->stage[i][z]->hasCharacter()) {
                data << "col: " << currentLevel->stage[i][z]->getCol() << " "
                     << "row: " << currentLevel->stage[i][z]->getRow() << " "
                     << "texture: " << currentLevel->stage[i][z]->pCharacter->getCharacterString() << " ";
            }
            else {
                data << "col: " << currentLevel->stage[i][z]->getCol() << " "
                 << "row: " << currentLevel->stage[i][z]->getRow() << " "
                 << "texture: " << currentLevel->stage[i][z]->getTexture() << " ";
            }

            if (currentLevel->stage[i][z]->getTexture() == "O")     //portal
            {
                data
                << "destCol " << dynamic_cast<Portal*>(currentLevel->stage[i][z])->getConnectingPortal()->getCol() << " "
                << "destRow " << dynamic_cast<Portal*>(currentLevel->stage[i][z])->getConnectingPortal()->getRow() << " ";
            }
            if (currentLevel->stage[i][z]->getTexture() == "-" || currentLevel->stage[i][z]->getTexture() == "/")  //door
            {
                data << "is_open " << dynamic_cast<Door*>(currentLevel->stage[i][z])->getStatus() << " ";
                Door* a = dynamic_cast<Door*>(currentLevel->stage[i][z]);

                Tile* tile;
                tile = dynamic_cast<Tile*>(a->getConnectedSwitch());
                data << "target "
                << "col_switch: " << tile->getCol() << " "
                << "row_switch: " << tile->getRow() << " ";

            }

            if (currentLevel->stage[i][z]->getTexture() == "?")//switch
            {
                Switch* a = dynamic_cast<Switch*>(currentLevel->stage[i][z]);

                Tile* tile;
                for(size_t i = 0; i < a->getPassiveObjects().size(); i++)
                {
                     tile = dynamic_cast<Tile*>(a->getPassiveObjects().at(i));
                     data << "target "
                     << "col_door: " << tile->getCol() << " "
                     << "row_door: " << tile->getRow() << " ";
                }


            }

            if (currentLevel->stage[i][z]->getTexture() == ">")//levelchange
            {
                int counter = 1;
                for(myList::iterator it = levelList->begin(); it != levelList->end(); ++it) {
                    if(dynamic_cast<levelChanger*>(currentLevel->stage[i][z])->getConnectingChanger()->getPLevel() == *it) {
                        data << "Level: " << counter;
                        break;
                    }
                    counter++;

                }
                data <<" row: " << dynamic_cast<levelChanger*>(currentLevel->stage[i][z])->getConnectingChanger()->getRow();
                data <<" col: " << dynamic_cast<levelChanger*>(currentLevel->stage[i][z])->getConnectingChanger()->getCol();

            }
            //data << typeid( *(currentLevel->getTile(i,z)) ).name() << ";";
            if (currentLevel->getTile(i,z)->hasCharacter())
            {
                data << "charactertype: ";
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
                data << "HP: " << std::to_string(tmpChar->getHitpoint()) << " ";

            }


            data << ";" << std::endl;
        }
        //data << std::endl;
    }
}
void DungeonCrawler::readFile(std::fstream& path) {
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
    Level* curLevel = level1;
    while(!path.eof()) {
        readLevel(path, curLevel);
        Level* level2 = new Level;
        levelList->push_back(level2);
        for(int i = 0; i < numRows; i ++ ) {
            for(int z = 0; z < numColumns; z++){
               level2->stage[i][z] = new Floor(level2, i, z);
            }
        }
        curLevel = level2;
    }
}

void DungeonCrawler::Save()
{
    QMessageBox msg;
    msg.setText(QString("Saved"));
    msg.exec();
    writeFile();

}

void DungeonCrawler::readLevel(std::fstream& path, Level* curLevel)
{
    /*Level* level1 = new Level;
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
//    std::vector<int> row_vector;*/
    std::string name;
    while (!path.eof())
    {
        int i = 0;
        int col{}, row{};
        path >> name;
        if(name == "level") {
            return;
        }
        path >> col;
        path >> name; path >> row;
        curLevel->stage[row][col] = new Floor(curLevel, row, col);
        //getline(path, name, ';');//read the rest of line
//        std::cout << "col: " << col
//                  << "row: " << row;
        i++;


        std::string texture, tile;
        path >> name; path >> texture;
        if (texture == "#")
        {
            delete curLevel->stage[row][col];
            curLevel->stage[row][col] = new Wall(curLevel, row, col);
        }
        if (texture == "v")
        {
            delete curLevel->stage[row][col];
            curLevel->stage[row][col] = new Pit(curLevel, row, col);
        }
        if (texture == "=")
        {
            delete curLevel->stage[row][col];
            curLevel->stage[row][col] = new Ramp(curLevel, row, col);
        }
        if (texture == "$")
        {
            delete curLevel->stage[row][col];
            curLevel->stage[row][col] = new lootChest(curLevel, row, col, this);
        }
        if (texture == ">")
        {
            int numLevel{}, row_levelChanger{}, col_levelChanger{};

            delete curLevel->stage[row][col];
            levelChanger* levelChanger1 = new levelChanger(curLevel, row, col, this);
            curLevel->stage[row][col] = levelChanger1;
            path >> name;
            path >> numLevel;
            path >> name; path >> row_levelChanger;
            path >> name; path >> col_levelChanger;
            if(numLevel == 1) {
                myList::iterator ite = levelList->begin();
                Level* level1 = *ite;
                levelChanger1->connectLevelChanger(dynamic_cast<levelChanger*>(level1->stage[row_levelChanger][col_levelChanger]));
            }


        }
        int destCol1{},destRow1{},destCol2{},destRow2{};
//        Portal* newPort;
//        Portal* newPort2;
        if (texture == "O")
        {
            if(typeid (*curLevel->stage[row][col]).name() != typeid (Portal).name()) {
                delete curLevel->stage[row][col];
                Portal* newPort1 = new Portal(curLevel, row, col, nullptr);
                curLevel->stage[row][col] = newPort1;
                path >> name; path >> destCol1;
                path >> name; path >> destRow1;
                delete curLevel->stage[destRow1][destCol1];
                Portal* newPort2 = new Portal(curLevel, destRow1, destCol1, nullptr);
                curLevel->stage[destRow1][destCol1] = newPort2;
                newPort1->connectPortal(newPort2);
            }

        }


        int col_door{}, row_door{};
        int col_switch{}, row_switch{};
        if (texture == "?")
        {
            //path >> name; path >> col_sw;
            //path >> name; path >> row_sw;
            path >> name; // read "target"
            path >> name; path >> col_door;
            path >> name; path >> row_door;

        }
        bool status;
        if(texture == "-" || texture == "/") {
            path >> name; //read is_open
            path >> status;
            path >> name;
            path >> name; path >> col_switch;
            path >> name; path >> row_switch;
            delete curLevel->stage[row][col];
            Door* door1 = new Door(curLevel, row, col);
            curLevel->stage[row][col] = door1;
            door1->setStatus(status);
            door1->setDoorTexture();
            if(typeid(*curLevel->stage[row_switch][col_switch]).name() != typeid (Switch).name()) {
                delete curLevel->stage[row_switch][col_switch];
                Switch* switch1 = new Switch(curLevel, row_switch, col_switch);
                curLevel->stage[row_switch][col_switch] = switch1;
                switch1->attach(door1);
            }
            else {
                dynamic_cast<Switch*>(curLevel->stage[row_switch][col_switch])->attach(door1);
            }
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
                curLevel->placePlayer(row, col);
                pGraphicalUI->chooseCharacter(this->currentLevel);
            }
            else
            {
                curLevel->placeNPC(row, col);
                pAttackController->chooseCharacter(this->currentLevel);
            }
        }

        getline(path, name, ';');//read the rest of line till ";"
        std::cout << std::endl;

    }
}


void DungeonCrawler::play() {
    initialisieren();
    //std::fstream path("level1.txt");
    //readLevel(path);
    MainWindow* mainWindow = new MainWindow(this);
    mainWindow->show();
    GraphicalUI::draw(getCurrentLevel(), mainWindow);
    //writeFile();











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
                QMessageBox msg;
                msg.setText(QString("All character is dead"));
                msg.exec();
                this->gameEnd = true;
                return true;
            }
        }
    }
    return false;
}
