#include "arduino.h"

Arduino::Arduino(QObject *parent) : QObject(parent)
{
    arduino = nullptr;
    arduino_is_available = false;
    arduino_port_name = "";
}

Arduino::~Arduino()
{
    disconnectArduino();
}

QStringList Arduino::getAvailablePorts()
{
    QStringList ports;
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        ports << serialPortInfo.portName();
    }
    return ports;
}

bool Arduino::connectArduino(const QString &portName)
{
    // Si déjà connecté, déconnecter d'abord
    if (arduino != nullptr && arduino->isOpen()) {
        disconnectArduino();
    }

    arduino = new QSerialPort(this);

    // Si un port spécifique est fourni, l'utiliser
    if (!portName.isEmpty()) {
        arduino->setPortName(portName);
    } else {
        // Sinon, chercher automatiquement un port Arduino
        bool arduino_port_is_available = false;
        QString port;

        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
            if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
                if (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id &&
                    serialPortInfo.productIdentifier() == arduino_uno_product_id) {
                    arduino_port_is_available = true;
                    port = serialPortInfo.portName();
                    break;
                }
            }
        }

        if (!arduino_port_is_available) {
            // Si pas trouvé par VID/PID, prendre le premier port disponible
            if (!QSerialPortInfo::availablePorts().isEmpty()) {
                port = QSerialPortInfo::availablePorts().first().portName();
            } else {
                qDebug() << "Aucun port série disponible";
                return false;
            }
        }

        arduino->setPortName(port);
    }

    // Configuration du port série
    if (arduino->open(QSerialPort::ReadWrite)) {
        if (arduino->setBaudRate(QSerialPort::Baud9600) &&
            arduino->setDataBits(QSerialPort::Data8) &&
            arduino->setParity(QSerialPort::NoParity) &&
            arduino->setStopBits(QSerialPort::OneStop) &&
            arduino->setFlowControl(QSerialPort::NoFlowControl)) {

            arduino_port_name = arduino->portName();
            arduino_is_available = true;

            connect(arduino, &QSerialPort::readyRead, this, &Arduino::readData);

            qDebug() << "Arduino connecté sur" << arduino_port_name;
            return true;
        } else {
            qDebug() << "Erreur de configuration du port série";
            arduino->close();
            return false;
        }
    } else {
        qDebug() << "Impossible d'ouvrir le port série:" << arduino->errorString();
        return false;
    }
}

void Arduino::disconnectArduino()
{
    if (arduino != nullptr) {
        if (arduino->isOpen()) {
            arduino->close();
        }
        delete arduino;
        arduino = nullptr;
    }
    arduino_is_available = false;
    arduino_port_name = "";
}

bool Arduino::sendData(const QString &data)
{
    if (arduino != nullptr && arduino->isOpen()) {
        QByteArray byteData = (data + "\n").toUtf8();
        qint64 bytesWritten = arduino->write(byteData);
        
        if (bytesWritten == -1) {
            qDebug() << "Erreur d'écriture sur le port série:" << arduino->errorString();
            return false;
        } else {
            arduino->waitForBytesWritten(100);
            qDebug() << "Données envoyées à Arduino:" << data;
            return true;
        }
    } else {
        qDebug() << "Arduino non connecté";
        return false;
    }
}

void Arduino::readData()
{
    if (arduino != nullptr && arduino->canReadLine()) {
        QByteArray data = arduino->readLine();
        QString message = QString::fromUtf8(data).trimmed();
        qDebug() << "Données reçues d'Arduino:" << message;
        emit dataReceived(message);
    }
}

