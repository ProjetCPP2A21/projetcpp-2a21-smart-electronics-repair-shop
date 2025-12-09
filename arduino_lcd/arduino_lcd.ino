

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Format: LiquidCrystal_I2C lcd(adresse, colonnes, lignes);
LiquidCrystal_I2C lcd(0x27, 16, 2);  
String messageBuffer = "";
bool messageComplete = false;

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  
 
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

