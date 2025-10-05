#ifndef GEMPLOYER_H
#define GEMPLOYER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Gemployer;
}
QT_END_NAMESPACE

class Gemployer : public QMainWindow
{
    Q_OBJECT

public:
    Gemployer(QWidget *parent = nullptr);
    ~Gemployer();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::Gemployer *ui;
};
#endif // GEMPLOYER_H
