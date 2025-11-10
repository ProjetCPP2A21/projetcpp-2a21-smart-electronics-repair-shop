#ifndef MENU_EMPLOYER_H
#define MENU_EMPLOYER_H

#include <QMainWindow>
#include "employer.h"
#include "stock.h"
// Nécessaire pour QModelIndex
#include <QModelIndex>

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

private slots:
    void on_btajouter_stock_clicked();

    void on_btsupprimer_stock_clicked();
    void on_btmodifier_stock_clicked();
    void on_pushButton_5_clicked();
    void on_btnSupprimer_clicked();
    void on_btnModifier_clicked();
    void on_lineEdit_recherche_textChanged(const QString &text);
    // Correction de la faute de frappe ici (QModelKndex -> QModelIndex)
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::menu_employer *ui;
    void goToPage(QWidget *page);
    Employer emp;
    void rafraichir();
    void viderFormulaire();
    void chargerFormulaire(const QString& id);
    stock tm;
    // Fonction de validation ajoutée
    bool validerChampsRequis();
};

#endif // MENU_EMPLOYER_H
