#ifndef GEMPLOYER_H
#define GEMPLOYER_H

#include <QMainWindow>
#include "employer.h"

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
    void on_pushButton_5_clicked();
    void on_btnSupprimer_clicked();
    void on_btnModifier_clicked();
    void on_lineEdit_recherche_textChanged(const QString &text);
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::Gemployer *ui;
    Employer emp;
    void rafraichir();
    void viderFormulaire();
    void chargerFormulaire(const QString& id);
};

#endif
