#include "gemployer.h"
#include "ui_gemployer.h"
#include <QMessageBox>
#include <QSqlQuery>        // AJOUTÉ
#include <QDate>

Gemployer::Gemployer(QWidget *parent) : QMainWindow(parent), ui(new Ui::Gemployer)
{
    ui->setupUi(this);
    rafraichir();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSortingEnabled(true);
}

Gemployer::~Gemployer() { delete ui; }

void Gemployer::rafraichir()
{
    QSqlQueryModel* model = emp.afficher();
    if (model) ui->tableView->setModel(model);
}

void Gemployer::viderFormulaire()
{
    ui->lineEdit->clear();                    // ID_EMPLOYE
    ui->lineEdit_3->clear();                  // NOMEMPLOYE
    ui->lineEdit_6->clear();                  // PRENOM
    ui->lineEdit_email->clear();              // EMAIL
    ui->lineEdit_tel->clear();                // TELEPHONE
    ui->lineEdit_date->setDate(QDate::currentDate());  // QDateEdit → setDate
    ui->dateEdit_recrutement->setDate(QDate::currentDate());
    ui->poste->clear();                       // POST
    ui->salaire->clear();                     // SALAIRE
}

void Gemployer::on_pushButton_5_clicked()
{
    emp.setId(ui->lineEdit->text());
    emp.setNom(ui->lineEdit_3->text());
    emp.setPrenom(ui->lineEdit_6->text());
    emp.setEmail(ui->lineEdit_email->text());
    emp.setTelephone(ui->lineEdit_tel->text().toInt());
    emp.setDateNaissance(ui->lineEdit_date->date());  // QDateEdit → date()
    emp.setDateRecrutement(ui->dateEdit_recrutement->date());
    emp.setPoste(ui->poste->text());
    emp.setSalaire(ui->salaire->text().toDouble());

    if (emp.ajouter()) {
        rafraichir();
        QMessageBox::information(this, "Succès", "Employé ajouté !");
        viderFormulaire();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec ajout (ID existe ?)");
    }
}

void Gemployer::on_btnSupprimer_clicked()
{
    QString id = ui->lineEdit->text();
    if (emp.supprimer(id)) {
        rafraichir();
        QMessageBox::information(this, "Succès", "Supprimé !");
        viderFormulaire();
    } else {
        QMessageBox::warning(this, "Erreur", "ID introuvable.");
    }
}

void Gemployer::on_btnModifier_clicked()
{
    emp.setId(ui->lineEdit->text());
    emp.setNom(ui->lineEdit_3->text());
    emp.setPrenom(ui->lineEdit_6->text());
    emp.setEmail(ui->lineEdit_email->text());
    emp.setTelephone(ui->lineEdit_tel->text().toInt());
    emp.setDateNaissance(ui->lineEdit_date->date());  // QDateEdit
    emp.setDateRecrutement(ui->dateEdit_recrutement->date());
    emp.setPoste(ui->poste->text());
    emp.setSalaire(ui->salaire->text().toDouble());

    if (emp.modifier()) {
        rafraichir();
        QMessageBox::information(this, "Succès", "Modifié !");
        viderFormulaire();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec modification.");
    }
}

void Gemployer::on_lineEdit_recherche_textChanged(const QString &text)
{
    if (text.isEmpty()) rafraichir();
    else ui->tableView->setModel(emp.rechercher(text));
}

void Gemployer::on_tableView_clicked(const QModelIndex &index)
{
    QString id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
    chargerFormulaire(id);
}

void Gemployer::chargerFormulaire(const QString& id)
{
    QSqlQuery q;  // OK maintenant
    q.prepare("SELECT * FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        ui->lineEdit->setText(q.value("ID_EMPLOYE").toString());
        ui->lineEdit_3->setText(q.value("NOMEMPLOYE").toString());
        ui->lineEdit_6->setText(q.value("PRENOM").toString());
        ui->lineEdit_email->setText(q.value("EMAIL").toString());
        ui->lineEdit_tel->setText(q.value("TELEPHONE").toString());
        ui->lineEdit_date->setDate(q.value("DATENAISSANCE").toDate());     // QDateEdit → setDate
        ui->dateEdit_recrutement->setDate(q.value("DATERECRUTEMENT").toDate());
        ui->poste->setText(q.value("POST").toString());
        ui->salaire->setText(q.value("SALAIRE").toString());
    }
}
