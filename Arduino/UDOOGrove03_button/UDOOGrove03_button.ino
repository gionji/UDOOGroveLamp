#define BUTTON_PIN 2
#define SMALL_LED_PIN 13
#define LONG_PRESS_TIMEOUT 1000

boolean isLightOn = false;

void setup() {
  Serial.begin(9600);
  Serial.println("UDOO Grove Happy Lamp! Step O3: Button");

  pinMode(BUTTON_PIN    , INPUT);
  pinMode(SMALL_LED_PIN, OUTPUT);
}

void loop() {
  boolean isButtonPressed = checkButtonState();
  if(isButtonPressed){
    Serial.print("Button pressed...");
    isLightOn = !isLightOn;  

    if(isLightOn){
      turnOnSmallLight();
      Serial.println(" so I turn on the light!");
    }
    else{
      turnOffSmallLight();
      Serial.println(" so I turn off the light!");
    }
    delay(LONG_PRESS_TIMEOUT);
  }

  delay(50);
}


boolean checkButtonState(){
  return digitalRead(BUTTON_PIN);
}

void  turnOnSmallLight(){
  digitalWrite(SMALL_LED_PIN, HIGH);
}

void  turnOffSmallLight(){
  digitalWrite(SMALL_LED_PIN, LOW);
}


