/********************************************************************************
** Form generated from reading UI file 'menu_employer.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_EMPLOYER_H
#define UI_MENU_EMPLOYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu_employer
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_2;
    QLabel *label_6;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_recherche;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_email;
    QLabel *label_5;
    QPushButton *pushButton_5;
    QLabel *label_3;
    QLabel *label;
    QDateEdit *lineEdit_date;
    QPushButton *ex;
    QLabel *mis;
    QPushButton *btnSupprimer;
    QLineEdit *lineEdit_3;
    QPushButton *btnModifie;
    QLabel *label_4;
    QLabel *label_9;
    QLineEdit *lineEdit_tel;
    QDateEdit *dateEdit_recrutement;
    QPushButton *pushButton_9;
    QLabel *label_8;
    QLabel *label_10;
    QTableView *tableView;
    QLabel *label_7;
    QLineEdit *poste;
    QLineEdit *salaire;
    QLabel *label_11;
    QPushButton *retour_4;
    QWidget *page_2;
    QPushButton *fourniseur;
    QToolButton *employer;
    QPushButton *appareils;
    QPushButton *stock;
    QLabel *label_12;
    QPushButton *client;
    QWidget *page_3;
    QTreeView *tableView_2;
    QPushButton *btajouter_stock;
    QLabel *prixachat;
    QPushButton *btsupprimer_stock;
    QDateEdit *dateEdit;
    QLabel *datelivraison;
    QLabel *nom;
    QPushButton *pushButton_7;
    QPushButton *pushButton_11;
    QPushButton *pushButton_8;
    QLabel *quantite;
    QLabel *prixvente;
    QLineEdit *lineEdit_prixvente;
    QLineEdit *lineEdit_fournisseur;
    QLineEdit *lineEdit_prixachat;
    QLabel *categorie;
    QLabel *reference_2;
    QLabel *label_14;
    QLabel *catgorie;
    QLabel *fournisseur;
    QLineEdit *lineEdit_IDstock;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_nomstock;
    QLabel *label_16;
    QPushButton *retour;
    QLabel *id;
    QLabel *label_13;
    QLineEdit *lineEdit_categorie;
    QPushButton *pushButton_10;
    QPushButton *btmodifier_stock;
    QLineEdit *lineEdit_quantite;
    QLineEdit *lineEdit_referencestock;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *menu_employer)
    {
        if (menu_employer->objectName().isEmpty())
            menu_employer->setObjectName("menu_employer");
        menu_employer->resize(1661, 881);
        centralwidget = new QWidget(menu_employer);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1661, 861));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 74);"));
        page = new QWidget();
        page->setObjectName("page");
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 240, 63, 20));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 530, 181, 41));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_6 = new QLineEdit(page);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(150, 300, 113, 26));
        lineEdit_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_recherche = new QLineEdit(page);
        lineEdit_recherche->setObjectName("lineEdit_recherche");
        lineEdit_recherche->setGeometry(QRect(530, 130, 181, 31));
        lineEdit_recherche->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit = new QLineEdit(page);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(140, 170, 113, 26));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_email = new QLineEdit(page);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(160, 450, 113, 26));
        lineEdit_email->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        label_5 = new QLabel(page);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 450, 91, 41));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        pushButton_5 = new QPushButton(page);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 700, 141, 31));
        pushButton_5->setStyleSheet(QString::fromUtf8(" background-color: rgb(18, 153, 29);"));
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 300, 71, 20));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 160, 101, 51));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 74, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        label->setPalette(palette);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_date = new QDateEdit(page);
        lineEdit_date->setObjectName("lineEdit_date");
        lineEdit_date->setGeometry(QRect(160, 540, 110, 26));
        lineEdit_date->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        ex = new QPushButton(page);
        ex->setObjectName("ex");
        ex->setGeometry(QRect(330, 700, 141, 31));
        ex->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(253, 154, 4);"));
        mis = new QLabel(page);
        mis->setObjectName("mis");
        mis->setGeometry(QRect(900, 130, 111, 31));
        mis->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);\n"
"background-color: rgb(18, 153, 29);\n"
""));
        btnSupprimer = new QPushButton(page);
        btnSupprimer->setObjectName("btnSupprimer");
        btnSupprimer->setGeometry(QRect(170, 700, 141, 31));
        btnSupprimer->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
" \n"
"background-color: rgb(253, 7, 27);"));
        lineEdit_3 = new QLineEdit(page);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(140, 240, 113, 26));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        btnModifie = new QPushButton(page);
        btnModifie->setObjectName("btnModifie");
        btnModifie->setGeometry(QRect(1050, 130, 121, 31));
        btnModifie->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
" background-color: rgb(253, 154, 4);"));
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 370, 91, 41));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_9 = new QLabel(page);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 640, 181, 20));
        label_9->setStyleSheet(QString::fromUtf8("font: 10pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        lineEdit_tel = new QLineEdit(page);
        lineEdit_tel->setObjectName("lineEdit_tel");
        lineEdit_tel->setGeometry(QRect(150, 370, 113, 26));
        lineEdit_tel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        dateEdit_recrutement = new QDateEdit(page);
        dateEdit_recrutement->setObjectName("dateEdit_recrutement");
        dateEdit_recrutement->setGeometry(QRect(200, 640, 110, 26));
        dateEdit_recrutement->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        pushButton_9 = new QPushButton(page);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(740, 130, 131, 29));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush3(QColor(154, 211, 238, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush3);
        QBrush brush4(QColor(39, 191, 115, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        pushButton_9->setPalette(palette1);
        pushButton_9->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(154, 211, 238);"));
        label_8 = new QLabel(page);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(400, 130, 111, 31));
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 91);\n"
" \n"
""));
        label_10 = new QLabel(page);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 100, 181, 51));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        label_10->setPalette(palette2);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: italic 9pt \"Segoe UI\";"));
        tableView = new QTableView(page);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(370, 400, 941, 192));
        tableView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(620, 650, 49, 16));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        poste = new QLineEdit(page);
        poste->setObjectName("poste");
        poste->setGeometry(QRect(680, 650, 113, 22));
        poste->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        salaire = new QLineEdit(page);
        salaire->setObjectName("salaire");
        salaire->setGeometry(QRect(930, 650, 113, 22));
        salaire->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_11 = new QLabel(page);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(870, 650, 49, 16));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        retour_4 = new QPushButton(page);
        retour_4->setObjectName("retour_4");
        retour_4->setGeometry(QRect(1200, 130, 141, 31));
        retour_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(253, 7, 27);\n"
""));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        fourniseur = new QPushButton(page_2);
        fourniseur->setObjectName("fourniseur");
        fourniseur->setGeometry(QRect(530, 418, 511, 41));
        fourniseur->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        employer = new QToolButton(page_2);
        employer->setObjectName("employer");
        employer->setGeometry(QRect(530, 228, 511, 51));
        employer->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        appareils = new QPushButton(page_2);
        appareils->setObjectName("appareils");
        appareils->setGeometry(QRect(530, 480, 511, 41));
        appareils->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        stock = new QPushButton(page_2);
        stock->setObjectName("stock");
        stock->setGeometry(QRect(530, 298, 511, 41));
        stock->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_12 = new QLabel(page_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(710, 140, 191, 61));
        label_12->setStyleSheet(QString::fromUtf8("font: 700 36pt \"Segoe UI\";"));
        client = new QPushButton(page_2);
        client->setObjectName("client");
        client->setGeometry(QRect(530, 358, 511, 41));
        client->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        tableView_2 = new QTreeView(page_3);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setGeometry(QRect(410, 190, 1071, 271));
        tableView_2->setStyleSheet(QString::fromUtf8("background-color: rgb(120, 120, 120);"));
        btajouter_stock = new QPushButton(page_3);
        btajouter_stock->setObjectName("btajouter_stock");
        btajouter_stock->setGeometry(QRect(190, 470, 93, 29));
        btajouter_stock->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 153, 29);"));
        prixachat = new QLabel(page_3);
        prixachat->setObjectName("prixachat");
        prixachat->setGeometry(QRect(110, 300, 111, 20));
        prixachat->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        btsupprimer_stock = new QPushButton(page_3);
        btsupprimer_stock->setObjectName("btsupprimer_stock");
        btsupprimer_stock->setGeometry(QRect(1240, 130, 93, 29));
        btsupprimer_stock->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        dateEdit = new QDateEdit(page_3);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(260, 420, 110, 26));
        dateEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        datelivraison = new QLabel(page_3);
        datelivraison->setObjectName("datelivraison");
        datelivraison->setGeometry(QRect(110, 420, 111, 20));
        datelivraison->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        nom = new QLabel(page_3);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(110, 140, 111, 20));
        nom->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        pushButton_7 = new QPushButton(page_3);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(660, 480, 93, 29));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 153, 29);"));
        pushButton_11 = new QPushButton(page_3);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(1360, 470, 93, 29));
        pushButton_11->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 145, 4);"));
        pushButton_8 = new QPushButton(page_3);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(430, 130, 93, 29));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 168, 168);"));
        quantite = new QLabel(page_3);
        quantite->setObjectName("quantite");
        quantite->setGeometry(QRect(110, 260, 111, 20));
        quantite->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        prixvente = new QLabel(page_3);
        prixvente->setObjectName("prixvente");
        prixvente->setGeometry(QRect(110, 340, 111, 20));
        prixvente->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_prixvente = new QLineEdit(page_3);
        lineEdit_prixvente->setObjectName("lineEdit_prixvente");
        lineEdit_prixvente->setGeometry(QRect(260, 340, 113, 26));
        lineEdit_prixvente->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_fournisseur = new QLineEdit(page_3);
        lineEdit_fournisseur->setObjectName("lineEdit_fournisseur");
        lineEdit_fournisseur->setGeometry(QRect(260, 380, 113, 26));
        lineEdit_fournisseur->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_prixachat = new QLineEdit(page_3);
        lineEdit_prixachat->setObjectName("lineEdit_prixachat");
        lineEdit_prixachat->setGeometry(QRect(260, 300, 113, 26));
        lineEdit_prixachat->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        categorie = new QLabel(page_3);
        categorie->setObjectName("categorie");
        categorie->setGeometry(QRect(110, 220, 111, 20));
        categorie->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        reference_2 = new QLabel(page_3);
        reference_2->setObjectName("reference_2");
        reference_2->setGeometry(QRect(110, 180, 111, 20));
        reference_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_14 = new QLabel(page_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(1330, 20, 91, 71));
        label_14->setStyleSheet(QString::fromUtf8("border-image: url(:/logo.jpeg);"));
        catgorie = new QLabel(page_3);
        catgorie->setObjectName("catgorie");
        catgorie->setGeometry(QRect(10, 40, 7, 20));
        fournisseur = new QLabel(page_3);
        fournisseur->setObjectName("fournisseur");
        fournisseur->setGeometry(QRect(110, 380, 111, 20));
        fournisseur->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_IDstock = new QLineEdit(page_3);
        lineEdit_IDstock->setObjectName("lineEdit_IDstock");
        lineEdit_IDstock->setGeometry(QRect(260, 100, 113, 26));
        lineEdit_IDstock->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_8 = new QLineEdit(page_3);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(550, 130, 301, 26));
        lineEdit_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_nomstock = new QLineEdit(page_3);
        lineEdit_nomstock->setObjectName("lineEdit_nomstock");
        lineEdit_nomstock->setGeometry(QRect(260, 140, 113, 26));
        lineEdit_nomstock->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_16 = new QLabel(page_3);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(20, -20, 1531, 611));
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        retour = new QPushButton(page_3);
        retour->setObjectName("retour");
        retour->setGeometry(QRect(550, 480, 93, 29));
        retour->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        id = new QLabel(page_3);
        id->setObjectName("id");
        id->setGeometry(QRect(110, 100, 111, 20));
        id->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_13 = new QLabel(page_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(230, 40, 151, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Simple Indust Shaded")});
        font.setPointSize(14);
        font.setUnderline(true);
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_categorie = new QLineEdit(page_3);
        lineEdit_categorie->setObjectName("lineEdit_categorie");
        lineEdit_categorie->setGeometry(QRect(260, 220, 113, 26));
        lineEdit_categorie->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_10 = new QPushButton(page_3);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(780, 480, 93, 29));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(154, 211, 238);"));
        btmodifier_stock = new QPushButton(page_3);
        btmodifier_stock->setObjectName("btmodifier_stock");
        btmodifier_stock->setGeometry(QRect(1360, 130, 93, 29));
        btmodifier_stock->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 145, 4);"));
        lineEdit_quantite = new QLineEdit(page_3);
        lineEdit_quantite->setObjectName("lineEdit_quantite");
        lineEdit_quantite->setGeometry(QRect(260, 260, 113, 26));
        lineEdit_quantite->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_referencestock = new QLineEdit(page_3);
        lineEdit_referencestock->setObjectName("lineEdit_referencestock");
        lineEdit_referencestock->setGeometry(QRect(260, 180, 113, 26));
        lineEdit_referencestock->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        stackedWidget->addWidget(page_3);
        label_16->raise();
        tableView_2->raise();
        btajouter_stock->raise();
        prixachat->raise();
        btsupprimer_stock->raise();
        dateEdit->raise();
        datelivraison->raise();
        nom->raise();
        pushButton_7->raise();
        pushButton_11->raise();
        pushButton_8->raise();
        quantite->raise();
        prixvente->raise();
        lineEdit_prixvente->raise();
        lineEdit_fournisseur->raise();
        lineEdit_prixachat->raise();
        categorie->raise();
        reference_2->raise();
        label_14->raise();
        catgorie->raise();
        fournisseur->raise();
        lineEdit_IDstock->raise();
        lineEdit_8->raise();
        lineEdit_nomstock->raise();
        retour->raise();
        id->raise();
        label_13->raise();
        lineEdit_categorie->raise();
        pushButton_10->raise();
        btmodifier_stock->raise();
        lineEdit_quantite->raise();
        lineEdit_referencestock->raise();
        menu_employer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(menu_employer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1661, 26));
        menu_employer->setMenuBar(menubar);
        statusbar = new QStatusBar(menu_employer);
        statusbar->setObjectName("statusbar");
        menu_employer->setStatusBar(statusbar);

        retranslateUi(menu_employer);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(menu_employer);
    } // setupUi

    void retranslateUi(QMainWindow *menu_employer)
    {
        menu_employer->setWindowTitle(QCoreApplication::translate("menu_employer", "menu_employer", nullptr));
        label_2->setText(QCoreApplication::translate("menu_employer", " Nom\302\240", nullptr));
        label_6->setText(QCoreApplication::translate("menu_employer", "Date de naissance ", nullptr));
        label_5->setText(QCoreApplication::translate("menu_employer", "Email  ", nullptr));
        pushButton_5->setText(QCoreApplication::translate("menu_employer", " Ajouter ", nullptr));
        label_3->setText(QCoreApplication::translate("menu_employer", "Prenom", nullptr));
        label->setText(QCoreApplication::translate("menu_employer", "ID Employ\303\251  ", nullptr));
        ex->setText(QCoreApplication::translate("menu_employer", " Exporter", nullptr));
        mis->setText(QCoreApplication::translate("menu_employer", " Mise \303\240 jour", nullptr));
        btnSupprimer->setText(QCoreApplication::translate("menu_employer", "supprimer ", nullptr));
        btnModifie->setText(QCoreApplication::translate("menu_employer", " Modifier", nullptr));
        label_4->setText(QCoreApplication::translate("menu_employer", "T\303\251l\303\251phone ", nullptr));
        label_9->setText(QCoreApplication::translate("menu_employer", " Date de recrutement ", nullptr));
        pushButton_9->setText(QCoreApplication::translate("menu_employer", " Trier", nullptr));
        label_8->setText(QCoreApplication::translate("menu_employer", " Rechercher", nullptr));
        label_10->setText(QCoreApplication::translate("menu_employer", " Formulaire Employ\303\251", nullptr));
        label_7->setText(QCoreApplication::translate("menu_employer", " poste", nullptr));
        label_11->setText(QCoreApplication::translate("menu_employer", " salaire", nullptr));
        retour_4->setText(QCoreApplication::translate("menu_employer", "retour", nullptr));
        fourniseur->setText(QCoreApplication::translate("menu_employer", "gestion des fourniseur", nullptr));
        employer->setText(QCoreApplication::translate("menu_employer", "gestion des employers", nullptr));
        appareils->setText(QCoreApplication::translate("menu_employer", "gestion des appareils", nullptr));
        stock->setText(QCoreApplication::translate("menu_employer", "gestion des stock", nullptr));
        label_12->setText(QCoreApplication::translate("menu_employer", "MENU", nullptr));
        client->setText(QCoreApplication::translate("menu_employer", "gestion des client", nullptr));
        btajouter_stock->setText(QCoreApplication::translate("menu_employer", "Ajouter", nullptr));
        prixachat->setText(QCoreApplication::translate("menu_employer", "Prix d'achat", nullptr));
        btsupprimer_stock->setText(QCoreApplication::translate("menu_employer", "Supprimer", nullptr));
        datelivraison->setText(QCoreApplication::translate("menu_employer", "Date de livraison", nullptr));
        nom->setText(QCoreApplication::translate("menu_employer", "Nom", nullptr));
        pushButton_7->setText(QCoreApplication::translate("menu_employer", "Mise \303\240 jour", nullptr));
        pushButton_11->setText(QCoreApplication::translate("menu_employer", "ExporterPDF", nullptr));
        pushButton_8->setText(QCoreApplication::translate("menu_employer", "Rechercher", nullptr));
        quantite->setText(QCoreApplication::translate("menu_employer", "Quantit\303\251", nullptr));
        prixvente->setText(QCoreApplication::translate("menu_employer", "Prix de vente", nullptr));
        categorie->setText(QCoreApplication::translate("menu_employer", "Cat\303\251gorie", nullptr));
        reference_2->setText(QCoreApplication::translate("menu_employer", "Reference", nullptr));
        label_14->setText(QString());
        catgorie->setText(QString());
        fournisseur->setText(QCoreApplication::translate("menu_employer", "Fournisseur", nullptr));
        label_16->setText(QString());
        retour->setText(QCoreApplication::translate("menu_employer", "Retour", nullptr));
        id->setText(QCoreApplication::translate("menu_employer", "ID Pi\303\250ce", nullptr));
        label_13->setText(QCoreApplication::translate("menu_employer", "Ajouter pi\303\250ces", nullptr));
        pushButton_10->setText(QCoreApplication::translate("menu_employer", "Trier", nullptr));
        btmodifier_stock->setText(QCoreApplication::translate("menu_employer", "Modifier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menu_employer: public Ui_menu_employer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_EMPLOYER_H
