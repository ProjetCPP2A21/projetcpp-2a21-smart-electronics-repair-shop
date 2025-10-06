#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "ui_menu.h"

class MENU : public QMainWindow
{
    Q_OBJECT

public:
    MENU(QWidget *parent = nullptr);
    ~MENU();

private slots:
    void onBtCLClicked();  // Slot for "Client" button
    void onretourCClicked();  // Slot for "Return" button (new slot)

private:
    Ui::MENU *ui;
};

#endif // MENU_H


