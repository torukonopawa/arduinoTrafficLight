/* Traffic Light with Button
 * https://github.com/torukonopawa
 * 11/30/2021 - 2:33 PM
 */

//LINE-1
//it is possible to add sensor to check: if there is anyone on crosswalk
//so that can be given extra time to them to pass across

//LINE-2
//should be modified delay(milisec)'s
//there is not enough time to pass across unless you are running :x

//Crosswalk
const int buttonCrosswalk = 2;
//const int sensorCrosswalk = 4; ***LINE-1
const int redCrosswalk = 7;
const int greenCrosswalk = 6;
//Traffic Light
const int redTraffic = 10;
const int yellowTraffic = 9;
const int greenTraffic = 8;

//interrupt's volatile
volatile boolean isCrosswalkRequested = false;

void whenButtonPressed() {
  noInterrupts(); //disable interrupts temporarily
  Serial.print("INTERRUPTED\n");
  Serial.print(digitalRead(2));
  Serial.print("\n");
  isCrosswalkRequested = true;
}

void setup() {
  Serial.begin(9600);
  setupLights();
  testLights();
  initializeLights();
    //sensor ***LINE-1
    //pinMode(sensorCrosswalk, INPUT); ***LINE-1
  //INTERRUPT decleration
  //interrupts(); //enable interrupts
  attachInterrupt(digitalPinToInterrupt(2), whenButtonPressed, HIGH);
}

void loop() {
  if(isCrosswalkRequested)
  {
    stopTraffic();
    startCrosswalk();
    delay(4000); //put here condition check sensor ***LINE-1
    stopCrosswalk();
    startTraffic();

    isCrosswalkRequested = false;
    interrupts();
  }
}

void stopTraffic() {
  delay(250);
  digitalWrite(greenTraffic, LOW);
  digitalWrite(yellowTraffic, HIGH);
  delay(250);
  digitalWrite(redTraffic, HIGH);
  digitalWrite(yellowTraffic, LOW);
}

void startTraffic() {
  delay(250);
  digitalWrite(yellowTraffic, HIGH);
  delay(250);
  digitalWrite(greenTraffic, HIGH);
  digitalWrite(yellowTraffic, LOW);
  digitalWrite(redTraffic, LOW);
}

void stopCrosswalk() {
  delay(250);
  digitalWrite(greenCrosswalk, LOW);
  digitalWrite(redCrosswalk, HIGH);
  delay(250);
}

void startCrosswalk() {
  delay(250);
  digitalWrite(greenCrosswalk, HIGH);
  digitalWrite(redCrosswalk, LOW);
  delay(250);
}

void setupLights() {
  pinMode(redCrosswalk, OUTPUT);
  pinMode(greenCrosswalk, OUTPUT);
  //----
  pinMode(redTraffic ,OUTPUT);
  pinMode(yellowTraffic, OUTPUT);
  pinMode(greenTraffic,OUTPUT);
}

void initializeLights() {
  digitalWrite(redCrosswalk, HIGH);
  digitalWrite(greenCrosswalk, LOW);

  digitalWrite(redTraffic, LOW);
  digitalWrite(yellowTraffic, LOW);
  digitalWrite(greenTraffic, HIGH);
}

void testLights() {
  delay(2000);
  //start 
  digitalWrite(redTraffic, HIGH);
  delay(500);
  digitalWrite(redTraffic, LOW);
  //end
  digitalWrite(yellowTraffic, HIGH);
  delay(500);
  digitalWrite(yellowTraffic, LOW);

  digitalWrite(greenTraffic, HIGH);
  delay(500);
  digitalWrite(greenTraffic, LOW);

  digitalWrite(redCrosswalk, HIGH);
  delay(500);
  digitalWrite(redCrosswalk, LOW);

  digitalWrite(greenCrosswalk, HIGH);
  delay(500);
  digitalWrite(greenCrosswalk, LOW);
  
  delay(500);
}
