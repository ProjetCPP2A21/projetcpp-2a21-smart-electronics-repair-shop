// filename: client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>

// Classe placeholder pour fonctionnalités Client
class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);

    // Méthodes placeholder
    void ajouterClient();
    void modifierClient();
    void supprimerClient();
};

#endif // CLIENT_H
