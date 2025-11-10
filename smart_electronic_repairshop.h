#ifndef SMART_ELECTRONIC_REPAIRSHOP_H
#define SMART_ELECTRONIC_REPAIRSHOP_H

#include <QMainWindow>
#include "client.h"
#include "connection.h"

namespace Ui { class menu_employer; }

class menu_employer : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu_employer(QWidget *parent = nullptr);
    ~menu_employer();

private slots:
    void on_Ajouter_clicked();
    void on_Supprimer_clicked();
    void on_Modifier_clicked();
    void on_retourC_clicked();

private:
    Ui::menu_employer *ui;
    Connection conn;

    void goToPage(QWidget *page);
    void setupClientValidators();
    void refreshClientTable();
    void clearClientFields();
};

#endif
