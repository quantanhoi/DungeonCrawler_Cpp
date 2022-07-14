#include "Graphicalui.h"
#include <QDebug>
#include <QGridLayout>
#include <QMessageBox>
#include<QPushButton>
#include<QLabel>
#include"Button.h"
#include"mainwindow.h"
#define BOTTOMROW 1
#define MIDROW 2
#define UPROW 3
#define LEFT 1
#define MID 2
#define RIGHT 3

GraphicalUI::GraphicalUI()
{
    pCharacter = nullptr;
    lastInput = down;
}
void GraphicalUI::setButton(QPushButton* button, const char *path, float max) {
    button->setIcon(QPixmap(path));
    button->setIconSize(QSize(max, max));
    button->setMaximumSize(max, max);
    button->setMinimumSize(20,20);
    button->setStyleSheet("border:none");
}
void GraphicalUI::draw(Level *level, MainWindow* mainWindow) {

    for(int r=0; r< numRows; r++)    {
        for(int c=0; c< numColumns; c++)    {
                auto* l = new QLabel(mainWindow);
                l->setPixmap(level->getTile(r, c)->getRenderedTexture());
                l->setScaledContents(true);    //set the pixmap to fit in the frame
                l->setMaximumSize(mainWindow->getMax(), mainWindow->getMax());
                l->setMinimumSize(20, 20);

                if(level->getTile(r,c)->hasCharacter()) {
                    if(typeid(*level->getTile(r,c)) == typeid (Pit)) {
                        auto* character = new QLabel(mainWindow);
                        character->setPixmap(level->getTile(r,c)->pCharacter->getCharacterTexture());
                        character->setScaledContents(true);
                        character->setMaximumSize(l->maximumWidth(), l->maximumHeight());
                        character->setMinimumSize(l->midLineWidth(), l->minimumHeight());
                        l = new QLabel(character);
                        l->setPixmap(level->getTile(r, c)->getRenderedTexture());
                        l->setScaledContents(true);    //set the pixmap to fit in the frame
                        l->setMaximumSize(mainWindow->getMax(), mainWindow->getMax());
                        l->setMinimumSize(20, 20);
                        mainWindow->getGridlayout()->addWidget(character,r+3,c);
                        continue;
                    }
                    auto* character = new QLabel(l);
                    character->setPixmap(level->getTile(r,c)->pCharacter->getCharacterTexture());
                    character->setScaledContents(true);
                    character->setMaximumSize(l->maximumWidth(), l->maximumHeight());
                    character->setMinimumSize(l->midLineWidth(), l->minimumHeight());


                }
                mainWindow->getGridlayout()->addWidget(l, r+3, c);

            }
        }
    QLabel* BloodyFrame = new QLabel(mainWindow);
    BloodyFrame->setPixmap(QPixmap(":/textures/bloody_frame.png"));
    BloodyFrame->setScaledContents(true);
    BloodyFrame->setMaximumSize(4000, 2000);
    BloodyFrame->setMinimumSize(700, 450);
    mainWindow->getGridlayout()->addWidget(BloodyFrame,0,0,numRows+10, numColumns+100);


    //Pushbutton
    Button* arrow_down = new Button(down,mainWindow);
    Button* arrow_down_left = new Button(down_left,mainWindow);
    Button* arrow_down_right = new Button(down_right,mainWindow);
    Button* arrow_left = new Button(left,mainWindow);
    Button* arrow_right = new Button(right,mainWindow);
    Button* arrow_skip = new Button(skip,mainWindow);
    Button* arrow_up = new Button(up,mainWindow);
    Button* arrow_up_left = new Button(up_left,mainWindow);
    Button* arrow_up_right = new Button(up_right,mainWindow);


    setButton(arrow_down,":/textures/arrows/arrow_down.png", mainWindow->getMax());
    mainWindow->getGridlayout()->addWidget(arrow_down, numRows -BOTTOMROW, numColumns+MID);
    setButton(arrow_down_left, ":/textures/arrows/arrow_down_left.png", mainWindow->getMax());
    mainWindow->getGridlayout()->addWidget(arrow_down_left, numRows-BOTTOMROW, numColumns+LEFT);
    setButton(arrow_down_right, ":/textures/arrows/arrow_down_right.png", mainWindow->getMax());
    mainWindow->getGridlayout()->addWidget(arrow_down_right, numRows-BOTTOMROW, numColumns+RIGHT);
    setButton(arrow_left, ":/textures/arrows/arrow_left.png", mainWindow->getMax());
    mainWindow->getGridlayout()->addWidget(arrow_left, numRows-MIDROW, numColumns+LEFT);
    setButton(arrow_right, ":/textures/arrows/arrow_right.png", mainWindow->getMax());
    mainWindow->getGridlayout()->addWidget(arrow_right, numRows-MIDROW, numColumns+RIGHT);
    setButton(arrow_skip, ":/textures/arrows/arrow_skip.png", mainWindow->getMax());
    mainWindow->getGridlayout()->addWidget(arrow_skip, numRows-MIDROW, numColumns+MID);
    setButton(arrow_up, ":/textures/arrows/arrow_up.png", mainWindow->getMax());
    mainWindow->getGridlayout()->addWidget(arrow_up, numRows-UPROW, numColumns+MID);
    setButton(arrow_up_left, ":/textures/arrows/arrow_up_left.png", mainWindow->getMax());
    mainWindow->getGridlayout()->addWidget(arrow_up_left, numRows-UPROW, numColumns+LEFT);
    setButton(arrow_up_right, ":/textures/arrows/arrow_up_right.png", mainWindow->getMax());
    mainWindow->getGridlayout()->addWidget(arrow_up_right, numRows-UPROW, numColumns+RIGHT);



}


void GraphicalUI::chooseCharacter(Level *level) {
    pCharacter = level->characterVector.at(0);
    pCharacter->setPController(this);
}
void GraphicalUI::moveToTile(int row, int col) {
    if(row <= numRows-1 && col <= numColumns -1 && row>= 0  && col >=0) {
        if(!this->pCharacter->getCurrentTile()->moveTo(this->pCharacter->getLevel()->getTile(row, col), this->pCharacter))
        {
        }
    }
    else {
        log("you can't move outside of the map");
    }
}

void GraphicalUI::test() {
    if(this->getLastInput() == down) {
        QMessageBox msg;
        msg.setText("yes this is working with out pointer to mainWindow");
        msg.exec();
    }
}
Input GraphicalUI::getLastInput() const
{
    return lastInput;
}

void GraphicalUI::setLastInput(Input newLastInput)
{
    lastInput = newLastInput;
}
int GraphicalUI::move(Input in) {
    this->pCharacter->move(in);
    return 1;
}
