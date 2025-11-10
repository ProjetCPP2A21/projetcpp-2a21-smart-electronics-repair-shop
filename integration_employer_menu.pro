QT += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    appareil.cpp \
    client.cpp \
    connection.cpp \
    employe.cpp \
    fournisseur.cpp \
    main.cpp \
    smart_electronic_repairshop.cpp \
    stock.cpp

HEADERS += \
    appareil.h \
    client.h \
    connection.h \
    employe.h \
    fournisseur.h \
    smart_electronic_repairshop.h \
    stock.h

FORMS += \
    smart_electronic_repairshop.ui
