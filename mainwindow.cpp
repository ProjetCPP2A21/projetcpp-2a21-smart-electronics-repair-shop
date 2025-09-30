#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connexion des boutons
    connect(ui->btnAjouter, &QPushButton::clicked, this, &MainWindow::ajouterEmploye);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &MainWindow::supprimerEmploye);
    connect(ui->btnExporter, &QPushButton::clicked, this, &MainWindow::exporterPDF);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ajouterEmploye()
{
    int row = ui->tableEmployes->rowCount();
    ui->tableEmployes->insertRow(row);

    ui->tableEmployes->setItem(row, 0, new QTableWidgetItem(ui->txtID->text()));
    ui->tableEmployes->setItem(row, 1, new QTableWidgetItem(ui->txtNom->text()));
    ui->tableEmployes->setItem(row, 2, new QTableWidgetItem(ui->txtPrenom->text()));
    ui->tableEmployes->setItem(row, 3, new QTableWidgetItem(ui->txtTel->text()));
    ui->tableEmployes->setItem(row, 4, new QTableWidgetItem(ui->dateNaissance->date().toString("dd/MM/yyyy")));
    ui->tableEmployes->setItem(row, 5, new QTableWidgetItem(ui->dateEmbauche->date().toString("dd/MM/yyyy")));

    QMessageBox::information(this, "Ajout", "Employé ajouté avec succès !");
}

void MainWindow::supprimerEmploye()
{
    int row = ui->tableEmployes->currentRow();
    if (row >= 0) {
        ui->tableEmployes->removeRow(row);
        QMessageBox::information(this, "Suppression", "Employé supprimé !");
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé !");
    }
}

void MainWindow::exporterPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter PDF", "", "*.pdf");

    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QString html = "<h1>Liste des Employés</h1><table border=1 cellspacing=0 cellpadding=4>";

    for (int i = 0; i < ui->tableEmployes->rowCount(); i++) {
        html += "<tr>";
        for (int j = 0; j < ui->tableEmployes->columnCount(); j++) {
            QTableWidgetItem *item = ui->tableEmployes->item(i, j);
            html += "<td>" + (item ? item->text() : "") + "</td>";
        }
        html += "</tr>";
    }
    html += "</table>";

    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(this, "Export PDF", "Exportation réussie !");
}
