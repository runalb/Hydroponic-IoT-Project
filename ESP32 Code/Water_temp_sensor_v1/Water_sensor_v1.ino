#include <OneWire.h>
#include <DallasTemperature.h>

// GPIO where the DS18B20 is connected to
#define oneWireBus 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); 
  float waterTemperatureCelsius = sensors.getTempCByIndex(0);
  float waterTemperatureFahrenheit = sensors.getTempFByIndex(0);
  
  // Print DS18B20 - Water Temp Sensor Values on Serial Monitor
  Serial.println("DS18B20 - Water Temp Sensor: ");
  Serial.println("  waterTemperatureCelsius: " + String(waterTemperatureCelsius) + "°C");
  Serial.println("  waterTemperatureFahrenheit: " +  String(waterTemperatureFahrenheit) + "°F");
  Serial.println(" ");
  delay(5000);
}
