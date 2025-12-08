#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appareil.h"

// --- Bibliothèques Qt Standards ---
#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>

// --- Bibliothèques pour l'impression PDF ---
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

// --- Bibliothèques pour l'affichage (Layouts) ---
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QLayout>

// --- Bibliothèques pour les Graphiques (Charts) ---
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>

// ====================================================================
// CONSTRUCTEUR & DESTRUCTEUR
// ====================================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    alerte_active = false; // Initialisation
    // --- TENTATIVE DE CONNEXION ---
    int ret = A.connect_arduino(); // A est l'objet Arduino déclaré dans le .h
    switch(ret){
    case(0):
        qDebug() << "Arduino connecté avec succès !";
        // Important : Connecter le signal pour recevoir les données
        QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));
        break;
    case(1):
        qDebug() << "Erreur : Le port est peut-être occupé (fermez l'IDE Arduino).";
        break;
    case(-1):
        qDebug() << "Erreur : Arduino non trouvé (Vérifiez le câble ou le Vendor ID).";
        break;
    }
    ui->stackedWidget->setCurrentWidget(ui->menu);

    // 1. Date Entrée : Toujours aujourd'hui et lecture seule
    ui->dateEdit_Entree->setDate(QDate::currentDate());
    ui->dateEdit_Entree->setReadOnly(true);

    // 2. Date Estimée : Aujourd'hui par défaut
    ui->dateEdit_Estime->setDate(QDate::currentDate());

    // --- Configuration de la Table ---
    // On s'assure qu'il y a 11 colonnes (0 à 10)
    ui->tablewidget_Appareils->setColumnCount(11);

    // Ajout de "Temp Max" dans les headers
    QStringList headers = {"ID", "Type", "Marque", "Modèle", "Défaut",
                           "Date Entrée", "Statut", "Remarques", "Prix Estimé",
                           "Date Estimée", "Temp Max"};

    ui->tablewidget_Appareils->setHorizontalHeaderLabels(headers);

    // Connexion Recherche
    connect(ui->rech, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_ID_textChanged);

    ui->tablewidget_Appareils->setSortingEnabled(true);

    // Chargement initial
    chargerTable();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// ====================================================================
// ## 🔍 Lecture et Filtrage (AFFICHAGE)
// ====================================================================

void MainWindow::chargerTable(const QString &filter)
{
    ui->tablewidget_Appareils->setSortingEnabled(false);
    ui->tablewidget_Appareils->setRowCount(0);

    QSqlQuery query;
    // --- MISE À JOUR SQL : Ajout de TEMP_MAX ---
    QString sql = "SELECT ID_APP, TYPE, MARQUE, MODELE, DEFAULTDECLARE, DATEENTREE, STATUT, REMARQUES, PRIXESTIME, DATEESTIME, TEMP_MAX FROM APPAREILS";

    if (!filter.isEmpty()) {
        sql += " WHERE " + filter;
    }

    if (!query.exec(sql))
    {
        QMessageBox::critical(this, "Erreur BDD", "Impossible de charger les données: " + query.lastError().text());
        return;
    }

    int row = 0;
    while(query.next())
    {
        ui->tablewidget_Appareils->insertRow(row);

        // --- Récupération des données ---
        QString id = query.value(0).toString();
        QString type = query.value(1).toString();
        QString marque = query.value(2).toString();
        QString modele = query.value(3).toString();
        QString defaut = query.value(4).toString();

        QDate dateEntree = query.value(5).toDateTime().date();
        if (!dateEntree.isValid()) dateEntree = query.value(5).toDate();

        QString statut = query.value(6).toString();
        QString remarques = query.value(7).toString();
        double prix = query.value(8).toDouble();

        QDate dateEstime = query.value(9).toDateTime().date();
        if (!dateEstime.isValid()) dateEstime = query.value(9).toDate();

        // --- NOUVEAU : Récupération Temp Max (Index 10) ---
        double tempMax = query.value(10).toDouble();

        // --- Remplissage du Tableau ---
        ui->tablewidget_Appareils->setItem(row, 0, new QTableWidgetItem(id));
        ui->tablewidget_Appareils->setItem(row, 1, new QTableWidgetItem(type));
        ui->tablewidget_Appareils->setItem(row, 2, new QTableWidgetItem(marque));
        ui->tablewidget_Appareils->setItem(row, 3, new QTableWidgetItem(modele));
        ui->tablewidget_Appareils->setItem(row, 4, new QTableWidgetItem(defaut));
        ui->tablewidget_Appareils->setItem(row, 6, new QTableWidgetItem(statut));
        ui->tablewidget_Appareils->setItem(row, 7, new QTableWidgetItem(remarques));

        // Date Entrée
        QString dateEStr = dateEntree.isValid() ? dateEntree.toString("dd/MM/yyyy") : "";
        QTableWidgetItem *itemDateE = new QTableWidgetItem(dateEStr);
        itemDateE->setData(Qt::UserRole, dateEntree);
        ui->tablewidget_Appareils->setItem(row, 5, itemDateE);

        // Prix
        QTableWidgetItem *itemPrix = new QTableWidgetItem(QString::number(prix, 'f', 2));
        itemPrix->setData(Qt::UserRole, prix);
        ui->tablewidget_Appareils->setItem(row, 8, itemPrix);

        // Date Estimée
        QString dateEstStr = dateEstime.isValid() ? dateEstime.toString("dd/MM/yyyy") : "";
        QTableWidgetItem *itemDateEst = new QTableWidgetItem(dateEstStr);
        itemDateEst->setData(Qt::UserRole, dateEstime);
        ui->tablewidget_Appareils->setItem(row, 9, itemDateEst);

        // --- NOUVEAU : Colonne Temp Max (Index 10) ---
        QTableWidgetItem *itemTemp = new QTableWidgetItem(QString::number(tempMax));
        itemTemp->setData(Qt::UserRole, tempMax); // Pour trier numériquement
        ui->tablewidget_Appareils->setItem(row, 10, itemTemp);

        row++;
    }

    query.finish();
    ui->tablewidget_Appareils->setSortingEnabled(true);
};

// ====================================================================
// ## ➕ Ajout (CRUD - Create)
// ====================================================================

void MainWindow::on_pushButton_Ajouter_clicked()
{
    QString id = ui->lineEdit_ID->text().trimmed();
    QString type = ui->lineEdit_Type->text();
    QString marque = ui->lineEdit_Marque->text();
    QString modele = ui->lineEdit_Modele->text();
    QString defaut = ui->lineEdit_Defaut->text();
    QDate dateEntree = ui->dateEdit_Entree->date();
    QString statut = ui->comboBox_Statut->currentText();
    QString remarques = ui->lineEdit_Remarques->text();
    QString prixTexte = ui->lineEdit_Prix->text();
    QDate dateEstime = ui->dateEdit_Estime->date();

    // --- NOUVEAU : Récupération Temp Max ---
    // Assurez-vous d'avoir ajouté lineEdit_TempMax dans votre fichier .ui
    float tempMax = ui->lineEdit_TempMax->text().toFloat();

    if (id.isEmpty()) { QMessageBox::warning(this, "Erreur", "L'ID est obligatoire."); return; }
    if (type.isEmpty() || marque.isEmpty()) { QMessageBox::warning(this, "Erreur", "Type et Marque obligatoires."); return; }

    bool prixValide;
    float prix = prixTexte.toFloat(&prixValide);
    if (!prixValide) prix = 0.0;

    // --- MISE À JOUR CONSTRUCTEUR ---
    // Vous devez ajouter tempMax à votre constructeur Appareil
    Appareil A_new(id, type, marque, modele, defaut, dateEntree, statut, remarques, prix, dateEstime, tempMax);

    if(A_new.ajouter()) {
        QMessageBox::information(this, "Succès", "Appareil ajouté.");
        chargerTable();
    } else {
        QMessageBox::critical(this, "Échec", "L'ajout a échoué. Vérifiez si l'ID existe déjà.");
    }
}

// ====================================================================
// ## ✏️ Modification (CRUD - Update)
// ====================================================================

void MainWindow::on_pushButton_Modifier_clicked()
{
    QString id = ui->lineEdit_ID->text().trimmed();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un appareil (ID vide).");
        return;
    }

    QString type = ui->lineEdit_Type->text();
    QString marque = ui->lineEdit_Marque->text();
    QString modele = ui->lineEdit_Modele->text();
    QString defaut = ui->lineEdit_Defaut->text();
    QDate dateEntree = ui->dateEdit_Entree->date();
    QString statut = ui->comboBox_Statut->currentText();
    QString remarques = ui->lineEdit_Remarques->text();
    float prix = ui->lineEdit_Prix->text().toFloat();
    QDate dateEstime = ui->dateEdit_Estime->date();

    // --- NOUVEAU : Récupération Temp Max ---
    float tempMax = ui->lineEdit_TempMax->text().toFloat();

    // --- MISE À JOUR CONSTRUCTEUR ---
    Appareil A_mod(id, type, marque, modele, defaut, dateEntree, statut, remarques, prix, dateEstime, tempMax);

    if(A_mod.modifier()) {
        QMessageBox::information(this, "Succès", "Appareil modifié avec succès.");
        chargerTable();
    } else {
        QMessageBox::critical(this, "Échec", "La modification a échoué.\nL'ID existe-t-il vraiment ?");
    }
}

// ====================================================================
// ## 🗑️ Suppression (CRUD - Delete)
// ====================================================================

void MainWindow::on_pushButton_Supprimer_clicked()
{
    QString id = ui->lineEdit_ID->text().trimmed();

    if(id.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner une ligne ou entrer un ID.");
        return;
    }

    QMessageBox::StandardButton reponse;
    reponse = QMessageBox::question(this, "Confirmation", "Supprimer l'appareil ID: " + id + " ?",
                                    QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes) {
        Appareil A_temp;
        if(A_temp.supprimer(id)) {
            QMessageBox::information(this, "Succès", "Appareil supprimé.");
            chargerTable();
            ui->lineEdit_ID->clear();
        } else {
            QMessageBox::critical(this, "Échec", "Suppression impossible.\nVérifiez que l'ID existe.");
        }
    }
}

// ====================================================================
// ## 🖱️ Interaction Tableau
// ====================================================================

void MainWindow::on_tablewidget_Appareils_cellClicked(int row, int column)
{
    (void)column;

    QTableWidgetItem* itemID = ui->tablewidget_Appareils->item(row, 0);
    if (!itemID) return;

    ui->lineEdit_ID->setText(itemID->text());

    QTableWidgetItem* itemType = ui->tablewidget_Appareils->item(row, 1);
    ui->lineEdit_Type->setText(itemType ? itemType->text() : "");

    QTableWidgetItem* itemMarque = ui->tablewidget_Appareils->item(row, 2);
    ui->lineEdit_Marque->setText(itemMarque ? itemMarque->text() : "");

    QTableWidgetItem* itemModele = ui->tablewidget_Appareils->item(row, 3);
    ui->lineEdit_Modele->setText(itemModele ? itemModele->text() : "");

    QTableWidgetItem* itemDefaut = ui->tablewidget_Appareils->item(row, 4);
    ui->lineEdit_Defaut->setText(itemDefaut ? itemDefaut->text() : "");

    // Date Entrée
    QTableWidgetItem* itemDateEntree = ui->tablewidget_Appareils->item(row, 5);
    if (itemDateEntree) {
        QDate d = itemDateEntree->data(Qt::UserRole).toDate();
        if (!d.isValid()) d = QDate::fromString(itemDateEntree->text(), "dd/MM/yyyy");
        ui->dateEdit_Entree->setDate(d);
    }

    QTableWidgetItem* itemStatut = ui->tablewidget_Appareils->item(row, 6);
    ui->comboBox_Statut->setCurrentText(itemStatut ? itemStatut->text() : "");

    QTableWidgetItem* itemRemarques = ui->tablewidget_Appareils->item(row, 7);
    ui->lineEdit_Remarques->setText(itemRemarques ? itemRemarques->text() : "");

    QTableWidgetItem* itemPrix = ui->tablewidget_Appareils->item(row, 8);
    ui->lineEdit_Prix->setText(itemPrix ? itemPrix->text() : "");

    // Date Estimée
    QTableWidgetItem* itemDateEstime = ui->tablewidget_Appareils->item(row, 9);
    if (itemDateEstime) {
        QDate d = itemDateEstime->data(Qt::UserRole).toDate();
        if (!d.isValid()) d = QDate::fromString(itemDateEstime->text(), "dd/MM/yyyy");
        ui->dateEdit_Estime->setDate(d);
    }

    // --- NOUVEAU : Remplissage Temp Max (Colonne 10) ---
    QTableWidgetItem* itemTemp = ui->tablewidget_Appareils->item(row, 10);
    ui->lineEdit_TempMax->setText(itemTemp ? itemTemp->text() : "");
}

// ====================================================================
// ## 🔎 Recherche
// ====================================================================

void MainWindow::on_lineEdit_ID_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        chargerTable();
    } else {
        QString filter = QString("ID_APP LIKE '%%1%' OR MARQUE LIKE '%%1%'").arg(text);
        chargerTable(filter);
    }
}

// ====================================================================
// ## 📊 Statistiques (GRAPHIQUES)
// ====================================================================

void MainWindow::on_ShowStats_clicked()
{
    // 1. --- RÉCUPÉRATION DES DONNÉES (SQL) ---
    QSqlQuery queryTotal;
    queryTotal.prepare("SELECT COUNT(*) FROM APPAREILS");
    int total = 0;
    if(queryTotal.exec() && queryTotal.next()) {
        total = queryTotal.value(0).toInt();
    }
    queryTotal.finish();

    if (total == 0) {
        QMessageBox::information(this, "Info", "Aucune donnée à afficher.");
        return;
    }

    QSqlQuery queryCours;
    queryCours.prepare("SELECT COUNT(*) FROM APPAREILS WHERE STATUT LIKE 'En %' OR STATUT = 'en_cours'");
    int encours = 0;
    if(queryCours.exec() && queryCours.next()) {
        encours = queryCours.value(0).toInt();
    }
    queryCours.finish();

    QSqlQuery queryRepare;
    queryRepare.prepare("SELECT COUNT(*) FROM APPAREILS WHERE STATUT LIKE 'R%par%' OR STATUT = 'reparé'");
    int repare = 0;
    if(queryRepare.exec() && queryRepare.next()) {
        repare = queryRepare.value(0).toInt();
    }
    queryRepare.finish();

    int enAttente = total - encours - repare;

    // 2. --- CRÉATION DU GRAPHIQUE ---
    QPieSeries *series = new QPieSeries();
    series->append("En cours", encours);
    series->append("Réparés", repare);
    if (enAttente > 0) series->append("En attente", enAttente);

    // Etiquettes et couleurs
    QPieSlice *sliceCours = series->slices().at(0);
    double pcCours = (static_cast<double>(encours) / total) * 100.0;
    sliceCours->setLabel(QString("En cours : %1%").arg(QString::number(pcCours, 'f', 1)));
    sliceCours->setLabelVisible(true);
    sliceCours->setBrush(QColor(255, 165, 0));

    QPieSlice *sliceRepare = series->slices().at(1);
    double pcRepare = (static_cast<double>(repare) / total) * 100.0;
    sliceRepare->setLabel(QString("Réparés : %1%").arg(QString::number(pcRepare, 'f', 1)));
    sliceRepare->setLabelVisible(true);
    sliceRepare->setBrush(QColor(0, 255, 0));
    sliceRepare->setExploded(true);

    if (enAttente > 0) {
        QPieSlice *sliceAttente = series->slices().at(2);
        double pcAttente = (static_cast<double>(enAttente) / total) * 100.0;
        sliceAttente->setLabel(QString("En attente : %1%").arg(QString::number(pcAttente, 'f', 1)));
        sliceAttente->setLabelVisible(true);
        sliceAttente->setBrush(Qt::gray);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("État des Appareils (Total: " + QString::number(total) + ")");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (!ui->widget_stats) {
        QMessageBox::critical(this, "Erreur UI", "Le widget 'widget_stats' est introuvable !");
        return;
    }

    if (ui->widget_stats->layout() != nullptr) {
        QLayoutItem* item;
        while ((item = ui->widget_stats->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->widget_stats->layout();
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->widget_stats);
    layout->addWidget(chartView);
    ui->widget_stats->setLayout(layout);
}

// ====================================================================
// ## 📄 Export PDF
// ====================================================================

void MainWindow::on_ExporterPDF_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty()) return;

    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(fileName);

    QString html = "<h1 align='center'>Rapport Atelier</h1><br>";
    html += "<table border='1' cellspacing='0' cellpadding='5' width='100%'>";

    // En-têtes
    html += "<thead><tr bgcolor='#f0f0f0'>";
    for (int i = 0; i < ui->tablewidget_Appareils->columnCount(); ++i) {
        // Ignorer remarques (7)
        if (i == 7) continue;
        html += "<th>" + ui->tablewidget_Appareils->horizontalHeaderItem(i)->text() + "</th>";
    }
    html += "</tr></thead><tbody>";

    // Données
    for (int row = 0; row < ui->tablewidget_Appareils->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < ui->tablewidget_Appareils->columnCount(); ++col) {
            if (col == 7) continue;
            QTableWidgetItem *item = ui->tablewidget_Appareils->item(row, col);
            html += "<td>" + (item ? item->text() : "") + "</td>";
        }
        html += "</tr>";
    }
    html += "</tbody></table>";
    html += "<p align='right'>Généré le : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>";

    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);

    QMessageBox::information(this, "Export PDF", "Le fichier PDF a été enregistré avec succès !");
}

// ====================================================================
// ## 🔃 Tri Rapide
// ====================================================================

void MainWindow::on_pushButton_4_clicked()
{
    Qt::SortOrder order = ui->tablewidget_Appareils->horizontalHeader()->sortIndicatorOrder();
    ui->tablewidget_Appareils->sortItems(0, (order == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder);
}

void MainWindow::on_appareils_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->appareil);
}

void MainWindow::on_EXIT_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->menu);
}
void MainWindow::update_label()
{
    // 1. Lire les données brutes de l'Arduino
    data = A.read_from_arduino();

    // Convertir en texte et nettoyer les espaces
    QString dataStr = QString::fromStdString(data.toStdString()).trimmed();

    // Si vide, on sort
    if(dataStr.isEmpty()) return;

    // Debug : Voir ce que l'Arduino envoie dans la console Qt Creator
    qDebug() << "Reçu Arduino:" << dataStr;

    // 2. Convertir en nombre (float)
    bool isNumeric;
    float tempActuelle = dataStr.toFloat(&isNumeric);

    // Si ce n'est pas un nombre (ex: bruit, erreur), on arrête là
    if(!isNumeric) return;

    // (Optionnel) Afficher la température reçue dans le champ TempMax pour voir si ça marche
    // ui->lineEdit_TempMax->setText(dataStr);

    // 3. Récupérer l'ID de l'appareil affiché à l'écran
    QString id_app = ui->lineEdit_ID->text();

    // Si aucun ID n'est écrit, on ne peut pas vérifier la base de données
    if(id_app.isEmpty()) return;

    // 4. Vérifier la limite dans la Base de Données
    QSqlQuery query;
    query.prepare("SELECT TEMP_MAX FROM APPAREILS WHERE ID_APP = :id");
    query.bindValue(":id", id_app);

    if(query.exec() && query.next()) {
        float tempMaxBDD = query.value(0).toFloat();

        // 5. COMPARER : Si la température dépasse ET qu'on n'est pas déjà en alerte
        if(tempActuelle > tempMaxBDD) {

            if(alerte_active == false) {
                // On active le verrou pour ne pas ouvrir 50 fenêtres
                alerte_active = true;

                // On joue un son (Bip système)
                QApplication::beep();

                // On affiche l'alerte bloquante
                QMessageBox::critical(this, "SURCHAUFFE DÉTECTÉE !",
                                      "Attention ! L'appareil " + id_app +
                                          "\nTempérature actuelle : " + QString::number(tempActuelle) + "°C" +
                                          "\nLimite autorisée : " + QString::number(tempMaxBDD) + "°C");

                // Quand l'utilisateur clique sur OK, on déverrouille pour la prochaine fois
                alerte_active = false;
            }
        }
    }
}
