//Bibliotecas//


#include <Bluepad32.h>


ControllerPtr meusControles[BP32_MAX_GAMEPADS];


//Entradas na ESP32 e Variáveis//


#define A11 25   //Esquerda Frente
#define A12 33   //Esquerda Trás
#define PWNA 13  //Esquerda Potência


#define B11 26   //Direita Frente
#define B12 27   //Direita Trás
#define PWNB 14  //Direita Potência


#define BUZZER 19


int VELOCIDADE =255;
int i;


//Setup//




void setup() {
  Serial.begin(115200);


  pinMode(PWNA, OUTPUT);
  pinMode(A11, OUTPUT);
  pinMode(A12, OUTPUT);


  pinMode(PWNB, OUTPUT);
  pinMode(B11, OUTPUT);
  pinMode(B12, OUTPUT);


  pinMode(BUZZER, OUTPUT);


  BP32.setup(&onConnectedController, &onDisconnectedController);


}


//Estabelece a conexão segura com os controles e os salva na matriz//




void onConnectedController(ControllerPtr ctl) {
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (meusControles[i] == nullptr) {
      tone(BUZZER,2500);
      delay(1000);
      noTone(BUZZER);
      delay(200);
      meusControles[i] = ctl;
      break;
    }
  }
}


//Desconenecta os controles e os retira da matriz//




void onDisconnectedController(ControllerPtr ctl) {
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (meusControles[i] == ctl) {
      meusControles[i] = nullptr;
      break;
    }
  }
}


//Confirma a conexão do dispositivo, seu tipo e os dados nele, o transmitindo os comandos do controle vindos do código//


void processaTodosControles() {
  for (auto ctl : meusControles) {
    if (ctl && ctl->isConnected() && ctl->hasData()) {
      if (ctl->isGamepad()) {
         processaControle(ctl);
      }
    }
  }
}


//Comandos do controle//


void processaControle(ControllerPtr ctl) {


  if(ctl->axisY() >= 30) {
    digitalWrite(A11, HIGH);                //Roda esquerda frente
    digitalWrite(A12, LOW);
    analogWrite(PWNA, VELOCIDADE);


  }


  else if(ctl->axisY() <= -30) {
    digitalWrite(A11, LOW);                 //Roda esquerda trás
    digitalWrite(A12, HIGH);
    analogWrite(PWNA, VELOCIDADE);
  }


  else {
    digitalWrite(A11, LOW);                 //Deadzone esquerda
    digitalWrite(A12, LOW);
    analogWrite(PWNA, 0);
  }




  if(ctl->axisRX() >= 30) {
    digitalWrite(B11, HIGH);                //Roda direita frente
    digitalWrite(B12, LOW);
    analogWrite(PWNB, VELOCIDADE);


  }


  else if(ctl->axisRY() <= -30) {
    digitalWrite(B11, LOW);                 //Roda direita trás
    digitalWrite(B12, HIGH);
    analogWrite(PWNB, VELOCIDADE);


  }


  else {
    digitalWrite(B11, LOW);                 //Deadzone direita
    digitalWrite(B12, LOW);
    analogWrite(PWNB, 0);


  }

  if (ctl->b()){
    for(i=0; i<3; i++){
      tone(BUZZER,2000);                    //Apito
      delay(150);
      noTone(BUZZER);
      delay(200);
    }
  }
}


//Função Principal//




void loop() {
  bool dataUpdated = BP32.update();
  if (dataUpdated){
    processaTodosControles();
    delay(150);
  }


}