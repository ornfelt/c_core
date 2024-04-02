#include "globals.h"
#include "input.h"
#include "online.h"

void setup() {
  Serial.begin(57600);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SERVO_BACK_PIN, OUTPUT);
  pinMode(SERVO_STEERING_PIN, OUTPUT);
  pinMode(MOTOR_B_PIN, OUTPUT);
  pinMode(MOTOR_A_PIN, OUTPUT);
  pinMode(LED_BACK_PIN, OUTPUT);
  pinMode(LED_BREAK_PIN, OUTPUT);
  pinMode(LED_HIGH_PIN, OUTPUT);
  pinMode(LED_LOW_PIN, OUTPUT);

  input_setup();
  online_setup();
}

void loop() {
  input_update(50);
  online_update(50);

  if (joy_just_connected()) {
    Serial.println(F("Connected"));
    online_set_connected(true);
  }

  if (joy_just_disconnected()) {
    Serial.println(F("Disconnected"));
    online_set_connected(false);
  }

  delay(50);
}
