#include "sclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sclient w;
    w.show();
    return a.exec();
}
