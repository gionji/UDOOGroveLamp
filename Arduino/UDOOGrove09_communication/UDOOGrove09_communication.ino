#define BUTTON_PIN         2
#define POTENTIOMETER_PIN  A1

#define SMALL_LED_PIN 13

#define BUZZER_PIN 3

void setup() {
  Serial.begin(115200);
  Serial.println("UDOO Grove Happy Lamp! Step O8: Serial Communication");

  pinMode(SMALL_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop(){

  if(Serial.available() > 0){
    char readedData = (char) Serial.read();
    decodeCommand(readedData);
  }

  if(checkButtonState()){
    int dataToSend = getPotentiometerValue();
    Serial.println(dataToSend);
  }
  
  delay(50);
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


void  turnOnSmallLight(){
  digitalWrite(SMALL_LED_PIN, HIGH);
}

void  turnOffSmallLight(){
  digitalWrite(SMALL_LED_PIN, LOW);
}

void buzz(){
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);
  delay(500);
  }


// Communication methods
void decodeCommand(char data){
  switch(data){
    case '0':
      turnOffSmallLight();
      break;
    case '1':
      turnOnSmallLight();
      break;
    case 'a':
      buzz();
      break;
    default:
      break;    
    }
  
}

  

