#ifndef SCLIENT_H
#define SCLIENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Sclient;
}
QT_END_NAMESPACE

class Sclient : public QMainWindow
{
    Q_OBJECT

public:
    Sclient(QWidget *parent = nullptr);
    ~Sclient();

private:
    Ui::Sclient *ui;
};
#endif // SCLIENT_H
