#ifndef NSTOCK_H
#define NSTOCK_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QVBoxLayout>
#include <QPdfWriter>
#include <QPainter>

#include "stock.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class stock;
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
    void on_btrechercher_stock_clicked();
    void on_bttrier_stock_clicked();
private slots:
    void on_btmisajour_stock_clicked();
    void on_btstatistique_stock_clicked();
    void exporterPDF();



private:
    Ui::stock *ui;
    stock stmp;
    void statistique();
    QChartView *chartViewGlobal = nullptr;


};
#endif
