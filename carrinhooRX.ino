#include <SPI.h>
#include <RF24.h>


RF24 radio(9, 10);                 // CE, CSN
const byte endereco[6] = "00302";  // Endereço de comunicação


int eixoX = 0;
int eixoY = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, endereco);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();  // Modo RX


  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);  // PWM
  pinMode(6, OUTPUT);  // PWM
  pinMode(7, OUTPUT);
}

void loop() {

  if (radio.available()) {
    int dados[2];
    radio.read(&dados, sizeof(dados));

    eixoX = dados[0];
    eixoY = dados[1];


    Serial.print("Eixo X Recebido: ");
    Serial.print(eixoX);
    Serial.print(" | Eixo Y Recebido: ");
    Serial.println(eixoY);


    if (eixoX > 500 && eixoX < 510 && eixoY > 505 && eixoY < 515) {
      parar();
    } else if (eixoX < 0 && eixoY < 0) {
      esquerdafianco();
    } else if (eixoX < 0 && eixoY > 1023) {
      direitafianco();
    } else if (eixoX < 499) {
      frente();
    } else if (eixoX > 511) {
      re();
    } else if (eixoY < 505) {
      esquerdaleve();
    } else if (eixoY > 515) {
      direitaleve();
    }
  }
}


void frente() {
  digitalWrite(4, 0);
  analogWrite(5, 230);  // PWM
  analogWrite(6, 250);  // PWM
  digitalWrite(7, 0);
}

void esquerdaleve() {
  digitalWrite(4, 1);
  analogWrite(5, 90);    // PWM
  analogWrite(6, 255);  // PWM
  digitalWrite(7, 0);
}

void direitaleve() {
  digitalWrite(4, 0);
  analogWrite(5, 255);  // PWM
  analogWrite(6, 90);    // PWM
  digitalWrite(7, 1);
}

void re() {
  digitalWrite(4, 1);
  analogWrite(5, 30);  // PWM
  analogWrite(6, 0);  // PWM
  digitalWrite(7, 1);
}
void parar() {
  digitalWrite(4, 0);
  analogWrite(5, 0);  // PWM
  analogWrite(6, 0);  // PWM
  digitalWrite(7, 0);
}
void esquerdafianco() {
  digitalWrite(4, 1);
  analogWrite(5, 150);  // PWM
  analogWrite(6, 255);  // PWM
  digitalWrite(7, 0);
}
void direitafianco() {
  digitalWrite(4, 0);
  analogWrite(5, 255);  // PWM
  analogWrite(6, 150);  // PWM
  digitalWrite(7, 1);
}