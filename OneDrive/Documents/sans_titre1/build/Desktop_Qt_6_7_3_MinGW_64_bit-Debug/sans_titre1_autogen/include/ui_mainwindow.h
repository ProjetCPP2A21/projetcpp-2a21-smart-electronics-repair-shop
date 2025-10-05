/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionHOME;
    QAction *actionCLIENTS;
    QAction *actionEmploy_s;
    QAction *actionStock;
    QAction *actionAppareils;
    QAction *actionID;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLineEdit *lineEdit_9;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_3;
    QLabel *label_2;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_18;
    QDateEdit *dateEdit;
    QPushButton *pushButton_8;
    QPushButton *pushButton_4;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QWidget *page_2;
    QMenuBar *menubar;
    QMenu *menuMENU;
    QMenu *menuStatistique;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1532, 675);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 74);"));
        actionHOME = new QAction(MainWindow);
        actionHOME->setObjectName("actionHOME");
        actionCLIENTS = new QAction(MainWindow);
        actionCLIENTS->setObjectName("actionCLIENTS");
        actionEmploy_s = new QAction(MainWindow);
        actionEmploy_s->setObjectName("actionEmploy_s");
        actionStock = new QAction(MainWindow);
        actionStock->setObjectName("actionStock");
        actionAppareils = new QAction(MainWindow);
        actionAppareils->setObjectName("actionAppareils");
        actionID = new QAction(MainWindow);
        actionID->setObjectName("actionID");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1581, 621));
        stackedWidget->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(0, 0, 209);"));
        page = new QWidget();
        page->setObjectName("page");
        lineEdit_9 = new QLineEdit(page);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(1580, 220, 131, 51));
        lineEdit_9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        pushButton_5 = new QPushButton(page);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(450, 60, 161, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(153, 153, 153);"));
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(1360, 80, 90, 31));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 40, 201, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Constantia")});
        font.setPointSize(14);
        font.setBold(false);
        font.setUnderline(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        pushButton_3 = new QPushButton(page);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(1650, 450, 131, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(153, 153, 153);"));
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 110, 71, 20));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_10 = new QLineEdit(page);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(1700, 220, 131, 51));
        lineEdit_10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        lineEdit = new QLineEdit(page);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(620, 60, 291, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        tableWidget = new QTableWidget(page);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(0, 5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(0, 7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(0, 8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(1, 3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(1, 4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(1, 5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(1, 6, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(1, 7, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(1, 8, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(2, 3, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(2, 4, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(2, 5, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setItem(2, 6, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(2, 7, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setItem(2, 8, __qtablewidgetitem26);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(360, 130, 1131, 311));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("PT Simple Ruled")});
        font1.setBold(true);
        tableWidget->setFont(font1);
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 74);\n"
"background-color: rgb(139, 139, 139);"));
        tableWidget->setRowCount(6);
        tableWidget->setColumnCount(9);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(125);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(50);
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 150, 71, 20));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 190, 71, 20));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_5 = new QLabel(page);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 230, 71, 20));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 270, 71, 20));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(30, 310, 81, 20));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_8 = new QLabel(page);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 350, 91, 20));
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_9 = new QLabel(page);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 390, 91, 20));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_10 = new QLabel(page);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(30, 430, 111, 20));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_11 = new QLineEdit(page);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(150, 110, 113, 26));
        lineEdit_11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_12 = new QLineEdit(page);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(150, 150, 113, 26));
        lineEdit_12->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_13 = new QLineEdit(page);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(150, 190, 113, 26));
        lineEdit_13->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_14 = new QLineEdit(page);
        lineEdit_14->setObjectName("lineEdit_14");
        lineEdit_14->setGeometry(QRect(150, 230, 113, 26));
        lineEdit_14->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_15 = new QLineEdit(page);
        lineEdit_15->setObjectName("lineEdit_15");
        lineEdit_15->setGeometry(QRect(150, 270, 113, 26));
        lineEdit_15->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_16 = new QLineEdit(page);
        lineEdit_16->setObjectName("lineEdit_16");
        lineEdit_16->setGeometry(QRect(150, 310, 113, 26));
        lineEdit_16->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_17 = new QLineEdit(page);
        lineEdit_17->setObjectName("lineEdit_17");
        lineEdit_17->setGeometry(QRect(150, 350, 113, 26));
        lineEdit_17->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_18 = new QLineEdit(page);
        lineEdit_18->setObjectName("lineEdit_18");
        lineEdit_18->setGeometry(QRect(150, 390, 113, 26));
        lineEdit_18->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateEdit = new QDateEdit(page);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(150, 430, 110, 26));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_8 = new QPushButton(page);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(160, 510, 90, 31));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1150, 80, 90, 31));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 153, 45);"));
        pushButton_9 = new QPushButton(page);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(1260, 80, 91, 31));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 145, 4);"));
        pushButton_10 = new QPushButton(page);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(50, 510, 90, 31));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 153, 45);"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1532, 26));
        QPalette palette;
        QBrush brush(QColor(0, 0, 74, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        menubar->setPalette(palette);
        menuMENU = new QMenu(menubar);
        menuMENU->setObjectName("menuMENU");
        menuStatistique = new QMenu(menubar);
        menuStatistique->setObjectName("menuStatistique");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMENU->menuAction());
        menubar->addAction(menuStatistique->menuAction());
        menuMENU->addAction(actionHOME);
        menuMENU->addAction(actionCLIENTS);
        menuMENU->addAction(actionEmploy_s);
        menuMENU->addAction(actionStock);
        menuMENU->addAction(actionAppareils);
        menuStatistique->addAction(actionID);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionHOME->setText(QCoreApplication::translate("MainWindow", "HOME", nullptr));
        actionCLIENTS->setText(QCoreApplication::translate("MainWindow", "Clients", nullptr));
        actionEmploy_s->setText(QCoreApplication::translate("MainWindow", "Employ\303\251s", nullptr));
        actionStock->setText(QCoreApplication::translate("MainWindow", "Stock", nullptr));
        actionAppareils->setText(QCoreApplication::translate("MainWindow", "Appareils", nullptr));
        actionID->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        lineEdit_9->setText(QCoreApplication::translate("MainWindow", "Electroplus", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Ajouter une pi\303\250ce", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ID Pi\303\250ce", nullptr));
        lineEdit_10->setText(QCoreApplication::translate("MainWindow", "15/6/2025", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "Rechercher pi\303\250ce...", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = tableWidget->item(0, 0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "    ID Pi\303\250ce", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->item(0, 1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "        Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->item(0, 2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "    R\303\251f\303\251rence", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "     Cat\303\251gorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "     Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "   Prix d'achat", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "  Prix de vente", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "   Fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Date de livraison", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(1, 0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "  001", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(1, 1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "R\303\251sistance SMD", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(1, 2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "      R-100S", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(1, 3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Composant electronique", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(1, 4);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(1, 5);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "1.50 TND", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(1, 6);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "3.00 TND", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(1, 7);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Electroplus", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(1, 8);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "   15/8/2025", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(2, 0);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "  002", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(2, 1);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Condensateur 10\302\265F", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(2, 2);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "      R-100R", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(2, 3);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "Composant electronique", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(2, 4);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(2, 5);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "2.00 TND", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(2, 6);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "4.00 TND", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(2, 7);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Electroplus", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->item(2, 8);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "15/6/2025", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        label_3->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "R\303\251f\303\251rence", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Prix d'achat", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Prix de vente", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Date de livraison", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Mise \303\240 jour", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        menuMENU->setTitle(QCoreApplication::translate("MainWindow", "MENU", nullptr));
        menuStatistique->setTitle(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
