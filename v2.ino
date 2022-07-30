#include <HTTPClient.h>
#include <WiFi.h>

#include "DHT.h"

#define DHTPIN 4     
#define umidadeDoSoloPin 2

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

#define MAX 100

const char* ssid = "RONDON";
const char* password = "1234567890";

String apiKey = "RZ9PSR9D5LJVIIBA";
//Your Domain name with URL path or IP address with path
String serverName = "https://api.thingspeak.com/update?api_key="+ apiKey +"&field1=";
//String serverName = "https://blynk.cloud/external/api/update?token=ffujYGgbf805tgsf&v5=";

void setup() {
  Serial.begin(115200); 
  wifiConectStartup();
  pinMode(umidadeDoSoloPin, INPUT);
  dht.begin();
}

void wifiConectStartup() {
  
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
}

void loop() {

  float humityValue;
  humityValue = getSensorHumityData();

  float temperatureValue;
  temperatureValue = getSensorTemperatureData();

  if (humityValue >0) {
    Serial.println("humidate a ser persistida : ");
    Serial.println(humityValue);


    char buf[MAX];
  
    //String valueToPersist = gcvt(humityValue, 4, buf);
    String valueToPersist = "ols";
      sendDataToAPI(valueToPersist);
  } else {
      Serial.println(F("deu ruim"));
    
    }
/*
  if (temperatureValue >0) {
    Serial.println("temperatura a ser persistida : ");
    Serial.println(temperatureValue);

      //sendDataToAPI(valueToPersist);
  } else {
      Serial.println(F("deu ruim"));
    
    }

    //Serial.println("humidade do solo a ser persistida : ");
    //Serial.println( analogRead(umidadeDoSoloPin));
    */
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

float getSensorTemperatureData() {

  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return -1.00;
  } 

  return t;
}


void senDaatToAPIPost(String postData) {
  
  
  client.println( "POST /update HTTP/1.1" );
  client.println( "Host: api.thingspeak.com" );
  client.println( "Connection: close" );
  client.println( "Content-Type: application/x-www-form-urlencoded" );
  client.println( "Content-Length: " + String( postData.length() ) );
  client.println();
  client.println( postData );

  Serial.println( postData );
        
  String answer=getResponse();
  Serial.println( answer );
  
}

String getResponse(){
  String response;
  long startTime = millis();

  delay( 200 );
  

  if( client.available() > 0 ){ // Get response from server.
     char charIn;
     do {
         charIn = client.read(); // Read a char from the buffer.
         response += charIn;     // Append the char to the string response.
        } while ( client.available() > 0 );
    }
  client.stop();
        
  return response;
}

void sendDataToAPI(String valueToSend) {
  

    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + 15;
      //valueToSend;
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
