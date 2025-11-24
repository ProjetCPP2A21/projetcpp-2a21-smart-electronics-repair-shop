QT += core gui sql widgets printsupport charts   # TOUT EN UNE SEULE LIGNE

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Pour Qt 6 (évite les warnings)
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET = Atelier_Connexion
TEMPLATE = app

SOURCES += \
    client.cpp \
    main.cpp \
    connection.cpp \
    mainwindow.cpp

HEADERS += \
    client.h \
    connection.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Exécutable plus rapide (optionnel, mais propre)
CONFIG += ltcg
