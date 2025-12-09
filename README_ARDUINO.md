# Système de Notification RDV avec Arduino et LCD

## Description
Ce système permet d'afficher automatiquement sur un LCD 2x16 les rendez-vous des clients lorsqu'ils arrivent. La communication se fait entre Qt (application de gestion) et Arduino via le port série.

## Matériel requis

### Pour Arduino:
- Arduino Uno ou Nano
- LCD 2x16 avec module I2C (ex: PCF8574)
- Câbles de connexion

### Connexions LCD I2C:
- **SDA** → A4 (Arduino Uno) ou SDA (Arduino Nano)
- **SCL** → A5 (Arduino Uno) ou SCL (Arduino Nano)
- **VCC** → 5V
- **GND** → GND

## Installation

### 1. Code Arduino

1. Ouvrir Arduino IDE
2. Installer la bibliothèque `LiquidCrystal_I2C` via le gestionnaire de bibliothèques:
   - Outils → Gérer les bibliothèques
   - Rechercher "LiquidCrystal_I2C"
   - Installer la bibliothèque de Frank de Brabander

3. Ouvrir le fichier `arduino_lcd.ino`
4. Vérifier l'adresse I2C du LCD (généralement 0x27 ou 0x3F)
   - Si le LCD ne s'affiche pas, changer la ligne:
     ```cpp
     LiquidCrystal_I2C lcd(0x27, 16, 2);  // Essayer 0x3F si 0x27 ne fonctionne pas
     ```

5. Téléverser le code sur l'Arduino

### 2. Application Qt

1. Le module `serialport` a été ajouté au fichier `.pro`
2. Compiler le projet Qt normalement
3. Connecter l'Arduino au PC via USB
4. Lancer l'application Qt

## Fonctionnement

1. **Vérification automatique**: L'application Qt vérifie toutes les 60 secondes s'il y a des RDV en cours (date et heure actuelles)

2. **Communication série**: Lorsqu'un RDV est détecté, Qt envoie un message au format `RDV:123` où 123 est l'ID du client

3. **Affichage LCD**: Arduino reçoit le message et affiche:
   - Ligne 1: "ID [ID_CLIENT]"
   - Ligne 2: "RDV maintenant"

4. **Durée d'affichage**: Le message reste affiché pendant 5 secondes, puis retourne à "En attente..."

## Format de communication

- **Qt → Arduino**: `RDV:[ID_CLIENT]\n`
  - Exemple: `RDV:123\n`

- **Arduino → Qt** (optionnel, pour debug): `RDV recu: ID [ID_CLIENT]`

## Configuration

### Changer le port série dans Qt:
Si l'Arduino n'est pas détecté automatiquement, vous pouvez modifier le code dans `mainwindow.cpp` pour spécifier un port:

```cpp
arduino->connectArduino("COM3");  // Remplacer COM3 par votre port
```

### Changer la fréquence de vérification:
Dans `mainwindow.cpp`, modifier l'intervalle du timer:

```cpp
timerRDV->start(30000);  // Vérifie toutes les 30 secondes au lieu de 60
```

## Dépannage

### Le LCD ne s'affiche pas:
1. Vérifier les connexions I2C
2. Vérifier l'adresse I2C (0x27 ou 0x3F)
3. Vérifier que le module I2C est alimenté (LED allumée)

### Arduino non détecté:
1. Vérifier que le port série est disponible dans le Gestionnaire de périphériques Windows
2. Vérifier que le bon driver USB est installé
3. Essayer de spécifier manuellement le port dans le code Qt

### Messages non reçus:
1. Vérifier que le port série est le même dans Qt et Arduino IDE
2. Vérifier le débit baud (9600 dans les deux)
3. Vérifier les messages de debug dans la console Qt

## Notes importantes

- Les RDV sont vérifiés à l'heure exacte (ex: 14:00)
- Un même RDV ne sera affiché qu'une seule fois (évite les doublons)
- Le système fonctionne uniquement pendant que l'application Qt est ouverte

