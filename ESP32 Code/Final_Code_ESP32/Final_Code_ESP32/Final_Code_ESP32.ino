#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h> //library for DS18B20
#include <DallasTemperature.h> //library for DS18B20
#include <DHT.h> //library for DHT temp sensor


// ----------- Sensors Connected to GPIO Pins --------------- 
#define oneWireBus 4  //D4 is connected to DS18B20 water temp sensor
#define DHTPIN 2     // D2 is connected to DHT temp sensor



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
  float waterTemperatureFahrenhei = sensors.getTempFByIndex(0);
  Serial.print(waterTemperatureCelsius);
  Serial.println("ºC");
  Serial.print(waterTemperatureFahrenhei);
  Serial.println("ºF");
  // ----------- [END] Water temp sensor: DS18B20 --------------- 


  // ----------- Temp sensor: DHT ---------------
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float dhtHumidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float dhtCelsiusTemperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float dhtFahrenheiTemperature = dht.readTemperature(true);

  // Compute heat index in Celsius (isFahreheit = false)
  float heatIndexCelsius = dht.computeHeatIndex(dhtCelsiusTemperature, dhtHumidity, false);
  // Compute heat index in Fahrenheit (the default)
  float heatIndexFahrenheit = dht.computeHeatIndex(dhtFahrenheiTemperature, dhtHumidity);
  
  // Print DHT Sensor Values on Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(dhtHumidity);
  Serial.print(F("% "));
  
  Serial.print(F("Temperature: "));
  Serial.print(dhtCelsiusTemperature);
  Serial.print(F("°C "));
  Serial.print(dhtFahrenheiTemperature);
  Serial.print(F("°F "));
  
  Serial.print(F("Heat index: "));
  Serial.print(heatIndexCelsius);
  Serial.print(F("°C "));
  Serial.print(heatIndexFahrenheit);
  Serial.println(F("°F"));
  // ----------- [END] Temp sensor: DHT --------------- 


  
  // -------- WIFI --------
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    // GET query
    String waterTempSensor = "?waterTemperatureCelsius=" + String(waterTemperatureCelsius) + "&waterTemperatureFahrenhei=" + String(waterTemperatureFahrenhei);
    String dhtTempSensor = "&dhtHumidity=" + String(dhtHumidity) + "&dhtCelsiusTemperature=" + String(dhtCelsiusTemperature) + "&dhtFahrenheiTemperature=" + String(dhtFahrenheiTemperature) + "&heatIndexCelsius=" + String(heatIndexCelsius) + "&heatIndexFahrenheit=" + String(heatIndexFahrenheit);
    String queryString = waterTempSensor + dhtTempSensor ;
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
  //Send an HTTP GET request every -- seconds
  delay(100000);  
}
