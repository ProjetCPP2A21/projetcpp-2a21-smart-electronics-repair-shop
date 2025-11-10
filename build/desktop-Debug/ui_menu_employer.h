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
        stackedWidget->addWidget(page_3);
        menu_employer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(menu_employer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1661, 26));
        menu_employer->setMenuBar(menubar);
        statusbar = new QStatusBar(menu_employer);
        statusbar->setObjectName("statusbar");
        menu_employer->setStatusBar(statusbar);

        retranslateUi(menu_employer);

        stackedWidget->setCurrentIndex(1);


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
    } // retranslateUi

};

namespace Ui {
    class menu_employer: public Ui_menu_employer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_EMPLOYER_H
