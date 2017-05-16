#define BUTTON_PIN         2
#define POTENTIOMETER_PIN  A1

#define BUZZER_PIN         3


void setup() {
  Serial.begin(115200);
  Serial.println("UDOO Grove Happy Lamp! Step O8: Buzzer, button and pot");

}

void loop(){
  if( checkButtonState() ) {
    playSong();  
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


// Buzzer Methods
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


