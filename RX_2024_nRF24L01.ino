/***********************************************************/
/* Aula 41 - Robô radiocontrolado - Receptor */
/* Programação do robô constituído pelo chassi 2WD e */
/* controlado através do módulo nRF24L01 e joystick */
/* shield. */
/***********************************************************/
/* Biblioteca RF24 by TNRh 20, Avamander */
/* http://librarymanager/All#RF24#simple#modules */
/* https://github.com/nRF24/RF24/ */
/***********************************************************/
/* Define o endereço de comunicação entre os módulos de */
/* transmissão e recepção. O endereço deverá ser o mesmo */
/* no transmissor e no receptor. */
const byte endereco[6] = "00001";
/* Inclui a Biblioteca para controle do módulo rádio. */
#include <RF24.h>
/* Definições dos pinos IN1 a IN4 da ponte H. */
/* Para controlar a velocidade dos motores, esses pinos */
/* deverão ser conectados em portas com o recurso PWM. */
#define IN1 10 // Porta PWM ~10
#define IN2 9 // Porta PWM ~9
#define IN3 6 // Porta PWM ~6
#define IN4 5 // Porta PWM ~5
/* Variáveis que definem as potências dos motores (0 a 255).*/
int potA = 255;
int potB = 255;
/* Define os pinos de comunicação do módulo rádio. */
#define CSN 3
#define CE 4
/* Criamos um objeto de controle para o rádio. */
RF24 radio(CE, CSN);
/* Variável que receberá os comandos do controle. */
char comando;
/* Criando as funções de controle dos motores. */
/* Move para frente. */
void Frente() {
 /* Motor A */
 analogWrite(IN1, potA);
 analogWrite(IN2, 0);
 /* Motor B */
 analogWrite(IN3, potB);
 analogWrite(IN4, 0);
}
/* Move para trás. */
void Re() {
 /* Motor A */
 analogWrite(IN1, 0);
 analogWrite(IN2, potA);
 /* Motor B */
 analogWrite(IN3, 0);
 analogWrite(IN4, potB);
}
/* Giro no sentido horário. */
void GiroHorario() {
 /* Motor A */
 analogWrite(IN1, potA * 0.5);
 analogWrite(IN2, 0);
 /* Motor B */
 analogWrite(IN3, 0);
 analogWrite(IN4, potB * 0.5);
}
/* Giro no sentido anti-horário. */
void GiroAntiHorario() {
 /* Motor A */
 analogWrite(IN1, 0);
 analogWrite(IN2, potA * 0.5);
 /* Motor B */
 analogWrite(IN3, potB * 0.5);
 analogWrite(IN4, 0);
}
/* Para o chassi. */
void Pare() {
 /* Motor A */
 analogWrite(IN1, 0);
 analogWrite(IN2, 0);
 /* Motor B */
 analogWrite(IN3, 0);
 analogWrite(IN4, 0);
}
void setup() {
 /* Inicia com os motores parados. */
 Pare();
 /* Inicia o monitor serial na velocidade 9600 bauds. */
 Serial.begin(9600);
 /* Inicia o objeto de controle do rádio. */
 radio.begin();
 /* Configura o canal 1 de recepção (0 a 5). Restringe */
 /* que o canal só receberá dados deste endereço. */
 radio.openReadingPipe(1, endereco);
 /* Configura o nível de potência do módulo radio. */
 /* RF24_PA_MIN: Nível mínimo de potência. */
 /* RF24_PA_LOW: Nível de potência baixo. */
 /* RF24_PA_HIGH: Nível de potência alto. */
 /* RF24_PA_MAX: Nível máximo de potência. */
 radio.setPALevel(RF24_PA_MIN);
 /* Coloca o módulo no modo de escuta, ou seja, no */
 /* modo de recepção de dados. */
 radio.startListening();
}
void loop() {
 /* Se o módulo rádio receber algum dado, faça... */
 if (radio.available()) {
 /* Armazena os dados recebidos na variável comando. */
 radio.read(&comando, sizeof(comando));
 /* Imprime no monitor serial o comando recebido. */
 Serial.println("Comando recebido: " + String(comando));
 }
 switch (comando) {
 case '1':
 /* Defina a potencia dos motores para 100. */
 potA = 100;
 potB = 100;
 break;
 case '2':
 /* Defina a potencia dos motores para 150. */
 potA = 150;
 potB = 150;
 break;
 case '3':
 /* Defina a potencia dos motores para 200. */
 potA = 200;
 potB = 200;
 break;
 case '4':
 /* Defina a potencia dos motores para 255. */
 potA = 255;
 potB = 255;
 break;
 case 'F':
 /* Move para frente. */
 Frente();
 break;
 case 'D':
 /* Move para Direita. */
 GiroHorario();
 break;
 case 'E':
 /* Move para esquerda. */
 GiroAntiHorario();
 break;
 case 'R':
 /* Move para trás. */
 Re();
 break;
 default:
 /* Para o movimento. */
 Pare();
 break;
 }
}