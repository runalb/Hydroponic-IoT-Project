#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* wifi_ssid     = "runalb.com - 5G";
const char* wifi_password = "2702runal@2702";

// REPLACE with your Domain name and URL path or IP address with path
const char* server_url = "http://192.168.1.20/Hydroponic-WebApp/add-data.php";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 

  WiFi.begin(wifi_ssid, wifi_password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    //test data
    String queryString = "?v1=test4&v2=e2&v3=e3&v4=e4&v5=e5";
    Serial.print("queryString: ");
    Serial.println(queryString);
    
    //HTTP
    http.begin(server_url + queryString); //HTTP
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
  //Send an HTTP POST request every 5 seconds
  delay(5000);  
  
 
}
