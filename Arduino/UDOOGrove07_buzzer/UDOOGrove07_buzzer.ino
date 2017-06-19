#define SMALL_LED_PIN 13

#define BUZZER_PIN  3


void setup() {
  Serial.begin(115200);
  Serial.println("UDOO Grove Happy Lamp! Step O7: Buzzer");

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop(){

  playBuzz(1000);

  playSong();

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
     if(notes[i] == ' ') {
        delay(beats[i] * tempo);
     } else {
        playTone(notes[i], beats[i] * tempo);
     }
        delay(tempo / 2); 
  } 
}

