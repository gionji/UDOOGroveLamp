/*
 * 
 * Need to install this library:
 * https://github.com/pjpmarques/ChainableLED
 * 
 */
#include <ChainableLED.h>

#define IR_DISTANCE_PIN    A0
#define DIST_IN_TH         100
#define CYCLES_TH          10
#define IR_CLOSEST_VALUE   700
#define IR_FAREST_VALUE    10

#define LED_PIN            7
#define NUM_LEDS           1

#define BUTTON_PIN         2
#define SMALL_LED_PIN      13
#define LONG_PRESS_TIMEOUT 1000

#define POTENTIOMETER_PIN  A1

#define SOUND_SENSOR_PIN   A2
#define SOUND_BIAS         721
#define SOUND_TH           150

#define LIGHT_SENSOR_PIN   A3
#define DARKNESS_TH        0.2

#define BUZZER_PIN         3

#define SERVO_PIN          5
#include <Servo.h>
Servo myservo;  

boolean isLightOn = false;

ChainableLED leds(LED_PIN, LED_PIN+1, NUM_LEDS);


// IR Distance variables
int cyclesUnderTh  = 0;

float brightness = 0.0;
float hue = 0.0;


void setup() {
  Serial.begin(115200);
  Serial.println("UDOO Grove Happy Lamp! Step O9-bis: All together!");

  leds.init();
  
  pinMode(BUTTON_PIN    , INPUT);
  pinMode(SMALL_LED_PIN, OUTPUT);

  myservo.attach(SERVO_PIN);

  shakeHand(2);  
}


void loop() {

  if(Serial.available() > 0){
    char readedData = (char) Serial.read();
    decodeCommand(readedData);
  }
  
  bool isButtonPressed = checkButtonState();  
  bool isClapDetected  = detectClap();
  hue = getPotentiometerPercentage();
  
  if( isButtonPressed || (isClapDetected && isTooDark() && !isLightOn)  ){
    if(isButtonPressed)
      Serial.print("Button pressed...");
    else
      Serial.print("Clap detected...");
    isLightOn = !isLightOn; 
    
    if(isLightOn){
      brightness = 1.0;
      Serial.println(" so I turn on the light!");
    }
    else{
      brightness = 0.0;
      Serial.println(" so I turn off the light!");
    }
    
    leds.setColorHSB(0, hue, 1.0, brightness * 0.65);
    delay(LONG_PRESS_TIMEOUT);
  }
  
  bool isIntensityChanged = controlDistance(IR_DISTANCE_PIN, &brightness);

  leds.setColorHSB(0, hue, 1.0, brightness * 0.65);

  delay(50);
 
}


// IR distance methods
bool controlDistance(int pin, int* intensity){
  int irDistance = getIrDistanceInCm(pin);
  int a = 0;
  
  if(irDistance < DIST_IN_TH)
    cyclesUnderTh++;
  else
    cyclesUnderTh = 0; 

  if(cyclesUnderTh > CYCLES_TH){
    *intensity = map(irDistance, 0, 100, 0 , 255);
    return true;
  }
  return false;
}

bool controlDistance(int pin, float* intensity){
  int irDistance = getIrDistanceInCm(pin);
  int a = 0;
  
  if(irDistance < DIST_IN_TH)
    cyclesUnderTh++;
  else
    cyclesUnderTh = 0; 

  if(cyclesUnderTh > CYCLES_TH){
    int d = map(irDistance, 0, 100, 0 , 255);
    if(d<0) d = 0;
    *intensity = (float)d / 255.0;
    return true;
  }
  return false;
}

int getIrDistanceInCm(int pin){
  int a = analogRead(pin);
  return map(a, IR_CLOSEST_VALUE, IR_FAREST_VALUE, 10, 100);
  }


// Button methods
boolean checkButtonState(){
  return digitalRead(BUTTON_PIN);
}

// Potentiometer methods
int getPotentiometerValue(){
  int value = analogRead(POTENTIOMETER_PIN);
  return value >> 2;
}

float getPotentiometerPercentage(){
  float value = (float)analogRead(POTENTIOMETER_PIN) / 1024.0;
  return value;
}

// Sound Sensor value
bool detectClap(){
  long sum = 0;
  for(int i=0; i<1024; i++)    {
    sum += analogRead(SOUND_SENSOR_PIN);
  }

  sum >>= 10;

  if(abs(sum - SOUND_BIAS) > SOUND_TH){      
     delay(50);
     return true;
  }
  return false;
}

// Light Sensor method
float getLuminosity(){
  int val = analogRead(LIGHT_SENSOR_PIN);
  return ((float)val / 1024.0);
  }

bool isTooDark(){
  if(getLuminosity() < DARKNESS_TH){
    return true;
  }
  else 
    return false;
}

// Buzzer Methods
void playBuzz(int duration){
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
  delay(duration);
}


void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(BUZZER_PIN, HIGH);
        delayMicroseconds(tone);
        digitalWrite(BUZZER_PIN, LOW);
        delayMicroseconds(tone);
    }
}

void playSong(){
  int  length = 15;  /* the number of notes */
  char notes[] = "ccggaagffeeddc ";
  int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
  int tempo = 300;
   
  for(int i = 0; i < length; i++) {
     tempo = (int) ((getPotentiometerPercentage() * 300) + 200);
     if(notes[i] == ' ') {
        delay(beats[i] * tempo);
     } else {
        playTone(notes[i], beats[i] * tempo);
     }
        delay(tempo / 2); 
  } 
}

//Servo methods
void shakeHand(int shakes){
  for(int i=0; i<shakes; i++){
    for (int pos = 70; pos <= 110; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
    for (int pos = 110; pos >= 70; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  }
}

void setServoPosition(float pos){
  myservo.write((int)(pos*180));
}

// Communication methods
void decodeCommand(char data){
  if(data >= 48 && data <= 57){
    setServoPosition((int)((data-48) * 18));
  }  
    
}
