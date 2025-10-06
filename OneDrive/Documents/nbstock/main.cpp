#include "nstock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    nstock w;
    w.show();
    return a.exec();
}
