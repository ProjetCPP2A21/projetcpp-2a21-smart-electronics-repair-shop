QT += core gui sql widgets printsupport charts serialport   # TOUT EN UNE SEULE LIGNE

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Atelier_Connexion
TEMPLATE = app

SOURCES += \
    arduino.cpp \
    client.cpp \
    main.cpp \
    connection.cpp \
    mainwindow.cpp

HEADERS += \
    arduino.h \
    client.h \
    connection.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Exécutable plus rapide (optionnel, mais propre)
CONFIG += ltcg
