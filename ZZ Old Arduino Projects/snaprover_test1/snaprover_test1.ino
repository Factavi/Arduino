const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int onOffSwitchStateSwitchPin = 5;

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 1000;
int motorDirection = 1;

int motorSwitcher = 0;

void setup() {
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW);
}

void loop() {
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  if (motorSwitcher < 1000)
  {
    motorSwitcher++;
  }
  else
  {
    motorDirection = !motorDirection;
    motorSwitcher = 0;
  }
  if (onOffSwitchState != previousOnOffSwitchState) 
  {
    if(onOffSwitchState == HIGH)
    {
      motorEnabled = !motorEnabled;
    }
  }

  if (motorDirection == 1) 
  {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW); 
  }
  else 
  {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH); 
  }

  if (motorEnabled == 1) 
  {
    analogWrite(enablePin, motorSpeed);//PWM the enable pin
  }
  else 
  {
    analogWrite(enablePin, 0);
  }
  
  previousOnOffSwitchState = onOffSwitchState;
}
