QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
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
