/*
 * Need to install this library:
 * https://github.com/pjpmarques/ChainableLED 
 */
#include <ChainableLED.h>

#define POTENTIOMETER_PIN  A1
#define SMALL_LED_PIN      13

#define LED_PIN            7
#define NUM_LEDS           1

ChainableLED leds(LED_PIN, LED_PIN+1, NUM_LEDS);

void setup() {
  Serial.begin(9600);
  Serial.println("UDOO Grove Happy Lamp! Step O4bis: Pot and LED");

  pinMode(SMALL_LED_PIN, OUTPUT);
  leds.init();
}

void loop() {

  // get the pot value in the 0 - 1 range
  float potPercentage = getPotentiometerPercentage();
  
  leds.setColorHSB(0, potPercentage, 1.0, 0.5);

  delay(50);
}


int getPotentiometerValue(){
  int value = analogRead(POTENTIOMETER_PIN);
  return value >> 2;
}


float getPotentiometerPercentage(){
  float value = (float)analogRead(POTENTIOMETER_PIN) / 1024.0;
  return value;
}


