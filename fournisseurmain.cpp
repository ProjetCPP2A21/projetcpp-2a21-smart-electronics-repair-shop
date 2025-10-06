#include "fournisseurwidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FournisseurWidget w;
    w.show();
    return app.exec();
}
