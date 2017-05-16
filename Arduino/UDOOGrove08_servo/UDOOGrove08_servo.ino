#define BUTTON_PIN         2
#define POTENTIOMETER_PIN  A1

#define SERVO_PIN 5

#include <Servo.h>

Servo myservo;  


void setup() {
  Serial.begin(115200);
  Serial.println("UDOO Grove Happy Lamp! Step O8: Servo");

  myservo.attach(SERVO_PIN);

  shakeHand(2);  
}

void loop(){

  float pos = getPotentiometerPercentage();
  setServoPosition(pos);
  delay(5);

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
