#define IR_DISTANCE_PIN  A0
#define DIST_IN_TH       100
#define CYCLES_TH        4
#define IR_CLOSEST_VALUE 775
#define IR_FAREST_VALUE  200


void setup() {
  Serial.begin(9600);
  Serial.println("UDOO Grove Happy Lamp! Step O1: IR distance sensor");
}


int cyclesUnderTh  = 0;
int lightIntensity = 255;

void loop() {

  Serial.print("Raw distance: ");
  Serial.println(analogRead(A0));

  bool isIntensityChanged = controlDistance(IR_DISTANCE_PIN, &lightIntensity);

  if(isIntensityChanged){
    Serial.print("New light intensity: ");
    Serial.println(lightIntensity);
  }
  
  delay(500);
}


// IR distance sensor methods
int getIrDistanceInCm(int pin){
  int a = analogRead(pin);
  return map(a, IR_CLOSEST_VALUE, IR_FAREST_VALUE, 10, 100);
  }
  
int controlDistance(int pin, int* intensity){
  int irDistance = getIrDistanceInCm(pin);
  int a = 0;
  
  if(irDistance < DIST_IN_TH)
    cyclesUnderTh++;
  else
    cyclesUnderTh = 0; 

  if(cyclesUnderTh > CYCLES_TH){
    *intensity = map(irDistance, 0, 100, 0 , 255);
    return 1;
  }
  return 0;
}
