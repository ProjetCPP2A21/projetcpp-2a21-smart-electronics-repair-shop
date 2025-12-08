#include "arduino.h"

Arduino::Arduino()
{
    data = "";
    arduino_port_name = "";
    arduino_is_available = false;
    serial = new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
    return serial;
}

int Arduino::connect_arduino()
{
    // Recherche du port sur lequel l'Arduino est branché
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            // Vérifier l'ID Vendeur (9025 pour Uno/Mega officiels)
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id){
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "Arduino trouvé sur le port :" << arduino_port_name;
            }
        }
    }

    if(arduino_is_available){
        serial->setPortName(arduino_port_name);

        // Configuration de la connexion série
        if(serial->open(QSerialPort::ReadWrite)){
            serial->setBaudRate(QSerialPort::Baud9600); // Mêmes bauds que dans Arduino IDE
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0; // Succès
        }
        return 1; // Erreur d'ouverture
    }
    return -1; // Arduino non trouvé
}

int Arduino::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
        data = serial->readAll();
        return data;
    }
    return "";
}

int Arduino::write_to_arduino(QByteArray d)
{
    if(serial->isWritable()){
        serial->write(d);
        return 0; // Succès
    }else{
        qDebug() << "Erreur : Impossible d'écrire sur le port série";
        return 1; // Erreur
    }
}
