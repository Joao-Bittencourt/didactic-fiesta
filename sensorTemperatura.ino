int tempSensor = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {  
  controlaCensorTemperatura();
}


int controlaCensorTemperatura() {
	float voltage, degreesC;
  
	voltage = (analogRead(tempSensor) * 0.004882814);
	degreesC = (voltage - 0.5) * 100;

	Serial.print("Temp: ");
	Serial.print(degreesC);
	
	delay(3000);  
  
  	return 0;
}
 

