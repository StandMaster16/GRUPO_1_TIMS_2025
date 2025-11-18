#include <Arduino.h>
#include <Bluepad32.h>

ControllerPtr meuControle[BP32_MAX_GAMEPADS];

//PIN CONNECTIONS

#define PWNA 25  //Left
#define A11 26   //Left
#define A12 27   //Left
  
#define B11 14   //Right
#define B12 12   //Right
#define PWNB 13  //Right

void processamentoControle(ControllerPtr ctl) {

//------------------- ANALÓGICOS----------------------//

  if(ctl->axisY() >= 75) {
    digitalWrite(A11, HIGH);
    digitalWrite(A12, LOW);
    analogWrite(PWNA, 200);

  }

  if(ctl->axisY() <= -75) {
    digitalWrite(A11, LOW);
    digitalWrite(A12, HIGH);
    analogWrite(PWNA, 200);
  }

//estabelecer a deadzone do analógico esquerdo

  if (ctl->axisY() > -75 && ctl->axisY() < 75 && ctl->axisX() > -75 && ctl->axisX() < 75) {
    digitalWrite(A11, LOW);
    digitalWrite(A12, LOW);

  }

  if(ctl->axisRX() >= 75) {
    digitalWrite(B11, HIGH);
    digitalWrite(B12, LOW);
    analogWrite(PWNB, 200);

  }

  if(ctl->axisRY() <= -75) {
    digitalWrite(B11, LOW);
    digitalWrite(B12, HIGH);
    analogWrite(PWNB, 200);

  }

//estabelecer a deadzone do analógico direito

  if (ctl->axisRY() > -75 && ctl->axisRY() < 75 && ctl->axisRX() > -75 && ctl->axisRX() < 75) {
    digitalWrite(B11, LOW);
    digitalWrite(B12, LOW);
  }
}


void processamentoControle() {
  for (auto meuControle : meuControle) {
    if (meuControle && meuControle->isConnected() && meuControle->hasData()) {
      if (meuControle->isGamepad()) {
         processamentoControle(meuControle);
      }
      else {
        Serial.println("Controle não suportado");
      }
    }
  }
}


void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (meuControle[i] == nullptr) {
      Serial.printf("Controle conectado, index=%d\n", i);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PWNA, OUTPUT);
  pinMode(A11, OUTPUT);
  pinMode(A12, OUTPUT);

  pinMode(PWNB, OUTPUT);
  pinMode(B11, OUTPUT);
  pinMode(B12, OUTPUT);

}

void loop() {
  bool dataUpdated = BP32.update();
  if (dataUpdated){
    processamentoControle();
    delay(150);
  }

}