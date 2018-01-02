const int infraredReceiver = A1;

void setup() {
  Serial.begin(9600);
  pinMode(infraredReceiver, INPUT);
}

void switchMode();

unsigned long time0 = 0;
unsigned long pressCounter = 0;
unsigned long lastPressTime = 0;
void loop() {
  int infraredValue = digitalRead(infraredReceiver);
  if ( infraredValue == 0 )
  {
      pressDetect( millis() );
  }
  if ( pressCounter > 0 && ( millis() - lastPressTime > 500) )
  {
    switchMode();
  }
  
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
      break;
    case 2:
      Serial.println("FORWARD");
      pressCounter = 0;
      break;
    case 3:
      Serial.println("LEFT");
      pressCounter = 0;
      break;
    case 4:
      Serial.println("RIGHT");
      pressCounter = 0;
      break;
    case 5:  
      Serial.println("REVERSE");
      pressCounter = 0;
      break;
    default:
      Serial.println("DEBUG");
      pressCounter = 0;
      break;
  }
}

