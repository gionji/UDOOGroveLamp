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

#define BUTTON_PIN 2
#define SMALL_LED_PIN 13
#define LONG_PRESS_TIMEOUT 1000

boolean isLightOn = false;

ChainableLED leds(LED_PIN, LED_PIN+1, NUM_LEDS);


// IR Distance variables
int cyclesUnderTh  = 0;
int lightIntensity = 255;


void setup() {
  Serial.begin(9600);
  Serial.println("UDOO Grove Happy Lamp! Step O3-bis: All together!");

  leds.init();
  
  pinMode(BUTTON_PIN    , INPUT);
  pinMode(SMALL_LED_PIN, OUTPUT);
}


void loop() {
  bool isButtonPressed = checkButtonState();
  if(isButtonPressed){
    Serial.print("Button pressed...");
    isLightOn = !isLightOn; 
    
    if(isLightOn){
      lightIntensity = 255;
      Serial.println(" so I turn on the light!");
    }
    else{
      lightIntensity = 0;
      Serial.println(" so I turn off the light!");
    }
    
    leds.setColorRGB(0, lightIntensity, lightIntensity, lightIntensity);
    delay(LONG_PRESS_TIMEOUT);
  }
  
  bool isIntensityChanged = controlDistance(IR_DISTANCE_PIN, &lightIntensity);

  if(lightIntensity < 0) {
    lightIntensity = 0;
    isLightOn = false;
  }

  if(isIntensityChanged){
    leds.setColorRGB(0, lightIntensity, lightIntensity, lightIntensity);
    isLightOn = true;
  }
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


// Button methods

boolean checkButtonState(){
  return digitalRead(BUTTON_PIN);
}
