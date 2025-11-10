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
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu_employer
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
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
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setBackground(QColor(120, 120, 120));
        __qtablewidgetitem->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setBackground(QColor(120, 120, 120));
        __qtablewidgetitem1->setForeground(brush1);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setBackground(QColor(120, 120, 120));
        __qtablewidgetitem2->setForeground(brush2);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QBrush brush3(QColor(255, 255, 255, 255));
        brush3.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setBackground(QColor(120, 120, 120));
        __qtablewidgetitem3->setForeground(brush3);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setBackground(QColor(255, 255, 255));
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QBrush brush4(QColor(255, 255, 255, 255));
        brush4.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setForeground(brush4);
        tableWidget->setItem(3, 0, __qtablewidgetitem7);
        QBrush brush5(QColor(255, 255, 255, 255));
        brush5.setStyle(Qt::BrushStyle::NoBrush);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setBackground(brush5);
        tableWidget->setItem(4, 2, __qtablewidgetitem8);
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
        QPalette palette;
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush6);
        QBrush brush7(QColor(0, 0, 74, 255));
        brush7.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush7);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush6);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush6);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush7);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush7);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush7);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush7);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush7);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush7);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush8);
#endif
        label->setPalette(palette);
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
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush6);
        QBrush brush9(QColor(154, 211, 238, 255));
        brush9.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush9);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush6);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush6);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush9);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush9);
        QBrush brush10(QColor(39, 191, 115, 255));
        brush10.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush10);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush8);
#endif
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush6);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush9);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush6);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush6);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush9);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush9);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush10);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush8);
#endif
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush6);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush9);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush6);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush6);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush9);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush9);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush10);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush8);
#endif
        pushButton_9->setPalette(palette1);
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
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush6);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush7);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush6);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush6);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush7);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush8);
#endif
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush6);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush7);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush6);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush6);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush7);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush8);
#endif
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush6);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush7);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush6);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush6);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush7);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush8);
#endif
        label_10->setPalette(palette2);
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

        QMetaObject::connectSlotsByName(menu_employer);
    } // setupUi

    void retranslateUi(QMainWindow *menu_employer)
    {
        menu_employer->setWindowTitle(QCoreApplication::translate("menu_employer", "menu_employer", nullptr));
        employer->setText(QCoreApplication::translate("menu_employer", "gestion des employers", nullptr));
        stock->setText(QCoreApplication::translate("menu_employer", "gestion des stock", nullptr));
        fourniseur->setText(QCoreApplication::translate("menu_employer", "gestion des fourniseur", nullptr));
        client->setText(QCoreApplication::translate("menu_employer", "gestion des client", nullptr));
        appareils->setText(QCoreApplication::translate("menu_employer", "gestion des appareils", nullptr));
        label_7->setText(QCoreApplication::translate("menu_employer", "MENU", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("menu_employer", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("menu_employer", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("menu_employer", " Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("menu_employer", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("menu_employer", " Tel", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("menu_employer", " Date de naissance", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("menu_employer", "1", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

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
