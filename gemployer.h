#ifndef GEMPLOYER_H
#define GEMPLOYER_H

#include <QMainWindow>
#include "employer.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

// Graphiques (Si QtCharts est installé)
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>

//using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class Gemployer; }
QT_END_NAMESPACE

class Gemployer : public QMainWindow
{
    Q_OBJECT

public:
    Gemployer(QWidget *parent = nullptr);
    ~Gemployer();

private slots:
    // --- Login & Récupération ---
    void on_btn_login_clicked();            // Se connecter
    void on_btn_oublie_clicked();           // Aller à la page oubli
    void on_btn_valider_recup_clicked();    // Vérifier Q/R et montrer MTP
    void on_btn_retour_login_clicked();
    void on_btn_retour1_login_clicked();    // Retour

    // --- CRUD ---
    void on_pushButton_5_clicked();         // Ajouter
    void on_btnSupprimer_clicked();         // Supprimer
    void on_btnModifier_clicked();          // Modifier
    void on_lineEdit_recherche_textChanged(const QString &text);
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_trier_clicked();

    // --- Extras ---
    void on_btn_pdf_clicked();
    void on_pushButton_stats_clicked();

    void on_btn_retour_login_2_clicked();

private:
    Ui::Gemployer *ui;
    Employer emp;
   bool verifierChamps();
    void rafraichir();
    void viderFormulaire();
    void chargerFormulaire(const QString& id);
    void afficherStatistiques();
};

#endif // GEMPLOYER_H
