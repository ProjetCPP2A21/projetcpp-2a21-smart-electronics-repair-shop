#include "nstock.h"
#include "ui_nstock.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>

nstock::nstock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::prixachat_2)
{
    ui->setupUi(this);
    ui->tableView->setModel(stmp.afficher());



}

nstock::~nstock()
{
    delete ui;
}


void nstock::on_btajouter_stock_clicked()
{


    int id = ui->lineEdit_IDstock->text().toInt();
    QString nom = ui->lineEdit_nomstock->text();
    QString reference = ui->lineEdit_referencestock->text();
    QString categorie = ui->lineEdit_categorie->text();
    QString quantite = ui->lineEdit_quantite->text();
    QString prixachat = ui->lineEdit_prixachat->text();
    QString prixvente = ui->lineEdit_prixvente->text();
    QString fournisseur = ui->lineEdit_fournisseur->text();
    QString datelivraison = ui->dateEdit->date().toString("yyyy-MM-dd");

    stock stmp(id,nom,reference,categorie,quantite,prixachat,prixvente,fournisseur,datelivraison);
    bool test = stmp.ajouter();
    if(test)
    {


        //refresh
        ui->tableView->setModel(stmp.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\nClick Cancel to exit."),
                                 QMessageBox::Cancel);

        }
    else
    {
        QMessageBox::critical(this, QObject::tr("Erreur"),
                              QObject::tr("Ajout non effectué\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
}
void nstock::on_btsupprimer_stock_clicked()
{
    int id = ui->lineEdit_IDstock->text().toInt();
    bool test = stmp.supprimer(id);

    if (test)
    {


        ui->tableView->setModel(stmp.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\nClick Cancel to exit."),
                                 QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Erreur"),
                              QObject::tr("Suppression non effectuée\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
}

void nstock::on_btmodifier_stock_clicked()
{
    int id = ui->lineEdit_IDstock->text().toInt();
    QString nom = ui->lineEdit_nomstock->text();
    QString reference = ui->lineEdit_referencestock->text();
    QString categorie = ui->lineEdit_categorie->text();
    QString quantite = ui->lineEdit_quantite->text();
    QString prixachat = ui->lineEdit_prixachat->text();
    QString prixvente = ui->lineEdit_prixvente->text();
    QString fournisseur = ui->lineEdit_fournisseur->text();
    QString datelivraison = ui->dateEdit->date().toString("yyyy-MM-dd");

    stock s(id, nom, reference, categorie, quantite, prixachat, prixvente, fournisseur, datelivraison);

    bool test = s.modifier();

    if (test) {
        QMessageBox::information(this, "Succès", "Modification effectuée !");
        ui->tableView->setModel(s.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}
