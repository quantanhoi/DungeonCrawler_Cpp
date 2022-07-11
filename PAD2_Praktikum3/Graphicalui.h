#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include <QObject>
#include <QWidget>
#include"AbstractUI.h"
#include"Button.h"
#include"mainwindow.h"
class GraphicalUI :
        virtual public AbstractUI,
        virtual public Controller
{
public:
    explicit GraphicalUI();
    static void draw(Level* level, MainWindow* mainWindow);
    int move(Input in) override;
    void chooseCharacter(Level* level) override;
    static void setButton(QPushButton* button, const char path[], float max_size);
    void moveSlot(Input input);
    void moveToTile(int row, int col);
    void test();
    Input getLastInput() const;
    void setLastInput(Input newLastInput);

protected:
    Input lastInput;
};

#endif // GRAPHICALUI_H
