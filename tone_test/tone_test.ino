#include <TimerFreeTone.h>

#define TONE_PIN 10 // Pin you have speaker/piezo connected to (be sure to include a 100 ohm resistor).

int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int duration[] = { 250, 125, 125, 250, 250, 250, 250, 250 };

void setup() {
  
}

void loop() {
  
    TimerFreeTone(TONE_PIN, 262, 250); // Play thisNote for duration.
    delay(50);
    TimerFreeTone(TONE_PIN, 262, 250); // Play thisNote for duration.
    delay(500);
  }
