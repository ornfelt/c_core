// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// struct JOY {
//   byte lx;
//   byte ly;
//   byte rx;
//   byte ry;
//   byte buttons1 = 0b00000000;
//   byte buttons2 = 0b00000000;
// };

// byte _JOY_START = 0b00000001;
// byte _JOY_SELECT = 0b00000010;
// byte _JOY_UP = 0b00000100;
// byte _JOY_RIGHT = 0b00001000;
// byte _JOY_DOWN = 0b00010000;
// byte _JOY_LEFT = 0b00100000;
// byte _JOY_L1 = 0b01000000;
// byte _JOY_R1 = 0b10000000;

// byte _JOY_L2 = 0b00000001;
// byte _JOY_R2 = 0b00000010;
// byte _JOY_L3 = 0b00000100;
// byte _JOY_R3 = 0b00001000;
// byte _JOY_TRIANGLE = 0b00010000;
// byte _JOY_CIRCLE = 0b00100000;
// byte _JOY_CROSS = 0b01000000;
// byte _JOY_SQUARE = 0b10000000;

// RF24 _radio;
// JOY _joystick;
// byte _prevButtons1 = 0b00000000;
// byte _prevButtons2 = 0b00000000;

// void input_setup() {
//   RF24 r(NF_CE_PIN, NF_CNS_PIN);
//   _radio = r;
//   _radio.begin();
//   _radio.setPALevel(RF24_PA_MIN);
//   _radio.setDataRate(RF24_250KBPS);
//   _radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
//   _radio.startListening();

//   if (_radio.available()) {
//     Serial.println(F("Radio available"));
//   } else {
//     Serial.println(F("Radio NOT available"));
//   }
// }

// void input_update(unsigned long delta) {
//   if (!_radio.available()) return;

//   // _prevButtons1 = _joystick.buttons1;
//   // _prevButtons2 = _joystick.buttons2;

//   _radio.read(&_joystick, sizeof(JOY));
//   Serial.print(_joystick.lx);
//   Serial.print(" ly: ");
//   Serial.print(_joystick.ly);
//   Serial.print(" rx: ");
//   Serial.print(_joystick.rx);
//   Serial.print(" ry: ");
//   Serial.print(_joystick.ry);
//   Serial.print(" buttons1: ");
//   Serial.print(_joystick.buttons1, BIN);
//   Serial.print(" buttons2: ");
//   Serial.println(_joystick.buttons2, BIN);
//   delay(50);
// }

// // bool _check_button(byte button, byte mask) {
// //   return (button & mask) > 0;
// // }

// // bool _is_pressed(byte current, byte prev, byte mask) {
// //   return _check_button(current, mask) && !_check_button(prev, mask);
// // }

// // bool _is_released(byte current, byte prev, byte mask) {
// //   return !_check_button(current, mask) && _check_button(prev, mask);
// // }

// // byte joy_lx() { return _joystick.lx; }
// // byte joy_ly() { return _joystick.ly; }
// // byte joy_rx() { return _joystick.rx; }
// // byte joy_ry() { return _joystick.ry; }

// // bool joy_start() { return _check_button(_joystick.buttons1, _JOY_START); }
// // bool joy_select() { return _check_button(_joystick.buttons1, _JOY_SELECT); }
// // bool joy_start_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, _JOY_START); }
// // bool joy_select_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, _JOY_SELECT); }
// // bool joy_start_released() { return _is_released(_joystick.buttons1, _prevButtons1, _JOY_START); }
// // bool joy_select_released() { return _is_released(_joystick.buttons1, _prevButtons1, _JOY_SELECT); }

// // bool joy_up() { return _check_button(_joystick.buttons1, _JOY_UP); }
// // bool joy_right() { return _check_button(_joystick.buttons1, _JOY_RIGHT); }
// // bool joy_down() { return _check_button(_joystick.buttons1, _JOY_DOWN); }
// // bool joy_left() { return _check_button(_joystick.buttons1, _JOY_LEFT); }
// // bool joy_up_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, _JOY_UP); }
// // bool joy_right_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, _JOY_RIGHT); }
// // bool joy_down_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, _JOY_DOWN); }
// // bool joy_left_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, _JOY_LEFT); }
// // bool joy_up_released() { return _is_released(_joystick.buttons1, _prevButtons1, _JOY_UP); }
// // bool joy_right_released() { return _is_released(_joystick.buttons1, _prevButtons1, _JOY_RIGHT); }
// // bool joy_down_released() { return _is_released(_joystick.buttons1, _prevButtons1, _JOY_DOWN); }
// // bool joy_left_released() { return _is_released(_joystick.buttons1, _prevButtons1, _JOY_LEFT); }

// // bool joy_triangle() { return _check_button(_joystick.buttons2, _JOY_TRIANGLE); }
// // bool joy_circle() { return _check_button(_joystick.buttons2, _JOY_CIRCLE); }
// // bool joy_cross() { return _check_button(_joystick.buttons2, _JOY_CROSS); }
// // bool joy_square() { return _check_button(_joystick.buttons2, _JOY_SQUARE); }
// // bool joy_triangle_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, _JOY_TRIANGLE); }
// // bool joy_circle_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, _JOY_CIRCLE); }
// // bool joy_cross_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, _JOY_CROSS); }
// // bool joy_square_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, _JOY_SQUARE); }
// // bool joy_triangle_released() { return _is_released(_joystick.buttons2, _prevButtons2, _JOY_TRIANGLE); }
// // bool joy_circle_released() { return _is_released(_joystick.buttons2, _prevButtons2, _JOY_CIRCLE); }
// // bool joy_cross_released() { return _is_released(_joystick.buttons2, _prevButtons2, _JOY_CROSS); }
// // bool joy_square_released() { return _is_released(_joystick.buttons2, _prevButtons2, _JOY_SQUARE); }

// // bool joy_l1() { return _check_button(_joystick.buttons1, _JOY_L1); }
// // bool joy_l2() { return _check_button(_joystick.buttons2, _JOY_L2); }
// // bool joy_l3() { return _check_button(_joystick.buttons2, _JOY_L3); }
// // bool joy_r1() { return _check_button(_joystick.buttons1, _JOY_R1); }
// // bool joy_r2() { return _check_button(_joystick.buttons2, _JOY_R2); }
// // bool joy_r3() { return _check_button(_joystick.buttons2, _JOY_R3); }
// // bool joy_l1_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, _JOY_L1); }
// // bool joy_l2_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, _JOY_L2); }
// // bool joy_l3_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, _JOY_L3); }
// // bool joy_r1_pressed() { return _is_pressed(_joystick.buttons1, _prevButtons1, _JOY_R1); }
// // bool joy_r2_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, _JOY_R2); }
// // bool joy_r3_pressed() { return _is_pressed(_joystick.buttons2, _prevButtons2, _JOY_R3); }
// // bool joy_l1_released() { return _is_released(_joystick.buttons1, _prevButtons1, _JOY_L1); }
// // bool joy_l2_released() { return _is_released(_joystick.buttons2, _prevButtons2, _JOY_L2); }
// // bool joy_l3_released() { return _is_released(_joystick.buttons2, _prevButtons2, _JOY_L3); }
// // bool joy_r1_released() { return _is_released(_joystick.buttons1, _prevButtons1, _JOY_R1); }
// // bool joy_r2_released() { return _is_released(_joystick.buttons2, _prevButtons2, _JOY_R2); }
// // bool joy_r3_released() { return _is_released(_joystick.buttons2, _prevButtons2, _JOY_R3); }



