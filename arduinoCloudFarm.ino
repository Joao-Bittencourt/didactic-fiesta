#include "thingProperties.h"

#include "DHT.h"

#define DHTPIN 4
#define umidadeDoSoloPin 2
#define sensorChuvaPin 5

#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(9600);
    // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
    delay(1500);

    // Defined in thingProperties.h
    initProperties();

    // Connect to Arduino IoT Cloud
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);

    /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();

    pinMode(umidadeDoSoloPin, INPUT);
    dht.begin();
}

void loop()
{
    ArduinoCloud.update();

    humity = getSensorHumityData();
    temperature = getSensorTemperatureData();

    raining = isRaining();
    soilMoisture = getSensorSoilMoistureData();

    delay(5000);
}

float getSensorHumityData()
{

    float h = dht.readHumidity();
    if (isnan(h))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return -1.00;
    }

    return h;
}

float getSensorTemperatureData()
{

    float t = dht.readTemperature();
    if (isnan(t))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return -1.00;
    }

    return t;
}

int getSensorSoilMoistureData()
{

    int soilMoistureValue = analogRead(umidadeDoSoloPin);

    if (isnan(soilMoistureValue))
    {
        return 0;
    }
    return soilMoistureValue;
}

int isRaining() {
 int sensorChuvaValue = analogRead(sensorChuvaPin);

    if (isnan(sensorChuvaValue))
    {
        return 0;
    }

    // o valor de comparação varia dependendo do vcc (3v ou 5v) e resistor utilizado ( 10k ohms utilizado)
    if (sensorChuvaValue > 2000) {
        return 1;
    }
  
    return 0;
}
