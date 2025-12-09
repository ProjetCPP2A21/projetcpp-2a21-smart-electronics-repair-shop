#include "arduino_fournisseur.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTime>           // ← ADD THIS LINE
#include <QSqlQuery>
#include <QDebug>         // ← this fixes QTime
ArduinoFournisseur::ArduinoFournisseur(QObject *parent)
    : QObject(parent)
{
    // Find Arduino Uno
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        if (info.vendorIdentifier() == 9025 && info.productIdentifier() == 67) {
            arduino = new QSerialPort(this);
            arduino->setPortName(info.portName());
            arduino->setBaudRate(QSerialPort::Baud9600);
            arduino->setDataBits(QSerialPort::Data8);
            arduino->setParity(QSerialPort::NoParity);
            arduino->setStopBits(QSerialPort::OneStop);
            arduino->setFlowControl(QSerialPort::NoFlowControl);

            if (arduino->open(QIODevice::ReadWrite)) {
                available = true;
                qDebug() << "Arduino connected:" << info.portName();
            }
            break;
        }
    }

    if (!available) {
        qDebug() << "Arduino Uno not found";
    }
}

ArduinoFournisseur::~ArduinoFournisseur()
{
    if (arduino && arduino->isOpen())
        arduino->close();
}

void ArduinoFournisseur::start()
{
    if (!available || !arduino) return;
    connect(arduino, &QSerialPort::readyRead, this, &ArduinoFournisseur::handleClaps);
}


void ArduinoFournisseur::stop()
{
    if (arduino)
        disconnect(arduino, &QSerialPort::readyRead, this, nullptr);
}

void ArduinoFournisseur::handleClaps()
{
    static QByteArray buffer;
    buffer += arduino->readAll();

    int index;
    while ((index = buffer.indexOf('\n')) != -1) {
        QByteArray line = buffer.left(index).trimmed(); // full line
        buffer.remove(0, index + 1); // remove processed part

        qDebug() << "Full line from Arduino:" << line;

        // Lenient clap detection
        if (line.contains("CL")) {
            QSqlQuery q;
            if (q.exec("SELECT COUNT(*) FROM FOURNISSEUR") && q.next()) {
                int count = q.value(0).toInt();

                // Find the QListWidget in the UI
                QWidget *parentWidget = qobject_cast<QWidget*>(parent()); // assuming parent is main window
                if (parentWidget) {
                    QListWidget *log = parentWidget->findChild<QListWidget*>("fournlistwidget"); // your widget name
                    if (log) {
                        log->addItem(QString("Clap detected – fournisseurs count: %1").arg(count));
                    }
                }

                // Optionally, send count back to Arduino
                arduino->write(QString::number(count).toUtf8() + "\n");
                qDebug() << "Action triggered, sent to Arduino:" << count;
            }
        }
    }
}
