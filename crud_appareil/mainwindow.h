#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appareil.h" // Assurez-vous que cet include est présent

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
    void on_pushButton_Ajouter_clicked();
    void on_pushButton_Supprimer_clicked();
    void on_pushButton_Modifier_clicked();
    // Slot pour le clic sur le tableau
    void on_tablewidget_Appareils_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    // Fonction privée pour charger/recharger le tableau
    void chargerTable();
};
#endif // MAINWINDOW_H
