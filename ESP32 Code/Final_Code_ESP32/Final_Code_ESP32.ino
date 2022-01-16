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
const char* wifi_ssid     = "runalb.com - 5G";
const char* wifi_password = "2702runal@2702";

// REPLACE with your Domain name and URL path or IP address with path
const char* server_url = "http://192.168.1.20/Hydroponic-WebApp/add-data.php";

void setup() {
  // put your setup code here, to run once:
  
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();

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
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  // ----------- [END] Water temp sensor: DS18B20 --------------- 


  
  // -------- WIFI --------
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    // GET query
    String queryString = "?v1=" + String(temperatureC) + "&v2=" + String(temperatureF);
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
