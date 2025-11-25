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
#include <QFileDialog> // Pour "Enregistrer sous"
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
// Note : Si elles sont déjà dans mainwindow.h, ces includes sont optionnels ici,
// mais on les garde pour être sûr que tout compile.
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

    // --- Configuration de la Table ---
    ui->tablewidget_Appareils->setColumnCount(10);
    QStringList headers = {"ID", "Type", "Marque", "Modèle", "Défaut",
                           "Date Entrée", "Statut", "Remarques", "Prix Estimé",
                           "Date Estimée"};
    ui->tablewidget_Appareils->setHorizontalHeaderLabels(headers);

    // --- Connexion du champ de recherche 'rech' ---
    connect(ui->rech, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_ID_textChanged);

    // Activer le tri sur le QTableWidget
    ui->tablewidget_Appareils->setSortingEnabled(true);

    // Chargement initial des données
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
    // On désactive le tri pendant le chargement
    ui->tablewidget_Appareils->setSortingEnabled(false);
    ui->tablewidget_Appareils->setRowCount(0);

    QSqlQuery query;
    QString sql = "SELECT ID_APP, TYPE, MARQUE, MODELE, DEFAULTDECLARE, DATEENTREE, STATUT, REMARQUES, PRIXESTIME, DATEESTIME FROM APPAREILS";

    if (!filter.isEmpty()) {
        sql += " WHERE " + filter;
    }

    // Exécution de la requête
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

        // --- CORRECTION DATE 1 (Date Entrée) ---
        // On récupère en DateTime, puis on prend la Date.
        QDate dateEntree = query.value(5).toDateTime().date();
        // Sécurité : si la conversion échoue, on tente la conversion simple
        if (!dateEntree.isValid()) dateEntree = query.value(5).toDate();

        QString statut = query.value(6).toString();
        QString remarques = query.value(7).toString();
        double prix = query.value(8).toDouble();

        // --- CORRECTION DATE 2 (Date Estimée) ---
        QDate dateEstime = query.value(9).toDateTime().date();
        if (!dateEstime.isValid()) dateEstime = query.value(9).toDate();


        // --- Remplissage du Tableau ---

        // Colonnes Textes
        ui->tablewidget_Appareils->setItem(row, 0, new QTableWidgetItem(id));
        ui->tablewidget_Appareils->setItem(row, 1, new QTableWidgetItem(type));
        ui->tablewidget_Appareils->setItem(row, 2, new QTableWidgetItem(marque));
        ui->tablewidget_Appareils->setItem(row, 3, new QTableWidgetItem(modele));
        ui->tablewidget_Appareils->setItem(row, 4, new QTableWidgetItem(defaut));
        ui->tablewidget_Appareils->setItem(row, 6, new QTableWidgetItem(statut));
        ui->tablewidget_Appareils->setItem(row, 7, new QTableWidgetItem(remarques));

        // Colonne Date Entrée (Affichage + UserRole pour le tri)
        // On vérifie si la date est valide pour ne pas afficher "01/01/2000" si c'est vide
        QString dateEStr = dateEntree.isValid() ? dateEntree.toString("dd/MM/yyyy") : "";
        QTableWidgetItem *itemDateE = new QTableWidgetItem(dateEStr);
        itemDateE->setData(Qt::UserRole, dateEntree); // Important pour le tri
        ui->tablewidget_Appareils->setItem(row, 5, itemDateE);

        // Colonne Prix
        QTableWidgetItem *itemPrix = new QTableWidgetItem(QString::number(prix, 'f', 2));
        itemPrix->setData(Qt::UserRole, prix);
        ui->tablewidget_Appareils->setItem(row, 8, itemPrix);

        // Colonne Date Estimée
        QString dateEstStr = dateEstime.isValid() ? dateEstime.toString("dd/MM/yyyy") : "";
        QTableWidgetItem *itemDateEst = new QTableWidgetItem(dateEstStr);
        itemDateEst->setData(Qt::UserRole, dateEstime);
        ui->tablewidget_Appareils->setItem(row, 9, itemDateEst);

        row++;
    }

    // IMPORTANT : Fermer la requête pour éviter les conflits ODBC "Sequence Error"
    query.finish();

    // Réactiver le tri
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

    if (id.isEmpty()) { QMessageBox::warning(this, "Erreur", "L'ID est obligatoire."); return; }
    if (type.isEmpty() || marque.isEmpty()) { QMessageBox::warning(this, "Erreur", "Type et Marque obligatoires."); return; }

    bool prixValide;
    float prix = prixTexte.toFloat(&prixValide);
    if (!prixValide) prix = 0.0;

    Appareil A_new(id, type, marque, modele, defaut, dateEntree, statut, remarques, prix, dateEstime);

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

    Appareil A_mod(id, type, marque, modele, defaut, dateEntree, statut, remarques, prix, dateEstime);

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
    (void)column; // Pour éviter le warning

    // Sécurité : Vérifier que l'ID (colonne 0) existe
    QTableWidgetItem* itemID = ui->tablewidget_Appareils->item(row, 0);
    if (!itemID) return;

    // --- Remplissage de l'ID ---
    ui->lineEdit_ID->setText(itemID->text());

    // --- Remplissage sécurisé des Textes ---
    // On utilise une petite astuce : (item ? item->text() : "")
    // Si l'item existe, on prend le texte, sinon on met du vide.

    QTableWidgetItem* itemType = ui->tablewidget_Appareils->item(row, 1);
    ui->lineEdit_Type->setText(itemType ? itemType->text() : "");

    QTableWidgetItem* itemMarque = ui->tablewidget_Appareils->item(row, 2);
    ui->lineEdit_Marque->setText(itemMarque ? itemMarque->text() : "");

    QTableWidgetItem* itemModele = ui->tablewidget_Appareils->item(row, 3);
    ui->lineEdit_Modele->setText(itemModele ? itemModele->text() : "");

    QTableWidgetItem* itemDefaut = ui->tablewidget_Appareils->item(row, 4);
    ui->lineEdit_Defaut->setText(itemDefaut ? itemDefaut->text() : "");

    // --- Remplissage sécurisé de la Date Entrée ---
    QTableWidgetItem* itemDateEntree = ui->tablewidget_Appareils->item(row, 5);
    if (itemDateEntree) {
        // On récupère la date stockée dans UserRole (plus fiable)
        QDate d = itemDateEntree->data(Qt::UserRole).toDate();
        // Si la date UserRole est invalide, on essaie de lire le texte
        if (!d.isValid()) d = QDate::fromString(itemDateEntree->text(), "dd/MM/yyyy");
        ui->dateEdit_Entree->setDate(d);
    }

    // --- Remplissage Statut, Remarques, Prix ---
    QTableWidgetItem* itemStatut = ui->tablewidget_Appareils->item(row, 6);
    ui->comboBox_Statut->setCurrentText(itemStatut ? itemStatut->text() : "");

    QTableWidgetItem* itemRemarques = ui->tablewidget_Appareils->item(row, 7);
    ui->lineEdit_Remarques->setText(itemRemarques ? itemRemarques->text() : "");

    QTableWidgetItem* itemPrix = ui->tablewidget_Appareils->item(row, 8);
    ui->lineEdit_Prix->setText(itemPrix ? itemPrix->text() : "");

    // --- Remplissage sécurisé de la Date Estimée ---
    QTableWidgetItem* itemDateEstime = ui->tablewidget_Appareils->item(row, 9);
    if (itemDateEstime) {
        QDate d = itemDateEstime->data(Qt::UserRole).toDate();
        if (!d.isValid()) d = QDate::fromString(itemDateEstime->text(), "dd/MM/yyyy");
        ui->dateEdit_Estime->setDate(d);
    }
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

    // Total
    QSqlQuery queryTotal;
    queryTotal.prepare("SELECT COUNT(*) FROM APPAREILS");
    int total = 0;
    if(queryTotal.exec() && queryTotal.next()) {
        total = queryTotal.value(0).toInt();
    }
    queryTotal.finish(); // Important pour ODBC

    if (total == 0) {
        QMessageBox::information(this, "Info", "Aucune donnée à afficher.");
        return;
    }

    // En cours
    QSqlQuery queryCours;
    queryCours.prepare("SELECT COUNT(*) FROM APPAREILS WHERE STATUT LIKE 'En %' OR STATUT = 'en_cours'");
    int encours = 0;
    if(queryCours.exec() && queryCours.next()) {
        encours = queryCours.value(0).toInt();
    }
    queryCours.finish();

    // Réparés
    QSqlQuery queryRepare;
    queryRepare.prepare("SELECT COUNT(*) FROM APPAREILS WHERE STATUT LIKE 'R%par%' OR STATUT = 'reparé'");
    int repare = 0;
    if(queryRepare.exec() && queryRepare.next()) {
        repare = queryRepare.value(0).toInt();
    }
    queryRepare.finish();

    // Calcul de "En attente" (Anciennement "Autres")
    int enAttente = total - encours - repare;

    // 2. --- CRÉATION DU GRAPHIQUE CAMEMBERT ---
    QPieSeries *series = new QPieSeries();

    // On ajoute les données brutes
    series->append("En cours", encours);
    series->append("Réparés", repare);
    if (enAttente > 0) series->append("En attente", enAttente);

    // --- PERSONNALISATION AVEC POURCENTAGES ---

    // 1. Slice "En cours"
    QPieSlice *sliceCours = series->slices().at(0);
    double pcCours = (static_cast<double>(encours) / total) * 100.0;
    sliceCours->setLabel(QString("En cours : %1%").arg(QString::number(pcCours, 'f', 1)));
    sliceCours->setLabelVisible(true);
    sliceCours->setBrush(QColor(255, 165, 0)); // Orange

    // 2. Slice "Réparés"
    QPieSlice *sliceRepare = series->slices().at(1);
    double pcRepare = (static_cast<double>(repare) / total) * 100.0;
    sliceRepare->setLabel(QString("Réparés : %1%").arg(QString::number(pcRepare, 'f', 1)));
    sliceRepare->setLabelVisible(true);
    sliceRepare->setBrush(QColor(0, 255, 0)); // Vert
    sliceRepare->setExploded(true);
    sliceRepare->setLabelArmLengthFactor(0.15);

    // 3. Slice "En attente" (si existe)
    if (enAttente > 0) {
        QPieSlice *sliceAttente = series->slices().at(2);
        double pcAttente = (static_cast<double>(enAttente) / total) * 100.0;
        sliceAttente->setLabel(QString("En attente : %1%").arg(QString::number(pcAttente, 'f', 1)));
        sliceAttente->setLabelVisible(true);
        sliceAttente->setBrush(Qt::gray); // Gris
    }

    // 3. --- CONFIGURATION DU CHART ---
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("État des Appareils (Total: " + QString::number(total) + ")");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom); // Légende en bas pour laisser de la place

    // 4. --- AFFICHAGE ---
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Nettoyage et Affichage
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
        if (i == 7) continue; // Ignorer remarques
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
