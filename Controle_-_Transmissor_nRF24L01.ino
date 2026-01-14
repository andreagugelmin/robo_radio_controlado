/********************************************************/
/* Aula 41  - Robô radiocontrolado - Transmissor        */
/* Programação do robô constituído pelo chassi 2WD e    */
/* controlado através do módulo nRF24L01 e joystick     */
/* shield.                                              */
/********************************************************/
/* Biblioteca RF24 by TNRh 20, Avamander                */
/* http://librarymanager/All#RF24#simple#modules        */
/* https://github.com/nRF24/RF24/                       */
/********************************************************/

/* Define o endereço de comunicação entre os módulos de */
/* transmissão e recepção. O endereço deverá ser o mesmo*/
/* no transmissor e no receptor.                        */
const byte endereco[6] = "00001";

/* Inclui a Biblioteca para controle do módulo rádio.   */
#include <RF24.h>

/* Define os pinos de comunicação do módulo rádio.      */
#define CSN 10
#define CE 9

/* Define os pinos de controle do joystick.             */
#define eixoX A0
#define eixoY A1
#define botaoA 2
#define botaoB 3
#define botaoC 4
#define botaoD 5

/* Criamos um objeto de controle para o rádio.         */
RF24 radio(CE, CSN);

void setup() {
  /* Inicia o monitor serial na velocidade 9600 bauds. */
  Serial.begin(9600);
  /* Inicia o objeto de controle do rádio.             */
  radio.begin();
  /* Configura o endereço que será usado para enviar   */
  /* os comandos.                                      */
  radio.openWritingPipe(endereco);
  /* Configura o nível de potência do módulo rádio.    */
  /* RF24_PA_MIN: Nível mínimo de potência.            */
  /* RF24_PA_LOW: Nível de potência baixo.             */
  /* RF24_PA_HIGH: Nível de potência alto.             */
  /* RF24_PA_MAX: Nível máximo de potência.            */
  radio.setPALevel(RF24_PA_MIN);
  /* Desativa o modo de escuta mantendo apenas o modo  */
  /* de transmissão de dados.                          */
  radio.stopListening();
  /* Configura os pinos dos botões como entrada        */
  /* ativando o resistor interno.                      */
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(botaoC, INPUT_PULLUP);
  pinMode(botaoD, INPUT_PULLUP);
}

void loop() {
  /* Armazena nas variáveis os dados da posição do     */
  /* joystick nos eixos X e Y.                         */
  int joyX = analogRead(eixoX);
  int joyY = analogRead(eixoY);
  /* Variável usada para armazenar o comando a ser     */
  /* enviado, inicialmente com o comando P.            */
  char comando = 'P';
  /* Se o botão A for pressionado, faça...             */
  if (digitalRead(botaoA) == LOW) {
    /* Defina o comando 1.                             */
    comando = '1';
  }
  /* Senão, se o botão B for pressionado, faça...      */
  else if (digitalRead(botaoB) == LOW) {
    /* Defina o comando 2.                             */
    comando = '2';
  }
  /* Senão, se o botão C for pressionado, faça...      */
  else if (digitalRead(botaoC) == LOW) {
    /* Defina o comando 3.                             */
    comando = '3';
  }
  /* Senão, se o botão D for pressionado, faça...      */
  else if (digitalRead(botaoD) == LOW) {
    /* Defina o comando 4.                             */
    comando = '4';
  }
  /* Senão, se o joystick for movido para frente,      */
  /* faça...                                           */
  else if (joyY > 700) {
    /* Defina o comando F.                             */
    comando = 'F';
  }
  /* Senão, se o joystick for movido para trás,        */
  /* faça...                                           */
  else if (joyY < 300) {
    /* Defina o comando R.                             */
    comando = 'R';
  }
  /* Senão, se o joystick for movido para direita,     */
  /* faça...                                           */
  else if (joyX > 700) {
    /* Defina o comando D.                             */
    comando = 'D';
  }
  /* Senão, se o joystick for movido para esquerda,    */
  /* faça...                                           */
  else if (joyX < 300) {
    /* Defina o comando E.                             */
    comando = 'E';
  }
  /* Envia o comando atual armazenado na variável.     */
  radio.write(&comando, sizeof(comando));
  /* Imprime no monitor serial o comando enviado.      */
  Serial.println("Comando enviado: " + String(comando));
}
