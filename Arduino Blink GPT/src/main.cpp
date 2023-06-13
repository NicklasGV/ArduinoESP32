#include <Arduino.h>

// Definer pinnumrene for LED'er og knap
#define LED1_PIN 2
#define LED2_PIN 3
#define BUTTON_PIN 4

// Definer LED-intervallerne i millisekunder
const unsigned long LED1_INTERVAL = 1000;   // 1 Hz
const unsigned long LED2_INTERVAL = 100;    // 10 Hz
const unsigned long LED_BOTH_INTERVAL = 200; // 5 Hz for begge LED'er

// Gem den aktuelle tilstand af knappen
bool buttonState = false;

// Gem den forrige tilstand af knappen
bool prevButtonState = false;

// Gem tidspunktet for seneste ændring i knaptilstanden
unsigned long buttonChangeTime = 0;

// Gem tidspunktet for seneste blink af LED1
unsigned long led1PreviousMillis = 0;

// Gem tidspunktet for seneste blink af LED2
unsigned long led2PreviousMillis = 0;

void setup() {
  // Initialiser serielt kommunikationsinterface
  Serial.begin(9600);

  // Konfigurer pinmodes
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Læs knaptilstanden
  buttonState = !digitalRead(BUTTON_PIN);

  // Håndter knaptilstandændringer
  if (buttonState != prevButtonState) {
    buttonChangeTime = millis();
  }

  // Tjek om der er gået nok tid siden sidste blink af LED1
  if ((millis() - led1PreviousMillis) >= (buttonState ? LED1_INTERVAL : LED_BOTH_INTERVAL)) {
    led1PreviousMillis = millis();
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
  }

  // Tjek om der er gået nok tid siden sidste blink af LED2
  if ((millis() - led2PreviousMillis) >= (buttonState ? LED2_INTERVAL : LED_BOTH_INTERVAL)) {
    led2PreviousMillis = millis();
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
  }

  // Opdater forrige knaptilstand
  prevButtonState = buttonState;
}
