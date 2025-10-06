#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MENU;
}
QT_END_NAMESPACE

class MENU : public QMainWindow
{
    Q_OBJECT

public:
    MENU(QWidget *parent = nullptr);
    ~MENU();

private:
    Ui::MENU *ui;
};
#endif // MENU_H
