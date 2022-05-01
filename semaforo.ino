int pinVermelho = 10;
int pinAmarelo = 11;
int pinVerde = 12;


void setup() {
 
  pinMode(pinVermelho, OUTPUT);
  pinMode(pinAmarelo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
} 

void loop() {
  controlaVermelho();
  controlaAmarelo();
  controlaVerde();

}

int controlaVermelho() {
  digitalWrite(pinVermelho, HIGH);
  delay(5000);
  digitalWrite(pinVermelho, LOW); 
  
  return 0;  
}

int controlaAmarelo() {
  
  digitalWrite(pinAmarelo, HIGH);
  delay(2000);
  digitalWrite(pinAmarelo, LOW);
  
  return 0;
}

int controlaVerde() {

  digitalWrite(pinVerde, HIGH);
  delay(4000);
  digitalWrite(pinVerde, LOW);
  
  return 0;
}
