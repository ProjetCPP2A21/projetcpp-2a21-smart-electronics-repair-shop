const int AMP_PIN = A0;
const unsigned long sampleWindow = 50;
const int threshold = 80;

void setup() {
  Serial.begin(9600);
  Serial.println("READY");
}

void loop() {
  unsigned long startMillis = millis();
  int signalMax = 0;
  int signalMin = 1024;

  while (millis() - startMillis < sampleWindow) {
    int sample = analogRead(AMP_PIN);
    if (sample > signalMax) signalMax = sample;
    if (sample < signalMin) signalMin = sample;
  }

  int peakToPeak = signalMax - signalMin;

  if (peakToPeak > threshold) {
    Serial.println("CLAP2");   // ← CHANGED FROM "CLAP DETECTED" TO "CLAP2"
    delay(300);
  }

  // ← NEW: receive number from Qt
  if (Serial.available()) {
    int count = Serial.parseInt();
    Serial.print("FOURNISSEURS: ");
    Serial.println(count);
    while (Serial.available()) Serial.read();  // clear buffer
  }
}