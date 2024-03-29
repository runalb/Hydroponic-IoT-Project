// v4 - Final

#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h> //library for DS18B20
#include <DallasTemperature.h> //library for DS18B20
#include <DHT.h> //library for DHT temp sensor


// ----------- Sensors Connected to GPIO Pins --------------- 
#define oneWireBus 4  //D4 is connected to DS18B20 water temp sensor
#define DHTPIN 2     // D2 is connected to DHT temp sensor
#define LDRPIN 13   // D13 (ADC) is connected to LDR 
#define PHPIN 12   // D12 (ADC) is connected to ph Sensor 




// ----------- Water temp sensor: DS18B20 --------------- 
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
// ----------- [END] Water temp sensor: DS18B20 --------------- 



// ----------- Temp sensor: DHT --------------- 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
// ----------- [END] Temp sensor: DHT --------------- 



// ------------- WIFI ---------------
// Replace with your network credentials
const char* wifi_ssid     = "wifiname";
const char* wifi_password = "password";

// REPLACE with your Domain name and URL path or IP address with path
const char* server_url = "http://192.168.1.20/Hydroponic-WebApp/add-data.php";

void setup() {
  // put your setup code here, to run once:
  
  // Start the Serial Monitor
  Serial.begin(115200);
  
  // Start the DS18B20 sensor
  sensors.begin();
  
  // Start the DHT sensor
  dht.begin(); 

  // -------- WIFI --------
  WiFi.begin(wifi_ssid, wifi_password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println("");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // ----------- Water temp sensor: DS18B20 --------------- 
  sensors.requestTemperatures(); 
  float waterTemperatureCelsius = sensors.getTempCByIndex(0);
  float waterTemperatureFahrenheit = sensors.getTempFByIndex(0);

  // Print DS18B20 - Water Temp Sensor Values on Serial Monitor
  Serial.println("DS18B20 - Water Temp Sensor: ");
  Serial.println("  waterTemperatureCelsius: " + String(waterTemperatureCelsius) + "°C");
  Serial.println("  waterTemperatureFahrenheit: " +  String(waterTemperatureFahrenheit) + "°F");
  Serial.println(" ");
  // ----------- [END] Water temp sensor: DS18B20 --------------- 



  // ----------- Temp sensor: DHT ---------------
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float dhtHumidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float dhtTemperatureCelsius = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float dhtTemperatureFahrenheit = dht.readTemperature(true);

  // Compute heat index in Celsius (isFahreheit = false)
  float heatIndexCelsius = dht.computeHeatIndex(dhtTemperatureCelsius, dhtHumidity, false);
  // Compute heat index in Fahrenheit (the default)
  float heatIndexFahrenheit = dht.computeHeatIndex(dhtTemperatureFahrenheit, dhtHumidity);
  
  // Print DHT - Temp Sensor Values on Serial Monitor
  Serial.println("DHT - Temp Sensor: ");
  Serial.println("  dhtHumidity: " + String(dhtHumidity) + "%");
  Serial.println("  dhtTemperatureCelsius: " + String(dhtTemperatureCelsius) + "°C");
  Serial.println("  dhtTemperatureFahrenheit: " + String(dhtTemperatureFahrenheit) + "°F");
  Serial.println("  heatIndexCelsius: " + String(heatIndexCelsius) + "°C");
  Serial.println("  heatIndexFahrenheit: " + String(heatIndexFahrenheit) + "°F");
  Serial.println(" ");
  // ----------- [END] Temp sensor: DHT --------------- 



  // ----------- LDR - Light Intensity Sensor --------------- 
  int ldrLightIntensity = analogRead(LDRPIN);
  // Print LDR Sensor Values on Serial Monitor
  Serial.println("LDR - Light Intensity Sensor: ");
  Serial.println("  ldrLightIntensity: " + String(ldrLightIntensity));
  Serial.println(" ");
  // ----------- [END] LDR - Light Intensity Sensor --------------- 
  


  
  // ----------- ph Sensor --------------- 
  float phValue = analogRead(PHPIN);
  // Print ph Sensor Values on Serial Monitor
  Serial.println("ph Sensor: ");
  Serial.println("  phValue: " + String(phValue));
  Serial.println(" ");
  // ----------- [END] ph Sensor --------------- 
  


  // -------- WIFI --------
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    // GET query
    String waterTempSensor = "?waterTemperatureCelsius=" + String(waterTemperatureCelsius) + "&waterTemperatureFahrenheit=" + String(waterTemperatureFahrenheit);
    String dhtTempSensor = "&dhtHumidity=" + String(dhtHumidity) + "&dhtTemperatureCelsius=" + String(dhtTemperatureCelsius) + "&dhtTemperatureFahrenheit=" + String(dhtTemperatureFahrenheit) + "&heatIndexCelsius=" + String(heatIndexCelsius) + "&heatIndexFahrenheit=" + String(heatIndexFahrenheit);
    String ldrSensor = "&ldrLightIntensity=" + String(ldrLightIntensity);
    String phSensor = "&phValue=" + String(phValue);

    
    String queryString = waterTempSensor + dhtTempSensor + ldrSensor + phSensor ;
    
    Serial.print("queryString: ");
    Serial.println(queryString);
    
    //HTTP
    http.begin(server_url + queryString); 
    int httpResponseCode = http.GET();

    // httpCode will be negative on error
    if(httpResponseCode > 0) {
      // file found at server
      if(httpResponseCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      } 
      else {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpResponseCode);
      }
    } 
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }
   
   
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //delay  -- seconds
  delay(100000);  
}
