#include <Arduino.h>
#include "utils.h"
#include "variables.h"

void playRolls() {
    for (int i=0; i<n_rolls; i++) {
        blinkOne(leds[rolls[i]], TIME_REPRODUCE_ON, TIME_REPRODUCE_OFF);
    }
}

void newRoll() { 
    int r = random()%n_pins;
    rolls[n_rolls] = r;
    n_rolls++;

    blinkOne(leds[r], TIME_REPRODUCE_ON, TIME_REPRODUCE_OFF);
}

void newTurn() {
    n_user_roll = 0;
    
    playRolls();
    newRoll();
    state = STATE_WAITING_PLAYER;
}

void newGame() {
    blinkAll(leds, n_pins, 100, 100);
    blinkAll(leds, n_pins, 100, 100);
    blinkAll(leds, n_pins, 100, 100);
    blinkAll(leds, n_pins, 100, 100);
    blinkAll(leds, n_pins, 600, 2000);
    
    randomSeed(analogRead(0)+analogRead(1));
    
    n_rolls = 0;
    newTurn();
}

void userPlay(int i) {
    if (rolls[n_user_roll] == i) {
        n_user_roll++;
        
        if (n_user_roll == n_rolls) {
            state = STATE_WAITING_GAME;
            delay(400);
            for (int i=0; i<n_pins; i++) {
                digitalWrite(leds[i], LOW);
            }
            delay(1000);
            newTurn();
        }
    } else {
        newGame();
    }
}

