QT       += core gui sql
QT += charts
QT += widgets
QT += widgets charts
QT += widgets printsupport charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appareil.cpp \
    client.cpp \
    connection.cpp \
    employe.cpp \
    fournisseur.cpp \
    main.cpp \
    smart_electronics_repairshop.cpp \
    stock.cpp
    client.cpp

HEADERS += \
    appareil.h \
    client.h \
    connection.h \
    employe.h \
    fournisseur.h \
    smart_electronics_repairshop.h \
    stock.h
    client_h

FORMS += \
    smart_electronics_repairshop.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
