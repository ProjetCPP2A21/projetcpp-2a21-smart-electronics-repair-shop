#include "mainwindow.h"          // OBLIGATOIRE EN TOUT PREMIER
#include "ui_mainwindow.h"

#include <QtCharts>
#include "client.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QDate>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QTextCharFormat>
#include <QSqlQuery>
#include <QItemSelectionModel>
#include <QInputDialog>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QVBoxLayout>

extern QSqlDatabase db;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui  (new Ui::MainWindow)
{
    ui->setupUi(this);

    // Affichage initial des clients
    ui->tableViewClients->setModel(C.afficher());

    // Validateurs
    ui->id->setValidator(new QIntValidator(1, 999999999, this));
    QRegularExpression nameRx("[A-Za-zÀ-ÿ ]+");
    ui->nom->setValidator(new QRegularExpressionValidator(nameRx, this));
    ui->prenom->setValidator(new QRegularExpressionValidator(nameRx, this));
    ui->telephone->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+"), this));

    // Remplissage automatique des heures RDV
    for (int h = 9; h <= 18; ++h)
        ui->comboBoxHeure->addItem(QString("%1:00").arg(h, 2, 10, QChar('0')));

    // Connexions des signaux
    connect(ui->RDV,                 &QPushButton::clicked, this, &MainWindow::on_RDV_clicked);
    connect(ui->btnRetourRDV,        &QPushButton::clicked, this, &MainWindow::on_btnRetourRDV_clicked);
    connect(ui->calendarWidget,      &QCalendarWidget::clicked, this, &MainWindow::on_calendarWidget_clicked);
    connect(ui->calendarWidget,      &QCalendarWidget::currentPageChanged, this, &MainWindow::colorierCalendrier);
    connect(ui->btnAjouterRDV,       &QPushButton::clicked, this, &MainWindow::on_btnAjouterRDV_clicked);
    connect(ui->btnSupprimerRDV,     &QPushButton::clicked, this, &MainWindow::on_btnSupprimerRDV_clicked);
}

MainWindow::~MainWindow() { delete ui; }

// ====================== AJOUTER CLIENT ======================
void MainWindow::on_Ajouter_clicked()
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text().trimmed().toUpper();
    QString prenom = ui->prenom->text().trimmed();
    QString tel = ui->telephone->text().trimmed();
    QDate dn = ui->dn->date();
    QDate di = ui->di->date();

    if (id <= 0 || nom.isEmpty() || prenom.isEmpty() || tel.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs sont obligatoires !");
        return;
    }

    CLIENT cl(id, nom, prenom, tel, dn.toString("dd/MM/yyyy"), di.toString("dd/MM/yyyy"));

    bool success;
    QString action;

    // Si le bouton dit "Enregistrer les modifications" → c'est une modification
    if (ui->Ajouter->text() == "Enregistrer les modifications") {
        success = cl.modifier();
        action = "modifié";
        // Remettre le bouton normal
        ui->Ajouter->setText("Ajouter");
        ui->id->setEnabled(true);
        ui->id->clear();
        ui->nom->clear();
        ui->prenom->clear();
        ui->telephone->clear();
    } else {
        success = cl.ajouter();
        action = "ajouté";
    }

    if (success) {
        QMessageBox::information(this, "Succès", QString("Client %1 avec succès !").arg(action));
        ui->tableViewClients->setModel(C.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'opération (ID existe déjà ?)");
    }
}

// ====================== SUPPRIMER CLIENT + SES RDV ======================
void MainWindow::on_Supprimer_clicked()
{
    bool ok;
    int id = ui->id->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide");
        return;
    }

    // Supprime d'abord les RDV du client
    QSqlQuery q(db);
    q.prepare("DELETE FROM GS_RDV WHERE ID = :id");
    q.bindValue(":id", id);
    q.exec();

    if (C.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Client et ses RDV supprimés !");
        ui->tableViewClients->setModel(C.afficher());
        ui->id->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Client non trouvé");
    }
}

// ====================== MODIFIER (tu peux compléter plus tard) ======================
void MainWindow::on_Modifier_clicked()
{
    // 1. Récupérer l'ID depuis le champ ID
    bool ok;
    int id = ui->id->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide !");
        return;
    }

    // 2. Chercher le client dans la base
    QSqlQuery query(db);
    query.prepare("SELECT NOM, PRENOM, TELEPHONE, "
                  "TO_CHAR(DATE_DE_NAISSANCE, 'DD/MM/YYYY'), "
                  "TO_CHAR(DATE_INSCRIPTION, 'DD/MM/YYYY') "
                  "FROM GS_CLIENTS WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Erreur", "Client non trouvé !");
        return;
    }

    // 3. Remplir automatiquement les champs
    ui->nom->setText(query.value(0).toString());
    ui->prenom->setText(query.value(1).toString());
    ui->telephone->setText(query.value(2).toString());

    QDate dn = QDate::fromString(query.value(3).toString(), "dd/MM/yyyy");
    QDate di = QDate::fromString(query.value(4).toString(), "dd/MM/yyyy");

    if (dn.isValid()) ui->dn->setDate(dn);
    if (di.isValid()) ui->di->setDate(di);

    // 4. Message + changement de comportement du bouton Ajouter
    QMessageBox::information(this, "Client chargé",
                             QString("Client <b>%1 %2</b> chargé. Modifiez les champs puis cliquez sur <u>Ajouter</u> pour enregistrer.")
                                 .arg(query.value(1).toString(), query.value(0).toString()));

    // Optionnel : changer le texte du bouton Ajouter temporairement
    ui->Ajouter->setText("Enregistrer les modifications");

    // On garde l'ID pour la modification
    ui->id->setEnabled(false); // on bloque l'ID pendant la modif
}

// ====================== RECHERCHER PAR ID ======================
void MainWindow::on_rechercherC_clicked()
{
    bool ok;
    int id = ui->IdC->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide");
        return;
    }
    ui->tableViewClients->setModel(C.rechercher(id));
}

// ====================== TRIER PAR ID ======================
void MainWindow::on_triC_clicked()
{
    ui->tableViewClients->setModel(C.afficherTrieParID());
}


// ====================== EXPORTER EN PDF ======================
void MainWindow::on_PDFC_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
    if (file.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);

    QPainter painter(&printer);

    painter.scale(4.8, 4.8);           // 4.8 = ENORME (tu peux monter à 5.5 si tu veux)
    painter.translate(80, 180);    // centre le tableau sur la page

    ui->tableViewClients->render(&painter);
    painter.end();

    QMessageBox::information(this, "PDF", "Exporté avec succès !");
}
// ====================== PAGE RDV ======================
void MainWindow::on_RDV_clicked()
{
    ui->stackedWidgetC->setCurrentIndex(1);
    colorierCalendrier();
    ui->tableViewRDV->setModel(new QSqlQueryModel());
    ui->labelInfoRDV->setText("Sélectionnez une date");
}

void MainWindow::on_btnRetourRDV_clicked()
{
    ui->stackedWidgetC->setCurrentIndex(0);
}

void MainWindow::colorierCalendrier()
{
    QCalendarWidget *cal = ui->calendarWidget;
    QDate debut = QDate(cal->yearShown(), cal->monthShown(), 1);
    QDate fin = debut.addMonths(1).addDays(-1);
    auto dispo = C.chargerDisponibilites(debut, fin);

    for (QDate d = debut; d <= fin; d = d.addDays(1)) {
        QTextCharFormat fmt;
        int nb = dispo.value(d, 0);
        if (d < QDate::currentDate())
            fmt.setBackground(QColor(150,150,150));
        else if (nb >= 8)
            fmt.setBackground(Qt::red), fmt.setForeground(Qt::white);
        else if (nb >= 4)
            fmt.setBackground(QColor(255,165,0)), fmt.setForeground(Qt::white);
        else
            fmt.setBackground(Qt::green), fmt.setForeground(Qt::white);
        cal->setDateTextFormat(d, fmt);
    }
}

void MainWindow::on_calendarWidget_clicked(QDate date)
{
    int nb = C.compterRDVParJour(date);
    ui->labelInfoRDV->setText(QString("Date : %1 | RDV : %2").arg(date.toString("dd/MM/yyyy")).arg(nb));
    ui->tableViewRDV->setModel(C.afficherRDVParDate(date));
    ui->btnAjouterRDV->setEnabled(date >= QDate::currentDate() && nb < 8);
}

void MainWindow::on_btnAjouterRDV_clicked()
{
    QDate date = ui->calendarWidget->selectedDate();
    if (date < QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur", "Date dans le passé");
        return;
    }

    QString txt = ui->lineEditIdClientRDV->text().trimmed();
    bool ok;
    int idc = txt.toInt(&ok);
    if (txt.isEmpty() || !ok || idc <= 0) {
        QMessageBox::warning(this, "Erreur", "ID client invalide");
        return;
    }

    QString heure = ui->comboBoxHeure->currentText();

    if (C.ajouterRDV(idc, date, heure)) {
        QMessageBox::information(this, "Succès", "RDV ajouté !");
        ui->lineEditIdClientRDV->clear();
        colorierCalendrier();
        on_calendarWidget_clicked(date);
    } else {
        QMessageBox::critical(this, "Erreur", "Heure déjà prise ou client inconnu");
    }
}

void MainWindow::on_btnSupprimerRDV_clicked()
{
    QDate date = ui->calendarWidget->selectedDate();
    if (date < QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur", "Impossible dans le passé");
        return;
    }

    auto sel = ui->tableViewRDV->selectionModel();
    if (!sel->hasSelection()) {
        QMessageBox::warning(this, "Aucun RDV", "Sélectionnez un RDV dans la liste");
        return;
    }

    int row = sel->currentIndex().row();
    QString heure = ui->tableViewRDV->model()->data(ui->tableViewRDV->model()->index(row, 0)).toString();

    if (QMessageBox::question(this, "Confirmer",
                              QString("Supprimer le RDV du %1 à %2 ?").arg(date.toString("dd/MM/yyyy")).arg(heure),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
        return;

    QSqlQuery q(db);
    q.prepare("DELETE FROM GS_RDV WHERE DATE_RDV = :d AND HEURE = :h");
    q.bindValue(":d", date.toString("dd/MM/yyyy"));
    q.bindValue(":h", heure);

    if (q.exec()) {
        QMessageBox::information(this, "Succès", "RDV supprimé");
        colorierCalendrier();
        on_calendarWidget_clicked(date);
    } else {
        QMessageBox::critical(this, "Erreur", "Suppression échouée");
    }
}
void MainWindow::on_historique_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                         "Historique des Rendez-vous",
                                         "<b>Entrez l'ID du client :</b>",
                                         QLineEdit::Normal,
                                         "",           // champ vide au départ
                                         &ok);

    if (!ok || text.trimmed().isEmpty()) {
        return; // Annulé ou vide
    }

    bool conversionOk;
    int id_client = text.toInt(&conversionOk);

    if (!conversionOk || id_client <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide (nombre entier positif) !");
        return;
    }

    // Chargement de l'historique
    QSqlQueryModel* model = C.historiqueRDV(id_client);
    ui->tableViewClients->setModel(model);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Historique RDV",
                                 QString("Aucun rendez-vous trouvé pour le client <b>ID %1</b>").arg(id_client));
        ui->tableViewClients->setModel(C.afficher()); // retour à la liste complète
    } else {
        QMessageBox::information(this, "Historique RDV",
                                 QString("<font color=green><b>%1</b></font> rendez-vous trouvé(s) pour le client <b>ID %2</b>")
                                     .arg(model->rowCount()).arg(id_client));
    }

    // Optionnel : titre de la fenêtre
    setWindowTitle(QString("Historique RDV - Client %1 (%2 RDV)")
                       .arg(id_client).arg(model->rowCount()));
}


void MainWindow::statistique()
{
    QPieSeries *series = new QPieSeries();

    QSqlQuery query(db);
    query.exec(
        "SELECT "
        " CASE "
        " WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) < 18 THEN '<18' "
        " WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) BETWEEN 18 AND 30 THEN '18-30' "
        " WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) BETWEEN 31 AND 50 THEN '31-50' "
        " ELSE '>50' "
        " END AS TRANCHE_AGE, "
        " COUNT(*) AS NB "
        "FROM GS_CLIENTS "
        "GROUP BY "
        " CASE "
        " WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) < 18 THEN '<18' "
        " WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) BETWEEN 18 AND 30 THEN '18-30' "
        " WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) BETWEEN 31 AND 50 THEN '31-50' "
        " ELSE '>50' END"
        );

    while (query.next()) {
        QString tranche = query.value(0).toString();
        int nb = query.value(1).toInt();
        series->append(tranche, nb);
    }

    for (QPieSlice *slice : series->slices()) {
        QString label = slice->label();

        // Set colors for different age groups
        if (label == "<18")       slice->setColor(QColor(0, 220, 0));
        else if (label == "18-30") slice->setColor(QColor(255, 165, 0));
        else if (label == "31-50") slice->setColor(Qt::red);
        else if (label == ">50")   slice->setColor(QColor(150,150,150));

        slice->setLabelVisible(true);
        slice->setLabel(QString("%1 → %2")
                            .arg(label)
                            .arg(QString::number(slice->percentage() * 100, 'f', 1) + "%"));

        slice->setLabelFont(QFont("Arial", 9, QFont::Bold));
        slice->setLabelColor(Qt::black);

        if (slice->percentage() < 0.05) {
            slice->setLabelFont(QFont("Arial", 8, QFont::Bold));
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par âge");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // NETTOYER CHARTVIEW
    if (chartView) {
        delete chartView;
        chartView = nullptr;
    }

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QLayout *old = ui->chartWidget->layout();
    if (old) delete old;

    QVBoxLayout *layout = new QVBoxLayout(ui->chartWidget);
    layout->addWidget(chartView);
    ui->chartWidget->setLayout(layout);
}

void MainWindow::on_statC_clicked()
{
    statistique();
}
