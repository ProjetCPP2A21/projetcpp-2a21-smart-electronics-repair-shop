#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Charger style.css
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = styleFile.readAll();
        a.setStyleSheet(style);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
