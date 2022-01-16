#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ----------- Water temp sensor: DS18B20 --------------- 
// GPIO where the DS18B20 is connected to
#define oneWireBus 4
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
// ----------- [END] Water temp sensor: DS18B20 --------------- 


// ------------- WIFI ---------------
// Replace with your network credentials
const char* wifi_ssid     = "runal";
const char* wifi_password = "1234512345";

// REPLACE with your Domain name and URL path or IP address with path
const char* server_url = "http://192.168.43.75/Hydroponic-WebApp/add-data.php";

void setup() {
  // put your setup code here, to run once:
  
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();

  

void loop() {
  // put your main code here, to run repeatedly:
  
  // ----------- Water temp sensor: DS18B20 --------------- 
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  // ----------- [END] Water temp sensor: DS18B20 --------------- 


  
  // -------- WIFI --------
  //Check WiFi connection status
  

    // GET query
    String queryString = "?v1=" + String(temperatureC) + "&v2=" + String(temperatureF);
    Serial.print("queryString: ");
    Serial.println(queryString);
    
    
    
      
    
  //Send an HTTP GET request every -- seconds
  delay(100000);  
  
 
}
