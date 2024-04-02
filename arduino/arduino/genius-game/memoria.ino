#include "game.h"

void setup() {    
    for (int i=0; i<n_pins; i++) { pinMode(buttons[i], INPUT); }
    for (int i=0; i<n_pins; i++) { pinMode(leds[i], OUTPUT); }
    
    newGame();
}

void loop() {
    if (state == STATE_WAITING_PLAYER) {
        for (int i=0; i<n_pins; i++) {
            int d = digitalRead(buttons[i]);
            
            if (button_states[i]==LOW && d==HIGH) {
                digitalWrite(leds[i], HIGH);
                userPlay(i);
            } else if (button_states[i]==HIGH && d==LOW) {
                digitalWrite(leds[i], LOW);
            }           
            button_states[i] = d;
        }
    } 
}
