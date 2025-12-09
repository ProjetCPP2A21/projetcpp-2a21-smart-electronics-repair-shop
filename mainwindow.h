#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTimer>
#include "client.h"
#include "arduino.h"

#include <QChartView>     // UNIQUEMENT ÇA
#include <QChart>
#include <QPieSeries>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Ajouter_clicked();
    void on_Supprimer_clicked();
    void on_Modifier_clicked();
    void on_rechercherC_clicked();
    void on_triC_clicked();
    void on_statC_clicked();
    void on_PDFC_clicked();
    void on_historique_clicked();
    void on_RDV_clicked();
    void on_btnRetourRDV_clicked();
    void on_btnVoirTousRDV_clicked();
    void on_btnRetourTousRDV_clicked();
    void alerterRDVDepuisTable(int row);
    void on_calendarWidget_clicked(QDate date);
    void on_btnAjouterRDV_clicked();
    void on_btnSupprimerRDV_clicked();
    void on_btnAlerterRDV_clicked();
    void colorierCalendrier();
    void statistiqueC();
    void on_tableViewClients_clicked(const QModelIndex &index);
    void verifierRDVEnCours();
    bool envoyerAlerteArduino(int idClient);

private:
    Ui::MainWindow *ui;
    CLIENT C;
    QChartView *chartView = nullptr;   // SANS QtCharts:: → ÇA MARCHE TOUJOURS
    Arduino *arduino;
    QTimer *timerRDV;
    QList<int> derniersRDV;  // Pour éviter les doublons
};

#endif // MAINWINDOW_H
