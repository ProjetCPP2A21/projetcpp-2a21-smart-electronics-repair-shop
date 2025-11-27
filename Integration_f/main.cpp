#include "smart_electronics_repairshop.h"
#include "connection.h"  // ADD THIS
#include <QApplication>
#include <iostream>      // ADD THIS

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::cout << "Program starting..." << std::endl; // Force console output

    // TEST DATABASE CONNECTION - ADD THIS BLOCK
    static Connection conn;
    bool connected = conn.createconnect();

    if (!connected) {
        std::cout << "CRITICAL: Database connection failed!" << std::endl;
        // Don't exit - let the user decide what to do
    }

    osana_dashboard w;
    w.show();
    return a.exec();
}
