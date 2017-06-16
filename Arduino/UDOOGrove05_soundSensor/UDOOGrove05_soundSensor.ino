
#define SOUND_SENSOR_PIN A2
#define SOUND_BIAS       721
#define SOUND_TH         150

#define SMALL_LED_PIN    13


void setup() {
  Serial.begin(115200);
  Serial.println("UDOO Grove Happy Lamp! Step O5: Sound Sensor");

  pinMode(SMALL_LED_PIN, OUTPUT);

}

void loop() {

  bool isClapDetected = detectClap();
 
  if( isClapDetected ){
    turnOnSmallLight();
    delay(1000);
    turnOffSmallLight();
  }

  delay(50);
}

// Sound Sensor value
bool detectClap(){
  long sum = 0;
  for(int i=0; i<64; i++)    {
    sum += analogRead(SOUND_SENSOR_PIN);
  }

  sum >>= 6;

  if(abs(sum - SOUND_BIAS) > SOUND_TH){      
     delay(50);
     return true;
  }
  return false;
}

void turnOnSmallLight(){  
  digitalWrite(SMALL_LED_PIN, HIGH);
}

void turnOffSmallLight(){  
  digitalWrite(SMALL_LED_PIN, LOW);
}

