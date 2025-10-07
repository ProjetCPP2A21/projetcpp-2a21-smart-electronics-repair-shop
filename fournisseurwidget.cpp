#include "fournisseurwidget.h"
#include "ui_fournisseurwidget.h"

static const char* QSS = R"(
  QWidget { background-color: #0F1328; color: #F2F2FA; font-family: 'Segoe UI','Inter',Arial; }
  QLabel { background: transparent; color: #EDEAF Fajouter9; }
  QLabel#formTitle { color: #B8A1FF; font-weight: bold; font-size: 20px; padding-left: 8px; }
  QGroupBox { background: #1B2040; border: 1px solid #6B6FB0; border-radius: 12px; margin-top: 8px; }
  QLineEdit, QComboBox, QDateEdit, QTextEdit {
    background: #23284F;
    color: #FFFFFF;
    border: 1px solid #6B6FB0;
    border-radius: 10px;
    padding: 8px 10px;
  }
  QLineEdit#leSearch { background: #3B2B67; border: 1px solid #8D77CC; }
  QTableWidget {
    background: #1A1F3D;
    color: #F2F2FA;
    gridline-color: #40467A;
    alternate-background-color: #232B57;
  }
  QHeaderView::section { background: #12163A; color: #B8A1FF; padding: 10px; border: none; }
  QPushButton#btnAjouter {
    background: #FF8C42;
    color: #1A1328;
    font-weight: bold;
    border-radius: 10px;
    padding: 8px 14px;
  }
  QPushButton#btnModifier {
    background: #1C1F4A;
    color: #EDEAF9;
    border-radius: 10px;
    padding: 8px 14px;
  }
  QPushButton#btnSupprimer {
    background: #7A1F2A;
    color: #FFE8E8;
    border-radius: 10px;
    padding: 8px 14px;
  }
  QPushButton#btnClearFilter {
    background: #3A3F6B;
    color: #EDEAF9;
    border-radius: 10px;
    padding: 6px 12px;
  }
  QPushButton#btnExportPDF {
    background: #2A5F2E;
    color: #E6FFE6;
    font-weight: bold;
    border-radius: 10px;
    padding: 8px 14px;
  }
  QPushButton#btnStatistiques {
    background: #4A3B7A;
    color: #F2F2FA;
    border-radius: 10px;
    padding: 8px 14px;
  }
)";

FournisseurWidget::FournisseurWidget(QWidget *parent) : QWidget(parent), ui(new Ui::FournisseurWidget) {
    ui->setupUi(this);
    applyStyle();
}

FournisseurWidget::~FournisseurWidget() {
    delete ui;
}

void FournisseurWidget::applyStyle() {
    setStyleSheet(QSS);
}
