#ifndef NSTOCK_H
#define NSTOCK_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QVBoxLayout>
#include <QPdfWriter>
#include <QPainter>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QApplication>
#include <QThread>
#include "stock.h"
#include "qrcodegen.hpp"
//

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


using namespace qrcodegen;

QT_BEGIN_NAMESPACE
namespace Ui { class stock; }
QT_END_NAMESPACE

class nstock : public QMainWindow
{
    Q_OBJECT

public:
    explicit nstock(QWidget *parent = nullptr);
    ~nstock();

private slots:
    void on_btajouter_stock_clicked();
    void on_btsupprimer_stock_clicked();
    void on_btmodifier_stock_clicked();
    void on_btrechercher_stock_clicked();
    void on_bttrier_stock_clicked();
    void on_btmisajour_stock_clicked();
    void on_btstatistique_stock_clicked();
    void on_btQR_stock_clicked();
    void exporterPDF();
//
    void on_btRechercheArduino_clicked();



private:
    Ui::stock *ui;
    stock stmp;
    void statistique();
    QChartView *chartViewGlobal = nullptr;
    QNetworkAccessManager *networkManager;
//
    QSerialPort *arduino;

private:
    void envoyerSMSsimple(const QString& message);
    void verifierStockEtAlerter();
};

#endif
