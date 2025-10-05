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
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1587, 662);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 74);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tableWidget = new QTableWidget(centralwidget);
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
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(470, 200, 1101, 321));
        QFont font;
        font.setFamilies({QString::fromUtf8("PT Simple Ruled")});
        font.setBold(true);
        tableWidget->setFont(font);
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 113);"));
        tableWidget->setLineWidth(9);
        tableWidget->setRowCount(6);
        tableWidget->setColumnCount(9);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(40);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(50);
        tableWidget_2 = new QTableWidget(centralwidget);
        if (tableWidget_2->columnCount() < 2)
            tableWidget_2->setColumnCount(2);
        if (tableWidget_2->rowCount() < 9)
            tableWidget_2->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setItem(2, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_2->setItem(3, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_2->setItem(4, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_2->setItem(5, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_2->setItem(6, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_2->setItem(7, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_2->setItem(8, 0, __qtablewidgetitem17);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(20, 70, 411, 341));
        tableWidget_2->setFont(font);
        tableWidget_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 113);\n"
"background-color: rgb(255, 255, 255);"));
        tableWidget_2->setRowCount(9);
        tableWidget_2->setColumnCount(2);
        tableWidget_2->horizontalHeader()->setVisible(false);
        tableWidget_2->horizontalHeader()->setDefaultSectionSize(200);
        tableWidget_2->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget_2->horizontalHeader()->setStretchLastSection(true);
        tableWidget_2->verticalHeader()->setVisible(false);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1290, 140, 141, 41));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(660, 560, 141, 41));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(830, 560, 141, 41));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(200, 450, 151, 41));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(660, 140, 591, 41));
        lineEdit->setToolTipDuration(1);
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1587, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = tableWidget->item(0, 0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID Pi\303\250ce ", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->item(0, 1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "    Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->item(0, 2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "    R\303\251f\303\251rence", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "      Quantit\303\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "   Prix d'achat ", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Prix de vente", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Date de livraison", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);


        const bool __sortingEnabled1 = tableWidget_2->isSortingEnabled();
        tableWidget_2->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->item(0, 0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "ID Pi\303\250ce", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->item(1, 0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->item(2, 0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "R\303\251f\303\251rence", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_2->item(3, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_2->item(4, 0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Quantit\303\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_2->item(5, 0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Prix d'achat", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_2->item(6, 0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Prix de vente", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_2->item(7, 0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_2->item(8, 0);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Date de livraison", nullptr));
        tableWidget_2->setSortingEnabled(__sortingEnabled1);

        pushButton->setText(QCoreApplication::translate("MainWindow", "rechercher", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "Rechercher pi\303\250ce....", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
