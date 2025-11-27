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
            "Téléphone", "Email", "Type Pièces", "Date Partenariat" , "Score"
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
    if (!q.exec("SELECT NVL(MAX(ID_FOURNISSEUR), 0) + 1 AS NEXT_ID FROM FOURNISSEUR")) {
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
        "INSERT INTO FOURNISSEUR (ID_FOURNISSEUR, NOM_ENT, NOM_F, PRENOM_F, TEL, EMAIL, ADRESSE, DATE_DE_PARTENERIAT, TYPES_DES_PIECES) "
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
    auto idEdit = page->findChild<QLineEdit*>("Id_2");
    if (!idEdit) return;

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(page, "Erreur", "ID invalide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT ID_FOURNISSEUR, NOM_ENT, NOM_F, PRENOM_F, TEL, EMAIL, TYPES_DES_PIECES, ADRESSE, DATE_DE_PARTENERIAT "
                  "FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
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
    q.prepare("SELECT NOM_F, PRENOM_F, TEL, EMAIL FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
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
    updateQuery += " WHERE ID_FOURNISSEUR=:id";

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
    auto idEdit = page->findChild<QLineEdit*>("Id_2");
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
    query.prepare("DELETE FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
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

    table->setColumnCount(9); // now includes Score column
    table->clearContents();
    table->setRowCount(0);

    QSqlQuery query("SELECT ID_FOURNISSEUR, NOM_ENT, NOM_F, PRENOM_F, TEL, EMAIL, TYPES_DES_PIECES, ADRESSE, DATE_DE_PARTENERIAT FROM FOURNISSEUR");
    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value("ID_FOURNISSEUR").toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value("NOM_ENT").toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value("NOM_F").toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value("PRENOM_F").toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value("TEL").toString()));
        table->setItem(row, 5, new QTableWidgetItem(query.value("EMAIL").toString()));
        table->setItem(row, 6, new QTableWidgetItem(query.value("TYPES_DES_PIECES").toString()));
        table->setItem(row, 7, new QTableWidgetItem(query.value("DATE_DE_PARTENERIAT").toString()));

        // ---- NEW: add Score column ----
        int id = query.value("ID_FOURNISSEUR").toInt();
        ScoreFournisseur sc = calculerScoreFournisseur(id);
        table->setItem(row, 8, new QTableWidgetItem(QString::number(sc.scoreTotal)));

        // Make first 8 columns non-editable
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

    // Create chart view (local)
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 400);

    // Dialog
    QDialog dialog;
    dialog.setWindowTitle("Statistiques Fournisseurs");
    dialog.resize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(chartView);

    dialog.exec();
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

    int companyColumn = 1;
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
// --- MA1 : calcul du score d'un fournisseur ---
fournisseur::ScoreFournisseur fournisseur::calculerScoreFournisseur(int idF)
{
    ScoreFournisseur sc;
    sc.scoreValeur = 0;
    sc.scoreRareté = 0;
    sc.scoreDiversité = 0;
    sc.scoreAnciennete = 0;
    sc.scoreTotal = 0;

    // --- récupérer données ---
    QSqlQuery query;
    query.prepare("SELECT TYPES_DES_PIECES, DATE_DE_PARTENERIAT "
                  "FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
    query.bindValue(":id", idF);

    if (!query.exec() || !query.next())
        return sc;

    // -----------------------------
    //  sécurisation du champ texte
    // -----------------------------
    QString typesTxt = query.value(0).toString().toLower();

    // enlever caractères invisibles/contrôles
    typesTxt.remove(QRegularExpression("[\\x00-\\x1F\\x7F]"));

    // normaliser les séparateurs
    typesTxt.replace("،", ",");
    typesTxt.replace(";", ",");
    typesTxt.replace("|", ",");

    typesTxt = typesTxt.trimmed();

    if (typesTxt.isEmpty())
        return sc;

    // -----------------------------
    //   split propre + dédoublons
    // -----------------------------
    QStringList piecesList = typesTxt.split(",", Qt::SkipEmptyParts);

    QSet<QString> pieces;
    for (QString p : piecesList) {
        p = p.trimmed();
        if (!p.isEmpty())
            pieces.insert(p);
    }

    // -----------------------------
    //   catégories
    // -----------------------------
    static const QSet<QString> critiques = {
        "batterie","ecran","carte","ic","chip","processeur","cpu","gpu",
        "ram","rom","ssd","hdd","motherboard","carte mere","pcb"
    };

    static const QSet<QString> importants = {
        "connecteur","bouton","camera","microphone","speaker","haut parleur",
        "antenne","capteur","sensor","led","diode","switch"
    };

    static const QSet<QString> communs = {
        "vis","cable","coque","plastique","metal","boitier","ruban",
        "tissu","adhesif","joint","clip","ressort","fil"
    };

    // -----------------------------
    //  score diversité
    // -----------------------------
    int recognized = 0;
    for (const QString &p : pieces)
        if (critiques.contains(p) || importants.contains(p) || communs.contains(p))
            recognized++;

    sc.scoreDiversité = recognized * 10;

    // -----------------------------
    //  score valeur
    // -----------------------------
    for (const QString &p : pieces) {
        if (critiques.contains(p))       sc.scoreValeur += 40;
        else if (importants.contains(p)) sc.scoreValeur += 20;
        else if (communs.contains(p))    sc.scoreValeur += 5;
    }

    // -----------------------------
    //  score rareté
    // -----------------------------
    for (const QString &p : pieces) {
        if (!critiques.contains(p) &&
            !importants.contains(p) &&
            !communs.contains(p))
            continue;

        QSqlQuery q2;
        q2.prepare("SELECT COUNT(*) FROM FOURNISSEUR "
                   "WHERE ',' || LOWER(TYPES_DES_PIECES) || ',' LIKE :m");
        q2.bindValue(":m", "%" + p + "%");

        if (q2.exec() && q2.next()) {
            int c = q2.value(0).toInt();
            if (c == 1)      sc.scoreRareté += 50;
            else if (c <= 3) sc.scoreRareté += 20;
            else             sc.scoreRareté += 5;
        }
    }

    // -----------------------------
    //  ancienneté
    // -----------------------------
    QVariant dateVar = query.value(1);
    QDate d;

    if (dateVar.canConvert<QDate>())
        d = dateVar.toDate();
    else {
        QString ds = dateVar.toString().left(10);
        d = QDate::fromString(ds, "yyyy-MM-dd");
        if (!d.isValid())
            d = QDate::fromString(ds, "dd/MM/yyyy");
    }

    if (d.isValid()) {
        int years = d.daysTo(QDate::currentDate()) / 365;
        sc.scoreAnciennete = years * 2;
    }

    // -----------------------------
    //  total
    // -----------------------------
    sc.scoreTotal = sc.scoreValeur + sc.scoreRareté +
                    sc.scoreDiversité + sc.scoreAnciennete;

    return sc;
}


// --- MA1 : afficher le score d'un fournisseur ---
void fournisseur::afficherScoreFournisseurMA1()
{
    // --- récupérer l'ID entré par l'utilisateur ---
    auto idEdit = page->findChild<QLineEdit*>("Id_2");
    if (!idEdit) {
        QMessageBox::warning(page, "Erreur", "Champ ID introuvable !");
        return;
    }

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(page, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    // --- calcul du score ---
    ScoreFournisseur sc = calculerScoreFournisseur(id);

    // --- afficher le score dans une message box ---
    QString details = QString(
                          "===== SCORE FOURNISSEUR ID %1 =====\n\n"
                          "Valeur des pièces      : %2 pts\n"
                          "Rareté                  : %3 pts\n"
                          "Diversité               : %4 pts\n"
                          "Ancienneté (années ×10) : %5 pts\n\n"
                          "SCORE TOTAL             : %6 pts"
                          ).arg(id)
                          .arg(sc.scoreValeur)
                          .arg(sc.scoreRareté)
                          .arg(sc.scoreDiversité)
                          .arg(sc.scoreAnciennete)
                          .arg(sc.scoreTotal);

    QMessageBox::information(page, "Évaluation Fournisseur (MA1)", details);

    // --- mettre à jour le tableau si présent ---
    auto table = page->findChild<QTableWidget*>("tabaff_6");
    if (table) {
        for (int row = 0; row < table->rowCount(); ++row) {
            if (table->item(row, 0) && table->item(row, 0)->text().toInt() == id) {
                if (table->columnCount() > 8) {
                    QTableWidgetItem *item = table->item(row, 8);
                    if (!item) {
                        item = new QTableWidgetItem();
                        table->setItem(row, 8, item);
                    }
                    item->setText(QString::number(sc.scoreTotal));
                }
                break;
            }
        }
    }
}

// --- MA2 : identifier fournisseurs prioritaires ---
QList<fournisseur::FournisseurCritique> fournisseur::identifierFournisseursPrioritaires()
{
    QList<FournisseurCritique> list;

    // --- récupérer tous les fournisseurs ---
    QSqlQuery q("SELECT ID_FOURNISSEUR, TYPES_DES_PIECES, DATE_DE_PARTENERIAT FROM FOURNISSEUR");

    while (q.next())
    {
        int id = q.value(0).toInt();
        QString typesTxt = q.value(1).toString().trimmed().toLower();
        QVariant dateVar  = q.value(2);

        // --- filtrage des entrées inutiles ---
        if (typesTxt.isEmpty()) continue;
        if (!dateVar.isValid()) continue;
        if (typesTxt.length() < 2) continue;

        // --- calcul score MA1 ---
        ScoreFournisseur sc = calculerScoreFournisseur(id);

        // --- ignorer si score critique nul ---
        if (sc.scoreValeur + sc.scoreRareté == 0) continue;

        FournisseurCritique fc;
        fc.id = id;

        // --- calcul score criticité MA2 ---
        fc.scoreCriticite = sc.scoreRareté * 0.5 + sc.scoreValeur * 0.5 + sc.scoreDiversité * 0.1;

        list.append(fc);
    }

    // --- tri par score criticité décroissant ---
    std::sort(list.begin(), list.end(), [](const FournisseurCritique &a, const FournisseurCritique &b){
        return a.scoreCriticite > b.scoreCriticite;
    });

    return list;
}

// --- MA2 : afficher fournisseurs prioritaires ---
void fournisseur::afficherFournisseursPrioritairesMA2()
{
    auto table = page->findChild<QTableWidget*>("tabaff_6");
    auto idEdit = page->findChild<QLineEdit*>("Id_2");

    if (!table || table->rowCount() == 0) {
        QMessageBox::warning(page, "Attention", "Aucun fournisseur à analyser.");
        return;
    }

    QList<FournisseurCritique> list = identifierFournisseursPrioritaires();
    if (list.isEmpty()) return;

    // --- effacer anciennes couleurs ---
    for (int row = 0; row < table->rowCount(); ++row)
        for (int col = 0; col < table->columnCount(); ++col)
            table->item(row, col)->setBackground(Qt::darkGray);

    // --- seuils manuels ---
    const double maxScore = 31.0;  // rouge
    const double midScore = 16.0;  // vert

    // --- appliquer les couleurs selon le score réel ---
    for (int row = 0; row < table->rowCount(); ++row) {
        QTableWidgetItem* idItem = table->item(row, 0);
        if (!idItem) continue;
        int id = idItem->text().toInt();
        auto it = std::find_if(list.begin(), list.end(), [id](const FournisseurCritique &fc){ return fc.id == id; });
        if (it == list.end()) continue;

        QColor color;
        double s = it->scoreCriticite;
        if (s >= maxScore)          color = Qt::red;    // top criticité
        else if (s >= midScore)     color = Qt::green;  // haute criticité
        else                        color = Qt::blue;   // moyenne criticité

        for (int col = 0; col < table->columnCount(); ++col)
            table->item(row, col)->setBackground(color);
    }

    // --- afficher le message ---
    QString msg;
    bool hasId = idEdit && !idEdit->text().trimmed().isEmpty();
    int id = hasId ? idEdit->text().trimmed().toInt() : -1;

    if (!hasId || id <= 0) {
        msg += "Fournisseurs prioritaires :\n\n";
        msg += "Le tableau met en évidence les fournisseurs les plus critiques.\n";
        msg += "Couleurs (du plus critique au moins critique) :\n";
        msg += " • Rouge → Criticité maximale\n";
        msg += " • Vert  → Criticité élevée\n";
        msg += " • Bleu  → Criticité modérée\n\n";
        msg += "Entrez un ID pour consulter les détails d'un fournisseur spécifique.";
    } else {
        auto it = std::find_if(list.begin(), list.end(), [id](const FournisseurCritique &fc){ return fc.id == id; });
        if (it != list.end()) {
            ScoreFournisseur sc = calculerScoreFournisseur(id);
            msg += QString("MA2 – Détails du fournisseur ID %1 :\n\n").arg(id);
            msg += QString("Score Valeur   : %1\n").arg(sc.scoreValeur);
            msg += QString("Score Rareté   : %1\n").arg(sc.scoreRareté);
            msg += QString("Score Criticité (Valeur + Rareté) : %1\n").arg(it->scoreCriticite);
            msg += "\n";
        } else {
            msg += "Fournisseur non classé.";
        }
    }

    QMessageBox::information(page, "MA2 – Fournisseurs prioritaires", msg);
}


//EXPORTATION PDF

void fournisseur::exporterPDF()
{
    // === 1. Récupération des données ===
    struct RowData {
        int id;
        QString nom, pieces, date, tel, email;
        ScoreFournisseur score;
        double criticite() const { return score.scoreValeur + score.scoreRareté; }
        bool operator==(const RowData& o) const { return id == o.id; }
    };

    QList<RowData> rows;
    QMap<QString, int> entrepriseCount;

    QSqlQuery q;
    if (!q.exec("SELECT ID_FOURNISSEUR, NOM_ENT, TYPES_DES_PIECES, "
                "TO_CHAR(DATE_DE_PARTENERIAT, 'dd/MM/yyyy'), TEL, EMAIL "
                "FROM FOURNISSEUR ORDER BY NOM_ENT")) {
        QMessageBox::critical(nullptr, "Erreur SQL", q.lastError().text());
        return;
    }

    while (q.next()) {
        RowData r;
        r.id = q.value(0).toInt();
        r.nom = q.value(1).toString().trimmed();
        r.pieces = q.value(2).toString().trimmed();
        r.date = q.value(3).toString();
        r.tel = q.value(4).toString();
        r.email = q.value(5).toString();
        r.score = calculerScoreFournisseur(r.id);
        rows << r;
        entrepriseCount[r.nom]++;
    }

    if (rows.isEmpty()) {
        QMessageBox::information(nullptr, "Export PDF", "Aucun fournisseur dans la base.");
        return;
    }

    // === 2. Top 5 + Stats ===
    auto sorted = rows;
    std::sort(sorted.begin(), sorted.end(), [](const RowData& a, const RowData& b){
        return a.criticite() > b.criticite();
    });
    QList<RowData> top5 = sorted.mid(0, 5);

    double sumScore = 0;
    int maxScore = 0, minScore = 99999;
    for (const auto& r : rows) {
        int s = r.score.scoreTotal;
        sumScore += s;
        maxScore = qMax(maxScore, s);
        minScore = qMin(minScore, s);
    }
    double avgScore = sumScore / rows.size();

    // === 3. Stats entreprises (triées) ===
    QString statsTable = R"(
        <table style="width:75%; margin:35px auto; font-size:11pt; border-collapse:collapse; box-shadow: 0 2px 8px rgba(0,0,0,0.1);">
            <tr style="background:#2c3e50; color:white;">
                <th style="padding:14px; font-size:12pt;">Entreprise</th>
                <th style="padding:14px; font-size:12pt;">Nombre</th>
                <th style="padding:14px; font-size:12pt;">Pourcentage</th>
            </tr>
    )";

    QList<QPair<QString, int>> list;
    for (auto it = entrepriseCount.constBegin(); it != entrepriseCount.constEnd(); ++it)
        list << qMakePair(it.key(), it.value());

    std::sort(list.begin(), list.end(), [](const auto& a, const auto& b){ return a.second > b.second; });

    int total = rows.size();
    for (int i = 0; i < list.size(); ++i) {
        double pct = list[i].second * 100.0 / total;
        statsTable += QString(R"(
            <tr style="background:%1;">
                <td style="padding:12px;">%2</td>
                <td style="padding:12px; text-align:center;">%3</td>
                <td style="padding:12px; text-align:center; font-weight:bold;">%4%</td>
            </tr>
        )").arg(i%2==0 ? "#f8f9fa" : "#ffffff")
                          .arg(list[i].first.toHtmlEscaped())
                          .arg(list[i].second)
                          .arg(QString::number(pct, 'f', 1));
    }
    statsTable += "</table>";

    // === 4. HTML FINAL — TOUT est parfait ===
    QString html = QStringLiteral(R"(
    <html>
    <head>
        <meta charset="utf-8">
        <style>
            body { font-family: "Segoe UI", Arial, sans-serif; margin: 40px; line-height: 1.6; color: #2c3e50; background: white; }
            h1 { text-align: center; font-size: 28pt; color: #2c3e50; margin: 10px 0 5px 0; }
            h2 { font-size: 18pt; color: #2980b9; border-bottom: 3px solid #3498db; padding-bottom: 10px; margin-top: 50px; margin-bottom: 20px; }
            .header { text-align: center; color: #7f8c8d; font-size: 12pt; margin-bottom: 30px; }
            .box { background: #f0f8ff; padding: 20px; border-radius: 12px; border-left: 6px solid #3498db; margin: 30px 0; font-size: 11pt; }
            .formula { background: #fff8e1; border-left-color: #ff9800; }
            table { width: 100%; border-collapse: collapse; margin: 30px 0; font-size: 10.5pt; }
            th, td { border: 1.8px solid #95a5a6; padding: 12px; text-align: center; vertical-align: top; }
            th { background: linear-gradient(#3498db, #2980b9); color: white; font-weight: bold; font-size: 11pt; }
            tr:nth-child(even) { background-color: #f8fdff; }
            .top1 { background: #d5f4e6 !important; font-weight: bold; }
            .top2 { background: #e8f8f5 !important; }
            .top3 { background: #f4f9f4 !important; }
            .top4 { background: #f8f9f8 !important; }
            .top5 { background: #fcfcfc !important; }
            .footer { margin-top: 100px; text-align: center; color: #95a5a6; font-size: 9pt; }
        </style>
    </head>
    <body>

        <h1>Rapport Complet des Fournisseurs</h1>
        <div class="header">
            <strong>OSANA Smart Electronics Repair Shop</strong><br>
            Généré le %1
        </div>

        <div class="box">
            <strong>Synthèse globale :</strong><br>
            • Nombre total de fournisseurs : <strong>%2</strong><br>
            • Score moyen : <strong>%3 pts</strong><br>
            • Score maximum : <strong>%4</strong> — Score minimum : <strong>%5</strong>
        </div>

        <h2>1. Répartition des Fournisseurs par Entreprise</h2>
        %6

        <h2>2. Liste Complète des Fournisseurs</h2>
        <table>
            <tr>
                <th>ID</th><th>Entreprise</th><th>Pièces Fournies</th><th>Date Partenariat</th>
                <th>Téléphone</th><th>Email</th>
                <th>Valeur</th><th>Rareté</th><th>Diversité</th><th>Ancienneté</th><th>Score Total</th>
            </tr>
    )").arg(QDateTime::currentDateTime().toString("dddd dd MMMM yyyy à hh:mm"))
                       .arg(rows.size())
                       .arg(QString::number(avgScore,'f',1))
                       .arg(maxScore).arg(minScore)
                       .arg(statsTable);

    // === Tableau complet ===
    for (int i = 0; i < rows.size(); ++i) {
        const auto& r = rows[i];
        QString rowClass = (i < 5) ? " class=\"top" + QString::number(i+1) + "\"" : "";
        html += "<tr" + rowClass + ">";
        html += "<td>" + QString::number(r.id) + "</td>";
        html += "<td>" + r.nom.toHtmlEscaped() + "</td>";
        html += "<td style=\"text-align:left; max-width:380px;\">" +
                r.pieces.toHtmlEscaped().replace(";", "<br>• ") + "</td>";
        html += "<td>" + r.date + "</td>";
        html += "<td>" + r.tel.toHtmlEscaped() + "</td>";
        html += "<td>" + r.email.toHtmlEscaped() + "</td>";
        html += "<td>" + QString::number(r.score.scoreValeur) + "</td>";
        html += "<td>" + QString::number(r.score.scoreRareté) + "</td>";
        html += "<td>" + QString::number(r.score.scoreDiversité) + "</td>";
        html += "<td>" + QString::number(r.score.scoreAnciennete/10) + "</td>";
        html += "<td><strong>" + QString::number(r.score.scoreTotal) + "</strong></td>";
        html += "</tr>";
    }

    html += QStringLiteral(R"(
        </table>

        <h2>3. Top 5 Fournisseurs par Criticité (Valeur + Rareté)</h2>
        <table>
            <tr>
                <th>Rang</th><th>Entreprise</th><th>Criticité</th><th>Score Total</th><th>Ancienneté</th>
            </tr>
    )");

    for (int i = 0; i < top5.size(); ++i) {
        const auto& r = top5[i];
        html += QString(R"(
            <tr class="top%1">
                <td><strong>%2</strong></td>
                <td><strong>%3</strong></td>
                <td><strong>%4</strong></td>
                <td><strong>%5</strong></td>
                <td>%6 an(s)</td>
            </tr>
        )").arg(i+1).arg(i+1).arg(r.nom.toHtmlEscaped())
                    .arg(int(r.criticite())).arg(r.score.scoreTotal).arg(r.score.scoreAnciennete/10);
    }

    html += QStringLiteral(R"(
        </table>

        <div class="box">
            <h2>Légende des Couleurs (Top 5)</h2>
            <ul>
                <li>1er → Fond vert clair = Meilleure criticité</li>
                <li>2e à 5e → Dégradé selon le classement</li>
            </ul>
        </div>

        <div class="box formula">
            <h2>Formule du Score Total</h2>
            <p><strong>Score = Valeur + Rareté + Diversité + Ancienneté</strong></p>
            <ul>
                <li><strong>Valeur</strong> : Volume et régularité des commandes</li>
                <li><strong>Rareté</strong> : Pièces uniques ou rares</li>
                <li><strong>Diversité</strong> : Nombre de catégories de pièces</li>
                <li><strong>Ancienneté</strong> : Années de partenariat × 10 points</li>
            </ul>
        </div>

        <div class="footer">
            Rapport généré automatiquement — OSANA Smart Electronics Repair Shop © 2025
        </div>
    </body></html>
    )");

    // === Export PDF ===
    QString fichier = QFileDialog::getSaveFileName(
        nullptr, "Exporter Rapport Fournisseurs",
        QDir::homePath() + "/Desktop/Rapport_Fournisseurs_OSANA_" + QDate::currentDate().toString("yyyy-MM-dd") + ".pdf",
        "Fichiers PDF (*.pdf)");

    if (fichier.isEmpty()) return;
    if (!fichier.endsWith(".pdf", Qt::CaseInsensitive)) fichier += ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPageSize::A4);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fichier);
    printer.setPageMargins(QMarginsF(10,10,10,10), QPageLayout::Millimeter);

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(nullptr, "Succès",
                             "Rapport PDF généré avec succès !\n\nFichier enregistré sur le Bureau.");
}
