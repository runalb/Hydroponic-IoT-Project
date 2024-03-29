// Example testing sketch for various DHT humidity/temperature sensors written by ladyada
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <DHT.h> //library for DHT temp sensor

#define DHTPIN 2     // D2

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float dhtHumidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float dhtTemperatureCelsius = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float dhtTemperatureFahrenheit = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(dhtHumidity) || isnan(dhtTemperatureCelsius) || isnan(dhtTemperatureFahrenheit)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  // Compute heat index in Celsius (isFahreheit = false)
  float heatIndexCelsius = dht.computeHeatIndex(dhtCelsiusTemperature, dhtHumidity, false);
  // Compute heat index in Fahrenheit (the default)
  float heatIndexFahrenheit = dht.computeHeatIndex(dhtFahrenheiTemperature, dhtHumidity);
  
  // Print DHT - Temp Sensor Values on Serial Monitor
  Serial.println("DHT - Temp Sensor: ");
  Serial.println("  dhtHumidity: " + String(dhtHumidity) + "%");
  Serial.println("  dhtTemperatureCelsius: " + String(dhtTemperatureCelsius) + "°C");
  Serial.println("  dhtTemperatureFahrenheit: " + String(dhtTemperatureFahrenheit) + "°F");
  Serial.println("  heatIndexCelsius: " + String(heatIndexCelsius) + "°C");
  Serial.println("  heatIndexFahrenheit: " + String(heatIndexFahrenheit) + "°F");
  Serial.println(" ");
  
}
