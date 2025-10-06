#ifndef NSTOCK_H
#define NSTOCK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class nstock;
}
QT_END_NAMESPACE

class nstock : public QMainWindow
{
    Q_OBJECT

public:
    nstock(QWidget *parent = nullptr);
    ~nstock();

private:
    Ui::nstock *ui;
};
#endif // NSTOCK_H
