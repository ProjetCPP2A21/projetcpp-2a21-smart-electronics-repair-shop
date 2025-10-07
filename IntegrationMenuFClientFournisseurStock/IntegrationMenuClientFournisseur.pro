QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartElectronicRepairShop
TEMPLATE = app

SOURCES += \
    main.cpp \
    menu.cpp \
    client.cpp \
    fournisseur.cpp

HEADERS += \
    menu.h \
    client.h \
    fournisseur.h

FORMS += \
    menu.ui
