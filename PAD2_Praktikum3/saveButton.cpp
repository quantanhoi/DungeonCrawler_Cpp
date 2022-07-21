#include "saveButton.h"
#include"DungeonCrawler.h"
#include<QMessageBox>
#include<QWidget>
#include<QMainWindow>
#include <QPushButton>
#include <QObject>
saveButton::saveButton(MainWindow* Window, DungeonCrawler* dungeonCrawler, QWidget* parent)
    :QPushButton(parent)
{
    mainWindow = Window;
    game = dungeonCrawler;
    QWidget::connect(this, &Button::clicked, this , &saveButton::onClicked);


}
void saveButton::onClicked() {
    game->Save();
}
