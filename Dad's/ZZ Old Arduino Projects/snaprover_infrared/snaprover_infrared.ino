//This version integrates the infrared tester 2 with
//the snaprover test 3, so we have a bot which can 
//go forward, backward, stop, and turn both directions
//depending on number of button presses.

//infrared receiver pin
    const int infraredReceiver = A1;

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
    
//initializers for the infrared part
void switchMode();
unsigned long time0 = 0;
unsigned long pressCounter = 0;
unsigned long lastPressTime = 0;

//initializers for the roverCommands
void roverSTOP();
void roverFORWARD();
void roverRIGHT();
void roverLEFT();
void roverREVERSE();

void setup() {
  Serial.begin(9600);
  pinMode(infraredReceiver, INPUT);
  pinMode(driverInput1A, OUTPUT);
  pinMode(driverInput2A, OUTPUT);  
  pinMode(driverInput3A, OUTPUT);
  pinMode(driverInput4A, OUTPUT);
  pinMode(discLauncherDriver, OUTPUT);

  digitalWrite(leftEnableDriver, HIGH);
  digitalWrite(leftEnableDriver, HIGH);
  digitalWrite(discLauncherDriver, HIGH);
}




void loop() {
  int infraredValue = digitalRead(infraredReceiver);
  if ( infraredValue == 0 )
  {
      pressDetect( millis() );
  }
  if ( pressCounter > 0 && ( millis() - lastPressTime > 750) )
  {
    switchMode();
  }
  moveVehicle();
}
int onOff = 0;
void pressDetect( unsigned long t ) {
  //allow user to press button a number of times
  //to signal the rover
  if ( millis() - lastPressTime > 1000 )
  {
    pressCounter = 0;
  }
  if ( ( t - time0 ) > 50)
  {
    Serial.println("pressed!");
    pressCounter++;
    lastPressTime = millis();
  }  
  time0 = t;
}

void switchMode()
{
  switch (pressCounter)
  {
    case 1:
      Serial.println("STOP");
      pressCounter = 0;
      roverSTOP();
      //stop the disc launcher too
      digitalWrite(discLauncherDriver, HIGH);
      break;
    case 2:
      Serial.println("FORWARD");
      roverFORWARD();
      pressCounter = 0;
      break;
    case 3:
      Serial.println("LEFT");
      roverLEFT();
      pressCounter = 0;
      break;
    case 4:
      Serial.println("RIGHT");
      roverRIGHT();
      pressCounter = 0;
      break;
    case 5:  
      Serial.println("REVERSE");
      roverREVERSE();
      pressCounter = 0;
      break;
     case 6:  
      Serial.println("SHOOT");
      digitalWrite(discLauncherDriver, LOW);
      pressCounter = 0;
      break;
     case 7: 
      Serial.println("STOP SHOOTIN");
      digitalWrite(discLauncherDriver, HIGH);
    default:
      Serial.println("DEBUG");
      pressCounter = 0;
      break;
  }
}

void roverSTOP()
{
  digitalWrite(driverInput1A, LOW);
  digitalWrite(driverInput2A, LOW);
  digitalWrite(driverInput3A, LOW);
  digitalWrite(driverInput4A, LOW);
}

void roverFORWARD()
{
  //make both sides of wheels go forward
  digitalWrite(driverInput1A, HIGH);
  digitalWrite(driverInput2A, LOW);
  digitalWrite(driverInput3A, HIGH);
  digitalWrite(driverInput4A, LOW);
}

void roverLEFT()
{
  digitalWrite(driverInput1A, LOW);
  digitalWrite(driverInput2A, HIGH);
  digitalWrite(driverInput3A, HIGH);
  digitalWrite(driverInput4A, LOW);
}

void roverRIGHT()
{
  digitalWrite(driverInput1A, HIGH);
  digitalWrite(driverInput2A, LOW);
  digitalWrite(driverInput3A, LOW);
  digitalWrite(driverInput4A, HIGH);  
}

void roverREVERSE()
{
  digitalWrite(driverInput1A, LOW);
  digitalWrite(driverInput2A, HIGH);
  digitalWrite(driverInput3A, LOW);
  digitalWrite(driverInput4A, HIGH);  

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

