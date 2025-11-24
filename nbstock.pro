QT += core gui

QT       += core sql
QT       += charts

QT += network


  # ou simplement "qrcode" selon la version de Qt






greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    main.cpp \
    nstock.cpp \
    qrcodegen.cpp \
    stock.cpp

HEADERS += \
    ../../../Downloads/QR-Code-generator-master (1)/QR-Code-generator-master/cpp/qrcodegen.hpp \
    connection.h \
    nstock.h \
    qrcodegen.hpp \
    stock.h \



FORMS += \
    nstock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

SUBDIRS += \
    ../../../Downloads/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/SMTPEmail.pro \
    ../../../Downloads/qzxing-master/qzxing-master/src/QZXing.pro \
    qzing/src/QZXing.pro

DISTFILES += \
    ../../../Downloads/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/.gitignore \
    ../../../Downloads/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/.travis.yml \
    ../../../Downloads/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/CMakeLists.txt \
    ../../../Downloads/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/LICENSE \
    ../../../Downloads/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/README.md \
    ../../../Downloads/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/CMakeLists.txt \
    ../../../Downloads/SmtpClient-for-Qt-2.0/SmtpClient-for-Qt-2.0/src/SmtpMimeConfig.cmake
