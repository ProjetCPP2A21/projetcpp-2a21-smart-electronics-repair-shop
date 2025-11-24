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
#include <QApplication>      // AJOUTÉ ICI (pour QApplication::beep())
#include <QThread>           // AJOUTÉ ICI (pour le son d'alerte)
#include "stock.h"
#include "qrcodegen.hpp"

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

private:
    Ui::stock *ui;
    stock stmp;
    void statistique();
    QChartView *chartViewGlobal = nullptr;
    QNetworkAccessManager *networkManager;

    // ALERTE STOCK CRITIQUE (gratuite, automatique, visuelle + sonore)
private:
private:
    void envoyerSMSsimple(const QString& message);  // ← AJOUTEZ CETTE LIGNE
    void verifierStockEtAlerter();
};

#endif // NSTOCK_H
