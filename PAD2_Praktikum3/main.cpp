#include "mainwindow.h"
#include"startscreen.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartScreen* sc = new StartScreen;
    sc->show();
    //DungeonCrawler* game = new DungeonCrawler;
    //game->play();
    return a.exec();
}
