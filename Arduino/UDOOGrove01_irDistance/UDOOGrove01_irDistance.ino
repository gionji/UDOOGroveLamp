#define IR_DISTANCE_PIN  A0
#define DIST_IN_TH       100
#define CYCLES_TH        4
#define IR_CLOSEST_VALUE 775
#define IR_FAREST_VALUE  200


void setup() {
  Serial.begin(9600);
  Serial.println("UDOO Grove Happy Lamp! Step O1: IR distance sensor");
}


void loop() {

  Serial.print("Raw sensor value: ");
  Serial.print( analogRead(IR_DISTANCE_PIN) );
  Serial.print(" - Raw Distance: ");
  Serial.print( getIrDistance(IR_DISTANCE_PIN) );
  Serial.print(" - Distance in centimeters: ");
  Serial.println( getIrDistanceInCm(IR_DISTANCE_PIN) );
  
  delay(1000);
}


// IR distance sensor methods
int getIrDistance(int pin){
  int a = analogRead(pin);
  return map(a, IR_CLOSEST_VALUE, IR_FAREST_VALUE, 10, 100);
}

// IR distance sensor methods
int getIrDistanceInCm(int pin){
  float volts = analogRead(pin)*0.00322265;
  float distance = 65*pow(volts, -1.10);
  return (int)distance;
}

