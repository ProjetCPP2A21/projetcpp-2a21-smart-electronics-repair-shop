#include "gemployer.h"
#include "ui_gemployer.h"
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QDate>
#include <QDesktopServices>
#include <QUrl>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "arduino.h"

// ==========================================
// CONSTRUCTEUR
// ==========================================
Gemployer::Gemployer(QWidget *parent) : QMainWindow(parent), ui(new Ui::Gemployer)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->page_2);    // Démarrage sur Login
    int ret = A.connect_arduino(); // Connexion à l'Arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_rfid()));


    // 1. ID et Téléphone : Uniquement des chiffres (0-9)
    ui->lineEdit->setValidator(new QIntValidator(0, 99999999, this));      // ID (max 8 chiffres)
    ui->lineEdit_tel->setValidator(new QIntValidator(0, 99999999, this));  // Tél (max 8 chiffres)
    ui->salaire->setValidator(new QDoubleValidator(0, 100000, 2, this));   // Salaire (chiffres à virgule)

    // 2. Nom et Prénom : Uniquement des lettres et espaces (pas de chiffres)
    // Le regex signifie : début(^) à fin($) autorise [a-z] [A-Z] et espace [\s]
    QRegularExpression rxLettres("^[a-zA-Z\\s]+$");
    QValidator *validatorLettres = new QRegularExpressionValidator(rxLettres, this);
    ui->lineEdit_3->setValidator(validatorLettres); // Nom
    ui->lineEdit_6->setValidator(validatorLettres); // Prénom
    // === REMPLISSAGE DES LISTES DE QUESTIONS ===
    QStringList listeQuestions;
    listeQuestions << "Quel est le nom de votre  equipe ?"
                   << "Quelle est votre ville de naissance ?"
                   << "Quel est le nom de jeune fille de votre mère ?"
                   << "Quel est votre film préféré ?"
                   << "Quel est votre plat préféré ?"
                   << "Quel est le prénom de votre meilleur ami ?"
                   << "Dans quelle école primaire êtes-vous allé ?";

    // 1. On remplit la liste pour l'AJOUT (Page 1)
    ui->comboBox_question_ajout->addItems(listeQuestions);

    // 2. On remplit la liste pour la RÉCUPÉRATION (Page 3)
    // Elle contient maintenant "plusieurs questions" fixes.
    ui->comboBox_question_recup->addItems(listeQuestions);

    // ... suite du constructeur ...
}

Gemployer::~Gemployer() { delete ui; }

// ==========================================
// GESTION CONNEXION & SECURITÉ
// ==========================================

// Login
void Gemployer::on_btn_login_clicked()
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
        ui->stackedWidget->setCurrentWidget(ui->page);

        rafraichir();
        ui->input_user->clear();
        ui->input_pass->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Identifiant ou Mot de passe incorrect.");
    }
}


void Gemployer::on_btn_oublie_clicked()
{
    ui->input_id_recup->clear();
    ui->input_reponse_recup->clear();
    ui->lbl_resultat_mtp->clear();


    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

// Bouton "Retour" (Vers Page 2)
void Gemployer::on_btn_retour_login_clicked()
{
    // 1. On vide le formulaire d'ajout pour laisser la place propre
    viderFormulaire();

    // 2. On retourne à la page de Login (page_2 / Index 1)
    ui->stackedWidget->setCurrentWidget(ui->page_2);

    QMessageBox::information(this, "Déconnexion", "Vous êtes déconnecté.");
}

// LOGIQUE DE RÉCUPERATION (ID + Question + Réponse)
void Gemployer::on_btn_valider_recup_clicked()
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
void Gemployer::on_pushButton_5_clicked() // AJOUTER
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

void Gemployer::on_btnModifier_clicked() // MODIFIER
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

void Gemployer::on_btnSupprimer_clicked() // SUPPRIMER
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

void Gemployer::rafraichir() {
    QSqlQueryModel* model = emp.afficher();
    if (model) ui->tableView->setModel(model);
}

void Gemployer::viderFormulaire() {
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

void Gemployer::chargerFormulaire(const QString& id) {
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

void Gemployer::on_tableView_clicked(const QModelIndex &index) {
    QString id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
    chargerFormulaire(id);
}

// ==========================================
// EXTRAS (Tri, Recherche, PDF, Stats)
// ==========================================
void Gemployer::on_lineEdit_recherche_textChanged(const QString &text) {
    if (text.isEmpty()) rafraichir();
    else ui->tableView->setModel(emp.rechercher(text));
}

void Gemployer::on_pushButton_trier_clicked() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES ORDER BY ID_EMPLOYE ASC");
    ui->tableView->setModel(model);
}
void Gemployer::on_btn_retour1_login_clicked()
{
    // 1. On efface le message de résultat (pour que ce soit propre la prochaine fois)
    ui->lbl_resultat_mtp->clear();

    // 2. On vide les champs (optionnel)
    ui->input_id_recup->clear();
    ui->input_reponse_recup->clear();

    // 3. On retourne à la page de Login (qui s'appelle page_2)
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void Gemployer::on_btn_pdf_clicked()
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
void Gemployer::on_pushButton_stats_clicked() {
    afficherStatistiques();
}

void Gemployer::afficherStatistiques() {
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

void Gemployer::on_btn_retour_login_2_clicked()
{
    // 1. On vide le formulaire d'ajout pour laisser la place propre
    viderFormulaire();

    // 2. On retourne à la page de Login (page_2 / Index 1)
    ui->stackedWidget->setCurrentWidget(ui->page_2);

    QMessageBox::information(this, "Déconnexion", "Vous êtes déconnecté.");
}
bool Gemployer::verifierChamps()
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
void Gemployer::update_rfid()
{
    // On récupère le port série
    QSerialPort *serial = A.getserial();

    // IMPORTANT : On utilise une boucle while et canReadLine()
    // Cela garantit qu'on ne lit QUE si une ligne complète est arrivée (terminée par \n)
    while (serial->canReadLine()) {

        QByteArray data = serial->readLine();

        // Nettoyage strict du code reçu
        QString uid = QString::fromUtf8(data).trimmed(); // Enlève les espaces début/fin et \n
        uid = uid.replace(" ", "");                      // Enlève les espaces au milieu

        // Si le code est trop court (bruit), on l'ignore et on attend la suite
        if (uid.length() < 4) {
            continue;
        }

        qDebug() << "✅ UID COMPLET REÇU :" << uid;

        // --- Vérification dans la base de données ---
        QSqlQuery query;
        query.prepare("SELECT NOMEMPLOYE, PRENOM FROM EMPLOYES WHERE RFID_UID = :uid");
        query.bindValue(":uid", uid);

        if (query.exec()) {
            if (query.next()) {
                // --- CAS 1 : Employé trouvé ---
                QString nom = query.value("NOMEMPLOYE").toString();
                QString prenom = query.value("PRENOM").toString();

                QMessageBox::information(this, "Accès Autorisé",
                                         "Bienvenue " + prenom + " " + nom);
                // Si vous voulez aller au menu après un scan réussi :
                // ui->stackedWidget->setCurrentWidget(ui->menu);
            } else {
                // --- CAS 2 : Carte inconnue ---
                // On affiche dans la console pour que vous puissiez copier le code
                qDebug() << "❌ INCONNU - COPIEZ CE CODE DANS ORACLE :" << uid;

                QMessageBox::warning(this, "Accès Refusé", "Carte non reconnue : " + uid);
            }
        } else {
            qDebug() << "Erreur SQL :" << query.lastError().text();
        }
    }
}


