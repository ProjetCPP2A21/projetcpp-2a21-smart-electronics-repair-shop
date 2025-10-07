/********************************************************************************
** Form generated from reading UI file 'menu_employer.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu_employer
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_5;
    QTextEdit *textEdit;
    QPushButton *connecter;
    QPushButton *quiter;
    QTextBrowser *textBrowser;
    QStackedWidget *stackedWidget_9;
    QWidget *page_29;
    QLineEdit *IDclient_4;
    QLabel *label_96;
    QLabel *label_97;
    QPushButton *rechercher_4;
    QPushButton *retour_8;
    QLineEdit *Id_4;
    QLabel *label_98;
    QDateEdit *DateN_4;
    QPushButton *PDF_4;
    QPushButton *maj_4;
    QLabel *label_99;
    QPushButton *annuler_4;
    QDateEdit *DateI_4;
    QLabel *label_100;
    QPushButton *Creer_4;
    QLabel *label_101;
    QLabel *label_102;
    QLineEdit *nom_4;
    QLineEdit *prenom_4;
    QLineEdit *tel_4;
    QLineEdit *remarques_4;
    QLabel *label_103;
    QTableWidget *tableWidget_10;
    QPushButton *tri_4;
    QPushButton *Modifier_4;
    QWidget *page_30;
    QWidget *page_6;
    QLabel *label_18;
    QPushButton *retour_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_11;
    QLineEdit *lineEdit_20;
    QPushButton *pushButton_2;
    QLabel *label_11;
    QLineEdit *lineEdit_11;
    QLabel *label_13;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_18;
    QPushButton *pushButton;
    QLineEdit *lineEdit_7;
    QLabel *label_16;
    QLineEdit *lineEdit_17;
    QLabel *label_12;
    QLabel *label_14;
    QPushButton *pushButton_10;
    QLineEdit *lineEdit_13;
    QDateEdit *dateEdit_3;
    QLabel *label_15;
    QLabel *label_21;
    QLineEdit *lineEdit_19;
    QPushButton *pushButton_4;
    QLabel *label_17;
    QLabel *label_19;
    QLabel *label_20;
    QPushButton *pushButton_8;
    QTableWidget *tableWidget_2;
    QLabel *label_30;
    QLineEdit *lineEdit_14;
    QPushButton *pushButton_16;
    QWidget *page;
    QToolButton *employer;
    QPushButton *stock;
    QPushButton *fourniseur;
    QPushButton *client;
    QPushButton *appareils;
    QLabel *label_7;
    QWidget *page_2;
    QStackedWidget *stackedWidget_2;
    QWidget *page_3;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QLabel *label_6;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_5;
    QLabel *label_5;
    QPushButton *pushButton_5;
    QLabel *label_3;
    QLabel *label;
    QDateEdit *dateEdit;
    QPushButton *ex;
    QLabel *mis;
    QPushButton *pushButton_7;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_6;
    QLabel *label_4;
    QLabel *label_9;
    QLineEdit *lineEdit_4;
    QDateEdit *dateEdit_2;
    QPushButton *pushButton_9;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *mis_2;
    QPushButton *retour_4;
    QWidget *page_4;
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
        stackedWidget->setGeometry(QRect(-40, -10, 1661, 881));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 74);"));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        textEdit = new QTextEdit(page_5);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(700, 250, 261, 41));
        connecter = new QPushButton(page_5);
        connecter->setObjectName("connecter");
        connecter->setGeometry(QRect(650, 410, 90, 29));
        quiter = new QPushButton(page_5);
        quiter->setObjectName("quiter");
        quiter->setGeometry(QRect(760, 410, 90, 29));
        textBrowser = new QTextBrowser(page_5);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(470, 250, 181, 41));
        textBrowser->setFrameShape(QFrame::Shape::NoFrame);
        stackedWidget_9 = new QStackedWidget(page_5);
        stackedWidget_9->setObjectName("stackedWidget_9");
        stackedWidget_9->setGeometry(QRect(-20, 10, 1711, 761));
        QPalette palette;
        QBrush brush(QColor(0, 0, 74, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        stackedWidget_9->setPalette(palette);
        stackedWidget_9->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 74);"));
        page_29 = new QWidget();
        page_29->setObjectName("page_29");
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        page_29->setPalette(palette1);
        IDclient_4 = new QLineEdit(page_29);
        IDclient_4->setObjectName("IDclient_4");
        IDclient_4->setGeometry(QRect(350, 120, 151, 28));
        QPalette palette2;
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        IDclient_4->setPalette(palette2);
        IDclient_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_96 = new QLabel(page_29);
        label_96->setObjectName("label_96");
        label_96->setGeometry(QRect(190, 280, 151, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Constantia")});
        font.setPointSize(11);
        font.setItalic(false);
        label_96->setFont(font);
        label_96->setScaledContents(false);
        label_97 = new QLabel(page_29);
        label_97->setObjectName("label_97");
        label_97->setGeometry(QRect(190, 110, 121, 41));
        label_97->setFont(font);
        label_97->setScaledContents(false);
        rechercher_4 = new QPushButton(page_29);
        rechercher_4->setObjectName("rechercher_4");
        rechercher_4->setGeometry(QRect(590, 90, 90, 29));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        QBrush brush3(QColor(31, 155, 93, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush3);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush3);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush3);
        rechercher_4->setPalette(palette3);
        retour_8 = new QPushButton(page_29);
        retour_8->setObjectName("retour_8");
        retour_8->setGeometry(QRect(1330, 580, 90, 29));
        QPalette palette4;
        QBrush brush4(QColor(253, 7, 27, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush4);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush4);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush4);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush3);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush4);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush4);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush4);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush3);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush4);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush4);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush4);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush3);
        retour_8->setPalette(palette4);
        retour_8->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        Id_4 = new QLineEdit(page_29);
        Id_4->setObjectName("Id_4");
        Id_4->setGeometry(QRect(690, 90, 261, 28));
        QPalette palette5;
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        Id_4->setPalette(palette5);
        Id_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_98 = new QLabel(page_29);
        label_98->setObjectName("label_98");
        label_98->setGeometry(QRect(180, 60, 241, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Constantia")});
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(true);
        label_98->setFont(font1);
        label_98->setScaledContents(false);
        DateN_4 = new QDateEdit(page_29);
        DateN_4->setObjectName("DateN_4");
        DateN_4->setGeometry(QRect(360, 290, 141, 29));
        PDF_4 = new QPushButton(page_29);
        PDF_4->setObjectName("PDF_4");
        PDF_4->setGeometry(QRect(1200, 90, 90, 29));
        QPalette palette6;
        QBrush brush5(QColor(253, 145, 4, 255));
        brush5.setStyle(Qt::BrushStyle::SolidPattern);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush5);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush5);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush5);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush3);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush5);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush5);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush5);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush3);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush5);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush5);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush5);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush3);
        PDF_4->setPalette(palette6);
        PDF_4->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 145, 4);"));
        maj_4 = new QPushButton(page_29);
        maj_4->setObjectName("maj_4");
        maj_4->setGeometry(QRect(1090, 90, 90, 29));
        QPalette palette7;
        QBrush brush6(QColor(18, 153, 29, 255));
        brush6.setStyle(Qt::BrushStyle::SolidPattern);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush6);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush6);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush6);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush3);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush6);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush6);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush6);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush3);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush6);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush6);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush6);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush3);
        maj_4->setPalette(palette7);
        maj_4->setStyleSheet(QString::fromUtf8("background-COLOR:rgb(18, 153, 29)"));
        label_99 = new QLabel(page_29);
        label_99->setObjectName("label_99");
        label_99->setGeometry(QRect(190, 230, 151, 41));
        label_99->setFont(font);
        label_99->setScaledContents(false);
        annuler_4 = new QPushButton(page_29);
        annuler_4->setObjectName("annuler_4");
        annuler_4->setGeometry(QRect(290, 550, 90, 29));
        QPalette palette8;
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush4);
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush4);
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush4);
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush3);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush4);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush4);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush4);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush3);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush4);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush4);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush4);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush3);
        annuler_4->setPalette(palette8);
        annuler_4->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        DateI_4 = new QDateEdit(page_29);
        DateI_4->setObjectName("DateI_4");
        DateI_4->setGeometry(QRect(360, 330, 141, 29));
        label_100 = new QLabel(page_29);
        label_100->setObjectName("label_100");
        label_100->setGeometry(QRect(190, 190, 151, 41));
        label_100->setFont(font);
        label_100->setScaledContents(false);
        Creer_4 = new QPushButton(page_29);
        Creer_4->setObjectName("Creer_4");
        Creer_4->setGeometry(QRect(190, 550, 90, 29));
        QPalette palette9;
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush6);
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush6);
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush6);
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush3);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush6);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush6);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush6);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush3);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush6);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush6);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush6);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush3);
        Creer_4->setPalette(palette9);
        Creer_4->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 153, 29);"));
        label_101 = new QLabel(page_29);
        label_101->setObjectName("label_101");
        label_101->setGeometry(QRect(190, 150, 151, 41));
        label_101->setFont(font);
        label_101->setScaledContents(false);
        label_102 = new QLabel(page_29);
        label_102->setObjectName("label_102");
        label_102->setGeometry(QRect(190, 320, 151, 41));
        label_102->setFont(font);
        label_102->setScaledContents(false);
        nom_4 = new QLineEdit(page_29);
        nom_4->setObjectName("nom_4");
        nom_4->setGeometry(QRect(350, 160, 151, 28));
        QPalette palette10;
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette10.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette10.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette10.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        nom_4->setPalette(palette10);
        nom_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        prenom_4 = new QLineEdit(page_29);
        prenom_4->setObjectName("prenom_4");
        prenom_4->setGeometry(QRect(350, 200, 151, 28));
        QPalette palette11;
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette11.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette11.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette11.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        prenom_4->setPalette(palette11);
        prenom_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tel_4 = new QLineEdit(page_29);
        tel_4->setObjectName("tel_4");
        tel_4->setGeometry(QRect(350, 240, 151, 28));
        QPalette palette12;
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette12.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette12.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette12.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        tel_4->setPalette(palette12);
        tel_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        remarques_4 = new QLineEdit(page_29);
        remarques_4->setObjectName("remarques_4");
        remarques_4->setGeometry(QRect(190, 400, 311, 131));
        QPalette palette13;
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette13.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette13.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette13.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        remarques_4->setPalette(palette13);
        remarques_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_103 = new QLabel(page_29);
        label_103->setObjectName("label_103");
        label_103->setGeometry(QRect(190, 360, 241, 41));
        label_103->setFont(font1);
        label_103->setScaledContents(false);
        tableWidget_10 = new QTableWidget(page_29);
        if (tableWidget_10->columnCount() < 7)
            tableWidget_10->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setBackground(QColor(126, 126, 126));
        tableWidget_10->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_10->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_10->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_10->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_10->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_10->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_10->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        if (tableWidget_10->rowCount() < 5)
            tableWidget_10->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_10->setVerticalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_10->setVerticalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_10->setVerticalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_10->setVerticalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_10->setVerticalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_10->setItem(0, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_10->setItem(0, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_10->setItem(0, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_10->setItem(0, 3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_10->setItem(0, 4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_10->setItem(0, 5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_10->setItem(1, 0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_10->setItem(1, 1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_10->setItem(1, 2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_10->setItem(1, 3, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_10->setItem(1, 4, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_10->setItem(1, 5, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_10->setItem(2, 0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_10->setItem(2, 1, __qtablewidgetitem25);
        tableWidget_10->setObjectName("tableWidget_10");
        tableWidget_10->setGeometry(QRect(590, 130, 821, 441));
        QPalette palette14;
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush2);
        QBrush brush7(QColor(120, 120, 120, 255));
        brush7.setStyle(Qt::BrushStyle::SolidPattern);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush7);
        QBrush brush8(QColor(252, 252, 252, 255));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush8);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush1);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush1);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush7);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush7);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush7);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush8);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush1);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush1);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush7);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush7);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush7);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush8);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush1);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush1);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush7);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush7);
        tableWidget_10->setPalette(palette14);
        tableWidget_10->setStyleSheet(QString::fromUtf8("background-color: rgb(120, 120, 120);\n"
"border-top-color: rgb(255, 255, 255);\n"
""));
        tri_4 = new QPushButton(page_29);
        tri_4->setObjectName("tri_4");
        tri_4->setGeometry(QRect(980, 90, 90, 29));
        tri_4->setStyleSheet(QString::fromUtf8("background-color: rgb(154, 211, 238);"));
        Modifier_4 = new QPushButton(page_29);
        Modifier_4->setObjectName("Modifier_4");
        Modifier_4->setGeometry(QRect(1310, 90, 90, 29));
        QPalette palette15;
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush4);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush4);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush4);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush3);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush4);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush4);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush4);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush3);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush4);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush4);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush4);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush3);
        Modifier_4->setPalette(palette15);
        Modifier_4->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        stackedWidget_9->addWidget(page_29);
        page_30 = new QWidget();
        page_30->setObjectName("page_30");
        stackedWidget_9->addWidget(page_30);
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        label_18 = new QLabel(page_6);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(140, 70, 141, 20));
        label_18->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        retour_5 = new QPushButton(page_6);
        retour_5->setObjectName("retour_5");
        retour_5->setGeometry(QRect(1430, 660, 93, 29));
        retour_5->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 145, 4);"));
        pushButton_3 = new QPushButton(page_6);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(1270, 210, 93, 29));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 145, 4);"));
        pushButton_11 = new QPushButton(page_6);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(230, 550, 93, 29));
        pushButton_11->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        lineEdit_20 = new QLineEdit(page_6);
        lineEdit_20->setObjectName("lineEdit_20");
        lineEdit_20->setGeometry(QRect(220, 490, 113, 26));
        lineEdit_20->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_2 = new QPushButton(page_6);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(1380, 210, 93, 29));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        label_11 = new QLabel(page_6);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(90, 330, 71, 20));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_11 = new QLineEdit(page_6);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(220, 130, 113, 26));
        lineEdit_11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_13 = new QLabel(page_6);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(90, 450, 101, 20));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_12 = new QLineEdit(page_6);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(220, 210, 113, 26));
        lineEdit_12->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_16 = new QLineEdit(page_6);
        lineEdit_16->setObjectName("lineEdit_16");
        lineEdit_16->setGeometry(QRect(220, 330, 113, 26));
        lineEdit_16->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_15 = new QLineEdit(page_6);
        lineEdit_15->setObjectName("lineEdit_15");
        lineEdit_15->setGeometry(QRect(220, 290, 113, 26));
        lineEdit_15->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_18 = new QLineEdit(page_6);
        lineEdit_18->setObjectName("lineEdit_18");
        lineEdit_18->setGeometry(QRect(220, 410, 113, 26));
        lineEdit_18->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(page_6);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(500, 620, 93, 29));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 153, 45);"));
        lineEdit_7 = new QLineEdit(page_6);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(620, 210, 221, 26));
        label_16 = new QLabel(page_6);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(90, 490, 111, 20));
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_17 = new QLineEdit(page_6);
        lineEdit_17->setObjectName("lineEdit_17");
        lineEdit_17->setGeometry(QRect(220, 370, 113, 26));
        lineEdit_17->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_12 = new QLabel(page_6);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(90, 210, 71, 20));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_14 = new QLabel(page_6);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(1210, 50, 121, 111));
        pushButton_10 = new QPushButton(page_6);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(480, 210, 93, 29));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 203, 203);"));
        lineEdit_13 = new QLineEdit(page_6);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(220, 170, 113, 26));
        lineEdit_13->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateEdit_3 = new QDateEdit(page_6);
        dateEdit_3->setObjectName("dateEdit_3");
        dateEdit_3->setGeometry(QRect(220, 490, 110, 26));
        label_15 = new QLabel(page_6);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(90, 290, 71, 20));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_21 = new QLabel(page_6);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(90, 410, 101, 20));
        label_21->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_19 = new QLineEdit(page_6);
        lineEdit_19->setObjectName("lineEdit_19");
        lineEdit_19->setGeometry(QRect(220, 450, 113, 26));
        lineEdit_19->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_4 = new QPushButton(page_6);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(120, 550, 93, 29));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 153, 45);"));
        label_17 = new QLabel(page_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(90, 370, 91, 20));
        label_17->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_19 = new QLabel(page_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(90, 250, 71, 20));
        label_19->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_20 = new QLabel(page_6);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(90, 170, 71, 20));
        label_20->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        pushButton_8 = new QPushButton(page_6);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(1420, 620, 101, 29));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 203, 203);"));
        tableWidget_2 = new QTableWidget(page_6);
        if (tableWidget_2->columnCount() < 9)
            tableWidget_2->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(7, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(8, __qtablewidgetitem34);
        if (tableWidget_2->rowCount() < 8)
            tableWidget_2->setRowCount(8);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(470, 260, 1081, 331));
        tableWidget_2->setRowCount(8);
        tableWidget_2->setColumnCount(9);
        tableWidget_2->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget_2->verticalHeader()->setVisible(false);
        tableWidget_2->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        label_30 = new QLabel(page_6);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(90, 130, 71, 20));
        label_30->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_14 = new QLineEdit(page_6);
        lineEdit_14->setObjectName("lineEdit_14");
        lineEdit_14->setGeometry(QRect(220, 250, 113, 26));
        lineEdit_14->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_16 = new QPushButton(page_6);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(620, 620, 93, 29));
        pushButton_16->setStyleSheet(QString::fromUtf8("background-color: rgb(154 , 211 , 238);"));
        stackedWidget->addWidget(page_6);
        page = new QWidget();
        page->setObjectName("page");
        employer = new QToolButton(page);
        employer->setObjectName("employer");
        employer->setGeometry(QRect(570, 278, 511, 51));
        employer->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        stock = new QPushButton(page);
        stock->setObjectName("stock");
        stock->setGeometry(QRect(570, 348, 511, 41));
        stock->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        fourniseur = new QPushButton(page);
        fourniseur->setObjectName("fourniseur");
        fourniseur->setGeometry(QRect(570, 468, 511, 41));
        fourniseur->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        client = new QPushButton(page);
        client->setObjectName("client");
        client->setGeometry(QRect(570, 408, 511, 41));
        client->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        appareils = new QPushButton(page);
        appareils->setObjectName("appareils");
        appareils->setGeometry(QRect(570, 530, 511, 41));
        appareils->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"font: 700 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(750, 190, 191, 61));
        label_7->setStyleSheet(QString::fromUtf8("font: 700 36pt \"Segoe UI\";"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget_2 = new QStackedWidget(page_2);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setGeometry(QRect(0, 0, 1671, 881));
        stackedWidget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 74);"));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        tableWidget = new QTableWidget(page_3);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QBrush brush9(QColor(255, 255, 255, 255));
        brush9.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        __qtablewidgetitem35->setBackground(QColor(120, 120, 120));
        __qtablewidgetitem35->setForeground(brush9);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem35);
        QBrush brush10(QColor(255, 255, 255, 255));
        brush10.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        __qtablewidgetitem36->setBackground(QColor(120, 120, 120));
        __qtablewidgetitem36->setForeground(brush10);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem36);
        QBrush brush11(QColor(255, 255, 255, 255));
        brush11.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        __qtablewidgetitem37->setBackground(QColor(120, 120, 120));
        __qtablewidgetitem37->setForeground(brush11);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem37);
        QBrush brush12(QColor(255, 255, 255, 255));
        brush12.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        __qtablewidgetitem38->setBackground(QColor(120, 120, 120));
        __qtablewidgetitem38->setForeground(brush12);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        __qtablewidgetitem39->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem40);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        __qtablewidgetitem41->setBackground(QColor(255, 255, 255));
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem41);
        QBrush brush13(QColor(255, 255, 255, 255));
        brush13.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        __qtablewidgetitem42->setForeground(brush13);
        tableWidget->setItem(3, 0, __qtablewidgetitem42);
        QBrush brush14(QColor(255, 255, 255, 255));
        brush14.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        __qtablewidgetitem43->setBackground(brush14);
        tableWidget->setItem(4, 2, __qtablewidgetitem43);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(400, 180, 941, 281));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(120, 120, 120);\n"
"background-color: rgb(120, 120, 120);"));
        label_2 = new QLabel(page_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 240, 63, 20));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        label_6 = new QLabel(page_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 530, 181, 41));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_3 = new QLineEdit(page_3);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(150, 300, 113, 26));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_6 = new QLineEdit(page_3);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(530, 130, 181, 31));
        lineEdit_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit = new QLineEdit(page_3);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(140, 170, 113, 26));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_5 = new QLineEdit(page_3);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(160, 450, 113, 26));
        lineEdit_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        label_5 = new QLabel(page_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 450, 91, 41));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        pushButton_5 = new QPushButton(page_3);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 700, 141, 31));
        pushButton_5->setStyleSheet(QString::fromUtf8(" background-color: rgb(18, 153, 29);"));
        label_3 = new QLabel(page_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 300, 71, 20));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        label = new QLabel(page_3);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 160, 101, 51));
        QPalette palette16;
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush1);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush1);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        QBrush brush15(QColor(255, 255, 255, 128));
        brush15.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush15);
#endif
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush1);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush1);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush15);
#endif
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush1);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush1);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush15);
#endif
        label->setPalette(palette16);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        dateEdit = new QDateEdit(page_3);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(160, 540, 110, 26));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        ex = new QPushButton(page_3);
        ex->setObjectName("ex");
        ex->setGeometry(QRect(330, 700, 141, 31));
        ex->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(253, 154, 4);"));
        mis = new QLabel(page_3);
        mis->setObjectName("mis");
        mis->setGeometry(QRect(900, 130, 111, 31));
        mis->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);\n"
"background-color: rgb(18, 153, 29);\n"
""));
        pushButton_7 = new QPushButton(page_3);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(170, 700, 141, 31));
        pushButton_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
" \n"
"background-color: rgb(253, 7, 27);"));
        lineEdit_2 = new QLineEdit(page_3);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(140, 240, 113, 26));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_6 = new QPushButton(page_3);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(1050, 130, 121, 31));
        pushButton_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
" background-color: rgb(253, 154, 4);"));
        label_4 = new QLabel(page_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 370, 91, 41));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_9 = new QLabel(page_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 640, 181, 20));
        label_9->setStyleSheet(QString::fromUtf8("font: 10pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        lineEdit_4 = new QLineEdit(page_3);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(150, 370, 113, 26));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        dateEdit_2 = new QDateEdit(page_3);
        dateEdit_2->setObjectName("dateEdit_2");
        dateEdit_2->setGeometry(QRect(200, 640, 110, 26));
        dateEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        pushButton_9 = new QPushButton(page_3);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(740, 130, 131, 29));
        QPalette palette17;
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush1);
        QBrush brush16(QColor(154, 211, 238, 255));
        brush16.setStyle(Qt::BrushStyle::SolidPattern);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush16);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush1);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush16);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush16);
        QBrush brush17(QColor(39, 191, 115, 255));
        brush17.setStyle(Qt::BrushStyle::SolidPattern);
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush17);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush15);
#endif
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush1);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush16);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush1);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush16);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush16);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush17);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush15);
#endif
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush16);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush1);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush1);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush16);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush16);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush17);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush15);
#endif
        pushButton_9->setPalette(palette17);
        pushButton_9->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(154, 211, 238);"));
        label_8 = new QLabel(page_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(400, 130, 111, 31));
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 91);\n"
" \n"
""));
        label_10 = new QLabel(page_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 100, 181, 51));
        QPalette palette18;
        palette18.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush1);
        palette18.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette18.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush1);
        palette18.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        palette18.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette18.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette18.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush15);
#endif
        palette18.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush1);
        palette18.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette18.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush1);
        palette18.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        palette18.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette18.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette18.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush15);
#endif
        palette18.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        palette18.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette18.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush1);
        palette18.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush1);
        palette18.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette18.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette18.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush15);
#endif
        label_10->setPalette(palette18);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: italic 9pt \"Segoe UI\";"));
        mis_2 = new QLabel(page_3);
        mis_2->setObjectName("mis_2");
        mis_2->setGeometry(QRect(1200, 130, 111, 31));
        mis_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(253, 7, 27);\n"
""));
        retour_4 = new QPushButton(page_3);
        retour_4->setObjectName("retour_4");
        retour_4->setGeometry(QRect(1050, 480, 121, 31));
        retour_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
" background-color: rgb(253, 154, 4);"));
        stackedWidget_2->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        stackedWidget_2->addWidget(page_4);
        stackedWidget->addWidget(page_2);
        menu_employer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(menu_employer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1661, 25));
        menu_employer->setMenuBar(menubar);
        statusbar = new QStatusBar(menu_employer);
        statusbar->setObjectName("statusbar");
        menu_employer->setStatusBar(statusbar);

        retranslateUi(menu_employer);

        stackedWidget_9->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(menu_employer);
    } // setupUi

    void retranslateUi(QMainWindow *menu_employer)
    {
        menu_employer->setWindowTitle(QCoreApplication::translate("menu_employer", "menu_employer", nullptr));
        connecter->setText(QCoreApplication::translate("menu_employer", "connecter", nullptr));
        quiter->setText(QCoreApplication::translate("menu_employer", "quiter", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("menu_employer", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:700;\">E-mail</span></p></body></html>", nullptr));
        IDclient_4->setText(QString());
        label_96->setText(QCoreApplication::translate("menu_employer", "Date de naissance", nullptr));
        label_97->setText(QCoreApplication::translate("menu_employer", "ID_Client", nullptr));
        rechercher_4->setText(QCoreApplication::translate("menu_employer", "Rechercher", nullptr));
        retour_8->setText(QCoreApplication::translate("menu_employer", "Retour", nullptr));
        Id_4->setText(QCoreApplication::translate("menu_employer", "rechercher par ID", nullptr));
        label_98->setText(QCoreApplication::translate("menu_employer", "Formulaire client ", nullptr));
        PDF_4->setText(QCoreApplication::translate("menu_employer", "exporter PDF", nullptr));
        maj_4->setText(QCoreApplication::translate("menu_employer", "Mise \303\240 jour", nullptr));
        label_99->setText(QCoreApplication::translate("menu_employer", "T\303\251l\303\251phone", nullptr));
        annuler_4->setText(QCoreApplication::translate("menu_employer", "Annuler", nullptr));
        label_100->setText(QCoreApplication::translate("menu_employer", "Prenom", nullptr));
        Creer_4->setText(QCoreApplication::translate("menu_employer", "Cr\303\251er", nullptr));
        label_101->setText(QCoreApplication::translate("menu_employer", "Nom", nullptr));
        label_102->setText(QCoreApplication::translate("menu_employer", "Date d'inscription ", nullptr));
        nom_4->setText(QString());
        prenom_4->setText(QString());
        tel_4->setText(QString());
        remarques_4->setText(QString());
        label_103->setText(QCoreApplication::translate("menu_employer", "Remarques:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_10->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("menu_employer", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_10->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("menu_employer", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_10->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("menu_employer", " T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_10->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("menu_employer", "Date de naissance", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_10->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("menu_employer", "Date d'inscription", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_10->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("menu_employer", "ID_Client", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_10->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("menu_employer", "Remarques", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_10->verticalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("menu_employer", "CLIENT1", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_10->verticalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("menu_employer", "CLIENT2", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_10->verticalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("menu_employer", "CLIENT3", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_10->verticalHeaderItem(3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("menu_employer", "CLIENT4", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_10->verticalHeaderItem(4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("menu_employer", "CLIENTN", nullptr));

        const bool __sortingEnabled = tableWidget_10->isSortingEnabled();
        tableWidget_10->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_10->item(0, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("menu_employer", "Ben guiza", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_10->item(0, 1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("menu_employer", "Sarah", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_10->item(0, 2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("menu_employer", "94...", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_10->item(0, 3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("menu_employer", "11/05/2005", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_10->item(0, 4);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("menu_employer", "....", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_10->item(0, 5);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("menu_employer", "241...", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_10->item(1, 0);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("menu_employer", "Oueslati", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_10->item(1, 1);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("menu_employer", "Selima", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_10->item(1, 2);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("menu_employer", "98...", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_10->item(1, 3);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("menu_employer", "08/10/2005", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_10->item(1, 4);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("menu_employer", "...", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_10->item(1, 5);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("menu_employer", "231..", nullptr));
        tableWidget_10->setSortingEnabled(__sortingEnabled);

        tri_4->setText(QCoreApplication::translate("menu_employer", "Trier", nullptr));
        Modifier_4->setText(QCoreApplication::translate("menu_employer", "Modifier", nullptr));
        label_18->setText(QCoreApplication::translate("menu_employer", "Ajouter une pi\303\251ce", nullptr));
        retour_5->setText(QCoreApplication::translate("menu_employer", "retour", nullptr));
        pushButton_3->setText(QCoreApplication::translate("menu_employer", "Modifier", nullptr));
        pushButton_11->setText(QCoreApplication::translate("menu_employer", "Supprimer", nullptr));
        pushButton_2->setText(QCoreApplication::translate("menu_employer", "Supprimer", nullptr));
        label_11->setText(QCoreApplication::translate("menu_employer", "Quantit\303\251", nullptr));
        label_13->setText(QCoreApplication::translate("menu_employer", "Fournisseur", nullptr));
        pushButton->setText(QCoreApplication::translate("menu_employer", "Mise \303\240 jour", nullptr));
        label_16->setText(QCoreApplication::translate("menu_employer", "Date de livraison", nullptr));
        label_12->setText(QCoreApplication::translate("menu_employer", "ID Pi\303\250ce", nullptr));
        label_14->setText(QString());
        pushButton_10->setText(QCoreApplication::translate("menu_employer", "Rechercher", nullptr));
        label_15->setText(QCoreApplication::translate("menu_employer", "Cat\303\251gorie ", nullptr));
        label_21->setText(QCoreApplication::translate("menu_employer", "Prix de vente", nullptr));
        pushButton_4->setText(QCoreApplication::translate("menu_employer", "Ajouter", nullptr));
        label_17->setText(QCoreApplication::translate("menu_employer", "Prix d'achat", nullptr));
        label_19->setText(QCoreApplication::translate("menu_employer", "R\303\250f\303\250rence", nullptr));
        label_20->setText(QCoreApplication::translate("menu_employer", "Nom", nullptr));
        pushButton_8->setText(QCoreApplication::translate("menu_employer", "Exporter PDF", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("menu_employer", "ID Pi\303\250ce", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("menu_employer", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("menu_employer", "R\303\251f\303\251rence", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("menu_employer", "Cat\303\251gorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("menu_employer", "Quanti\303\251 ", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("menu_employer", "Prix d'achat", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("menu_employer", "prix de vente", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_2->horizontalHeaderItem(7);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("menu_employer", "Fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_2->horizontalHeaderItem(8);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("menu_employer", "Date de livraison", nullptr));
        label_30->setText(QCoreApplication::translate("menu_employer", "ID Pi\303\250ce", nullptr));
        pushButton_16->setText(QCoreApplication::translate("menu_employer", "trier", nullptr));
        employer->setText(QCoreApplication::translate("menu_employer", "gestion des employers", nullptr));
        stock->setText(QCoreApplication::translate("menu_employer", "gestion des stock", nullptr));
        fourniseur->setText(QCoreApplication::translate("menu_employer", "gestion des fourniseur", nullptr));
        client->setText(QCoreApplication::translate("menu_employer", "gestion des client", nullptr));
        appareils->setText(QCoreApplication::translate("menu_employer", "gestion des appareils", nullptr));
        label_7->setText(QCoreApplication::translate("menu_employer", "MENU", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("menu_employer", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("menu_employer", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("menu_employer", " Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("menu_employer", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("menu_employer", " Tel", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("menu_employer", " Date de naissance", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("menu_employer", "1", nullptr));

        const bool __sortingEnabled1 = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled1);

        label_2->setText(QCoreApplication::translate("menu_employer", " Nom\302\240", nullptr));
        label_6->setText(QCoreApplication::translate("menu_employer", "Date de naissance ", nullptr));
        label_5->setText(QCoreApplication::translate("menu_employer", "Email  ", nullptr));
        pushButton_5->setText(QCoreApplication::translate("menu_employer", " Ajouter ", nullptr));
        label_3->setText(QCoreApplication::translate("menu_employer", "Prenom", nullptr));
        label->setText(QCoreApplication::translate("menu_employer", "ID Employ\303\251  ", nullptr));
        ex->setText(QCoreApplication::translate("menu_employer", " Exporter", nullptr));
        mis->setText(QCoreApplication::translate("menu_employer", " Mise \303\240 jour", nullptr));
        pushButton_7->setText(QCoreApplication::translate("menu_employer", "supprimer ", nullptr));
        pushButton_6->setText(QCoreApplication::translate("menu_employer", " Modifier", nullptr));
        label_4->setText(QCoreApplication::translate("menu_employer", "T\303\251l\303\251phone ", nullptr));
        label_9->setText(QCoreApplication::translate("menu_employer", " Date de recrutement ", nullptr));
        pushButton_9->setText(QCoreApplication::translate("menu_employer", " Trier", nullptr));
        label_8->setText(QCoreApplication::translate("menu_employer", " Rechercher", nullptr));
        label_10->setText(QCoreApplication::translate("menu_employer", " Formulaire Employ\303\251", nullptr));
        mis_2->setText(QCoreApplication::translate("menu_employer", "     Retour", nullptr));
        retour_4->setText(QCoreApplication::translate("menu_employer", "retour", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menu_employer: public Ui_menu_employer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_EMPLOYER_H
