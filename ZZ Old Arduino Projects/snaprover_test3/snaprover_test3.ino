//L293 information sheet
//http://www.ti.com/lit/ds/symlink/l293d.pdf

//This version adds a disc launcher to pin11. 
//In order to hook it up correctly, the Signal contact (second from right on the disc launcher)
//needs to be plugged into pin11 on the Arduino. The negative contact on the disc launcher must
//be connected to ground on the Arduino, and also to the negative contact on the snap rover. The
//postive contact on the snap rover (second from left) needs to be connected to the positive
//contact on the snap rover (+ 9v)

//disc-launcher pin
    const int discLauncherDriver = 11;

//motor IC chip-related pins
  //side L
    const int leftEnableDriver = 9;  //enableDriver12EN
    const int driverInput1A = 3;  
    const int driverInput2A = 2;  
    //const int driverOutput1Y = pin 3 on IC, goes to motor
    //const int driverOutput2Y = pin 6 on Ic, goes to motor
    int leftMotorEnabled = 1;
    int leftMotorDirection = 0;
    int leftMotorSpeed = 255;
  //side R  
    const int rightEnableDriver = 10;  //enableDriver34EN
    const int driverInput3A = 7;
    const int driverInput4A = 6;
    //const int driverOutput3Y = pin 11 on IC, goes to motor
    //const int driverOutput4Y = pin 14 on IC, goes to motor  
    int rightMotorEnabled = 1;
    int rightMotorDirection = 0;
    int rightMotorSpeed = 255;
//push button pins
  const int onOffButton = 5;
  int onOffState = 0;
  int previousOnOffState = 0;
  const int secondaryButton = 4; 
//photoresistor input
  const int photoresistorInput = A0;
  int photoresistorValue = 0;
  int turnThreshold = 750;   //adjust for how bright is the threshold for turning

void setup() {
  Serial.begin(9600);
  pinMode(secondaryButton, INPUT);
  pinMode(onOffButton, INPUT);
  pinMode(driverInput1A, OUTPUT);
  pinMode(driverInput2A, OUTPUT);  
  pinMode(driverInput3A, OUTPUT);
  pinMode(driverInput4A, OUTPUT);
  pinMode(discLauncherDriver, OUTPUT);

  digitalWrite(leftEnableDriver, HIGH);
  digitalWrite(leftEnableDriver, HIGH);
}

void loop() {
//  checkToTurnOnOffMotors();
  decideDirection();
  moveVehicle();  
//  previousOnOffState = onOffState;
}

bool checkPhotoresistor() {
  photoresistorValue = analogRead(photoresistorInput);
  Serial.print("photoresistor value: ");
  Serial.println(photoresistorValue);
  if (photoresistorValue > turnThreshold)
  {
    Serial.println("GOOD LIGHT");
    return true;
  }
  else
  {
    Serial.println("BAD LIGHT");
    return false;
  }
}

void turnLeft(){
  //when photoreceptor is getting too shadowed,
  Serial.print("Turning Left ");
  //reverse the wheels on the left
  digitalWrite(driverInput1A, HIGH);
  digitalWrite(driverInput2A, LOW);
  //keep the wheels on the right going forward  
  digitalWrite(driverInput3A, LOW);
  digitalWrite(driverInput4A, HIGH);

  //stop the disc launcher
  digitalWrite(discLauncherDriver, HIGH);
  Serial.print("NO SHOOT" );

  //**untested** optional: make it turn left a set amount of time
  //delay(4000);
}

void goStraight(){
  //when photoreceptor has enough light on it
  Serial.print("Going Straight ");
  //make both sides of wheels go forward
  digitalWrite(driverInput1A, HIGH);
  digitalWrite(driverInput2A, LOW);
  digitalWrite(driverInput3A, HIGH);
  digitalWrite(driverInput4A, LOW);

  //start the disc launcher
  digitalWrite(discLauncherDriver, LOW);
  Serial.print("SHOOOOOOT");
}
//// buggy, seems to proc when photoresistor changes straight to left
//void checkToTurnOnOffMotors() {
//  onOffState = digitalRead(onOffButton);
//  if (onOffState != previousOnOffState) 
//  {
//    if(onOffState == HIGH)
//    {
//      Serial.println("ON/OFF MOTORS PRESSED");
//      rightMotorEnabled = !rightMotorEnabled;
//      leftMotorEnabled = !leftMotorEnabled;
//      delay(4000);
//    }
//  }
//}

void decideDirection() {
  if (checkPhotoresistor())
  {
    goStraight();
  }
  else
  {
    turnLeft();
  }
}


void moveVehicle() {  
  if (rightMotorEnabled == 1) 
  {
    analogWrite(rightEnableDriver, rightMotorSpeed);//PWM the enable pin
  }
  else 
  {
    analogWrite(rightEnableDriver, 0);
  }

  
  if (leftMotorEnabled == 1) 
  {
    analogWrite(leftEnableDriver, leftMotorSpeed);//PWM the enable pin
  }
  else 
  {
    analogWrite(leftEnableDriver, 0);
  }
}

