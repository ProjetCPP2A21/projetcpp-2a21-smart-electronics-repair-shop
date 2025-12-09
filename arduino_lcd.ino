/*
 * Code Arduino pour afficher les RDV sur LCD 2x16 avec module I2C
 * 
 * Matériel requis:
 * - Arduino Uno/Nano
 * - LCD 2x16 avec module I2C (ex: PCF8574 ou similaire)
 * 
 * Connexions:
 * - SDA -> A4 (Arduino Uno) ou SDA (Arduino Nano)
 * - SCL -> A5 (Arduino Uno) ou SCL (Arduino Nano)
 * - VCC -> 5V
 * - GND -> GND
 * 
 * Bibliothèque nécessaire:
 * - LiquidCrystal_I2C (installer via le gestionnaire de bibliothèques Arduino)
 * 
 * Format de communication:
 * - Qt envoie: "RDV:123\n" où 123 est l'ID du client
 * - Arduino affiche: "ID 123" sur la ligne 1 et "RDV maintenant" sur la ligne 2
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialiser le LCD avec l'adresse I2C (généralement 0x27 ou 0x3F)
// Format: LiquidCrystal_I2C lcd(adresse, colonnes, lignes);
// Si 0x27 ne fonctionne pas, essayer 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

String messageBuffer = "";
bool messageComplete = false;

void setup() {
  // Initialiser la communication série à 9600 bauds
  Serial.begin(9600);
  
  // Initialiser le LCD
  lcd.init();
  lcd.backlight();
  
  // Afficher un message de démarrage
  lcd.setCursor(0, 0);
  lcd.print("Systeme RDV");
  lcd.setCursor(0, 1);
  lcd.print("En attente...");
  
  // Réserver de l'espace pour le buffer
  messageBuffer.reserve(50);
  
  delay(2000);
  lcd.clear();
}

void loop() {
  // Lire les données série
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    
    if (inChar == '\n') {
      messageComplete = true;
    } else {
      messageBuffer += inChar;
    }
  }
  
  // Traiter le message complet
  if (messageComplete) {
    traiterMessage(messageBuffer);
    messageBuffer = "";
    messageComplete = false;
  }
}

void traiterMessage(String message) {
  // Format attendu: "RDV:123" où 123 est l'ID du client
  // Ce format est utilisé à la fois par:
  // - La vérification automatique (toutes les 60 secondes)
  // - Le bouton "Alerter" manuel
  if (message.startsWith("RDV:")) {
    String idClient = message.substring(4);  // Extraire l'ID après "RDV:"
    
    // Afficher sur le LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ID " + idClient);
    lcd.setCursor(0, 1);
    lcd.print("RDV maintenant");
    
    // Confirmer la réception (optionnel, pour debug)
    Serial.print("RDV recu: ID ");
    Serial.println(idClient);
    
    // Attendre 5 secondes avant de revenir à l'état d'attente
    delay(5000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("En attente...");
  }
}

