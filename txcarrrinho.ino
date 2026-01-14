#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10);  // CE, CSN
const byte endereco[6] = "00302"; // Endereço de comunicação


int eixoX = 0;
int eixoY = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(endereco);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening(); // Modo TX


  pinMode(A0, INPUT); // Eixo X
  pinMode(A1, INPUT); // Eixo Y
}

void loop() {

  eixoX = analogRead(A0);
  eixoY = analogRead(A1);


  int dados[2] = {eixoX, eixoY};
  radio.write(&dados, sizeof(dados));


  Serial.print("Eixo X: ");
  Serial.print(eixoX);
  Serial.print(" | Eixo Y: ");
  Serial.println(eixoY);

  delay(50); 
}
