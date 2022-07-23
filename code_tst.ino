#include <HTTPClient.h>
#include <WiFi.h>

#include "DHT.h"

#define DHTPIN 4     

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


#define MAX 100

const char* ssid = "RONDON";
const char* password = "1234567890";

//Your Domain name with URL path or IP address with path
String serverName = "https://api.thingspeak.com/update?api_key=OML10E8ZI9POFXYK&field1=";

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

  dht.begin();
}

void loop() {

  float humityValue;
  humityValue = getSensorHumityData();

  if (humityValue >0) {
    Serial.println("humidate a ser persistida : ");
    Serial.println(humityValue);


    char buf[MAX];
  
    String valueToPersist = gcvt(humityValue, 4, buf);
    
      sendDataToAPI(valueToPersist);
  } else {
      Serial.println(F("deu ruim"));
    
    }
  delay(5000);
  
}


float getSensorHumityData() {

  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return -1.00;
  } 

  return h;
}


void sendDataToAPI(String valueToSend) {
  

    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + valueToSend;
      Serial.println(serverPath);
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
 
}
