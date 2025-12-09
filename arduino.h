#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDebug>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);
    ~Arduino();

    bool connectArduino(const QString &portName = "");
    void disconnectArduino();
    bool sendData(const QString &data);
    bool isConnected() const { return arduino != nullptr && arduino->isOpen(); }
    QStringList getAvailablePorts();

signals:
    void dataReceived(const QString &data);

private slots:
    void readData();

private:
    QSerialPort *arduino;
    QString buffer;
    static const quint16 arduino_uno_vendor_id = 9025;  // Arduino Uno
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
};

#endif // ARDUINO_H
