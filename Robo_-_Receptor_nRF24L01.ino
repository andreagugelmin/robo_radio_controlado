/*******************************************************/
/* Aula 41  - Robô radiocontrolado - Receptor          */
/* Programação do robô constituído pelo chassi 2WD e   */
/* controlado através do módulo nRF24L01 e joystick    */
/* shield.                                             */
/*******************************************************/
/* Biblioteca L298N by Andrea Lombardo                 */
/* http://librarymanager/All#L298N#EASY                */
/* https://github.com/AndreaLombardo/L298N             */
/* Biblioteca RF24 by TNRh 20, Avamander               */
/* http://librarymanager/All#RF24#simple#modules       */
/* https://github.com/nRF24/RF24/                      */
/*******************************************************/

/* Define o endereço de comunicação entre os módulos de*/
/* transmissão e recepção. O endereço deverá ser o mesmo*/
/* no transmissor e no receptor.                       */
const byte endereco[6] = "00001";

/* Inclui a Biblioteca para controle da ponte H.       */
#include <L298NX2.h>

/* Inclui a Biblioteca para controle do módulo rádio.  */
#include <RF24.h>

/* Define os pinos de controle da ponte H.             */
#define ENA 10 /* ENA precisa estar em uma porta PWM   */
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENB 5  /* ENB precisa estar em uma porta PWM   */

/* Define os pinos de comunicação do módulo rádio.     */
#define CSN 3
#define CE 4

/* Criamos um objeto de controle para os motores.      */
L298NX2 motores(ENA, IN1, IN2, ENB, IN3, IN4);

/* Criamos um objeto de controle para o rádio.         */
RF24 radio(CE, CSN);

/* Variável que receberá os comandos do controle.      */
char comando = ' ';

void setup() {
  /* Inicia com os motores parados.                    */
  motores.stop();
  /* Inicia o monitor serial na velocidade 9600 bauds. */
  Serial.begin(9600);
  /* Inicia o objeto de controle do rádio.             */
  radio.begin();
  /* Configura o canal 1 de recepção (0 a 5). Restringe*/
  /* que o canal só receberá dados deste endereço.     */
  radio.openReadingPipe(1, endereco);
  /* Configura o nível de potência do módulo radio.    */
  /* RF24_PA_MIN: Nível mínimo de potência.            */
  /* RF24_PA_LOW: Nível de potência baixo.             */
  /* RF24_PA_HIGH: Nível de potência alto.             */
  /* RF24_PA_MAX: Nível máximo de potência.            */
  radio.setPALevel(RF24_PA_MIN);
  /* Coloca o módulo no modo de escuta, ou seja, no    */
  /* modo de recepção de dados.                        */
  radio.startListening();
}

void loop() {
  /* Se o módulo rádio receber algum dado, faça...       */
  if (radio.available()) {
    /* Armazena os dados recebidos na variável comando.*/
    radio.read(&comando, sizeof(comando));
    /* Imprime no monitor serial o comando recebido.   */
    Serial.println("Comando recebido: " + String(comando));
  }
  /* Se o comando recebido for 1, faça...              */
  if (comando == '1') {
    /* Defina a potencia dos motores pra 100.          */
    motores.setSpeed(100);
  }
  /* Senão, se o comando recebido for 2, faça...       */
  else if (comando == '2') {
    /* Defina a potencia dos motores pra 150.          */
    motores.setSpeed(150);
  }
  /* Senão, se o comando recebido for 3, faça...       */
  else if (comando == '3') {
    /* Defina a potencia dos motores pra 200.          */
    motores.setSpeed(200);
  }
  /* Senão, se o comando recebido for 4, faça...       */
  else if (comando == '4') {
    /* Defina a potencia dos motores pra 255.          */
    motores.setSpeed(255);
  }
  /* Senão, se o comando recebido for F, faça...       */
  else if (comando == 'F') {
    /* Move para frente.                               */
    motores.forward();
  }
  /* Senão, se o comando recebido for D, faça...       */
  else if (comando == 'D') {
    /* Move para Direita.                              */
    motores.backwardB();
    motores.forwardA();
  }
  /* Senão, se o comando recebido for R, faça...       */
  else if (comando == 'R') {
    /* Move para trás.                                 */
    motores.backward();
  }
  /* Senão, se o comando recebido for E, faça...       */
  else if (comando == 'E') {
    /* Move para esquerda.                             */
    motores.backwardA();
    motores.forwardB();
  }
  /* Senão, se o comando recebido for P, faça...       */
  else if (comando == 'P') {
    /* Para o movimento.                               */
    motores.stop();
  }
}
