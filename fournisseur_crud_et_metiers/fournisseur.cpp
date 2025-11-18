#include "fournisseur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QDebug>
#include <QVBoxLayout>


fournisseur::fournisseur(QWidget *parentWidget, QObject *parent)
    : QObject(parent), page(parentWidget)
{
    auto table = page->findChild<QTableWidget*>("tabaff_6");
    if (table) {
        table->setColumnCount(8);
        QStringList headers = {
            "ID", "Nom Entreprise", "Contact Nom", "Contact Prénom",
            "Téléphone", "Email", "Type Pièces", "Date Partenariat"
        };
        table->setHorizontalHeaderLabels(headers);
    }

    rafraichirListeFournisseurs();
}

bool fournisseur::validerChamps(const QString &email, const QString &telephone, const QString &nomEntreprise)
{
    if (nomEntreprise.trimmed().isEmpty()) {
        QMessageBox::warning(page, "Erreur", "Nom de l'entreprise obligatoire.");
        return false;
    }

    QRegularExpression regexEmail(R"(^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$)");
    if (!regexEmail.match(email).hasMatch()) {
        QMessageBox::warning(page, "Erreur", "Adresse email invalide.");
        return false;
    }

    QRegularExpression regexTel(R"(^\d{8,}$)");
    if (!regexTel.match(telephone).hasMatch()) {
        QMessageBox::warning(page, "Erreur", "Numéro de téléphone invalide (8 chiffres minimum).");
        return false;
    }

    return true;
}

int fournisseur::genererIdSiVide()
{
    auto idEdit = page->findChild<QLineEdit*>("leld_4");
    if (!idEdit) return -1;

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (ok && id > 0) return id;

    QSqlQuery q;
    if (!q.exec("SELECT NVL(MAX(ID_FORUNISSEUR), 0) + 1 AS NEXT_ID FROM FOURNISSEUR")) {
        qDebug() << "Erreur récup ID:" << q.lastError().text();
        return -1;
    }
    if (q.next()) return q.value("NEXT_ID").toInt();
    return -1;
}

// AJOUTER
void fournisseur::ajouterFournisseur()
{
    auto nomEdit = page->findChild<QLineEdit*>("leNomEntreprise_4");
    auto nomFEdit = page->findChild<QLineEdit*>("leContactNom_4");
    auto prenomFEdit = page->findChild<QLineEdit*>("leContactPrenom_4");
    auto telEdit = page->findChild<QLineEdit*>("leTelephone_4");
    auto emailEdit = page->findChild<QLineEdit*>("leEmail_4");
    auto typeEdit = page->findChild<QLineEdit*>("leTypePieces_4");
    auto adrEdit = page->findChild<QTextEdit*>("teAdresse_4");
    auto dateEdit = page->findChild<QDateEdit*>("deDatePartenariat_4");

    if (!nomEdit || !telEdit || !emailEdit || !dateEdit) {
        QMessageBox::critical(page, "Erreur", "Champs introuvables dans l'interface.");
        return;
    }

    QString nomEntreprise = nomEdit->text().trimmed();
    QString nomF = nomFEdit ? nomFEdit->text().trimmed() : QString();
    QString prenomF = prenomFEdit ? prenomFEdit->text().trimmed() : QString();
    QString telephone = telEdit->text().trimmed();
    QString email = emailEdit->text().trimmed();
    QString typePieces = typeEdit ? typeEdit->text().trimmed() : QString();
    QString adresse = adrEdit ? adrEdit->toPlainText().trimmed() : QString();
    QString date = dateEdit->date().toString("yyyy-MM-dd");

    if (!validerChamps(email, telephone, nomEntreprise))
        return;

    int id = genererIdSiVide();
    if (id <= 0) {
        QMessageBox::critical(page, "Erreur", "Impossible de générer un ID valide.");
        return;
    }

    QSqlQuery query;
    query.prepare(
        "INSERT INTO FOURNISSEUR (ID_FORUNISSEUR, NOM_ENT, NOM_F, PRENOM_F, TEL, EMAIL, ADRESSE, DATE_DE_PARTENERIAT, TYPES_DES_PIECES) "
        "VALUES (:id, :nom, :nomf, :prenomf, :tel, :email, :adr, TO_DATE(:date,'YYYY-MM-DD'), :type)"
        );
    query.bindValue(":id", id);
    query.bindValue(":nom", nomEntreprise);
    query.bindValue(":nomf", nomF);
    query.bindValue(":prenomf", prenomF);
    query.bindValue(":tel", telephone);
    query.bindValue(":email", email);
    query.bindValue(":adr", adresse);
    query.bindValue(":date", date);
    query.bindValue(":type", typePieces);

    if (!query.exec()) {
        QMessageBox::critical(page, "Erreur", "Échec d’ajout : " + query.lastError().text());
        return;
    }

    rafraichirListeFournisseurs();
    viderChamps();
    QMessageBox::information(page, "Succès", "Fournisseur ajouté avec succès.");
}

// RECHERCHER PAR ID
void fournisseur::rechercherFournisseurParId()
{
    auto idEdit = page->findChild<QLineEdit*>("Id_4");
    if (!idEdit) return;

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(page, "Erreur", "ID invalide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT ID_FORUNISSEUR, NOM_ENT, NOM_F, PRENOM_F, TEL, EMAIL, TYPES_DES_PIECES, ADRESSE, DATE_DE_PARTENERIAT "
                  "FROM FOURNISSEUR WHERE ID_FORUNISSEUR = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(page, "Erreur", "Recherche impossible : " + query.lastError().text());
        return;
    }

    if (query.next()) {
        page->findChild<QLineEdit*>("leNomEntreprise_4")->setText(query.value("NOM_ENT").toString());
        page->findChild<QLineEdit*>("leContactNom_4")->setText(query.value("NOM_F").toString());
        page->findChild<QLineEdit*>("leContactPrenom_4")->setText(query.value("PRENOM_F").toString());
        page->findChild<QLineEdit*>("leTelephone_4")->setText(query.value("TEL").toString());
        page->findChild<QLineEdit*>("leEmail_4")->setText(query.value("EMAIL").toString());
        page->findChild<QLineEdit*>("leTypePieces_4")->setText(query.value("TYPES_DES_PIECES").toString());
        page->findChild<QTextEdit*>("teAdresse_4")->setPlainText(query.value("ADRESSE").toString());
        page->findChild<QDateEdit*>("deDatePartenariat_4")->setDate(QDate::fromString(query.value("DATE_DE_PARTENERIAT").toString(), "yyyy-MM-dd"));

        QMessageBox::information(page, "Trouvé", "Fournisseur trouvé !");
    } else {
        QMessageBox::information(page, "Non trouvé", "Aucun fournisseur avec cet ID.");
        viderChamps();
    }
}

// MODIFIER
void fournisseur::modifierFournisseur()
{
    auto idEdit = page->findChild<QLineEdit*>("leld_4");
    if (!idEdit) return;

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(page, "Erreur", "Recherchez d'abord un ID valide.");
        return;
    }

    QString nom = page->findChild<QLineEdit*>("leNomEntreprise_4")->text().trimmed();
    QString nomF = page->findChild<QLineEdit*>("leContactNom_4")->text().trimmed();
    QString prenomF = page->findChild<QLineEdit*>("leContactPrenom_4")->text().trimmed();
    QString telephone = page->findChild<QLineEdit*>("leTelephone_4")->text().trimmed();
    QString email = page->findChild<QLineEdit*>("leEmail_4")->text().trimmed();
    QString typePieces = page->findChild<QLineEdit*>("leTypePieces_4")->text().trimmed();
    QString adresse = page->findChild<QTextEdit*>("teAdresse_4")->toPlainText().trimmed();
    QString date = page->findChild<QDateEdit*>("deDatePartenariat_4")->date().toString("yyyy-MM-dd");

    if (!validerChamps(email, telephone, nom))
        return;

    QString currentEmail, currentTel, currentNomF, currentPrenomF;
    QSqlQuery q;
    q.prepare("SELECT NOM_F, PRENOM_F, TEL, EMAIL FROM FOURNISSEUR WHERE ID_FORUNISSEUR = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        currentNomF = q.value("NOM_F").toString();
        currentPrenomF = q.value("PRENOM_F").toString();
        currentTel = q.value("TEL").toString();
        currentEmail = q.value("EMAIL").toString();
    }

    idEdit->setText(QString::number(id));
    page->findChild<QLineEdit*>("leContactNom_4")->setText(currentNomF);
    page->findChild<QLineEdit*>("leContactPrenom_4")->setText(currentPrenomF);

    QString updateQuery = "UPDATE FOURNISSEUR SET NOM_ENT=:nom, NOM_F=:nomf, PRENOM_F=:prenomf, "
                          "ADRESSE=:adr, DATE_DE_PARTENERIAT=TO_DATE(:date,'YYYY-MM-DD'), TYPES_DES_PIECES=:type";
    if (telephone != currentTel) updateQuery += ", TEL=:tel";
    if (email != currentEmail) updateQuery += ", EMAIL=:email";
    updateQuery += " WHERE ID_FORUNISSEUR=:id";

    QSqlQuery query;
    query.prepare(updateQuery);
    query.bindValue(":nom", nom);
    query.bindValue(":nomf", nomF);
    query.bindValue(":prenomf", prenomF);
    query.bindValue(":adr", adresse);
    query.bindValue(":date", date);
    query.bindValue(":type", typePieces);
    query.bindValue(":id", id);
    if (telephone != currentTel) query.bindValue(":tel", telephone);
    if (email != currentEmail) query.bindValue(":email", email);

    if (!query.exec()) {
        QMessageBox::critical(page, "Erreur", "Échec modification : " + query.lastError().text());
        return;
    }

    rafraichirListeFournisseurs();
    QMessageBox::information(page, "Succès", "Fournisseur modifié !");
}

// SUPPRIMER
void fournisseur::supprimerFournisseur()
{
    auto idEdit = page->findChild<QLineEdit*>("leld_4");
    if (!idEdit) return;

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(page, "Erreur", "Recherchez d'abord un ID valide.");
        return;
    }

    if (QMessageBox::question(page, "Confirmer", "Supprimer ce fournisseur ?", QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
        return;

    QSqlQuery query;
    query.prepare("DELETE FROM FOURNISSEUR WHERE ID_FORUNISSEUR = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(page, "Erreur", "Échec suppression : " + query.lastError().text());
        return;
    }

    rafraichirListeFournisseurs();
    viderChamps();
    QMessageBox::information(page, "Succès", "Fournisseur supprimé !");
}

// RAFRAICHIR TABLE
void fournisseur::rafraichirListeFournisseurs()
{
    auto table = page->findChild<QTableWidget*>("tabaff_6");
    if (!table) {
        QMessageBox::critical(page, "Erreur", "Tableau non trouvé !");
        return;
    }

    table->setColumnCount(8);
    table->clearContents();
    table->setRowCount(0);

    QSqlQuery query("SELECT ID_FORUNISSEUR, NOM_ENT, NOM_F, PRENOM_F, TEL, EMAIL, TYPES_DES_PIECES, ADRESSE, DATE_DE_PARTENERIAT FROM FOURNISSEUR");
    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value("ID_FORUNISSEUR").toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value("NOM_ENT").toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value("NOM_F").toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value("PRENOM_F").toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value("TEL").toString()));
        table->setItem(row, 5, new QTableWidgetItem(query.value("EMAIL").toString()));
        table->setItem(row, 6, new QTableWidgetItem(query.value("TYPES_DES_PIECES").toString()));
        table->setItem(row, 7, new QTableWidgetItem(query.value("DATE_DE_PARTENERIAT").toString()));

        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *it = table->item(row, col);
            if (it) it->setFlags(it->flags() & ~Qt::ItemIsEditable);
        }
        row++;
    }
}

// TRIER
void fournisseur::trierParNomEntreprise()
{
    auto table = page->findChild<QTableWidget*>("tabaff_6");
    if (table) table->sortItems(1, Qt::AscendingOrder);
}

// VIDER CHAMPS
void fournisseur::viderChamps()
{
    auto idEdit = page->findChild<QLineEdit*>("leld_4");
    if (idEdit) idEdit->clear();

    auto nom = page->findChild<QLineEdit*>("leNomEntreprise_4"); if (nom) nom->clear();
    auto cnom = page->findChild<QLineEdit*>("leContactNom_4"); if (cnom) cnom->clear();
    auto cprenom = page->findChild<QLineEdit*>("leContactPrenom_4"); if (cprenom) cprenom->clear();
    auto tel = page->findChild<QLineEdit*>("leTelephone_4"); if (tel) tel->clear();
    auto mail = page->findChild<QLineEdit*>("leEmail_4"); if (mail) mail->clear();
    auto type = page->findChild<QLineEdit*>("leTypePieces_4"); if (type) type->clear();
    auto adr = page->findChild<QTextEdit*>("teAdresse_4"); if (adr) adr->clear();
    auto date = page->findChild<QDateEdit*>("deDatePartenariat_4"); if (date) date->setDate(QDate::currentDate());
}

//STATISTIQUE
QPieSeries* fournisseur::statistiqueParEntreprise()
{
    QSqlQuery query;
    query.prepare(
        "SELECT NOM_ENT, COUNT(*) AS total "
        "FROM FOURNISSEUR "
        "GROUP BY NOM_ENT "
        "ORDER BY total DESC"
        );

    if(!query.exec()) {
        qDebug() << "Erreur stats:" << query.lastError();
        return nullptr;
    }

    QPieSeries *series = new QPieSeries();

    int rank = 0;
    int otherSum = 0;

    while (query.next()) {
        QString nom = query.value("NOM_ENT").toString();
        int total = query.value("total").toInt();

        if (rank < 5) {
            series->append(nom + " (" + QString::number(total) + ")", total);
        } else {
            otherSum += total;
        }

        rank++;
    }

    if (otherSum > 0)
        series->append("OTHER (" + QString::number(otherSum) + ")", otherSum);

    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

    return series;
}

void fournisseur::afficherStatistiques()
{
    QPieSeries *series = statistiqueParEntreprise();
    if (!series || series->count() == 0) {
        QMessageBox::information(page, "Statistiques", "Aucune donnée disponible.");
        delete series;
        return;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Fournisseurs par Entreprise");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    // On recrée proprement le QChartView à chaque fois
    delete chartViewStatPtr;
    chartViewStatPtr = new QChartView(chart);
    chartViewStatPtr->setRenderHint(QPainter::Antialiasing);
    chartViewStatPtr->setMinimumSize(600, 400);

    QDialog dialog;
    dialog.setWindowTitle("Statistiques Fournisseurs");
    dialog.resize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(chartViewStatPtr);
    dialog.setLayout(layout);
    dialog.exec();
}
//EXPORTATION PDF


void fournisseur::exporterPDF()
{
    auto table = page->findChild<QTableWidget*>("tabaff_6");
    if (!table || table->rowCount() == 0) {
        QMessageBox::warning(page, "Attention", "Aucun fournisseur à exporter.");
        return;
    }

    // Choix du fichier PDF
    QString fileName = QFileDialog::getSaveFileName(
        page,
        "Exporter en PDF",
        "Fournisseurs_" + QDate::currentDate().toString("yyyy-MM-dd") + ".pdf",
        "Fichiers PDF (*.pdf)"
        );
    if (fileName.isEmpty()) return;

    // Configuration du PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageLayout(QPageLayout(QPageSize(QPageSize::A4),
                                      QPageLayout::Portrait,
                                      QMarginsF(15,15,15,15),
                                      QPageLayout::Millimeter));

    QPainter painter(&printer);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    const QRectF pageRect = printer.pageRect(QPrinter::DevicePixel);
    double y = 50;

    // ====== TITRE ======
    QFont font = painter.font();
    font.setPointSize(22);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRectF(0, y, pageRect.width(), 50), Qt::AlignCenter, "Liste des Fournisseurs");
    y += 70;

    // ====== GRAPHIC PIE CHART ======
    QMap<QString,int> companyCounts;
    int companyCol = 1; // adjust if your "Entreprise" column index is different
    for (int row = 0; row < table->rowCount(); ++row) {
        QTableWidgetItem *item = table->item(row, companyCol);
        if (item) companyCounts[item->text()] += 1;
    }

    QPieSeries *series = new QPieSeries();
    for (auto it = companyCounts.begin(); it != companyCounts.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QChart chart;
    chart.addSeries(series);
    chart.setTitle("Répartition par entreprise");
    chart.legend()->setVisible(true);
    chart.legend()->setAlignment(Qt::AlignRight);

    QChartView chartView(&chart);
    chartView.setRenderHint(QPainter::Antialiasing);

    QPixmap chartPixmap(pageRect.width(), 300);
    chartPixmap.fill(Qt::white);
    QPainter chartPainter(&chartPixmap);
    chartView.resize(chartPixmap.size());
    chartView.render(&chartPainter);
    chartPainter.end();

    painter.drawPixmap(0, y, chartPixmap);
    y += chartPixmap.height() + 30;

    // ====== TABLEAU ======
    painter.drawText(QRectF(0, y, pageRect.width(), 30), Qt::AlignCenter, "Détails des fournisseurs");
    y += 40;

    QPoint tablePos(50, static_cast<int>(y));
    table->render(&painter, tablePos);

    painter.end();

    QMessageBox::information(page, "Succès", "PDF généré avec succès !\n" + QFileInfo(fileName).fileName());
}



//ai:
void fournisseur::afficherTopEntreprise()
{
    auto table = page->findChild<QTableWidget*>("tabaff_6");
    if (!table || table->rowCount() == 0) {
        QMessageBox::warning(page, "Attention", "Aucun fournisseur à analyser.");
        return;
    }

    QMap<QString, int> companyCounts;

    int companyColumn = 1; // adjust this to the column index of "Entreprise" in your table
    for (int row = 0; row < table->rowCount(); ++row) {
        QTableWidgetItem *item = table->item(row, companyColumn);
        if (item) {
            QString company = item->text();
            companyCounts[company] += 1;
        }
    }

    if (companyCounts.isEmpty()) {
        QMessageBox::information(page, "Résultat", "Aucune donnée trouvée.");
        return;
    }

    // Find the company with the max count
    QString topCompany;
    int maxCount = 0;
    for (auto it = companyCounts.begin(); it != companyCounts.end(); ++it) {
        if (it.value() > maxCount) {
            maxCount = it.value();
            topCompany = it.key();
        }
    }

    QMessageBox::information(page, "Top Entreprise",
                             QString("L'entreprise avec le plus de fournisseurs est : %1\nNombre : %2")
                                 .arg(topCompany)
                                 .arg(maxCount));
}
