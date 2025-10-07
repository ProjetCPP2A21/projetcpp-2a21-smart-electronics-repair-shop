#ifndef MENU_EMPLOYER_H
#define MENU_EMPLOYER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class menu_employer;
}
QT_END_NAMESPACE

class menu_employer : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu_employer(QWidget *parent = nullptr);
    ~menu_employer();

private:
    Ui::menu_employer *ui;

    void goToPage(QWidget *page);
};

#endif // MENU_EMPLOYER_H
