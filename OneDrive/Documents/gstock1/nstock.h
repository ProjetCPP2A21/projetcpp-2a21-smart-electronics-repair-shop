#ifndef NSTOCK_H
#define NSTOCK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Nstock;
}
QT_END_NAMESPACE

class Nstock : public QMainWindow
{
    Q_OBJECT

public:
    Nstock(QWidget *parent = nullptr);
    ~Nstock();

private:
    Ui::Nstock *ui;
};
#endif // NSTOCK_H
