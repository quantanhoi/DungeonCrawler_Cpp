#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QPushButton>
#include"AbstractUI.h"
#include"Button.h"
#include <QGridLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class DungeonCrawler;
class Character;
class MainWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DungeonCrawler* game, QWidget *parent = nullptr);
    ~MainWindow();
    /*void draw(Level* level) override;
    int move() override;
    void chooseCharacter(Level* level) override;
    void setButton(QPushButton* button, const char path[], float max_size);
    void moveSlot(Input input);
    void moveToTile(int row, int col);*/
    Ui::MainWindow *getUi() const;
    QWidget* getCentralWidget();
    QGridLayout *getGridlayout() const;

    float getMax() const;

public slots:
    void moveSlot(Input input);
private:
    Ui::MainWindow *ui;
    DungeonCrawler* game;
    QGridLayout* gridlayout;
    float max;

};
#endif // MAINWINDOW_H
