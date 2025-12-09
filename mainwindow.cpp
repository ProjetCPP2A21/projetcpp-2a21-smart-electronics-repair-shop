#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appareil.h"
#include "stock.h"
#include "qrcodegen.hpp"

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
//
#include <QStyledItemDelegate>
#include <QPdfWriter>
#include <QDialog>
#include <QPixmap>
#include <QLabel>
#include <QDateTime>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRegularExpression>
#include <QThread>
#include <QApplication>
#include "qrcodegen.hpp"
#include <QUrl>
#include <QSqlTableModel>
#include <QSqlRecord>

#include <QPalette>
//
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSqlError>




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
#include "arduino.h"
// ====================================================================
// CONSTRUCTEUR & DESTRUCTEUR
// ====================================================================
// Classe pour la coloration du stock
class StockColorDelegate : public QStyledItemDelegate
{
public:
    StockColorDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override
    {
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);

        // colonne 4 = quantite
        if (index.column() == 4)
        {
            int qte = index.data().toInt();
            if (qte <= 10)
            {
                opt.palette.setColor(QPalette::Text, Qt::red);
                opt.palette.setColor(QPalette::HighlightedText, Qt::red);
            }
        }

        QStyledItemDelegate::paint(painter, opt, index);
    }
};
using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
, networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    int ret = A.connect_arduino(); // Connexion à l'Arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_rfid()));
    connect(ui->btexporterPDF_stock, &QPushButton::clicked, this, &MainWindow::exporterPDF);

    ui->tableView->setItemDelegate(new StockColorDelegate(this));
    // Dans MainWindow::MainWindow(), après ui->setupUi(this);
   // connect(ui->btexporterPDF_stock, &QPushButton::clicked, this, &MainWindow::on_btexporterPDF_stock_clicked);

    // --- Configuration de la Table ---
    ui->tablewidget_Appareils->setColumnCount(10);
    QStringList headers = {"ID", "Type", "Marque", "Modèle", "Défaut",
                           "Date Entrée", "Statut", "Remarques", "Prix Estimé",
                           "Date Estimée"};
    ui->tablewidget_Appareils->setHorizontalHeaderLabels(headers);
// configuration stock
    ui->tableView->setModel(tm.afficher());
    ui->tableView->setItemDelegate(new StockColorDelegate(this));

    // --- Connexion du champ de recherche 'rech' ---
    connect(ui->rech, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_ID_textChanged);

    // Activer le tri sur le QTableWidget
    ui->tablewidget_Appareils->setSortingEnabled(true);
arduino = new QSerialPort(this);
    // Chargement initial des données
    chargerTable();
    // Trouver automatiquement l'Arduino
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.vendorIdentifier() != 0) {   // Arduino détecté
            arduino->setPort(info);
            break;
        }
    }

    arduino->setBaudRate(QSerialPort::Baud9600);

    if (arduino->open(QIODevice::ReadWrite)) {
        qDebug() << "Arduino connecté !";
        QThread::msleep(1200);  // Laisser l'Arduino redémarrer
    } else {
        qDebug() << "Erreur ouverture Arduino !";
    }
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

void MainWindow::on_appareils_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->appareil);

}
           // stock(page)
void MainWindow::on_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pstock);
    ui->tableView->setModel(tm.afficher());
}
void MainWindow::on_btretour_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_btajouter_stock_clicked()
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
        ui->tableView->setModel(tm.afficher());
        QMessageBox::information(this, "Succès", "Ajout effectué avec succès !");


        if (quantiteInt <= 10) {
            QString message = QString("🛒 AJOUT - STOCK FAIBLE:\n"
                                      "Produit: %1\n"
                                      "Quantité: %2\n"
                                      "ID: %3\n\n"
                                      "⚠️ Stock critique détecté!")
                                  .arg(nom, quantite, QString::number(id));
            envoyerSMSsimple(message);
            // Optionnel: Afficher une alerte visuelle
            QMessageBox::warning(this, "Stock Faible",
                                 QString("Le produit '%1' a un stock faible (%2 unités).\nUn SMS d'alerte a été envoyé.")
                                     .arg(nom, quantite));
        }





    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout !");
    }
}

void MainWindow::on_btsupprimer_stock_clicked()
{
    int id = ui->lineEdit_IDstock->text().toInt();
    bool test = tm.supprimer(id);

    if (test)
    {


        ui->tableView->setModel(tm.afficher());
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

void MainWindow::on_btmodifier_stock_clicked()
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

        if (quantiteInt <= 10){
            QString message = QString("🛒 MODIFICATION - STOCK FAIBLE:\n"
                                      "Produit: %1\n"
                                      "Nouvelle quantité: %2\n"
                                      "ID: %3\n\n"
                                      "⚠️ Stock critique détecté!")
                                  .arg(nom, quantite, QString::number(id));
            envoyerSMSsimple(message);
           // Optionnel: Afficher une alerte visuelle
                              QMessageBox::warning(this, "Stock Faible",
                                                   QString("Le produit '%1' a un stock faible (%2 unités).\nUn SMS d'alerte a été envoyé.")
                                                       .arg(nom, quantite));

        }

    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void MainWindow::on_btrechercher_stock_clicked()
{
    QString nom = ui->lineEdit_recherche_stock->text().trimmed();
    qDebug() << "Recherche :" << nom;

    if (nom.isEmpty()) {
        ui->tableView->setModel(tm.afficher()); // affiche tout si vide
        return;
    }

    ui->tableView->setModel(tm.rechercher(nom));

}


void MainWindow::on_bttrier_stock_clicked()
{
    QString critere = "PRIXVENTE";
    QString ordre = "DESC";

    ui->tableView->setModel(tm.trier(critere, ordre));

}
void MainWindow::on_btmisajour_stock_clicked()
{
    // Recharge toute la table depuis la base
    ui->tableView->setModel(tm.afficher());

    QMessageBox::information(this, "Mise à jour", "Table mise à jour avec succès !");
}



void MainWindow::statistique()
{
    // Récupère le modèle actuellement affiché dans le tableView
    QAbstractItemModel* model = ui->tableView->model();
    if (!model) return;

    QMap<QString, int> totals; // catégorie -> somme des quantités

    int rowCount = model->rowCount();
    int categorieCol = 3; // colonne catégorie
    int quantiteCol = 4;  // colonne quantité

    for (int row = 0; row < rowCount; ++row)
    {
        QString categorie = model->index(row, categorieCol).data().toString();
        int quantite = model->index(row, quantiteCol).data().toInt();
        totals[categorie] += quantite;
    }

    // Création du graphique
    QPieSeries *series = new QPieSeries();
    for (auto it = totals.begin(); it != totals.end(); ++it)
        series->append(it.key(), it.value());

    for (auto slice : series->slices())
        slice->setLabelVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des quantités par catégorie");
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartViewGlobal = new QChartView(chart);
    chartViewGlobal->setRenderHint(QPainter::Antialiasing);

    // Supprime le layout précédent si existant
    if(ui->chartFrame_->layout() != nullptr)
        delete ui->chartFrame_->layout();

    QVBoxLayout *layout = new QVBoxLayout(ui->chartFrame_);
    layout->addWidget(chartViewGlobal);
    ui->chartFrame_->setLayout(layout);
}





void MainWindow::on_btstatistique_stock_clicked()
{
    statistique();
}








void MainWindow::exporterPDF()
{
    if (!chartViewGlobal) {
        QMessageBox::critical(this, "Erreur", "Aucun graphique à exporter !");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Exporter en PDF",
        "",
        "PDF (*.pdf)"
        );
    if (filePath.isEmpty())
        return;

    chartViewGlobal->update();
    qApp->processEvents();

    QPixmap pix = chartViewGlobal->grab();
    if (pix.isNull()) {
        QMessageBox::critical(this, "Erreur", "Échec de la capture du graphique !");
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);

    QRect rect = painter.viewport();
    QSize size = pix.size();
    size.scale(rect.size(), Qt::KeepAspectRatio);

    int x = (rect.width() - size.width()) / 2;
    int y = (rect.height() - size.height()) / 2;

    painter.drawPixmap(x, y, size.width(), size.height(), pix);
    painter.end();

    QMessageBox::information(this, "Succès", "PDF exporté avec succès !");
}

void MainWindow::on_btQR_stock_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une ligne !");
        return;
    }

    // Récupérer toutes les colonnes nécessaires
    QString id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
    QString nom = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1)).toString();
    QString reference = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toString();
    QString categorie = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 3)).toString();
    QString quantite = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 4)).toString();
    QString prixachat = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 5)).toString();
    QString prixvente = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 6)).toString();
    QString fournisseur = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 7)).toString();
    QString datelivraison = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 8)).toString();

    // Construire le texte du QR code
    QString qrText = QString(
                         "ID=%1\nNom=%2\nRéf=%3\nCatégorie=%4\nQté=%5\nPrix Achat=%6\nPrix Vente=%7\nFournisseur=%8\nDate=%9"
                         ).arg(id, nom, reference, categorie, quantite, prixachat, prixvente, fournisseur, datelivraison);

    std::string qrUtf8 = qrText.toUtf8().toStdString();
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(
        qrUtf8.c_str(),
        qrcodegen::QrCode::Ecc::MEDIUM
        );

    int size = qr.getSize();
    int scale = 10;
    QImage img(size * scale, size * scale, QImage::Format_RGB32);
    img.fill(Qt::white);

    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++)
            if (qr.getModule(x, y))
                for (int dy = 0; dy < scale; dy++)
                    for (int dx = 0; dx < scale; dx++)
                        img.setPixel((x*scale)+dx, (y*scale)+dy, qRgb(0, 0, 0));

    QDialog dialog(this);
    dialog.setWindowTitle("QR Code de la pièce");
    QLabel label(&dialog);
    label.setPixmap(QPixmap::fromImage(img));
    label.setAlignment(Qt::AlignCenter);

    QVBoxLayout layout(&dialog);
    layout.addWidget(&label);
    dialog.setLayout(&layout);
    dialog.setFixedSize(img.width()+20, img.height()+20);
    dialog.exec();
}





void MainWindow::envoyerSMSsimple(const QString& message)
{
    QString botToken = "8187829076:AAEuILOkPV-6h1muaynULKPxRJK4fqxGoU8";
    QString chatId = "8345893376";

    QUrl url(QString("https://api.telegram.org/bot%1/sendMessage").arg(botToken));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject telegramMessage;
    telegramMessage["chat_id"] = chatId;
    telegramMessage["text"] = "🛒 STOCK ALERTE\n" + message + "\n\n👤 Stock Bjaoui";

    QJsonDocument document(telegramMessage);
    QByteArray data = document.toJson();

    QNetworkReply *reply = networkManager->post(request, data);

    // === CORRECTION : Sans QMessageBox dans le callback ===
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            qDebug() << "✅ SMS envoyé! Réponse:" << response;
        } else {
            qDebug() << "❌ Erreur SMS:" << reply->errorString();
        }
        reply->deleteLater();
    });
}
void MainWindow::verifierStockEtAlerter()
{
    QSqlTableModel model;
    model.setTable("stock");
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);

    QString alertes = "🚨 ALERTE STOCK CRITIQUE 🚨\n\n";
    bool alerte = false;
    int compteurProduits = 0;

    int rows = model.rowCount();

    for (int i = 0; i < rows; i++)
    {
        QString nom = model.data(model.index(i, model.fieldIndex("nom"))).toString();
        int qty     = model.data(model.index(i, model.fieldIndex("quantite"))).toInt();

        if (qty <= 10)   // équivalent du WHERE
        {
            alertes += "• " + nom + " : seulement " + QString::number(qty) + " en stock !!\n";
            alerte = true;

            QString message = QString("ALERTE: %1 (Qte: %2)").arg(nom).arg(qty);
            envoyerSMSsimple(message);
            compteurProduits++;

            QThread::msleep(800);

            if (compteurProduits >= 3)
                break;
        }
    }

    if (alerte)
    {
        QMessageBox::critical(this, "ALERTE ENVOYÉE",
                              alertes +
                                  QString("\n\n✓ %1 alertes SMS envoyées!").arg(compteurProduits),
                              QMessageBox::Ok);

        QApplication::beep(); QThread::msleep(300);
        QApplication::beep(); QThread::msleep(300);
        QApplication::beep();
    }
}
//
void MainWindow::on_btRechercheArduino_clicked()
{
    QString idText = ui->lineEdit_idArduino->text().trimmed();

    // SIMPLE APPEL - sans le 'if' incorrect
    tm.rechercherArduino(arduino, idText);
}

#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QDate>
#include <QDesktopServices>
#include <QUrl>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

// ==========================================
// CONSTRUCTEUR
// ==========================================


// ==========================================
// GESTION CONNEXION & SECURITÉ
// ==========================================

// Login
void MainWindow::on_btn_login_clicked()
{
    QString id = ui->input_user->text();
    QString mtp = ui->input_pass->text();

    if (id.isEmpty() || mtp.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez remplir l'ID et le Mot de passe.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE ID_EMPLOYE = :id AND MTP = :pass");
    query.bindValue(":id", id);
    query.bindValue(":pass", mtp);

    if (query.exec() && query.next()) {
        QMessageBox::information(this, "Bienvenue", "Connexion réussie !");

        // Aller sur la page App (page)
        ui->stackedWidget->setCurrentWidget(ui->menu);
        rafraichir();
        ui->input_user->clear();
        ui->input_pass->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Identifiant ou Mot de passe incorrect.");
    }
}


void MainWindow::on_btn_oublie_clicked()
{
    ui->input_id_recup->clear();
    ui->input_reponse_recup->clear();
    ui->lbl_resultat_mtp->clear();


    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

// Bouton "Retour" (Vers Page 2)
void MainWindow::on_btn_retour_login_clicked()
{
    // 1. On vide le formulaire d'ajout pour laisser la place propre
    viderFormulaire();

    // 2. On retourne à la page de Login (page_2 / Index 1)
    ui->stackedWidget->setCurrentWidget(ui->page_2);

    QMessageBox::information(this, "Déconnexion", "Vous êtes déconnecté.");
}

// LOGIQUE DE RÉCUPERATION (ID + Question + Réponse)
void MainWindow::on_btn_valider_recup_clicked()

{
    // 1. On récupère ce que l'utilisateur a saisi
    QString id = ui->input_id_recup->text();

    // L'utilisateur DOIT sélectionner lui-même la bonne question dans la liste
    QString questionSelectionnee = ui->comboBox_question_recup->currentText();

    QString reponse = ui->input_reponse_recup->text();

    if(id.isEmpty() || reponse.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez remplir l'ID et la Réponse.");
        return;
    }

    QSqlQuery query;
    // 2. On vérifie si ce trio (ID + QUESTION + REPONSE) existe dans la base
    query.prepare("SELECT MTP FROM EMPLOYES WHERE ID_EMPLOYE = :id AND QUESTION = :q AND REPONSE = :r");

    query.bindValue(":id", id);
    query.bindValue(":q", questionSelectionnee);
    query.bindValue(":r", reponse);

    if(query.exec() && query.next()) {
        // --- C'EST GAGNÉ ---
        QString leMtp = query.value("MTP").toString();

        ui->lbl_resultat_mtp->setText("MOT DE PASSE : " + leMtp);
        ui->lbl_resultat_mtp->setStyleSheet("color: green; font-weight: bold; font-size: 14pt;");

    } else {
        // --- C'EST PERDU ---
        ui->lbl_resultat_mtp->setText("Données incorrectes !");
        ui->lbl_resultat_mtp->setStyleSheet("color: red; font-size: 12pt;");

        QMessageBox::critical(this, "Erreur", "Impossible de récupérer le mot de passe.\n\n"
                                              "Causes possibles :\n"
                                              "- ID incorrect\n"
                                              "- Vous n'avez pas choisi la bonne question\n"
                                              "- Votre réponse est fausse");
    }
}

// ==========================================
// CRUD (Ajout, Modif, Suppr)
// ==========================================
void MainWindow::on_pushButton_5_clicked() // AJOUTER
{
    emp.setId(ui->lineEdit->text());
    emp.setNom(ui->lineEdit_3->text());
    emp.setPrenom(ui->lineEdit_6->text());
    emp.setEmail(ui->lineEdit_email->text());
    emp.setTelephone(ui->lineEdit_tel->text().toInt());
    emp.setDateNaissance(ui->lineEdit_date->date());
    emp.setDateRecrutement(ui->dateEdit_recrutement->date());
    emp.setPoste(ui->poste->text());
    emp.setSalaire(ui->salaire->text().toDouble());

    // Champs Sécurité
    emp.setMtp(ui->lineEdit_mtp->text());
    emp.setQuestion(ui->comboBox_question_ajout->currentText());
    emp.setReponse(ui->lineEdit_reponse_ajout->text());

    if (emp.ajouter()) {
        rafraichir();
        QMessageBox::information(this, "Succès", "Employé ajouté avec sécurité !");
        viderFormulaire();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec ajout (ID existe ?)");
    }
}

void MainWindow::on_btnModifier_clicked() // MODIFIER
{
    emp.setId(ui->lineEdit->text());
    emp.setNom(ui->lineEdit_3->text());
    emp.setPrenom(ui->lineEdit_6->text());
    emp.setEmail(ui->lineEdit_email->text());
    emp.setTelephone(ui->lineEdit_tel->text().toInt());
    emp.setDateNaissance(ui->lineEdit_date->date());
    emp.setDateRecrutement(ui->dateEdit_recrutement->date());
    emp.setPoste(ui->poste->text());
    emp.setSalaire(ui->salaire->text().toDouble());

    emp.setMtp(ui->lineEdit_mtp->text());
    emp.setQuestion(ui->comboBox_question_ajout->currentText());
    emp.setReponse(ui->lineEdit_reponse_ajout->text());

    if (emp.modifier()) {
        rafraichir();
        QMessageBox::information(this, "Succès", "Modifié !");
        viderFormulaire();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec modification.");
    }
}

void MainWindow::on_btnSupprimer_clicked() // SUPPRIMER
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

void MainWindow::rafraichir() {
    QSqlQueryModel* model = emp.afficher();
    if (model) ui->tableView->setModel(model);
}

void MainWindow::viderFormulaire() {
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_tel->clear();
    ui->poste->clear();
    ui->salaire->clear();
    ui->lineEdit_mtp->clear();
    ui->lineEdit_reponse_ajout->clear();
}

void MainWindow::chargerFormulaire(const QString& id) {
    QSqlQuery q;
    q.prepare("SELECT * FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        ui->lineEdit->setText(q.value("ID_EMPLOYE").toString());
        ui->lineEdit_3->setText(q.value("NOMEMPLOYE").toString());
        ui->lineEdit_6->setText(q.value("PRENOM").toString());
        ui->lineEdit_email->setText(q.value("EMAIL").toString());
        ui->lineEdit_tel->setText(q.value("TELEPHONE").toString());
        ui->lineEdit_date->setDate(q.value("DATENAISSANCE").toDate());
        ui->dateEdit_recrutement->setDate(q.value("DATERECRUTEMENT").toDate());
        ui->poste->setText(q.value("POST").toString());
        ui->salaire->setText(q.value("SALAIRE").toString());

        ui->lineEdit_mtp->setText(q.value("MTP").toString());
        ui->lineEdit_reponse_ajout->setText(q.value("REPONSE").toString());
        // Pour le combo box, c'est plus complexe de remettre la bonne question,
        // on peut utiliser setCurrentText si elle existe dans la liste
        ui->comboBox_question_ajout->setCurrentText(q.value("QUESTION").toString());
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    QString id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
    chargerFormulaire(id);
}

// ==========================================
// EXTRAS (Tri, Recherche, PDF, Stats)
// ==========================================
void MainWindow::on_lineEdit_recherche_textChanged(const QString &text) {
    if (text.isEmpty()) rafraichir();
    else ui->tableView->setModel(emp.rechercher(text));
}

void MainWindow::on_pushButton_trier_clicked() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES ORDER BY ID_EMPLOYE ASC");
    ui->tableView->setModel(model);
}
void MainWindow::on_btn_retour1_login_clicked()
{
    // 1. On efface le message de résultat (pour que ce soit propre la prochaine fois)
    ui->lbl_resultat_mtp->clear();

    // 2. On vide les champs (optionnel)
    ui->input_id_recup->clear();
    ui->input_reponse_recup->clear();

    // 3. On retourne à la page de Login (qui s'appelle page_2)
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_btn_pdf_clicked()
{
    // 1. Choix du fichier
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter Tout",
                                                    QDir::homePath() + "/Desktop/Employes_Complet.pdf",
                                                    "PDF (*.pdf)");
    if (fileName.isEmpty()) return;

    // 2. Configuration Imprimante (PAYSAGE OBLIGATOIRE)
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageOrientation(QPageLayout::Landscape); // Format Paysage
    printer.setPageMargins(QMarginsF(5, 5, 5, 5), QPageLayout::Millimeter); // Marges très fines

    // 3. HTML & CSS
    // On force les bordures sur TOUTES les cellules (td) même vides
    QString html = R"(
      <html>
      <head>
        <style>
          table {
            width: 100%;
            border-collapse: collapse;
            font-size: 7pt; /* Police petite pour tout faire entrer */
            font-family: Arial, Helvetica, sans-serif;
          }
          th {
            background-color: #4CAF50;
            color: white;
            border: 1px solid black;
            padding: 4px;
            text-align: center;
          }
          td {
            border: 1px solid black; /* Bordure noire visible partout */
            padding: 3px;
            text-align: center;
            height: 15px; /* Hauteur min pour voir la case même si vide */
          }
          /* Style spécial pour les colonnes de sécurité à droite */
          .secu { background-color: #ffcccc; }
        </style>
      </head>
      <body>
        <h2 style="text-align:center;">LISTE COMPLÈTE DES EMPLOYÉS</h2>

        <table>
          <thead>
            <tr>
              <th width="3%">ID</th>
              <th width="8%">Nom</th>
              <th width="8%">Prénom</th>
              <th width="12%">Email</th>
              <th width="7%">Tél</th>
              <th width="6%">Naiss.</th>
              <th width="6%">Recrut.</th>
              <th width="8%">Poste</th>
              <th width="7%">Salaire</th>
              <th width="7%" style="background-color: #B22222;">MTP</th>
              <th width="18%" style="background-color: #B22222;">Question</th>
              <th width="10%" style="background-color: #B22222;">Réponse</th>
            </tr>
          </thead>
          <tbody>
    )";

    // 4. Remplissage des données
    QSqlQuery q;
    q.prepare("SELECT * FROM EMPLOYES ORDER BY ID_EMPLOYE ASC");

    if (q.exec()) {
        while (q.next()) {
            html += "<tr>";

            // Si une donnée est vide dans la BDD, .toString() renvoie ""
            // Le CSS (border: 1px solid black) affichera quand même la case.

            html += "<td>" + q.value("ID_EMPLOYE").toString() + "</td>";
            html += "<td>" + q.value("NOMEMPLOYE").toString() + "</td>";
            html += "<td>" + q.value("PRENOM").toString() + "</td>";
            html += "<td>" + q.value("EMAIL").toString() + "</td>";
            html += "<td>" + q.value("TELEPHONE").toString() + "</td>";
            html += "<td>" + q.value("DATENAISSANCE").toDate().toString("dd/MM/yy") + "</td>";
            html += "<td>" + q.value("DATERECRUTEMENT").toDate().toString("dd/MM/yy") + "</td>";
            html += "<td>" + q.value("POST").toString() + "</td>";
            html += "<td>" + q.value("SALAIRE").toString() + " DT</td>";

            // Colonnes de sécurité (Fond rouge clair)
            // Même si c'est vide, la case rouge apparaîtra
            html += "<td class='secu'>" + q.value("MTP").toString() + "</td>";
            html += "<td class='secu'>" + q.value("QUESTION").toString() + "</td>";
            html += "<td class='secu'>" + q.value("REPONSE").toString() + "</td>";

            html += "</tr>";
        }
    }

    html += R"(
          </tbody>
        </table>
      </body>
      </html>
    )";

    // 5. Impression
    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);

    QMessageBox::information(this, "Succès", "PDF Complet généré sur le Bureau !");
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
void MainWindow::on_pushButton_stats_clicked() {
    afficherStatistiques();
}

void MainWindow::afficherStatistiques() {
    int c1 = 0, c2 = 0, c3 = 0, total = 0;
    QSqlQuery query("SELECT DATENAISSANCE FROM EMPLOYES");
    while (query.next()) {
        int age = query.value(0).toDate().daysTo(QDate::currentDate()) / 365;
        if (age < 25) c1++;
        else if (age >= 25 && age <= 40) c2++;
        else c3++;
        total++;
    }
    if (total == 0) return;
    QPieSeries *series = new QPieSeries();
    series->append("Jeunes <25", c1);
    series->append("Adultes 25-40", c2);
    series->append("Seniors >40", c3);
    QPieSlice *s1 = series->slices().at(0);
    QPieSlice *s2 = series->slices().at(1);
    QPieSlice *s3 = series->slices().at(2);
    s1->setLabel(QString("Jeunes: %1%").arg((double(c1)/total)*100, 0, 'f', 1));
    s2->setLabel(QString("Adultes: %1%").arg((double(c2)/total)*100, 0, 'f', 1));
    s3->setLabel(QString("Seniors: %1%").arg((double(c3)/total)*100, 0, 'f', 1));
    s1->setColor(QColor("#3498db")); s2->setColor(QColor("#2ecc71")); s3->setColor(QColor("#e74c3c"));
    s1->setLabelVisible(true); s2->setLabelVisible(true); s3->setLabelVisible(true);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition par Âge");
    chart->legend()->setAlignment(Qt::AlignRight);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->graphicsView);
    chartView->resize(ui->graphicsView->size());
    chartView->show();
}

void MainWindow::on_btn_retour_login_2_clicked()
{
    // 1. On vide le formulaire d'ajout pour laisser la place propre
    viderFormulaire();

    // 2. On retourne à la page de Login (page_2 / Index 1)
    ui->stackedWidget->setCurrentWidget(ui->page_2);

    QMessageBox::information(this, "Déconnexion", "Vous êtes déconnecté.");
}
bool MainWindow::verifierChamps()
{
    // 1. VÉRIFICATION DES CHAMPS VIDES
    // On liste tous les champs importants
    if (ui->lineEdit->text().isEmpty() ||       // ID
        ui->lineEdit_3->text().isEmpty() ||     // Nom
        ui->lineEdit_6->text().isEmpty() ||     // Prénom
        ui->lineEdit_email->text().isEmpty() || // Email
        ui->lineEdit_tel->text().isEmpty() ||   // Tel
        ui->poste->text().isEmpty() ||          // Poste
        ui->salaire->text().isEmpty() ||        // Salaire
        ui->lineEdit_mtp->text().isEmpty())     // Mot de passe
    {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir TOUS les champs.");
        return false; // On bloque
    }

    // 2. VÉRIFICATION DU TÉLÉPHONE (Exactement 8 chiffres)
    QString tel = ui->lineEdit_tel->text();

    // On vérifie la taille ET si c'est bien un nombre
    bool isNumber;
    tel.toInt(&isNumber); // Tente de convertir en nombre

    if (tel.length() != 8 || !isNumber) {
        QMessageBox::warning(this, "Erreur Téléphone", "Le numéro de téléphone doit contenir exactement 8 chiffres.");
        return false; // On bloque
    }

    // 3. VÉRIFICATION DE L'EMAIL (Format xxxx@xxxx.xx)
    QString email = ui->lineEdit_email->text();

    // Expression régulière pour un email standard
    QRegularExpression regex("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");

    if (!regex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur Email", "L'adresse email n'est pas valide.\nExemple attendu : nom@gmail.com");
        return false; // On bloque
    }

    // Si on arrive ici, tout est BON !
    return true;
}
void MainWindow::on_employe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);

}
void MainWindow::on_btn_retour_menu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);

}


void MainWindow::on_retour_connection_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);

}


void MainWindow::on_pushButton_exit_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::update_rfid()
{
    QSerialPort *serial = A.getserial();
    if (!serial || !serial->isOpen()) return;

    while (serial->canReadLine()) {
        QString ligne = QString::fromUtf8(serial->readLine()).trimmed();

        // EXTRAIRE UNIQUEMENT les 8 caractères hexadécimaux
        QRegularExpression re("([A-F0-9]{8})", QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch match = re.match(ligne);

        if (!match.hasMatch()) {
            continue; // ignore tout le reste
        }

        QString uid = match.captured(1).toUpper();
        qDebug() << "UID VALIDE :" << uid;

        QSqlQuery query;
        query.prepare("SELECT NOMEMPLOYE, PRENOM FROM EMPLOYES WHERE RFID_UID = :uid");
        query.bindValue(":uid", uid);

        if (query.exec() && query.next()) {
            // EMPLOYE TROUVÉ → ACCÈS AUTORISÉ
            QString prenom = query.value("PRENOM").toString();
            QString nom    = query.value("NOMEMPLOYE").toString();

            // 1. Message de bienvenue
            QMessageBox::information(this, "Accès Autorisé",
                                     "Bienvenue " + prenom + " " + nom + " !");

            // 2. Ouvre la porte
            serial->write("1");
            serial->flush();

            // 3. PASSER DIRECTEMENT À L'INTERFACE STOCK
            ui->stackedWidget->setCurrentWidget(ui->pstock);  // ou le nom exact de ta page stock
            // Si tu utilises un autre système (ex: QWidget séparé), remplace par :
            // stockWindow->show();
            // this->hide();

        } else {
            // CARTE INCONNUE
            QMessageBox::warning(this, "Accès Refusé", "Carte non reconnue !");
            serial->write("0");
            serial->flush();
        }

        // On traite une seule carte à la fois → on sort après le premier UID valide
        return;
    }
}
