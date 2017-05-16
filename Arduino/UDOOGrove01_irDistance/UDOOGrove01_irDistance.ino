#define DIST_IN_TH       100
#define CYCLES_TH        5
#define IR_CLOSEST_VALUE 900
#define IR_FAREST_VALUE  10


void setup() {
  Serial.begin(9600);
  Serial.println("UDOO Grove Happy Lamp! Step O1: IR distance sensor");
}


int cyclesUnderTh  = 0;
int lightIntensity = 255;

void loop() {

  bool isIntensityChanged = controlDistance(A0, &lightIntensity);

  if(isIntensityChanged)
    Serial.println(lightIntensity);
  
  delay(300);
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

int getIrDistanceInCm(int pin){
  int a = analogRead(pin);
  return map(a, IR_CLOSEST_VALUE, IR_FAREST_VALUE, 10, 100);
  }
