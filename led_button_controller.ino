/*
  3 Buttons & 3 LEDs Control - Advanced Version with Debouncing

  Controls 3 LEDs using 3 separate buttons with toggle functionality
  Each button toggles its corresponding LED on/off
  Includes debouncing to prevent switch bounce issues

  Connections:
  - LED 1 connected from pin 9 to ground through 220 ohm resistor
  - LED 2 connected from pin 10 to ground through 220 ohm resistor  
  - LED 3 connected from pin 11 to ground through 220 ohm resistor
  - Button 1 connected to pin 2 with INPUT_PULLUP (button to GND)
  - Button 2 connected to pin 3 with INPUT_PULLUP (button to GND)
  - Button 3 connected to pin 4 with INPUT_PULLUP (button to GND)
*/

// Change these pin numbers if your connections are different
const int BTN1 = 2;   // Button 1
const int BTN2 = 3;   // Button 2
const int BTN3 = 4;   // Button 3
const int LED1 = 9;   // LED 1
const int LED2 = 10;  // LED 2
const int LED3 = 11;  // LED 3

// Group them in arrays to reduce code repetition
const int buttonPins[3] = { BTN1, BTN2, BTN3 };
const int ledPins[3]    = { LED1, LED2, LED3 };

// State variables for each LED
bool ledState[3] = { false, false, false };

// Debouncing variables
int lastReading[3]        = { HIGH, HIGH, HIGH };  // Last immediate reading
int debouncedState[3]     = { HIGH, HIGH, HIGH };  // Stable state (with PULLUP: HIGH = not pressed)
unsigned long lastChange[3] = { 0, 0, 0 };
const unsigned long debounceDelay = 50; // milliseconds

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Buttons connected to GND
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    int reading = digitalRead(buttonPins[i]);
    
    // If the immediate reading changed, reset the debounce timer
    if (reading != lastReading[i]) {
      lastChange[i] = millis();
      lastReading[i] = reading;
    }
    
    // After debounce delay, consider the state stable
    if (millis() - lastChange[i] > debounceDelay) {
      if (debouncedState[i] != reading) {
        debouncedState[i] = reading;
        
        // With INPUT_PULLUP: LOW means actual button press
        if (debouncedState[i] == LOW) {
          ledState[i] = !ledState[i];                      // Toggle LED state
          digitalWrite(ledPins[i], ledState[i] ? HIGH : LOW);
        }
      }
    }
  }
}