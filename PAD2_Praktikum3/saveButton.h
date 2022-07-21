#ifndef SAVEBUTTON_H
#define SAVEBUTTON_H
#include<QWidget>
#include<QMainWindow>
#include <QPushButton>
#include <QObject>
class DungeonCrawler;
class MainWindow;
class saveButton : public QPushButton
{
public:
    saveButton(MainWindow* Window, DungeonCrawler* dungeonCrawler, QWidget* parent = nullptr);
signals:
public slots:
    void onClicked();
protected:
    DungeonCrawler* game;
    MainWindow* mainWindow;
};

#endif // SAVEBUTTON_H
