#include <Arduino.h>

const int SONAR_TRIG = 8;
const int SONAR_ECHO = 9;
const int MOTOR_IN1 = 2;
const int MOTOR_IN2 = 3;
const int MOTOR_IN3 = 4;
const int MOTOR_IN4 = 5;
const int MOTOR_ENA = 11;
const int MOTOR_ENB = 10;

const int RIGHT_BACKWARD = MOTOR_IN1;
const int RIGHT_FORWARD = MOTOR_IN2;
const int LEFT_SPEED = MOTOR_ENB;
const int LEFT_FORWARD = MOTOR_IN3;
const int LEFT_BACKWARD = MOTOR_IN4;
const int RIGHT_SPEED = MOTOR_ENA;

const float SPEED_FULL = 1;
const float SPEED_THREE_QUARTER = .75;
const float SPEED_HALF = .5;
const float SPEED_QUARTER = .25;
const float SPEED_STOPPED = 0;

const float FORCE_FULL = 1;
const float FORCE_ALMOST_FULL = .75;
const float FORCE_HALF = .5;
const float FORCE_SMALL = .25;
const float FORCE_NONE = 0;

const float FORWARD = 1;
const float BACKWARD = -1;
const float RIGHT = 1;
const float LEFT = -1;


float g_direction = 0; // 1 = forward; -1 = backward; 0 = stopped;
float g_rotation = 0; // 1 = right; -1 = backward; 0 = stopped;
float g_speed = 0; // 0 = stopped - 1 = full speed;
float g_rotationSpeed = 0; // 0 = stopped - 1 = full speed;

void setup() {
  Serial.begin(115200);

  pinMode(SONAR_ECHO, INPUT);
  pinMode(SONAR_TRIG, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
}

int dir = 0;
void loop() {
  long distance = readSonar();

  if (distance > 50) {
    dir = 0;
    MoveForward();
  } else if (distance > 10) {
    if (dir == 0) {
      dir = getRandomDirection();
    }

    if (dir > 0) {
      RotateRight();
    } else {
      RotateLeft();
    }
  } else {
    dir = 0;
    MoveBackward();
  }

  delay(1000);
}


void MoveForward() {
  analogWrite(LEFT_SPEED, 255);
  analogWrite(RIGHT_SPEED, 255);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
}

void MoveBackward() {
  analogWrite(LEFT_SPEED, 255);
  analogWrite(RIGHT_SPEED, 255);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, HIGH);
}

void Stop() {
  analogWrite(LEFT_SPEED, 0);
  analogWrite(RIGHT_SPEED, 0);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
}

void RotateLeft() {
  analogWrite(LEFT_SPEED, 255);
  analogWrite(RIGHT_SPEED, 255);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
}

void RotateRight() {
  analogWrite(LEFT_SPEED, 255);
  analogWrite(RIGHT_SPEED, 255);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, HIGH);
}

long readSonar() {
  digitalWrite(SONAR_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIG, LOW);

  long duration = pulseIn(SONAR_ECHO, HIGH);
  long distance = microsecondsToCentimeters(duration);

  return distance;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29.4 / 2;
}


int getRandomDirection() {
  return random() > 0.5? 1 : -1;
}