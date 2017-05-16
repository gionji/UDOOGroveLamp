#define SMALL_LED_PIN 13

#define LIGHT_SENSOR_PIN A3
#define DARKNESS_TH      0.2


void setup() {
  Serial.begin(115200);
  Serial.println("UDOO Grove Happy Lamp! Step O6: Light Sensor");

  pinMode(SMALL_LED_PIN, OUTPUT);
}

void loop() {

  float externalLightIntensity = getLuminosity();

  Serial.println(externalLightIntensity);

  if(externalLightIntensity < DARKNESS_TH)
    turnOnSmallLight();
  else
    turnOffSmallLight();

  delay(500);
}

float getLuminosity(){
  int val = analogRead(LIGHT_SENSOR_PIN);
  return ((float)val / 1024.0);
  }

void turnOffSmallLight(){  
  digitalWrite(SMALL_LED_PIN, LOW);
}

void turnOnSmallLight(){  
  digitalWrite(SMALL_LED_PIN, HIGH);
}

