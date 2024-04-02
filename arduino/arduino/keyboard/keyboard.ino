#include "Keyboard.h"

int outputs[3] = { 2, 3, 4 }; 
int inputs[3] = { 5, 6, 7 };
bool states[3][3] = {
  {false, false, false},
  {false, false, false},
  {false, false, false}
};
int characters[3][3] = {
  {KEY_KP_7, KEY_KP_8, KEY_KP_9},
  {KEY_KP_4, KEY_KP_5, KEY_KP_6},
  {KEY_KP_1, KEY_KP_2, KEY_KP_3}
};
int currentOutput = -1;


void setup() {
  pinMode(outputs[0], OUTPUT);
  pinMode(outputs[1], OUTPUT);
  pinMode(outputs[2], OUTPUT);
  pinMode(inputs[0], INPUT);
  pinMode(inputs[1], INPUT);
  pinMode(inputs[2], INPUT);

  Serial.begin(9600);
  Keyboard.begin();
  
  digitalWrite(outputs[0], LOW);
  digitalWrite(outputs[1], LOW);
  digitalWrite(outputs[2], LOW);
}

void loop() {
  if (currentOutput >= 0) {
    digitalRead(inputs[0]) == HIGH ? press(0, currentOutput) : release(0, currentOutput);
    digitalRead(inputs[1]) == HIGH ? press(1, currentOutput) : release(1, currentOutput);
    digitalRead(inputs[2]) == HIGH ? press(2, currentOutput) : release(2, currentOutput);
    digitalWrite(outputs[currentOutput], LOW);
  }

  currentOutput++;
  if (currentOutput >= 3) currentOutput = 0;
  digitalWrite(outputs[currentOutput], HIGH);
  delay(10);
}

void press(int in, int out) {
  if (!states[in][out]) {
    states[in][out] = true;
    Keyboard.press(characters[in][out]);
  }
}

void release(int in, int out) {
  if (states[in][out]) {
    states[in][out] = false;
    Keyboard.release(characters[in][out]);
  }
}











