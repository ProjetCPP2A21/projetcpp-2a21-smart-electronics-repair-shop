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
#include <QDialog>
#include <QPixmap>
#include <QLabel>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include "qrcodegen.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QByteArray>
#include <QApplication>
#include <QThread>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPalette>
#include <QJsonObject>
#include <QJsonDocument>
//
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSqlError>
#include <QSqlTableModel>


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



nstock::nstock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stock)
{
    ui->setupUi(this);
    ui->tableView->setModel(stmp.afficher());
    connect(ui->btexporterPDF_stock, &QPushButton::clicked, this, &nstock::exporterPDF);
    networkManager = new QNetworkAccessManager(this);
    ui->tableView->setItemDelegate(new StockColorDelegate(this));
    arduino = new QSerialPort(this);

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


                if (quantiteInt <= 10) {
                QString message = QString("AJOUT: %1 (Qte: %2)").arg(nom, quantite);
                envoyerSMSsimple(message);
                }



            verifierStockEtAlerter();
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

        if (quantiteInt <= 10){
        QString message = QString("AJOUT: %1 (Qte: %2)").arg(nom, quantite);
            envoyerSMSsimple(message);
        }
        verifierStockEtAlerter();
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



void nstock::statistique()
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





void nstock::on_btstatistique_stock_clicked()
{
    statistique();
}




void nstock::exporterPDF()
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

void nstock::on_btQR_stock_clicked()
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






void nstock::envoyerSMSsimple(const QString& message)
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

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            qDebug() << "✅ Telegram envoyé! Réponse:" << response;
            QMessageBox::information(this, "Succès", "✅ Message reçu sur TLF!");
        } else {
            qDebug() << "❌ Erreur Telegram:" << reply->errorString();
            QMessageBox::warning(this, "Erreur", "Vérifiez votre connexion Internet");
        }
        reply->deleteLater();
    });
}
void nstock::verifierStockEtAlerter()
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
void nstock::on_btRechercheArduino_clicked()
{
    QString idText = ui->lineEdit_idArduino->text().trimmed();

    // SIMPLE APPEL - sans le 'if' incorrect
    stmp.rechercherArduino(arduino, idText);
}
