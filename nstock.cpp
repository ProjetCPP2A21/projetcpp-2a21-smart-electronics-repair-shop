#include "nstock.h"
#include "ui_nstock.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
nstock::nstock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stock)
{
    ui->setupUi(this);
    ui->tableView->setModel(stmp.afficher());
    connect(ui->btexporterPDF_stock, &QPushButton::clicked, this, &nstock::exporterPDF);


}

nstock::~nstock()
{
    delete ui;
}


void nstock::on_btajouter_stock_clicked()
{
    QString idText = ui->lineEdit_IDstock->text().trimmed();


    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez saisir un identifiant (ID) !");
        ui->lineEdit_IDstock->setFocus();
        return;
    }


    bool okId;
    int id = idText.toInt(&okId);
    if (!okId || idText.contains(QRegularExpression("[^0-9]"))) {
        QMessageBox::critical(this, "Erreur de saisie",
                              "L'ID doit contenir uniquement des chiffres (pas de lettres ni de symboles).");
        ui->lineEdit_IDstock->setFocus();
        return;
    }


    QString nom = ui->lineEdit_nomstock->text();
    QString reference = ui->lineEdit_referencestock->text();
    QString categorie = ui->lineEdit_categorie->text();
    QString quantite = ui->lineEdit_quantite->text();
    QString prixachat = ui->lineEdit_prixachat->text();
    QString prixvente = ui->lineEdit_prixvente->text();
    QString fournisseur = ui->lineEdit_fournisseur->text();
    QString datelivraison = ui->dateEdit->date().toString("yyyy-MM-dd");

    QString quantiteText = ui->lineEdit_quantite->text();


    bool ok;
    int quantiteInt = quantiteText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être un nombre entier !");
        return;
    }



    prixachat.replace(",", ".");
    prixvente.replace(",", ".");
    bool ok1 = true, ok2 = true;
    if (!prixachat.trimmed().isEmpty()) prixachat.toDouble(&ok1);
    if (!prixvente.trimmed().isEmpty()) prixvente.toDouble(&ok2);
    if (!ok1 || !ok2) {
        QMessageBox::critical(this, "Erreur de saisie",
                              "Veuillez entrer des valeurs numériques valides pour les prix !");
        return;
    }


    stock stmp(id, nom, reference, categorie, quantite, prixachat, prixvente, fournisseur, datelivraison);

    bool test = stmp.ajouter();
    if (test) {
        ui->tableView->setModel(stmp.afficher());
        QMessageBox::information(this, "Succès", "Ajout effectué avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout !");
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
    QString quantiteText = ui->lineEdit_quantite->text();


    bool ok;
    int quantiteInt = quantiteText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être un nombre entier !");
        return;
    }

    prixachat.replace(",", ".");
    prixvente.replace(",", ".");
    bool ok1 = true, ok2 = true;
    if (!prixachat.trimmed().isEmpty()) prixachat.toDouble(&ok1);
    if (!prixvente.trimmed().isEmpty()) prixvente.toDouble(&ok2);
    if (!ok1 || !ok2) {
        QMessageBox::critical(this, "Erreur de saisie",
                              "Veuillez entrer des valeurs numériques valides pour les prix !");
        return;
    }
    stock s(id, nom, reference, categorie, quantite, prixachat, prixvente, fournisseur, datelivraison);

    bool test = s.modifier();

    if (test) {
        QMessageBox::information(this, "Succès", "Modification effectuée !");
        ui->tableView->setModel(s.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void nstock::on_btrechercher_stock_clicked()
{
    QString nom = ui->lineEdit_recherche_stock->text().trimmed();
    qDebug() << "Recherche :" << nom;

    if (nom.isEmpty()) {
        ui->tableView->setModel(stmp.afficher()); // affiche tout si vide
        return;
    }

    ui->tableView->setModel(stmp.rechercher(nom));
}


void nstock::on_bttrier_stock_clicked()
{
    QString critere = "PRIXVENTE";
    QString ordre = "DESC";

    ui->tableView->setModel(stmp.trier(critere, ordre));
}
void nstock::on_btmisajour_stock_clicked()
{
    // Recharge toute la table depuis la base
    ui->tableView->setModel(stmp.afficher());

    QMessageBox::information(this, "Mise à jour", "Table mise à jour avec succès !");
}


/*void nstock::statistique()
{
    QSqlQuery query;
    query.prepare("SELECT categorie, SUM(quantite) FROM stock GROUP BY categorie");

    QPieSeries *series = new QPieSeries();

    if(query.exec()) {
        while(query.next()) {
            QString categorie = query.value(0).toString();
            int total = query.value(1).toInt();

            series->append(categorie, total);
        }
    }

    for (auto slice : series->slices()) {
        slice->setLabelVisible(true);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des quantités par catégorie");
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->resize(600, 400);
    chartView->show();
}*/
void nstock::statistique()
{
    QSqlQuery query;
    query.prepare("SELECT categorie, SUM(quantite) FROM stock GROUP BY categorie");

    QPieSeries *series = new QPieSeries();
    if(query.exec()) {
        while(query.next()) {
            QString categorie = query.value(0).toString();
            int total = query.value(1).toInt();
            series->append(categorie, total);
        }
    }

    for (auto slice : series->slices())
        slice->setLabelVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des quantités par catégorie");
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartViewGlobal = new QChartView(chart);  // sauvegarde pour l’export
    chartViewGlobal->setRenderHint(QPainter::Antialiasing);


    if(ui->chartFrame_->layout() != nullptr)
        delete ui->chartFrame_->layout();

    QVBoxLayout *layout = new QVBoxLayout(ui->chartFrame_);
    layout->addWidget(chartViewGlobal);
    ui->chartFrame_->setLayout(layout);
}

void nstock::on_btstatistique_stock_clicked()
{
    statistique();
}
void nstock::exporterPDF()
{

    if (ui->tableView->model()->rowCount() == 0) {
        QMessageBox::critical(this, "Erreur", "Aucune donnée à exporter !");
        return;
    }

    // Choisir le fichier PDF
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Exporter en PDF",
        "",
        "PDF (*.pdf)"
        );
    if (filePath.isEmpty())
        return;

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setFont(QFont("Arial", 10));

    int rowCount = ui->tableView->model()->rowCount();
    int colCount = ui->tableView->model()->columnCount();

    int margin = 20;
    int yPos = margin;
    int rowHeight = 25;


    int xPos = margin;
    for (int col = 0; col < colCount; col++) {
        QString headerText = ui->tableView->model()->headerData(col, Qt::Horizontal).toString();
        painter.drawText(xPos, yPos, 100, rowHeight, Qt::AlignLeft, headerText);
        xPos += 100;
    }

    yPos += rowHeight;


    for (int row = 0; row < rowCount; row++) {
        xPos = margin;
        for (int col = 0; col < colCount; col++) {
            QString cellText = ui->tableView->model()->data(ui->tableView->model()->index(row, col)).toString();
            painter.drawText(xPos, yPos, 100, rowHeight, Qt::AlignLeft, cellText);
            xPos += 100;
        }
        yPos += rowHeight;


        if (yPos + rowHeight > pdfWriter.height() - margin) {
            pdfWriter.newPage();
            yPos = margin;
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "PDF exporté avec succès !");
}

