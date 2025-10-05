#include "gemployer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gemployer w;
    w.show();
    return a.exec();
}
