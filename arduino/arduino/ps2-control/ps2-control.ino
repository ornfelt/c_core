#include <PS2X_lib.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// ----------------------------------------------------------------------------
// Types
// ----------------------------------------------------------------------------
struct JOY {
  byte lx;
  byte ly;
  byte rx;
  byte ry;
  byte buttons1 = 0b00000000;
  byte buttons2 = 0b00000000;
};

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------
#define PS_CLOCK_PIN 2
#define PS_CMD_PIN 3
#define PS_ATTENTION_PIN 4
#define PS_DATA_PIN 5

#define NF_CE_PIN 9
#define NF_CNS_PIN 10
#define NF_MOSI_PIN 11
#define NF_MISO_PIN 12
#define NF_SCK_PIN 13

PS2X ps2x;
RF24 radio(NF_CE_PIN, NF_CNS_PIN);
JOY joystick;

int ps_error = 0;

void setup() {
  Serial.begin(57600);

  setup_ps2();
  setup_rf();
}

void loop() {
  if (ps_error == 1) return;

  ps2x.read_gamepad(false, false);

  check_button(1, PSB_START, 0);
  check_button(1, PSB_SELECT, 1);
  check_button(1, PSB_PAD_UP, 2);
  check_button(1, PSB_PAD_RIGHT, 3);
  check_button(1, PSB_PAD_DOWN, 4);
  check_button(1, PSB_PAD_LEFT, 5);
  check_button(1, PSB_L1, 6);
  check_button(1, PSB_R1, 7);

  check_button(2, PSB_L2, 0);
  check_button(2, PSB_R2, 1);
  check_button(2, PSB_L3, 2);
  check_button(2, PSB_R3, 3);
  check_button(2, PSB_TRIANGLE, 4);
  check_button(2, PSB_CIRCLE, 5);
  check_button(2, PSB_CROSS, 6);
  check_button(2, PSB_SQUARE, 7);

  joystick.lx = ps2x.Analog(PSS_LX);
  joystick.ly = ps2x.Analog(PSS_LY);
  joystick.rx = ps2x.Analog(PSS_RX);
  joystick.ry = ps2x.Analog(PSS_RY);

  Serial.print("lx: ");
  Serial.print(joystick.lx);
  Serial.print(" ly: ");
  Serial.print(joystick.ly);
  Serial.print(" rx: ");
  Serial.print(joystick.rx);
  Serial.print(" ry: ");
  Serial.print(joystick.ry);
  Serial.print(" buttons1: ");
  Serial.print(joystick.buttons1, BIN);
  Serial.print(" buttons2: ");
  Serial.println(joystick.buttons2, BIN);
  
  radio.write(&joystick, sizeof(JOY));

  delay(50);
}

void setup_ps2() {
  // config_gamepad(clock, command, attention, data, Pressures?, Rumble?)
  ps_error = ps2x.config_gamepad(PS_CLOCK_PIN, PS_CMD_PIN, PS_ATTENTION_PIN, PS_DATA_PIN, true, true);

  if (ps_error == 0) {
    Serial.println(F("Controller configured successful."));

  } else if (ps_error == 1) {
    Serial.println(F("No controller found, check wiring."));

  } else if (ps_error == 2) {
    Serial.println(F("Controller found but not accepting commands."));

  } else if (ps_error == 3) {
    Serial.println(F("Controller refusing to enter Pressures mode, may not support it. "));
  }
}

void setup_rf() {
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  radio.openWritingPipe(0xF0F0F0F0E1LL);
}

void check_button(uint8_t buttons, uint16_t btn, uint8_t bit) {
  if (ps2x.Button(btn)) {
    if (buttons == 1) {
      bitWrite(joystick.buttons1, bit, 1);
    } else {
      bitWrite(joystick.buttons2, bit, 1);
    }
  } else {
    if (buttons == 1) {
      bitWrite(joystick.buttons1, bit, 0);
    } else {
      bitWrite(joystick.buttons2, bit, 0);
    }
  }
}
