/********************************************************************************
** Form generated from reading UI file 'nstock.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NSTOCK_H
#define UI_NSTOCK_H

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

class Ui_Nstock
{
public:
    QAction *actionID;
    QAction *actionEmployer;
    QAction *actionSuivi_du_stock_en_temps_r_el;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLineEdit *lineEdit_14;
    QPushButton *Supprimer;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit;
    QPushButton *Miseajour;
    QPushButton *Trier;
    QLabel *label_3;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineEdit_15;
    QLabel *label_2;
    QLabel *label_6;
    QPushButton *ExporterPDF;
    QLineEdit *lineEdit_11;
    QPushButton *Modifier;
    QLineEdit *lineEdit_12;
    QLabel *label_12;
    QLineEdit *lineEdit_19;
    QLabel *label_4;
    QLineEdit *lineEdit_16;
    QLabel *label_7;
    QLineEdit *lineEdit_18;
    QPushButton *Supprimer_2;
    QTableWidget *tableWidget;
    QLabel *label;
    QPushButton *Rechercher;
    QDateEdit *dateEdit_3;
    QLabel *label_5;
    QPushButton *Ajouter;
    QLineEdit *lineEdit_17;
    QPushButton *Rechercher_2;
    QWidget *page_2;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QMenu *menuStatistique;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Nstock)
    {
        if (Nstock->objectName().isEmpty())
            Nstock->setObjectName("Nstock");
        Nstock->resize(1544, 709);
        actionID = new QAction(Nstock);
        actionID->setObjectName("actionID");
        actionEmployer = new QAction(Nstock);
        actionEmployer->setObjectName("actionEmployer");
        actionSuivi_du_stock_en_temps_r_el = new QAction(Nstock);
        actionSuivi_du_stock_en_temps_r_el->setObjectName("actionSuivi_du_stock_en_temps_r_el");
        centralwidget = new QWidget(Nstock);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1571, 651));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 74);"));
        page = new QWidget();
        page->setObjectName("page");
        lineEdit_14 = new QLineEdit(page);
        lineEdit_14->setObjectName("lineEdit_14");
        lineEdit_14->setGeometry(QRect(270, 200, 113, 26));
        lineEdit_14->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Supprimer = new QPushButton(page);
        Supprimer->setObjectName("Supprimer");
        Supprimer->setGeometry(QRect(1170, 160, 93, 29));
        Supprimer->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        lineEdit_13 = new QLineEdit(page);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(270, 120, 113, 26));
        lineEdit_13->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit = new QLineEdit(page);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(630, 160, 221, 26));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Miseajour = new QPushButton(page);
        Miseajour->setObjectName("Miseajour");
        Miseajour->setGeometry(QRect(490, 530, 93, 29));
        Miseajour->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 153, 45);"));
        Trier = new QPushButton(page);
        Trier->setObjectName("Trier");
        Trier->setGeometry(QRect(610, 530, 93, 29));
        Trier->setStyleSheet(QString::fromUtf8("background-color: rgb(154, 211, 238);"));
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 120, 71, 20));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_9 = new QLabel(page);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(150, 360, 101, 20));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_8 = new QLabel(page);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(150, 320, 91, 20));
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_10 = new QLabel(page);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(150, 400, 101, 20));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_11 = new QLabel(page);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(150, 440, 111, 20));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_15 = new QLineEdit(page);
        lineEdit_15->setObjectName("lineEdit_15");
        lineEdit_15->setGeometry(QRect(270, 240, 113, 26));
        lineEdit_15->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(150, 80, 71, 20));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(150, 240, 71, 20));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        ExporterPDF = new QPushButton(page);
        ExporterPDF->setObjectName("ExporterPDF");
        ExporterPDF->setGeometry(QRect(1350, 530, 101, 29));
        ExporterPDF->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 203, 203);\n"
"background-color: rgb(253, 145, 4);"));
        lineEdit_11 = new QLineEdit(page);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(270, 80, 113, 26));
        lineEdit_11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Modifier = new QPushButton(page);
        Modifier->setObjectName("Modifier");
        Modifier->setGeometry(QRect(1060, 160, 93, 29));
        Modifier->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 145, 4);"));
        lineEdit_12 = new QLineEdit(page);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(270, 160, 113, 26));
        lineEdit_12->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_12 = new QLabel(page);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(1310, 20, 121, 111));
        lineEdit_19 = new QLineEdit(page);
        lineEdit_19->setObjectName("lineEdit_19");
        lineEdit_19->setGeometry(QRect(270, 400, 113, 26));
        lineEdit_19->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(150, 160, 71, 20));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_16 = new QLineEdit(page);
        lineEdit_16->setObjectName("lineEdit_16");
        lineEdit_16->setGeometry(QRect(270, 280, 113, 26));
        lineEdit_16->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(150, 280, 71, 20));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_18 = new QLineEdit(page);
        lineEdit_18->setObjectName("lineEdit_18");
        lineEdit_18->setGeometry(QRect(270, 360, 113, 26));
        lineEdit_18->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Supprimer_2 = new QPushButton(page);
        Supprimer_2->setObjectName("Supprimer_2");
        Supprimer_2->setGeometry(QRect(270, 490, 93, 29));
        Supprimer_2->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 7, 27);"));
        tableWidget = new QTableWidget(page);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setBackground(QColor(139, 139, 139));
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setBackground(QColor(120, 120, 120));
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        if (tableWidget->rowCount() < 9)
            tableWidget->setRowCount(9);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(410, 200, 1081, 311));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(120, 120, 120);"));
        tableWidget->setRowCount(9);
        tableWidget->setColumnCount(9);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 20, 191, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("Constantia")});
        font.setPointSize(14);
        font.setUnderline(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        Rechercher = new QPushButton(page);
        Rechercher->setObjectName("Rechercher");
        Rechercher->setGeometry(QRect(510, 160, 93, 29));
        Rechercher->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 203, 203);"));
        dateEdit_3 = new QDateEdit(page);
        dateEdit_3->setObjectName("dateEdit_3");
        dateEdit_3->setGeometry(QRect(270, 440, 110, 26));
        dateEdit_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_5 = new QLabel(page);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(150, 200, 71, 20));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        Ajouter = new QPushButton(page);
        Ajouter->setObjectName("Ajouter");
        Ajouter->setGeometry(QRect(150, 490, 93, 29));
        Ajouter->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 153, 45);"));
        lineEdit_17 = new QLineEdit(page);
        lineEdit_17->setObjectName("lineEdit_17");
        lineEdit_17->setGeometry(QRect(270, 320, 113, 26));
        lineEdit_17->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Rechercher_2 = new QPushButton(page);
        Rechercher_2->setObjectName("Rechercher_2");
        Rechercher_2->setGeometry(QRect(730, 530, 93, 29));
        Rechercher_2->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 203, 203);"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        Nstock->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Nstock);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1544, 26));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName("menuMenu");
        menuStatistique = new QMenu(menubar);
        menuStatistique->setObjectName("menuStatistique");
        Nstock->setMenuBar(menubar);
        statusbar = new QStatusBar(Nstock);
        statusbar->setObjectName("statusbar");
        Nstock->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menubar->addAction(menuStatistique->menuAction());
        menuMenu->addAction(actionEmployer);
        menuStatistique->addAction(actionID);
        menuStatistique->addAction(actionSuivi_du_stock_en_temps_r_el);

        retranslateUi(Nstock);

        QMetaObject::connectSlotsByName(Nstock);
    } // setupUi

    void retranslateUi(QMainWindow *Nstock)
    {
        Nstock->setWindowTitle(QCoreApplication::translate("Nstock", "Nstock", nullptr));
        actionID->setText(QCoreApplication::translate("Nstock", "D\303\251tection fin du stock", nullptr));
        actionEmployer->setText(QCoreApplication::translate("Nstock", "Id", nullptr));
        actionSuivi_du_stock_en_temps_r_el->setText(QCoreApplication::translate("Nstock", "Suivi du stock en temps r\303\251el", nullptr));
        Supprimer->setText(QCoreApplication::translate("Nstock", "Supprimer", nullptr));
        Miseajour->setText(QCoreApplication::translate("Nstock", "Mise \303\240 jour", nullptr));
        Trier->setText(QCoreApplication::translate("Nstock", "Trier", nullptr));
        label_3->setText(QCoreApplication::translate("Nstock", "Nom", nullptr));
        label_9->setText(QCoreApplication::translate("Nstock", "Prix de vente", nullptr));
        label_8->setText(QCoreApplication::translate("Nstock", "Prix d'achat", nullptr));
        label_10->setText(QCoreApplication::translate("Nstock", "Fournisseur", nullptr));
        label_11->setText(QCoreApplication::translate("Nstock", "Date de livraison", nullptr));
        label_2->setText(QCoreApplication::translate("Nstock", "ID Pi\303\250ce", nullptr));
        label_6->setText(QCoreApplication::translate("Nstock", "Cat\303\251gorie ", nullptr));
        ExporterPDF->setText(QCoreApplication::translate("Nstock", "Exporter PDF", nullptr));
        Modifier->setText(QCoreApplication::translate("Nstock", "Modifier", nullptr));
        label_12->setText(QString());
        label_4->setText(QCoreApplication::translate("Nstock", "ID Pi\303\250ce", nullptr));
        label_7->setText(QCoreApplication::translate("Nstock", "Quantit\303\251", nullptr));
        Supprimer_2->setText(QCoreApplication::translate("Nstock", "Supprimer", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Nstock", "ID Pi\303\250ce", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Nstock", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Nstock", "R\303\251f\303\251rence", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Nstock", "Cat\303\251gorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Nstock", "Quanti\303\251 ", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Nstock", "Prix d'achat", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Nstock", "prix de vente", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("Nstock", "Fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("Nstock", "Date de livraison", nullptr));
        label->setText(QCoreApplication::translate("Nstock", "Ajouter une pi\303\251ce", nullptr));
        Rechercher->setText(QCoreApplication::translate("Nstock", "Rechercher", nullptr));
        label_5->setText(QCoreApplication::translate("Nstock", "R\303\250f\303\250rence", nullptr));
        Ajouter->setText(QCoreApplication::translate("Nstock", "Ajouter", nullptr));
        Rechercher_2->setText(QCoreApplication::translate("Nstock", "Rechercher", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("Nstock", "Statistiques", nullptr));
        menuStatistique->setTitle(QCoreApplication::translate("Nstock", "M\303\251tiers Innovants", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Nstock: public Ui_Nstock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NSTOCK_H
