#pragma once
#include <QMainWindow>
#include <QMenu>
#include <QDialog>
#include <QString>
class QToolBar;
class QPoint;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots de l'UI existants
    void on_btnAjouter_clicked();
    void on_btnModifier_clicked();
    void on_btnSupprimer_clicked();
    void on_leSearch_textChanged(const QString &);
    void on_cbSecteurF_currentIndexChanged(int);
    void on_cbPaysF_currentIndexChanged(int);
    void on_tableClients_itemSelectionChanged();
    void on_btnClearFilter_clicked();
    void on_btnExportCSV_clicked();

    // Menu contextuel
    void on_tableContextMenuRequested(const QPoint &pos);

    // Toolbar (créée en C++)
    void actSortDateAsc();
    void actSortDateDesc();
    void actSortCountryAsc();void actExportListCSV();
    void actShowStats();
    void actMarkInactive();

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    void ensureToolbarVisible();

    // Utils/Metiers
    void applyStyle();
    void brightenPlaceholders();
    void clearForm();
    void applyFilters();

    void updateInactiveIndicators(int days = 30);
    int  selectedRow() const;void exportListToCSV();
    void showMonthlyStatsDialog();
    void sortByDateAsc();
    void sortByDateDesc();
    void sortByCountryAsc();

    Ui::MainWindow *ui;
    QToolBar *m_tb = nullptr;
};
