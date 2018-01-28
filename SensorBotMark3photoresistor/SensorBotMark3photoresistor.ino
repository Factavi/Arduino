//L293 information sheet
//http://www.ti.com/lit/ds/symlink/l293d.pdf

//This project uses Arduino UNO and the L293DNE IC to run two 
//motors independently forward and backward, and with speed 
//adjustable with pulse-width modulation (PWM). 

/*
 * This is the photoresistor robot
 * 
 * 
 * 
 * 
 */


const int sensorPin = A0;
int sensorValue = 0;
int sensorLowThreshold = 1;
int sensorHighThreshold = 1000;

const int dialPin = A1; // we are adding a potentiometer to adjust settings on the fly
int dialValue = 0;  // variable to store the setting on the potentiometer 

// Hook up the Arduino to the L293 IC, and define constants: 

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

// debug LEDs
  const int forwardLED = 4;
  const int backwardLED = 5;
  const int rightLED = 8;
  const int leftLED = 12;
  
void setup() {
  Serial.begin(9600);
  pinMode(leftEnableDriver, OUTPUT);
  pinMode(rightEnableDriver, OUTPUT); 
  pinMode(driverInput1A, OUTPUT);
  pinMode(driverInput2A, OUTPUT);
  pinMode(driverInput3A, OUTPUT);
  pinMode(driverInput4A, OUTPUT);

  pinMode(forwardLED, OUTPUT);
  pinMode(backwardLED, OUTPUT);

  //set the wheels to spinning
  digitalWrite(leftEnableDriver, HIGH);
  digitalWrite(rightEnableDriver, HIGH);
}

void loop() {

dialValue = analogRead(dialPin);
Serial.print("dial Value: ");
Serial.println(dialValue);
  
int oldSensorValue = sensorValue;
sensorValue = analogRead(sensorPin);
int sensorDifference = oldSensorValue -sensorValue; 
  
  if ( (sensorValue > sensorLowThreshold) && (sensorValue < sensorHighThreshold) ){
      Serial.print("In light range.\n");
      Serial.print(sensorValue);
      if ( sensorDifference < -5   && oldSensorValue != 0 ){
        Serial.print("I notice I am getting closer to shadow.\n"); 
        goBackward(); 
        delay(1000);
       //goRight();
       //   delay(200);
      }
      else 
      {
        Serial.println("I feel I should be safe going forward.");
        goForward();
      }
  }
  else {
    Serial.print("Out of light range.\n");
    Serial.print(sensorValue);
  }
  delay(500);

}

void goForward(){
    Serial.print("Going Forward");
  //make both sides of wheels go forward
  digitalWrite(driverInput1A, HIGH);
  digitalWrite(driverInput2A, LOW);
  digitalWrite(driverInput3A, HIGH);
  digitalWrite(driverInput4A, LOW);
  //debug lights
  digitalWrite(forwardLED, HIGH);
  digitalWrite(backwardLED, LOW);
  digitalWrite(rightLED, LOW);
  digitalWrite(leftLED, LOW);
}

void goBackward(){
    Serial.print("Going Backward ");
  //make both sides of wheels go backward
  digitalWrite(driverInput1A, LOW);
  digitalWrite(driverInput2A, HIGH);
  digitalWrite(driverInput3A, LOW);
  digitalWrite(driverInput4A, HIGH);
  //debug lights
  digitalWrite(forwardLED, LOW);
  digitalWrite(backwardLED, HIGH);
  digitalWrite(rightLED, LOW);
  digitalWrite(leftLED, LOW);
}

void goRight(){
    Serial.print("Going Right ");
  //make left side go forward
  digitalWrite(driverInput1A, HIGH);
  digitalWrite(driverInput2A, LOW);
  //make right side go forward
  digitalWrite(driverInput3A, LOW);
  digitalWrite(driverInput4A, HIGH);    
  //debug lights
  digitalWrite(forwardLED, LOW);
  digitalWrite(backwardLED, LOW);
  digitalWrite(rightLED, HIGH);
  digitalWrite(leftLED, LOW);
}

void goLeft(){
    Serial.print("Going Left ");
  //make left side go backward
  digitalWrite(driverInput1A, LOW);
  digitalWrite(driverInput2A, HIGH);
  //make right side go forward
  digitalWrite(driverInput3A, HIGH);
  digitalWrite(driverInput4A, LOW);
  //debug lights
  digitalWrite(forwardLED, LOW);
  digitalWrite(backwardLED, LOW);
  digitalWrite(rightLED, LOW);
  digitalWrite(leftLED, HIGH);
}




