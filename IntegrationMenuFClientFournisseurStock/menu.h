#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "client.h"
#include "fournisseur.h"

namespace Ui {
class MENU;
}

class MENU : public QMainWindow
{
    Q_OBJECT

public:
    explicit MENU(QWidget *parent = nullptr);
    ~MENU();

private slots:
    void on_btCL_clicked();
    void on_btFO_clicked();
    void on_retourC_clicked();
    void on_retourF_clicked();
    void on_ajouterC_clicked();
    void on_ModifierC_clicked();
    void on_SupprimerC_clicked();
    void on_rechercheC_clicked();
    void on_triC_clicked();
    void on_btnAjouter_clicked();
    void on_btnModifier_clicked();
    void on_btnSupprimer_clicked();
    void on_rechercheF_clicked();
    void on_triF_clicked();

private:
    Ui::MENU *ui;
    Client *clientGestionnaire;
    Fournisseur *fournisseurGestionnaire;
};

#endif // MENU_H
