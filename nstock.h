#ifndef NSTOCK_H
#define NSTOCK_H

#include <QMainWindow>
#include "stock.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class prixachat_2;
}
QT_END_NAMESPACE

class nstock : public QMainWindow
{
    Q_OBJECT

public:
    nstock(QWidget *parent = nullptr);
    ~nstock();
private slots:
    void on_btajouter_stock_clicked();

    void on_btsupprimer_stock_clicked();
    void on_btmodifier_stock_clicked();
private:
    Ui::prixachat_2 *ui;
    stock stmp;
};
#endif
