#include "startscreen.h"
#include "ui_startscreen.h"
#include<QLabel>
#include<QMainWindow>
#include<DungeonCrawler.h>
StartScreen::StartScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    //QWidget::setStyleSheet("background-color: black;");
    //QLabel* start = new QLabel(this);
    //start->setPixmap(QPixmap(":/textures/startscreen.png"));
    //start->setScaledContents(true);


}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::on_pushButton_clicked()
{
    QWidget::hide();
    DungeonCrawler* game = new DungeonCrawler;
    game->play();
}


void StartScreen::on_pushButton_2_clicked()
{
    QWidget::hide();
    DungeonCrawler* game = new DungeonCrawler;
    game->loadGame();
}

