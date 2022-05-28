#include <Servo.h>

Servo servo_esquerdo;
Servo servo_direito;

int sensor_esquerdo = A1;
int sensor_direito = A2;

void setup() {
    servo_esquerdo.attach(10);
    servo_direito.attach(11);
}

void loop() {
    movimentaParaFrente();
    movimentaSeSairDaArena();
}

void movimentaSeSairDaArena() {

    int valorCorEsquerdo = leSensorCorBranco(sensor_esquerdo);
    int valorCorDireito = leSensorCorBranco(sensor_direito);

    int valorBranco = 700;

    if (valorCorEsquerdo <= valorBranco) {
        movimentaParaTras();
        movimentaParaDireita();
    }

    if (valorCorDireito <= valorBranco) {
        movimentaParaTras();
        movimentaParaEsquerda();
    }

    delay(400);
}

void movimentaParaEsquerda() {
    servo_esquerdo.write(180);
    servo_direito.write(180);
}

void movimentaParaDireita() {
    movimenta(servo_esquerdo, 0, 0);
    movimenta(servo_direito, 0, 400);
}

void movimentaParaFrente() {
    movimenta(servo_direito, 10, 0);
    movimenta(servo_esquerdo, 180, 400);
}

void movimentaParaTras() {
    movimenta(servo_direito, 180, 0);
    movimenta(servo_esquerdo, 10, 400);
    delay(400);
}

void movimenta(Servo motor, int velocidade, int espera) {
    motor.write(velocidade);
    delay(espera);
}

int leSensorCorBranco(int sensor) {
    int valor = (int) analogRead(sensor);

    delay(1);
    return valor;
}