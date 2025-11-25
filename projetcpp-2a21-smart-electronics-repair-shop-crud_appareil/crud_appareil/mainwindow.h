#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appareil.h"

// --- Includes Graphiques ---
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>

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

    // Fonctionnalités
    void on_lineEdit_ID_textChanged(const QString &text);
    void on_ExporterPDF_clicked();
    void on_ShowStats_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    void chargerTable(const QString &filter = "");
};

#endif // MAINWINDOW_H
