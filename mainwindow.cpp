#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts>
#include <QSqlDatabase>
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
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

extern QSqlDatabase db;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialisation Arduino
    arduino = new Arduino(this);
    
    // Tentative de connexion automatique à Arduino
    QStringList ports = arduino->getAvailablePorts();
    if (!ports.isEmpty()) {
        // Essayer de se connecter au premier port disponible
        if (arduino->connectArduino(ports.first())) {
            qDebug() << "Arduino connecté sur" << ports.first();
        } else {
            qDebug() << "Échec de connexion à Arduino";
        }
    } else {
        qDebug() << "Aucun port série disponible pour Arduino";
    }

    // Timer pour vérifier les RDV toutes les minutes
    timerRDV = new QTimer(this);
    connect(timerRDV, &QTimer::timeout, this, &MainWindow::verifierRDVEnCours);
    timerRDV->start(60000);  // Vérifie toutes les 60 secondes

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
    
    // Connexion du bouton Alerter (si le bouton existe dans l'interface)
    QPushButton *btnAlerter = findChild<QPushButton*>("btnAlerterRDV");
    if (btnAlerter) {
        connect(btnAlerter, &QPushButton::clicked, this, &MainWindow::on_btnAlerterRDV_clicked);
    }
    
    // Connexion du bouton Voir Tous RDV (si le bouton existe dans l'interface)
    QPushButton *btnVoirTousRDV = findChild<QPushButton*>("btnVoirTousRDV");
    if (btnVoirTousRDV) {
        connect(btnVoirTousRDV, &QPushButton::clicked, this, &MainWindow::on_btnVoirTousRDV_clicked);
        qDebug() << "Bouton btnVoirTousRDV trouvé et connecté";
    } else {
        qDebug() << "ATTENTION: Bouton btnVoirTousRDV non trouvé dans l'interface";
    }
    
    // Connexion du bouton Retour Tous RDV (si le bouton existe dans l'interface)
    QPushButton *btnRetourTousRDV = findChild<QPushButton*>("btnRetourTousRDV");
    if (btnRetourTousRDV) {
        connect(btnRetourTousRDV, &QPushButton::clicked, this, &MainWindow::on_btnRetourTousRDV_clicked);
    }
    
    connect(ui->tableViewClients,    &QTableView::clicked, this, &MainWindow::on_tableViewClients_clicked);
}

MainWindow::~MainWindow() 
{ 
    if (timerRDV) {
        timerRDV->stop();
    }
    delete ui; 
}

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

    if (ui->Ajouter->text() == "Enregistrer les modifications") {
        success = cl.modifier();
        action = "modifié";
        ui->Ajouter->setText("Ajouter");
        ui->id->setEnabled(true);
    } else {
        success = cl.ajouter();
        action = "ajouté";
    }

    if (success) {
        QMessageBox::information(this, "Succès", QString("Client %1 avec succès !").arg(action));
        ui->tableViewClients->setModel(C.afficher());
        // Réinitialiser les champs après succès
        ui->id->clear();
        ui->nom->clear();
        ui->prenom->clear();
        ui->telephone->clear();
        ui->dn->setDate(QDate::currentDate());
        ui->di->setDate(QDate::currentDate());
    } else {
        QString errorMsg = cl.getLastError();
        if (errorMsg.contains("unique", Qt::CaseInsensitive) || 
            errorMsg.contains("duplicate", Qt::CaseInsensitive) ||
            errorMsg.contains("ORA-00001", Qt::CaseInsensitive)) {
            QMessageBox::critical(this, "Erreur", 
                QString("L'ID %1 existe déjà dans la base de données !").arg(id));
        } else {
            QMessageBox::critical(this, "Erreur", 
                QString("Échec de l'opération :\n%1").arg(errorMsg.isEmpty() ? "Erreur inconnue" : errorMsg));
        }
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

// ====================== RÉCUPÉRER LES DONNÉES DEPUIS LE TABLEAU ======================
void MainWindow::on_tableViewClients_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    QAbstractItemModel *model = ui->tableViewClients->model();
    int row = index.row();

    // Récupérer les données de la ligne sélectionnée
    // Colonnes: ID(0), NOM(1), PRENOM(2), TELEPHONE(3), DATE_DE_NAISSANCE(4), DATE_INSCRIPTION(5)
    int id = model->data(model->index(row, 0)).toInt();
    QString nom = model->data(model->index(row, 1)).toString();
    QString prenom = model->data(model->index(row, 2)).toString();
    QString telephone = model->data(model->index(row, 3)).toString();
    QString dateNaissance = model->data(model->index(row, 4)).toString();
    QString dateInscription = model->data(model->index(row, 5)).toString();

    // Remplir les champs du formulaire
    ui->id->setText(QString::number(id));
    ui->nom->setText(nom);
    ui->prenom->setText(prenom);
    ui->telephone->setText(telephone);

    // Convertir et remplir les dates
    QDate dn = QDate::fromString(dateNaissance, "dd/MM/yyyy");
    QDate di = QDate::fromString(dateInscription, "dd/MM/yyyy");

    if (dn.isValid()) ui->dn->setDate(dn);
    if (di.isValid()) ui->di->setDate(di);

    // Activer le mode modification
    ui->Ajouter->setText("Enregistrer les modifications");
    ui->id->setEnabled(false);
}

// ====================== MODIFIER ======================
void MainWindow::on_Modifier_clicked()
{
    // Vérifier qu'une ligne est sélectionnée dans le tableau
    QItemSelectionModel *selection = ui->tableViewClients->selectionModel();
    if (!selection->hasSelection()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client dans le tableau !");
        return;
    }

    // Récupérer les données de la ligne sélectionnée
    QModelIndex index = selection->currentIndex();
    on_tableViewClients_clicked(index);

    QMessageBox::information(this, "Client chargé",
                             QString("Client <b>%1 %2</b> chargé. Modifiez les champs puis cliquez sur <u>Enregistrer les modifications</u> pour sauvegarder.")
                                 .arg(ui->prenom->text(), ui->nom->text()));
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
    painter.scale(4.8, 4.8);
    painter.translate(80, 180);

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

// ====================== ALERTER RDV ======================
void MainWindow::on_btnAlerterRDV_clicked()
{
    // Vérifier qu'Arduino est connecté
    if (!arduino->isConnected()) {
        QMessageBox::warning(this, "Erreur", 
            "Arduino non connecté !\nVeuillez vérifier la connexion série.");
        return;
    }

    // Vérifier qu'une date est sélectionnée
    QDate date = ui->calendarWidget->selectedDate();
    if (!date.isValid()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une date dans le calendrier !");
        return;
    }

    // Vérifier qu'un RDV est sélectionné dans le tableau
    auto sel = ui->tableViewRDV->selectionModel();
    if (!sel->hasSelection()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un RDV dans la liste !");
        return;
    }

    // Récupérer l'heure du RDV sélectionné
    int row = sel->currentIndex().row();
    QString heure = ui->tableViewRDV->model()->data(ui->tableViewRDV->model()->index(row, 0)).toString();
    
    // Récupérer l'ID du client depuis la base de données
    QSqlQuery q(db);
    q.prepare("SELECT ID FROM GS_RDV WHERE DATE_RDV = :d AND HEURE = :h");
    q.bindValue(":d", date.toString("dd/MM/yyyy"));
    q.bindValue(":h", heure);
    
    if (!q.exec() || !q.next()) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer l'ID du client !");
        return;
    }
    
    int idClient = q.value(0).toInt();
    
    // Envoyer l'alerte à Arduino
    if (envoyerAlerteArduino(idClient)) {
        QMessageBox::information(this, "Succès", 
            QString("Alerte envoyée à l'afficheur pour le client ID %1 !").arg(idClient));
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi de l'alerte à Arduino !");
    }
}

// ====================== ENVOYER ALERTE À ARDUINO ======================
bool MainWindow::envoyerAlerteArduino(int idClient)
{
    if (!arduino->isConnected()) {
        qDebug() << "Arduino non connecté";
        return false;
    }
    
    QString message = QString("RDV:%1").arg(idClient);
    bool success = arduino->sendData(message);
    
    if (success) {
        qDebug() << "Alerte envoyée à Arduino pour client ID:" << idClient;
        // Ajouter à la liste des derniers RDV pour éviter les doublons dans la vérification automatique
        if (!derniersRDV.contains(idClient)) {
            derniersRDV.append(idClient);
        }
    }
    
    return success;
}

void MainWindow::on_historique_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                         "Historique des Rendez-vous",
                                         "<b>Entrez l'ID du client :</b>",
                                         QLineEdit::Normal,
                                         "",
                                         &ok);

    if (!ok || text.trimmed().isEmpty()) {
        return;
    }

    bool conversionOk;
    int id_client = text.toInt(&conversionOk);

    if (!conversionOk || id_client <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide (nombre entier positif) !");
        return;
    }

    QSqlQueryModel* model = C.historiqueRDV(id_client);
    ui->tableViewClients->setModel(model);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Historique RDV",
                                 QString("Aucun rendez-vous trouvé pour le client <b>ID %1</b>").arg(id_client));
        ui->tableViewClients->setModel(C.afficher());
    } else {
        QMessageBox::information(this, "Historique RDV",
                                 QString("<font color=green><b>%1</b></font> rendez-vous trouvé(s) pour le client <b>ID %2</b>")
                                     .arg(model->rowCount()).arg(id_client));
    }

    setWindowTitle(QString("Historique RDV - Client %1 (%2 RDV)")
                       .arg(id_client).arg(model->rowCount()));
}

// ====================== VOIR TOUS LES RDV ======================
void MainWindow::on_btnVoirTousRDV_clicked()
{
    qDebug() << "Bouton Voir Tous RDV cliqué";
    
    // Créer ou récupérer le QTableWidget pour afficher tous les RDV
    QTableWidget *tableTousRDV = findChild<QTableWidget*>("tableWidgetTousRDV");
    
    if (!tableTousRDV) {
        qDebug() << "TableWidget tableWidgetTousRDV non trouvé, recherche dans toutes les pages...";
        
        // Chercher dans toutes les pages du stackedWidget
        for (int i = 0; i < ui->stackedWidgetC->count(); ++i) {
            QWidget *page = ui->stackedWidgetC->widget(i);
            tableTousRDV = page->findChild<QTableWidget*>("tableWidgetTousRDV");
            if (tableTousRDV) {
                qDebug() << "TableWidget trouvé dans la page" << i;
                break;
            }
        }
    }
    
    if (!tableTousRDV) {
        // Si le widget n'existe pas, créer une nouvelle page dans le stackedWidget
        // Pour l'instant, on utilise la page RDV existante et on change l'affichage
        // Il faudra ajouter une nouvelle page dans Qt Designer avec un QTableWidget nommé "tableWidgetTousRDV"
        QMessageBox::warning(this, "Configuration requise", 
            "Veuillez ajouter une nouvelle page dans Qt Designer avec un QTableWidget nommé 'tableWidgetTousRDV'\n\n"
            "Étapes:\n"
            "1. Ajouter une nouvelle page au stackedWidgetC\n"
            "2. Ajouter un QTableWidget sur cette page\n"
            "3. Nommer le QTableWidget: tableWidgetTousRDV\n"
            "4. Ajouter un bouton 'Retour' nommé: btnRetourTousRDV");
        return;
    }
    
    // Aller à la page qui contient le tableau (chercher quelle page contient le widget)
    int pageIndex = -1;
    for (int i = 0; i < ui->stackedWidgetC->count(); ++i) {
        QWidget *page = ui->stackedWidgetC->widget(i);
        if (page->findChild<QTableWidget*>("tableWidgetTousRDV")) {
            pageIndex = i;
            qDebug() << "TableWidget trouvé dans la page" << i;
            break;
        }
    }
    
    if (pageIndex == -1) {
        QMessageBox::critical(this, "Erreur", "Page avec le tableau non trouvée !");
        return;
    }
    
    ui->stackedWidgetC->setCurrentIndex(pageIndex);
    qDebug() << "Passage à la page" << pageIndex;
    
    // Récupérer tous les RDV
    QSqlQueryModel *model = C.afficherTousLesRDV();
    
    // Configurer le tableau
    tableTousRDV->setRowCount(model->rowCount());
    tableTousRDV->setColumnCount(5); // ID, Date, Heure, Client, Alerter
    
    // En-têtes
    QStringList headers;
    headers << "ID Client" << "Date RDV" << "Heure" << "Client" << "Alerter";
    tableTousRDV->setHorizontalHeaderLabels(headers);
    
    // Remplir le tableau
    for (int row = 0; row < model->rowCount(); ++row) {
        // ID Client
        int idClient = model->data(model->index(row, 0)).toInt();
        tableTousRDV->setItem(row, 0, new QTableWidgetItem(QString::number(idClient)));
        
        // Date RDV
        QString dateRDV = model->data(model->index(row, 1)).toString();
        tableTousRDV->setItem(row, 1, new QTableWidgetItem(dateRDV));
        
        // Heure
        QString heure = model->data(model->index(row, 2)).toString();
        tableTousRDV->setItem(row, 2, new QTableWidgetItem(heure));
        
        // Client
        QString client = model->data(model->index(row, 3)).toString();
        tableTousRDV->setItem(row, 3, new QTableWidgetItem(client));
        
        // Bouton Alerter
        QPushButton *btnAlerter = new QPushButton("Alerter");
        btnAlerter->setProperty("row", row);
        btnAlerter->setProperty("idClient", idClient);
        connect(btnAlerter, &QPushButton::clicked, [this, row, idClient]() {
            this->alerterRDVDepuisTable(row);
        });
        tableTousRDV->setCellWidget(row, 4, btnAlerter);
    }
    
    // Ajuster la largeur des colonnes
    tableTousRDV->resizeColumnsToContents();
    tableTousRDV->horizontalHeader()->setStretchLastSection(true);
    
    qDebug() << QString("Affichage de %1 rendez-vous dans le tableau").arg(model->rowCount());
    
    delete model;
}

void MainWindow::on_btnRetourTousRDV_clicked()
{
    // Retourner à la page principale
    ui->stackedWidgetC->setCurrentIndex(0);
}

void MainWindow::alerterRDVDepuisTable(int row)
{
    // L'ID du client est stocké dans la propriété du bouton
    QTableWidget *tableTousRDV = findChild<QTableWidget*>("tableWidgetTousRDV");
    if (!tableTousRDV) return;
    
    QPushButton *btn = qobject_cast<QPushButton*>(tableTousRDV->cellWidget(row, 4));
    if (!btn) return;
    
    int idClient = btn->property("idClient").toInt();
    
    if (envoyerAlerteArduino(idClient)) {
        QMessageBox::information(this, "Succès", 
            QString("Alerte envoyée à l'afficheur pour le client ID %1 !").arg(idClient));
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi de l'alerte à Arduino !");
    }
}

// ====================== STATISTIQUES (MAIN FUNCTION) ======================
void MainWindow::statistiqueC()
{
    QPieSeries *series = new QPieSeries();

    // Use the new function that doesn't use complex SELECT
    QSqlQueryModel* statsModel = C.statsParAge();

    // Get data from the model
    for (int i = 0; i < statsModel->rowCount(); ++i) {
        QString tranche = statsModel->data(statsModel->index(i, 0)).toString();
        int nb = statsModel->data(statsModel->index(i, 1)).toInt();

        if (nb > 0) {
            series->append(tranche, nb);
        }
    }

    // Clean up the model
    delete statsModel;

    // If no data, show message
    if (series->count() == 0) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée disponible pour les statistiques.");
        delete series;
        return;
    }

    // Configure pie slices
    for (QPieSlice *slice : series->slices()) {
        QString label = slice->label();

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

    // Clean up previous chart
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
    statistiqueC();
}

// ====================== VÉRIFIER LES RDV EN COURS ======================
void MainWindow::verifierRDVEnCours()
{
    QList<int> rdvEnCours = C.getRDVEnCours();
    
    // Vérifier les nouveaux RDV (ceux qui ne sont pas dans la liste précédente)
    foreach(int idClient, rdvEnCours) {
        if (!derniersRDV.contains(idClient)) {
            // Nouveau RDV détecté, envoyer à Arduino via la fonction dédiée
            envoyerAlerteArduino(idClient);
        }
    }
    
    // Mettre à jour la liste des derniers RDV
    derniersRDV = rdvEnCours;
}
