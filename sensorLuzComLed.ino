int LDR = A0;
int luz;
int pinVermelho = 6;
int pinAmarelo = 8;
int pinVerde = 10;


int pouca = 100;
int media = 300;
int muita = 500;


void setup() {
   Serial.begin(9600);
   pinMode(LDR, INPUT);

  pinMode(pinVermelho, OUTPUT);
  pinMode(pinAmarelo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
}

void loop() {
  luz = analogRead(LDR);

  Serial.print("Luz : ");
  Serial.println(luz);


  if (luz < pouca) {
    digitalWrite(pinVerde, HIGH);
    digitalWrite(pinAmarelo, LOW);
    digitalWrite(pinVermelho, LOW);
    
    
  }

  if (luz > pouca && luz < muita) {
    digitalWrite(pinAmarelo, HIGH);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinVermelho, LOW);
    
  }

  if (luz >= muita) {
    digitalWrite(pinVermelho, HIGH);
    digitalWrite(pinAmarelo, LOW);
    digitalWrite(pinVerde, LOW);
    
  }
  
  delay(1000);
}
