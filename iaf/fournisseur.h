#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
//pie chart:
#include <QtCharts/QPieSeries> //pie chart handling
#include <QtCharts/QChartView> //affichage
//pdf:
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QTextTable>
#include <QtCharts/QChartView>
#include <QTableView>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStandardPaths>   // ← AJOUTE ÇA !
#include <QFileInfo>
#include <QTextDocument>
class fournisseur : public QObject
{
    Q_OBJECT

public:
    explicit fournisseur(QWidget *parentWidget, QObject *parent = nullptr);
    ~fournisseur() = default;
    typedef struct {
        int scoreValeur;
        int scoreRareté;
        int scoreDiversité;
        int scoreAnciennete;
        int scoreTotal;
    } ScoreFournisseur;
    typedef struct {
        int id;
        int scoreCriticite;
    } FournisseurCritique;
public slots:
    //crud:
    void ajouterFournisseur();
    void rechercherFournisseurParId(QWidget *page);
    void modifierFournisseur();
    void supprimerFournisseur();
    void rafraichirListeFournisseurs();
    //metiers:
    void trierParNomEntreprise();
    QPieSeries* statistiqueParEntreprise();
    void afficherStatistiques();
    void exporterPDF();
    void afficherTopEntreprise();
    ScoreFournisseur calculerScoreFournisseur(int idF);
    QList <FournisseurCritique> identifierFournisseursPrioritaires();
    void afficherScoreFournisseurMA1();
    void afficherFournisseursPrioritairesMA2();

private:
    QWidget *page;
    fournisseur *fourn = nullptr;
    void viderChamps();
    bool validerChamps(const QString &email, const QString &telephone, const QString &nomEntreprise);
    int genererIdSiVide(); // retourne l'ID à utiliser (soit l'ID saisi, soit MAX+1 depuis la BDD)
    //elements virtuels de pie chart:
    QChartView* chartViewStatPtr = nullptr;
    QTableView* tableViewPtr = nullptr;
};

#endif
