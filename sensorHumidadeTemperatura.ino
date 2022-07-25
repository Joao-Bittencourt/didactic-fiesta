#include "DHT.h"

#define DHTPIN 4     

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); 

  dht.begin();
}

void loop() {

  float humityValue;
  humityValue = getSensorHumityData();

  float temperatureValue;
  temperatureValue = getSensorTemperatureData();

  Serial.print("Umidate : ");
  Serial.println(humityValue);

  Serial.print("Temperatura : ");
  Serial.println(temperatureValue);

  delay(5000);
  
}


float getSensorHumityData() {

  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println(F("Failed to read (humidity) from DHT sensor!"));
    return -1.00;
  } 

  return h;
}

float getSensorTemperatureData() {

  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read (temperature) from DHT sensor!"));
    return -1.00;
  } 

  return t;
}

