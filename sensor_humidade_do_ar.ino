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

  Serial.println("humidate : ");
  Serial.println(humityValue);

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

