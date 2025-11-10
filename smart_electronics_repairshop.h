#ifndef SMART_ELECTRONIC_REPAIRSHOP_H
#define SMART_ELECTRONIC_REPAIRSHOP_H

#include <QMainWindow>
#include "employe.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class menu_employer;
}
QT_END_NAMESPACE

class menu_employer : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu_employer(QWidget *parent = nullptr);
    ~menu_employer();
private slots :
    void on_pushButton_5_clicked();
    void on_btnSupprimer_clicked();
    void on_btnModifier_clicked();
    void on_lineEdit_recherche_textChanged(const QString &text);
    // Correction de la faute de frappe ici (QModelKndex -> QModelIndex)
    void on_tableView_2_clicked(const QModelIndex &index);
private:
    Ui::menu_employer *ui;
    Employer emp;
    void goToPage(QWidget *page);
    void rafraichir();
    void viderFormulaire();
    void chargerFormulaire(const QString& id);
    // Fonction de validation ajoutée
    bool validerChampsRequis();
};

#endif // SMART_ELECTRONIC_REPAIRSHOP_H
