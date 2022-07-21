#ifndef BUTTON_H
#define BUTTON_H
#include<QWidget>
#include<QMainWindow>
#include <QPushButton>
#include <QObject>
enum Input {
    down, down_left, down_right, left, right, skip, up, up_left, up_right
};
class MainWindow;
class GraphicalUI;
class Button : public QPushButton
{
public:
    Button(Input input, MainWindow* mainWindow, QWidget* parent = nullptr);
    Input getInput();

signals:
public slots:
    void onClicked();
protected:
    Input input;
private:
    GraphicalUI* pGraphicalUI;
    MainWindow* mainWindow;
};

#endif // BUTTON_H
