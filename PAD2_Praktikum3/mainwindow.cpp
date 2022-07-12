#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGridLayout>
#include <QMessageBox>
#include<QPushButton>
#include"Button.h"
#include"DungeonCrawler.h"
#include"AbstractUI.h"
MainWindow::MainWindow(DungeonCrawler* ptrGame, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    game = ptrGame;
    ui->setupUi(this);
    gridlayout = new QGridLayout(this->centralWidget());   //centralwidget = QWidget* basically create a new Qlayout

    float labelHeight = (this->height())/numRows+3;
    float labelWidth = (this->width())/numColumns+3;
    max = std::min(labelWidth, labelHeight);

}

MainWindow::~MainWindow()
{
    delete ui;
}
QWidget* MainWindow::getCentralWidget() {
    return ui->centralwidget;
}
Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}
//void MainWindow::moveSlot(Input input) {}
void MainWindow::moveSlot(Input in) {
    QMessageBox msg;
    game->getPGraphicalUI()->move(in);
    if(game->getPGraphicalUI()->getPCharacter()->getStatus() == alive)  {
        ui->statusbar->showMessage(
                    QString("HP: ") + QString::number(game->getPGraphicalUI()->getPCharacter()->getHitpoint()) +
                    QString("  Stamina: ") + QString::number(game->getPGraphicalUI()->getPCharacter()->getStamina()) +
                    QString("  Strength: ") + QString::number(game->getPGraphicalUI()->getPCharacter()->getStrength()) +
                    QString(" Status: Alive")
                    );
    }
    else {
        ui->statusbar->showMessage(
                    QString("HP: ") + QString::number(game->getPGraphicalUI()->getPCharacter()->getHitpoint()) +
                    QString("  Stamina: ") + QString::number(game->getPGraphicalUI()->getPCharacter()->getStamina()) +
                    QString("  Strength: ") + QString::number(game->getPGraphicalUI()->getPCharacter()->getStrength()) +
                    QString(" Status: Dead")
                    );
    }
    while(gridlayout->count()) {
        QWidget* widget = gridlayout->itemAt(0)->widget();
        if(widget){
            gridlayout->removeWidget(widget);
            delete widget;
        }
    }
    GraphicalUI::draw(game->getCurrentLevel(), this);
    if(game->checkEndGame()) {
        msg.setText(QString("Game Over"));
        msg.exec();
        this->hide();

    }


    //can actually end the game here


}

float MainWindow::getMax() const
{
    return max;
}

QGridLayout *MainWindow::getGridlayout() const
{
    return gridlayout;
}


