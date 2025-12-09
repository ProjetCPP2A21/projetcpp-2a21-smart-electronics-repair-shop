#ifndef ARDUINO_FOURNISSEUR_H
#define ARDUINO_FOURNISSEUR_H

#include <QObject>
#include <QSerialPort>
#include <QListWidget>

class ArduinoFournisseur : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoFournisseur(QObject *parent = nullptr);
    ~ArduinoFournisseur();

    void start();   // call when entering fournisseur page
    void stop();    // call when leaving

private slots:
    void handleClaps();

private:
    QSerialPort *arduino = nullptr;
    bool available = false;
signals:
    void clapDetected(int count);  // emits the number of fournisseurs when clap happens
};

#endif
