/*
 * 
 * Need to install this library:
 * https://github.com/pjpmarques/ChainableLED
 * 
 */
#include <ChainableLED.h>

#define LED_PIN            7
#define NUM_LEDS           1

ChainableLED leds(LED_PIN, LED_PIN+1, NUM_LEDS);


void setup() {
  Serial.begin(9600);
  Serial.println("UDOO Grove Happy Lamp! Step O2: RGB LED");

  leds.init();
}



void loop() {

  leds.setColorRGB(0, 255, 0, 0);  
  Serial.println("All RED!");  
  delay(500);
  
  leds.setColorRGB(0, 0, 255, 0);  
  Serial.println("All GREEN!");  
  delay(500);
  
  leds.setColorRGB(0, 0, 0, 255);  
  Serial.println("All BLUE!");   
  delay(500);

  Serial.println("Fade in"); 
  for(float i=0; i<=1.0; i+=0.05){    
    leds.setColorHSB(0, 0, 0, i);    
    delay(10);
    }   
  delay(500);

  Serial.println("Fade out"); 
  for(float i=1.0; i>=0.0; i-=0.05){    
    leds.setColorHSB(0, 0, 0, i);    
    delay(10);
    }   
  delay(500); 

  Serial.println("Yellow Fade in"); 
  for(float i=0.0; i<=0.50; i+=0.05){    
    leds.setColorHSB(0, 0.25, 1.0, i);    
    delay(10);
    }   
  delay(500); 

  Serial.println("Rainbow!"); 
  for(float i=0.0; i<=1; i+=0.05){    
    leds.setColorHSB(0, i, 1.0, 0.5);    
    delay(200);
    }   
  delay(500);
}



