#define TIME_REPRODUCE_ON 1000
#define TIME_REPRODUCE_OFF 250

#define STATE_WAITING_GAME 0
#define STATE_WAITING_PLAYER 1

// PINS =========================
int n_pins = 4;
int buttons[] = {2, 3, 4, 5};
int leds[] = {8, 9, 11, 12};
// ==============================

// GAME VARS ====================
int max_rolls = 100;
int n_rolls = 0;
int rolls[100];
int n_user_roll = 0;

int state = STATE_WAITING_GAME;
int button_states[] = {0, 0, 0, 0};
// ==============================
