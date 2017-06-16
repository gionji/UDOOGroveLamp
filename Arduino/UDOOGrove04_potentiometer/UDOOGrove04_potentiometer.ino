#define POTENTIOMETER_PIN A1


void setup() {
  Serial.begin(9600);
  Serial.println("UDOO Grove Happy Lamp! Step O4: Pot");

  pinMode(SMALL_LED_PIN, OUTPUT);
}

void loop() {

  // get the pot value in the 0 - 255 range
  int   potValue      = getPotentiometerValue();

  // get the pot value in the 0 - 1 range
  float potPercentage = getPotentiometerPercentage();

  Serial.print("Pot value: ");
  Serial.print(potValue);
  Serial.print("  expressed in percentage: ");
  Serial.println(potPercentage);

  delay(500);
}


int getPotentiometerValue(){
  int value = analogRead(POTENTIOMETER_PIN);
  return value >> 2;
}

float getPotentiometerPercentage(){
  float value = (float)analogRead(POTENTIOMETER_PIN) / 1024.0;
  return value;
}
