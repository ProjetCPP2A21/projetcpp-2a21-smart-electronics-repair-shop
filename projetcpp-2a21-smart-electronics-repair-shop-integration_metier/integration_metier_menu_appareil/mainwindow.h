#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appareil.h"
#include "stock.h"
// --- Includes Graphiques ---
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include "qrcodegen.hpp"
#include <QNetworkAccessManager>
// --- Correction pour Qt 6 ---
// La macro QT_CHARTS_USE_NAMESPACE n'existe plus.
// On utilise l'espace de nom standard.

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // CRUD
    void on_pushButton_Ajouter_clicked();
    void on_pushButton_Supprimer_clicked();
    void on_pushButton_Modifier_clicked();
    void on_tablewidget_Appareils_cellClicked(int row, int column);
    //stock

    void on_btajouter_stock_clicked();
    void on_btsupprimer_stock_clicked();
    void on_btmodifier_stock_clicked();
    void on_btrechercher_stock_clicked();
    void on_bttrier_stock_clicked();
    void on_btmisajour_stock_clicked();
    void on_btstatistique_stock_clicked();
    void on_btQR_stock_clicked();
    void exporterPDF();
    void envoyerSMSsimple(const QString& message);
    void verifierStockEtAlerter();
    void on_btretour_stock_clicked();
     void on_stock_clicked();
    // Fonctionnalités
    void on_lineEdit_ID_textChanged(const QString &text);
    void on_ExporterPDF_clicked();
    void on_ShowStats_clicked();
    void on_pushButton_4_clicked();

    void on_appareils_clicked();

private:
    Ui::MainWindow *ui;
    void chargerTable(const QString &filter = "");
    //stock
    stock tm;
    void statistique();
    QChartView *chartViewGlobal = nullptr;
    QNetworkAccessManager *networkManager;
    //

};

#endif // MAINWINDOW_H
