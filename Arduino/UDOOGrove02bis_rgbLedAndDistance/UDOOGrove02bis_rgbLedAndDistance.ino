/*
 * 
 * Need to install this library:
 * https://github.com/pjpmarques/ChainableLED
 * 
 */
#include <ChainableLED.h>

#define IR_DISTANCE_PIN  A0
#define DIST_IN_TH       100
#define CYCLES_TH        4
#define IR_CLOSEST_VALUE 775
#define IR_FAREST_VALUE  200

#define LED_PIN            7
#define NUM_LEDS           1

ChainableLED leds(LED_PIN, LED_PIN+1, NUM_LEDS);


// IR Distance variables
int cyclesUnderTh  = 0;
int lightIntensity = 255;


void setup() {
  Serial.begin(9600);
  Serial.println("UDOO Grove Happy Lamp! Step O2-bis: Distance and RGB LED");

  leds.init();
}


void loop() {

  bool isIntensityChanged = controlDistance(IR_DISTANCE_PIN, &lightIntensity);

  if(lightIntensity < 0) lightIntensity = 0;

  if(isIntensityChanged)
    leds.setColorRGB(0, lightIntensity, lightIntensity, lightIntensity);
  
  delay(30);
 
}


// IR distance methods
int controlDistance(int pin, int* intensity){
  int irDistance = getIrDistance(pin);
  int a = 0;
  
  if(irDistance < DIST_IN_TH)
    cyclesUnderTh++;
  else
    cyclesUnderTh = 0; 

  if(cyclesUnderTh > CYCLES_TH){
    *intensity = map(irDistance, 0, 100, 0 , 255);
    return 1;
  }
  return 0;
}

int getIrDistance(int pin){
  int a = analogRead(pin);
  return map(a, IR_CLOSEST_VALUE, IR_FAREST_VALUE, 10, 100);
  }
