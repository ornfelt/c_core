const int relayOut = 5;
const unsigned long timeOff = 60000; // 1 minute
const unsigned long timeOn = 120000; // 2 minutes

bool on = false;
unsigned long previousMillis = 0;
unsigned long interval = timeOn;

void setup() {
  Serial.begin(9600);
  pinMode(relayOut, OUTPUT);
  
  on = true;
  previousMillis = millis();
  interval = timeOn;
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis < previousMillis) {
    // The millis() internal counter overflowed and reseted to zero
    previousMillis = currentMillis;
  }
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (on) {
      turnOff();
      interval = timeOff;
    } else {
      turnOn();
      interval = timeOn;
    }
  }
  
  delay(1000);
}

void turnOn() {
  on = true;
  digitalWrite(relayOut, LOW);
}

void turnOff() {
  on = false;
  digitalWrite(relayOut, HIGH);
}