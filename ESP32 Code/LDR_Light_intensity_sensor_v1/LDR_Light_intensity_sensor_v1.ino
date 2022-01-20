#define LDRPIN 13   // D13 (ADC) is connected to LDR 

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
}

void loop() {
  // reads the input on analog pin
  int ldrLightIntensity = analogRead(LDRPIN);

  // Print LDR Sensor Values on Serial Monitor
  Serial.println("LDR - Light Intensity Sensor: ");
  Serial.println("  ldrLightIntensity: " + String(ldrLightIntensity));
  Serial.println(" ");
  delay(5000);
}
