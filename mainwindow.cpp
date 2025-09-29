\
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>


#include <QShortcut>
#include <QKeySequence>
#include <QKeyEvent>
#include <QPainter>
#include <QHeaderView>
#include <QFileDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QDate>
#include <QPalette>
#include <QColor>
#include <QPixmap>
#include <QMap>
#include <QFile>
#include <QDialog>
#include <QVBoxLayout>

#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QTextStream>
#include <QDate>
#include <QTableWidget>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
static const char* QSS = R"(
  QWidget { background-color: #0F1328; color: #F2F2FA; font-family: 'Segoe UI','Inter',Arial; }
  QLabel { background: transparent; color: #EDEAF9; }
  QLabel#formTitle { color:#D2B7FF; font-weight:800; font-size:18px; padding-left:6px; }
  QGroupBox { background:#1B2040; border:1px solid #6B6FB0; border-radius:12px; margin-top:6px; }
  QLineEdit, QComboBox, QDateEdit { background:#23284F; color:#FFFFFF; border:1px solid #6B6FB0; border-radius:10px; padding:8px 10px; }
  QLineEdit#leSearch { background:#3B2B67; border:1px solid #8D77CC; }
  QTableWidget { background:#1A1F3D; color:#F2F2FA; gridline-color:#40467A; alternate-background-color:#232B57; }
  QHeaderView::section { background:#12163A; color:#D2B7FF; padding:10px; border:none; }
  QPushButton#btnAjouter   { background:#FF8C42; color:#1A1328; font-weight:800; border-radius:10px; padding:8px 14px; }
  QPushButton#btnModifier  { background:#1C1F4A; color:#EDEAF9; border-radius:10px; padding:8px 14px; }
  QPushButton#btnSupprimer { background:#7A1F2A; color:#FFE8E8; border-radius:10px; padding:8px 14px; }
  QPushButton#btnClearFilter { background:#3A3F6B; color:#EDEAF9; border-radius:10px; padding:6px 12px; }
  QPushButton#btnExportCSV { background:#2A5F2E; color:#E6FFE6; border-radius:10px; padding:8px 14px; }
)";

enum Col { COL_ID=0, COL_NOM, COL_EMAIL, COL_TEL, COL_SECTEUR, COL_PAYS, COL_DATE };

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    
    // Keyboard shortcuts to force toolbar visible
    auto scSpace = new QShortcut(QKeySequence(Qt::Key_Space), this);
    connect(scSpace, &QShortcut::activated, this, [this](){ ensureToolbarVisible(); });
    auto scEnter = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(scEnter, &QShortcut::activated, this, [this](){ ensureToolbarVisible(); });
    auto scEnter2 = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    connect(scEnter2, &QShortcut::activated, this, [this](){ ensureToolbarVisible(); });
    auto scZ = new QShortcut(QKeySequence(Qt::Key_Z), this);
    connect(scZ, &QShortcut::activated, this, [this](){ ensureToolbarVisible(); });
// === Toolbar créée en C++ (interface visible) ===
    m_tb = addToolBar(tr("Client"));

    m_tb->setObjectName("clientToolbar");
    m_tb->setMovable(false);
    m_tb->setFloatable(false);
    addToolBar(Qt::TopToolBarArea, m_tb);
    m_tb->setToolButtonStyle(Qt::ToolButtonTextOnly);
    QAction *aSortDateAsc  = m_tb->addAction(tr("Tri Date ↑"));
    QAction *aSortDateDesc = m_tb->addAction(tr("Tri Date ↓"));
    QAction *aSortCountry  = m_tb->addAction(tr("Tri Pays A→Z"));
    m_tb->addSeparator();QAction *aExportCSV = m_tb->addAction(tr("Export CSV"));
    m_tb->addSeparator();
    QAction *aStats = m_tb->addAction(tr("Stats/Mois"));
    QAction *aInactive = m_tb->addAction(tr("Inactifs >30j"));

    connect(aSortDateAsc,  &QAction::triggered, this, &MainWindow::actSortDateAsc);
    connect(aSortDateDesc, &QAction::triggered, this, &MainWindow::actSortDateDesc);
    connect(aSortCountry,  &QAction::triggered, this, &MainWindow::actSortCountryAsc);connect(aExportCSV,    &QAction::triggered, this, &MainWindow::actExportListCSV);
    connect(aStats,        &QAction::triggered, this, &MainWindow::actShowStats);
    connect(aInactive,     &QAction::triggered, this, &MainWindow::actMarkInactive);

    ui->tableClients->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableClients, &QWidget::customContextMenuRequested,
            this, &MainWindow::on_tableContextMenuRequested);
    ui->tableClients->setSortingEnabled(true);
    updateInactiveIndicators(30);
    if (ui->deDate) ui->deDate->setDisplayFormat("yyyy-MM-dd");
setWindowTitle("ClientStudio - Clean");
    applyStyle();
    brightenPlaceholders();

    ui->deDate->setDisplayFormat("yyyy-MM-dd");
    ui->deDate->setDate(QDate::currentDate());

    // Init filter combos from form combos
    ui->cbSecteurF->addItem("Tous");
    for (int i=0;i<ui->cbSecteur->count();++i) ui->cbSecteurF->addItem(ui->cbSecteur->itemText(i));
    ui->cbPaysF->addItem("Tous");
    for (int i=0;i<ui->cbPays->count();++i) ui->cbPaysF->addItem(ui->cbPays->itemText(i));

    // Table
    ui->tableClients->setRowCount(0);
    ui->tableClients->setColumnCount(7);
    QStringList headers = {"ID","Nom","Email","Téléphone","SecteurActivité","Pays","DateCréation"};
    ui->tableClients->setHorizontalHeaderLabels(headers);
    ui->tableClients->horizontalHeader()->setStretchLastSection(true);
    ui->tableClients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableClients->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableClients->setAlternatingRowColors(true);
    ui->tableClients->setSortingEnabled(true);

    connect(ui->tableClients, &QTableWidget::itemSelectionChanged,
            this, &MainWindow::on_tableClients_itemSelectionChanged);
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::applyStyle(){ setStyleSheet(QSS); }
void MainWindow::brightenPlaceholders(){
    for (auto *le : findChildren<QLineEdit*>()) {
        QPalette p = le->palette();
        p.setColor(QPalette::PlaceholderText, QColor("#B9B3E6"));
        le->setPalette(p);
    }
}
void MainWindow::clearForm(){
    ui->leId->clear(); ui->leNom->clear(); ui->leEmail->clear();
    ui->leTel->clear();
    ui->cbSecteur->setCurrentIndex(0);
    ui->cbPays->setCurrentIndex(0);
    ui->deDate->setDate(QDate::currentDate());
    ui->leNom->setFocus();
}

void MainWindow::on_btnAjouter_clicked(){
    ensureToolbarVisible();

    const QString id  = ui->leId->text().trimmed();
    const QString nom = ui->leNom->text().trimmed();
    if(nom.isEmpty()) return;

    int r = ui->tableClients->rowCount();
    ui->tableClients->insertRow(r);
    ui->tableClients->setItem(r,COL_ID,      new QTableWidgetItem(id.isEmpty()?QString::number(r+1):id));
    ui->tableClients->setItem(r,COL_NOM,     new QTableWidgetItem(nom));
    ui->tableClients->setItem(r,COL_EMAIL,   new QTableWidgetItem(ui->leEmail->text().trimmed()));
    ui->tableClients->setItem(r,COL_TEL,     new QTableWidgetItem(ui->leTel->text().trimmed()));
    ui->tableClients->setItem(r,COL_SECTEUR, new QTableWidgetItem(ui->cbSecteur->currentText()));
    ui->tableClients->setItem(r,COL_PAYS,    new QTableWidgetItem(ui->cbPays->currentText()));
    ui->tableClients->setItem(r,COL_DATE,    new QTableWidgetItem(ui->deDate->date().toString("yyyy-MM-dd")));
    clearForm();
    applyFilters();

    updateInactiveIndicators(30);

    updateInactiveIndicators(30);
}

void MainWindow::on_tableClients_itemSelectionChanged(){
    ensureToolbarVisible();
auto items = ui->tableClients->selectedItems();
    if(items.isEmpty()) return;
    int r = items.first()->row();
    ui->leId->setText(ui->tableClients->item(r,COL_ID)->text());
    ui->leNom->setText(ui->tableClients->item(r,COL_NOM)->text());
    ui->leEmail->setText(ui->tableClients->item(r,COL_EMAIL)->text());
    ui->leTel->setText(ui->tableClients->item(r,COL_TEL)->text());
    ui->cbSecteur->setCurrentText(ui->tableClients->item(r,COL_SECTEUR)->text());
    ui->cbPays->setCurrentText(ui->tableClients->item(r,COL_PAYS)->text());
    ui->deDate->setDate(QDate::fromString(ui->tableClients->item(r,COL_DATE)->text(),"yyyy-MM-dd"));
}

void MainWindow::on_btnModifier_clicked(){
    ensureToolbarVisible();

    auto items = ui->tableClients->selectedItems();
    if(items.isEmpty()) return;
    int r = items.first()->row();
    ui->tableClients->item(r,COL_ID)->setText(ui->leId->text().trimmed());
    ui->tableClients->item(r,COL_NOM)->setText(ui->leNom->text().trimmed());
    ui->tableClients->item(r,COL_EMAIL)->setText(ui->leEmail->text().trimmed());
    ui->tableClients->item(r,COL_TEL)->setText(ui->leTel->text().trimmed());
    ui->tableClients->item(r,COL_SECTEUR)->setText(ui->cbSecteur->currentText());
    ui->tableClients->item(r,COL_PAYS)->setText(ui->cbPays->currentText());
    ui->tableClients->item(r,COL_DATE)->setText(ui->deDate->date().toString("yyyy-MM-dd"));
    applyFilters();

    updateInactiveIndicators(30);

    updateInactiveIndicators(30);
}

void MainWindow::on_btnSupprimer_clicked(){
    ensureToolbarVisible();

    auto items = ui->tableClients->selectedItems();
    if(items.isEmpty()) return;
    ui->tableClients->removeRow(items.first()->row());

    updateInactiveIndicators(30);

    updateInactiveIndicators(30);
}

void MainWindow::on_leSearch_textChanged(const QString &){
    ensureToolbarVisible();
 applyFilters(); }
void MainWindow::on_cbSecteurF_currentIndexChanged(int){
    ensureToolbarVisible();
 applyFilters(); }
void MainWindow::on_cbPaysF_currentIndexChanged(int){
    ensureToolbarVisible();
 applyFilters(); }
void MainWindow::on_btnClearFilter_clicked(){ ui->leSearch->clear(); ui->cbSecteurF->setCurrentIndex(0); ui->cbPaysF->setCurrentIndex(0); applyFilters(); }

void MainWindow::applyFilters(){
    const QString q = ui->leSearch->text().trimmed();
    const QString sec = ui->cbSecteurF->currentText();
    const QString pays = ui->cbPaysF->currentText();

    for(int r=0;r<ui->tableClients->rowCount();++r){
        bool match = true;
        if(!q.isEmpty()){
            bool any=false;
            for(int c=0;c<ui->tableClients->columnCount();++c){
                auto *it = ui->tableClients->item(r,c);
                if(it && it->text().contains(q, Qt::CaseInsensitive)){ any=true; break; }
            }
            match &= any;
        }
        if(sec!="Tous")  match &= (ui->tableClients->item(r,COL_SECTEUR)->text()==sec);
        if(pays!="Tous") match &= (ui->tableClients->item(r,COL_PAYS)->text()==pays);
        ui->tableClients->setRowHidden(r, !match);
    }
}

void MainWindow::on_btnExportCSV_clicked(){
    QString path = QFileDialog::getSaveFileName(this, "Exporter CSV", "clients.csv", "CSV (*.csv)");
    if(path.isEmpty()) return;
    QFile f(path);
    if(!f.open(QIODevice::WriteOnly|QIODevice::Text)) return;
    QTextStream out(&f);
    out << "ID;Nom;Email;Téléphone;SecteurActivité;Pays;DateCréation\n";
    for(int r=0;r<ui->tableClients->rowCount();++r){
        if(ui->tableClients->isRowHidden(r)) continue;
        out << ui->tableClients->item(r,COL_ID)->text()<<";"
            << ui->tableClients->item(r,COL_NOM)->text()<<";"
            << ui->tableClients->item(r,COL_EMAIL)->text()<<";"
            << ui->tableClients->item(r,COL_TEL)->text()<<";"
            << ui->tableClients->item(r,COL_SECTEUR)->text()<<";"
            << ui->tableClients->item(r,COL_PAYS)->text()<<";"
            << ui->tableClients->item(r,COL_DATE)->text() << "\n";
    }
    f.close();
}

int MainWindow::selectedRow() const {
    auto items = ui->tableClients->selectedItems();
    return items.isEmpty() ? -1 : items.first()->row();
}

void MainWindow::updateInactiveIndicators(int days) {
    const QDate cutoff = QDate::currentDate().addDays(-days);
    for (int r = 0; r < ui->tableClients->rowCount(); ++r) {
        auto *dateItem = ui->tableClients->item(r, COL_DATE);
        if (!dateItem) continue;
        const QDate d = QDate::fromString(dateItem->text(), "yyyy-MM-dd");
        const bool inactive = d.isValid() && d <= cutoff;

        QPixmap dot(12, 12); dot.fill(Qt::transparent);
        QPainter p(&dot); p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(Qt::NoPen);
        p.setBrush(inactive ? QColor("#D9534F") : QColor("#2ECC71"));
        p.drawEllipse(1,1,10,10);

        if (auto *idItem = ui->tableClients->item(r, COL_ID)) {
            idItem->setData(Qt::DecorationRole, dot);
            idItem->setToolTip(inactive ? tr("Inactif depuis plus de %1 jours").arg(days) : tr("Actif"));
        }

        const QColor bgInactive(0x3b,0x0a,0x0a);
        for (int c = 0; c < ui->tableClients->columnCount(); ++c) {
            if (auto *it = ui->tableClients->item(r, c)) {
                it->setBackground(inactive ? QBrush(bgInactive) : QBrush(Qt::NoBrush));
            }
        }
    }
    ensureToolbarVisible();
}

void MainWindow::on_tableContextMenuRequested(const QPoint &pos) {
    ensureToolbarVisible();
QMenu m(this);QAction *actListeCSV = m.addAction(tr("Exporter liste (CSV/Excel)"));
    QAction *actTriDateAsc = m.addAction(tr("Trier par Date (↑)"));
    QAction *actTriDateDesc = m.addAction(tr("Trier par Date (↓)"));
    QAction *actTriPaysAsc = m.addAction(tr("Trier par Pays (A→Z)"));
    QAction *actStats = m.addAction(tr("Statistiques : nouveaux clients / mois"));
    QAction *chosen = m.exec(ui->tableClients->viewport()->mapToGlobal(pos));
    if (!chosen) { ensureToolbarVisible(); return; }

if (chosen == actListeCSV) exportListToCSV();
    else if (chosen == actTriDateAsc) sortByDateAsc();
    else if (chosen == actTriDateDesc) sortByDateDesc();
    else if (chosen == actTriPaysAsc) sortByCountryAsc();
    else if (chosen == actStats) showMonthlyStatsDialog();

    ensureToolbarVisible();
}

void MainWindow::exportListToCSV() {
    const QString fn = QFileDialog::getSaveFileName(this, tr("Exporter la liste (CSV/Excel)"), "Clients.csv", tr("CSV (*.csv)"));
    if (fn.isEmpty()) return;
    QFile f(fn);
    if (!f.open(QIODevice::WriteOnly|QIODevice::Text)) return;
    QTextStream out(&f);
    out << "ID;Nom;Email;Téléphone;SecteurActivité;Pays;DateCréation\n";
    for (int r=0;r<ui->tableClients->rowCount();++r) {
        if (ui->tableClients->isRowHidden(r)) continue;
        out << ui->tableClients->item(r,COL_ID)->text() << ";"
            << ui->tableClients->item(r,COL_NOM)->text() << ";"
            << ui->tableClients->item(r,COL_EMAIL)->text() << ";"
            << ui->tableClients->item(r,COL_TEL)->text() << ";"
            << ui->tableClients->item(r,COL_SECTEUR)->text() << ";"
            << ui->tableClients->item(r,COL_PAYS)->text() << ";"
            << ui->tableClients->item(r,COL_DATE)->text() << "\n";
    }
    f.close();
}

void MainWindow::showMonthlyStatsDialog() {
    QMap<QString,int> perMonth;
    for (int r = 0; r < ui->tableClients->rowCount(); ++r) {
        if (ui->tableClients->isRowHidden(r)) continue;
        const QString s = ui->tableClients->item(r, COL_DATE)->text();
        const QDate d = QDate::fromString(s, "yyyy-MM-dd");
        if (!d.isValid()) continue;
        perMonth[d.toString("yyyy-MM")] += 1;
    }
    QDialog *dlg = new QDialog(this); dlg->setWindowTitle(tr("Statistiques — Nouveaux clients par mois"));
    auto *layout = new QVBoxLayout(dlg);
    auto *tbl = new QTableWidget(dlg);
    tbl->setColumnCount(2);
    tbl->setHorizontalHeaderLabels({tr("Mois"), tr("Nouveaux clients")});
    tbl->horizontalHeader()->setStretchLastSection(true);
    QStringList keys = perMonth.keys(); keys.sort();
    tbl->setRowCount(keys.size());
    for (int i=0;i<keys.size();++i) {
        tbl->setItem(i,0,new QTableWidgetItem(keys[i]));
        tbl->setItem(i,1,new QTableWidgetItem(QString::number(perMonth[keys[i]])));
    }
    layout->addWidget(tbl);
    auto *btnBar = new QWidget(dlg);
    auto *btnLay = new QHBoxLayout(btnBar); btnLay->setContentsMargins(0,0,0,0);
    auto *btnExport = new QPushButton(tr("Exporter (CSV)"), btnBar);
    auto *btnClose  = new QPushButton(tr("Fermer"), btnBar);
    btnLay->addStretch(1); btnLay->addWidget(btnExport); btnLay->addWidget(btnClose);
    layout->addWidget(btnBar);
    connect(btnClose, &QPushButton::clicked, dlg, &QDialog::accept);
    connect(btnExport, &QPushButton::clicked, dlg, [tbl, this](){
        const QString fn = QFileDialog::getSaveFileName(this, tr("Exporter stats"), "Stats_clients_par_mois.csv", tr("CSV (*.csv)"));
        if (fn.isEmpty()) return;
        QFile f(fn);
        if (!f.open(QIODevice::WriteOnly|QIODevice::Text)) return;
        QTextStream out(&f);
        out << "Mois;NouveauxClients\n";
        for (int r=0;r<tbl->rowCount();++r)
            out << tbl->item(r,0)->text() << ";" << tbl->item(r,1)->text() << "\n";
        f.close();
    });
    dlg->resize(520, 420);
    dlg->exec();
}


void MainWindow::sortByDateAsc()  { ui->tableClients->sortItems(COL_DATE, Qt::AscendingOrder); }
void MainWindow::sortByDateDesc() { ui->tableClients->sortItems(COL_DATE, Qt::DescendingOrder); }
void MainWindow::sortByCountryAsc(){ ui->tableClients->sortItems(COL_PAYS, Qt::AscendingOrder); }

void MainWindow::actSortDateAsc()  { ensureToolbarVisible(); sortByDateAsc(); }
void MainWindow::actSortDateDesc() { ensureToolbarVisible(); sortByDateDesc(); }
void MainWindow::actSortCountryAsc(){ ensureToolbarVisible(); sortByCountryAsc(); }
void MainWindow::actExportListCSV(){ ensureToolbarVisible(); exportListToCSV(); }
void MainWindow::actShowStats()    { ensureToolbarVisible(); showMonthlyStatsDialog(); }
void MainWindow::actMarkInactive() { ensureToolbarVisible(); updateInactiveIndicators(30); }

void MainWindow::ensureToolbarVisible(){
    if (!m_tb) return;
    if (!m_tb->isVisible())
        m_tb->setVisible(true);
    if (m_tb->parentWidget() != this)
        m_tb->setParent(this);
    addToolBar(Qt::TopToolBarArea, m_tb);
    m_tb->setAllowedAreas(Qt::TopToolBarArea);
    m_tb->setMovable(false);
    m_tb->setFloatable(false);
}



void MainWindow::keyPressEvent(QKeyEvent *e){
    if (!e){ QMainWindow::keyPressEvent(e); return; }
    const int k = e->key();
    if (k == Qt::Key_Space || k == Qt::Key_Return || k == Qt::Key_Enter || k == Qt::Key_Z){
        ensureToolbarVisible();
        e->accept();
        return;
    }
    QMainWindow::keyPressEvent(e);
}
