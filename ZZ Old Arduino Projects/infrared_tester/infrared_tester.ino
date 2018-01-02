const int infraredReceiver = A1;

void setup() {
  Serial.begin(9600);
  pinMode(infraredReceiver, INPUT);
}

void switchMode();

void loop() {
  int infraredValue = digitalRead(infraredReceiver);
  if ( infraredValue == 0 )
  {
    switchMode();
  }
}
int onOff = 0;
void switchMode() {
  if ( onOff == 0 )
  {
    Serial.println("On!");
    onOff = 1;
    delay(300);
   // Serial.println("Listening again");

  }
  else if (onOff == 1 )
  {
    Serial.println("Off!");
    onOff = 0;
    delay(300);
   // Serial.println("Listening again");
  }
}

