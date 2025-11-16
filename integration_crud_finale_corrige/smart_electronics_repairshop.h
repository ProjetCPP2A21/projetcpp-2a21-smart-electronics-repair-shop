#ifndef SMART_ELECTRONIC_REPAIRSHOP_H
#define SMART_ELECTRONIC_REPAIRSHOP_H
#include "stock.h"
#include "employe.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class osana_dashboard;
}
QT_END_NAMESPACE

class osana_dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit osana_dashboard(QWidget *parent = nullptr);
    ~osana_dashboard();
private slots :
    //stock
    void on_btajouter_stock_3_clicked(); //stock add
    void on_btsupprimer_stock_3_clicked(); //stock delete
    void on_btmodifier_stock_3_clicked(); //stock edit
    //employe
    void on_pushButton_5_clicked(); //employe add
    void on_btnSupprimer_clicked(); //employe delete
    void on_btnModifier_clicked(); //employe delete
    void on_lineEdit_recherche_textChanged(const QString &text);
    // Correction de la faute de frappe ici (QModelKndex -> QModelIndex)
    void on_tableView_2_clicked(const QModelIndex &index);
private:
    Ui::osana_dashboard *ui;
    employe emp; //employe data object
    stock tm; //stock data object
    void goToPage(QWidget *page);
    void rafraichir();
    void viderFormulaire();
    void chargerFormulaire(const QString& id);
    // Fonction de validation ajoutée
    bool validerChampsRequis();
};

#endif // SMART_ELECTRONIC_REPAIRSHOP_H
