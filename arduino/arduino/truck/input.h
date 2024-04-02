#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "globals.h"

struct JOY {
  byte lx;
  byte ly;
  byte rx;
  byte ry;
  byte buttons1 = 0b00000000;
  byte buttons2 = 0b00000000;
};

byte JOY_START = 0b00000001;
byte JOY_SELECT = 0b00000010;
byte JOY_UP = 0b00000100;
byte JOY_RIGHT = 0b00001000;
byte JOY_DOWN = 0b00010000;
byte JOY_LEFT = 0b00100000;
byte JOY_L1 = 0b01000000;
byte JOY_R1 = 0b10000000;

byte JOY_L2 = 0b00000001;
byte JOY_R2 = 0b00000010;
byte JOY_L3 = 0b00000100;
byte JOY_R3 = 0b00001000;
byte JOY_TRIANGLE = 0b00010000;
byte JOY_CIRCLE = 0b00100000;
byte JOY_CROSS = 0b01000000;
byte JOY_SQUARE = 0b10000000;

RF24 _radio(NF_CE_PIN, NF_CNS_PIN);
JOY _joystick;
byte _prevButtons1 = 0b00000000;
byte _prevButtons2 = 0b00000000;
bool _conn = false;
bool _prevConn = false;
int _connCount = 0;

bool _check_button(byte button, byte mask) {
  return (button & mask) > 0;
}

bool _is_pressed(byte current, byte prev, byte mask) {
  return _check_button(current, mask) && !_check_button(prev, mask);
}

bool _is_released(byte current, byte prev, byte mask) {
  return !_check_button(current, mask) && _check_button(prev, mask);
}

void input_setup() {
  _radio.begin();
  _radio.setPALevel(RF24_PA_MIN);
  _radio.setDataRate(RF24_250KBPS);
  _radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
  _radio.startListening();

  // if (_radio.available()) {
  //   Serial.println(F("Radio available"));
  // } else {
  //   Serial.println(F("Radio NOT available"));
  // }
}

void input_update(unsigned long delta) {
  _prevButtons1 = _joystick.buttons1;
  _prevButtons2 = _joystick.buttons2;
  _prevConn = _conn;

  if (!_radio.available()) {
    _connCount += 1;
    if (_connCount > 10) {
      _conn = false;
      _connCount = 10;
    }

  } else {
    _connCount = 0;
    _conn = true;
  }

  if (!_conn) {
    return;
  }

  _radio.read(&_joystick, sizeof(JOY));
  // Serial.print(_joystick.lx);
  // Serial.print(" ly: ");
  // Serial.print(_joystick.ly);
  // Serial.print(" rx: ");
  // Serial.print(_joystick.rx);
  // Serial.print(" ry: ");
  // Serial.print(_joystick.ry);
  // Serial.print(" buttons1: ");
  // Serial.print(_joystick.buttons1, BIN);
  // Serial.print(" buttons2: ");
  // Serial.println(_joystick.buttons2, BIN);
}

byte joy_lx() { return _joystick.lx; }
byte joy_ly() { return _joystick.ly; }
byte joy_rx() { return _joystick.rx; }
byte joy_ry() { return _joystick.ry; }

bool joy_start() { return _check_button(_joystick.buttons1, JOY_START); }
bool joy_select() { return _check_button(_joystick.buttons1, JOY_SELECT); }
bool joy_start_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, JOY_START); }
bool joy_select_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, JOY_SELECT); }
bool joy_start_released() { return _is_released(_joystick.buttons1, _prevButtons1, JOY_START); }
bool joy_select_released() { return _is_released(_joystick.buttons1, _prevButtons1, JOY_SELECT); }

bool joy_up() { return _check_button(_joystick.buttons1, JOY_UP); }
bool joy_right() { return _check_button(_joystick.buttons1, JOY_RIGHT); }
bool joy_down() { return _check_button(_joystick.buttons1, JOY_DOWN); }
bool joy_left() { return _check_button(_joystick.buttons1, JOY_LEFT); }
bool joy_up_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, JOY_UP); }
bool joy_right_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, JOY_RIGHT); }
bool joy_down_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, JOY_DOWN); }
bool joy_left_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, JOY_LEFT); }
bool joy_up_released() { return _is_released(_joystick.buttons1, _prevButtons1, JOY_UP); }
bool joy_right_released() { return _is_released(_joystick.buttons1, _prevButtons1, JOY_RIGHT); }
bool joy_down_released() { return _is_released(_joystick.buttons1, _prevButtons1, JOY_DOWN); }
bool joy_left_released() { return _is_released(_joystick.buttons1, _prevButtons1, JOY_LEFT); }

bool joy_triangle() { return _check_button(_joystick.buttons2, JOY_TRIANGLE); }
bool joy_circle() { return _check_button(_joystick.buttons2, JOY_CIRCLE); }
bool joy_cross() { return _check_button(_joystick.buttons2, JOY_CROSS); }
bool joy_square() { return _check_button(_joystick.buttons2, JOY_SQUARE); }
bool joy_triangle_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, JOY_TRIANGLE); }
bool joy_circle_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, JOY_CIRCLE); }
bool joy_cross_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, JOY_CROSS); }
bool joy_square_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, JOY_SQUARE); }
bool joy_triangle_released() { return _is_released(_joystick.buttons2, _prevButtons2, JOY_TRIANGLE); }
bool joy_circle_released() { return _is_released(_joystick.buttons2, _prevButtons2, JOY_CIRCLE); }
bool joy_cross_released() { return _is_released(_joystick.buttons2, _prevButtons2, JOY_CROSS); }
bool joy_square_released() { return _is_released(_joystick.buttons2, _prevButtons2, JOY_SQUARE); }

bool joy_l1() { return _check_button(_joystick.buttons1, JOY_L1); }
bool joy_l2() { return _check_button(_joystick.buttons2, JOY_L2); }
bool joy_l3() { return _check_button(_joystick.buttons2, JOY_L3); }
bool joy_r1() { return _check_button(_joystick.buttons1, JOY_R1); }
bool joy_r2() { return _check_button(_joystick.buttons2, JOY_R2); }
bool joy_r3() { return _check_button(_joystick.buttons2, JOY_R3); }
bool joy_l1_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, JOY_L1); }
bool joy_l2_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, JOY_L2); }
bool joy_l3_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, JOY_L3); }
bool joy_r1_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, JOY_R1); }
bool joy_r2_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, JOY_R2); }
bool joy_r3_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, JOY_R3); }
bool joy_l1_released() { return _is_released(_joystick.buttons1, _prevButtons1, JOY_L1); }
bool joy_l2_released() { return _is_released(_joystick.buttons2, _prevButtons2, JOY_L2); }
bool joy_l3_released() { return _is_released(_joystick.buttons2, _prevButtons2, JOY_L3); }
bool joy_r1_released() { return _is_released(_joystick.buttons1, _prevButtons1, JOY_R1); }
bool joy_r2_released() { return _is_released(_joystick.buttons2, _prevButtons2, JOY_R2); }
bool joy_r3_released() { return _is_released(_joystick.buttons2, _prevButtons2, JOY_R3); }

bool joy_connected() { return _conn; }
bool joy_just_connected() { return _conn && _conn != _prevConn; }
bool joy_just_disconnected() { return !_conn && _conn != _prevConn; }

#endif