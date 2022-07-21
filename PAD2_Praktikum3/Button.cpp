#include "Button.h"
#include"mainwindow.h"
#include"Graphicalui.h"
#include<QMessageBox>
Button::Button(Input in,MainWindow* mainWindow, QWidget* parent)
    :QPushButton(parent)
{
    this->mainWindow = mainWindow;
    input = in;
    QWidget::connect(this, &Button::clicked, this , &Button::onClicked);

}
void Button::onClicked() {
    mainWindow->moveSlot(input);

}
Input Button::getInput() {
    return input;
}
