#ifndef ONLINE_H
#define ONLINE_H

#include <Arduino.h>

unsigned long _th = 0;
bool _con = false;
bool _up = false;

void online_setup() {
  pinMode(LED_ONLINE_PIN, OUTPUT);
}

void online_update(unsigned long delta) {
  _th += delta;

  // Connected -- just high
  if (_con) {
    _up = true;
    _th = 0;

    // Not connected -- blink fast
  } else {
    if (_th < 300) {
      _up = !_up;
      _th -= 300;
    }
  }

  if (_up) {
    digitalWrite(LED_ONLINE_PIN, HIGH);
  } else {
    digitalWrite(LED_ONLINE_PIN, LOW);
  }
}

void online_set_connected(bool con) {
  _con = con;
}

#endif