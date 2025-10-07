#include "menu_employer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menu_employer w;
    w.show();
    return a.exec();
}
