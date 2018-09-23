//L293 information sheet
//http://www.ti.com/lit/ds/symlink/l293d.pdf

//This project uses Arduino UNO and the L293DNE IC to run two 
//motors independently forward and backward, and with speed 
//adjustable with pulse-width modulation (PWM). 

/*
 * This is the bump robot
 * 
 * 
 * 
 * 
 */
 
const int sensorPin = A0; // this pin will be used accross bot varieties, can be used for analog or digital input
int sensorValue = 0; // storage for a value for whatever sensor <-- edit this description.
unsigned long currenttime = millis(); // time since the last "bump"
unsigned long basetime = millis();  // the time since the second to last bump // 
//const int dialPin = A1; // we are adding a potentiometer to adjust settings on the fly
//int dialValue = 0;  // variable to store the setting on the potentiometer 
//
// Hook up the Arduino to the L293 IC, and define constants: 
//
// side L (going from top left to bottom left on IC) 
  const int leftEnableDriver = 9; // pin 1 on IC, enableDriver12EN, on a PWM-capable arduino pin
  const int driverInput1A = 3;  // pin 2 on IC 
  // pin 3 on IC = driverOutput1Y , goes to L motor
  // pin 4 on IC = ground
  // pin 5 on IC = ground
  // pin 6 on IC = driverOutput2Y, goes to L motor
  const int driverInput2A = 2;  // pin 7 on IC 
  // pin 8 on IC  is positive power source for the motors 

//side R (going from bottom right to top right on IC, as is the convention) 
  const int rightEnableDriver = 10;  //pin 9 on IC, enableDriver34EN, on a PWM-capable arduino pin
  const int driverInput3A = 6; // pin 10 on IC 
  // pin 11 on IC = driverOutput3Y, goes to R motor
  // pin 12 on IC = ground
  // pin 13 on IC = ground 
  // pin 14 on IC = driverOutput4Y, goes to R motor 
  const int driverInput4A = 7; // pin 15 on IC 
  // pin 16 on IC powers the IC, needs 5V 
  
void setup() {
  Serial.begin(9600);
  pinMode(leftEnableDriver, OUTPUT);
  pinMode(rightEnableDriver, OUTPUT); 
  pinMode(driverInput1A, OUTPUT);
  pinMode(driverInput2A, OUTPUT);
  pinMode(driverInput3A, OUTPUT);
  pinMode(driverInput4A, OUTPUT);

  //set the wheels to spinning
  digitalWrite(leftEnableDriver, HIGH);
  digitalWrite(rightEnableDriver, HIGH);
}

void loop() {
  //read sensor
  sensorValue = digitalRead(sensorPin);
  if (sensorValue == HIGH) { //if no bump go forward
    Serial.println("Way is clear, go forward");
    goForward();
  }
  else {
    currenttime = millis(); //we just bumped so set the current bump time to now
    if ( (currenttime -  basetime) > 2000) { //if this is first bump within 2 sec, back up a little and turn left
      Serial.println("First bump, back up and turn left");
      Serial.print("Current time: ");
      Serial.println(currenttime);
      Serial.print("Base time: ");
      Serial.println(basetime);
      basetime = millis(); //setting the time to compare for next time
      goBackward();
      delay(500);
      goLeft();
      delay(500);
      } 
     else { //if subsequent bump back up a little and turn right and repeat
      Serial.println("Subsequent bump, back up and turn right");
      Serial.print("Current time: ");
      Serial.println(currenttime);
      Serial.print("Base time: ");
      Serial.println(basetime);
      basetime = millis(); //setting the time to compare for next time
      goBackward();
      delay(500);
      goRight();
      delay(500);
     }    
  }
  Serial.println(" ");
}

void goForward(){
  Serial.print("Going Forward"); 
  //make both sides of wheels go forward
  digitalWrite(driverInput1A, HIGH);
  digitalWrite(driverInput2A, LOW);
  digitalWrite(driverInput3A, HIGH);
  digitalWrite(driverInput4A, LOW);

}

void goBackward(){
  Serial.print("Going Backward "); 
  //make both sides of wheels go backward
  digitalWrite(driverInput1A, LOW);
  digitalWrite(driverInput2A, HIGH);
  digitalWrite(driverInput3A, LOW);
  digitalWrite(driverInput4A, HIGH);

}

void goRight(){
  Serial.print("Going Right "); 
  //make left side go forward
  digitalWrite(driverInput1A, HIGH);
  digitalWrite(driverInput2A, LOW);
  //make right side go forward
  digitalWrite(driverInput3A, LOW);
  digitalWrite(driverInput4A, HIGH);    
}

void goLeft(){
    Serial.print("Going Left ");
  //make left side go backward
  digitalWrite(driverInput1A, LOW);
  digitalWrite(driverInput2A, HIGH);
  //make right side go forward
  digitalWrite(driverInput3A, HIGH);
  digitalWrite(driverInput4A, LOW);
}




