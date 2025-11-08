#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

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

private:
    Ui::MainWindow *ui;
    CLIENT C;

};

#endif // MAINWINDOW_H
