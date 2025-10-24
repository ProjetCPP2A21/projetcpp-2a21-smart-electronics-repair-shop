#include "smart_electronic_repairshop.h"
#include "connection.h"  // ADD THIS
#include <QApplication>
#include <iostream>      // ADD THIS

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::cout << "Program starting..." << std::endl; // Force console output

    // TEST DATABASE CONNECTION - ADD THIS BLOCK
    Connection conn;
    bool connected = conn.createconnect();

    if (!connected) {
        std::cout << "CRITICAL: Database connection failed!" << std::endl;
        // Don't exit - let the user decide what to do
    }

    menu_employer w;
    w.show();
    return a.exec();
}
