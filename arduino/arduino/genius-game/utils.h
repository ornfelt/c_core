#include <Arduino.h>

void turnOn(int pin) { digitalWrite(pin, HIGH); }
void turnOff(int pin) { digitalWrite(pin, LOW); }

void blinkAll(int pins[], int pinCount, int timeOn, int timeOff) {
    for (int i=0; i<pinCount; i++) { turnOn(pins[i]); }
    delay(timeOn);
    
    for (int i=0; i<pinCount; i++) { turnOff(pins[i]); }
    delay(timeOff);
}

void blinkOne(int pin, int timeOn, int timeOff) {
    turnOn(pin);
    delay(timeOn);
    
    turnOff(pin);
    delay(timeOff);
}
