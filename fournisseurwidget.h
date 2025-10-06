#pragma once
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class FournisseurWidget; }
QT_END_NAMESPACE

class FournisseurWidget : public QWidget {
    Q_OBJECT
public:
    explicit FournisseurWidget(QWidget *parent = nullptr);
    ~FournisseurWidget();

private:
    void applyStyle(); // Apply custom styles

    Ui::FournisseurWidget *ui;
};
