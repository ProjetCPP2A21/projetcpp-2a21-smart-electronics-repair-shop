#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class Arduino
{
public:
    Arduino();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray d);
    QByteArray read_from_arduino();
    QSerialPort* getserial();

    // --- LIGNE AJOUTÉE ICI ---
    QString getarduino_port_name();

private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_H
