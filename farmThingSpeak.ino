#include <HTTPClient.h>
#include <WiFi.h>
#include "ThingSpeak.h"
#include "secrets.h"

#include "DHT.h"

#define DHTPIN 4     
#define umidadeDoSoloPin 34
#define sensorChuvaPin 5

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  ThingSpeak.begin(client);
  
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

  bool raining;
  raining = isRaining();

  float soilMoisture;
  soilMoisture = getSensorSoilMoistureData();

    // set the fields with the values
    ThingSpeak.setField(1, humityValue);
    ThingSpeak.setField(2, temperatureValue);
    ThingSpeak.setField(3, soilMoisture);
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(channel, apiKey);

    Serial.print("response code: ");
    Serial.println(x);
    
    delay(5000);
  
}

float getSensorHumityData() {

    float h = dht.readHumidity();
    if (isnan(h)) {
        //Serial.println(F("Failed to read from DHT sensor!"));
        return -1.00;
    }

    return h;
}

float getSensorTemperatureData() {

    float t = dht.readTemperature();
    if (isnan(t)) {
        //Serial.println(F("Failed to read from DHT sensor!"));
        return -1.00;
    }

    return t;
}

int getSensorSoilMoistureData() {

    int soilMoistureValue = analogRead(umidadeDoSoloPin);
        
    if (isnan(soilMoistureValue)) {
        return 0;
    }
    return soilMoistureValue;
}

bool isRaining() {
 int sensorChuvaValue = analogRead(sensorChuvaPin);

    if (isnan(sensorChuvaValue)) {
        return false;
    }

    // o valor de comparação varia dependendo do vcc (3v ou 5v) e resistor utilizado ( 10k ohms utilizado)
    if (sensorChuvaValue > 2000) {
        return true;
    }
  
    return false;
}

