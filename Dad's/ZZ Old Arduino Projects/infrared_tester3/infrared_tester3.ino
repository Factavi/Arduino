//with this one we are trying to find the IR signatures
//of the different buttons on the remote. Theory: the
//remote sends info at different frequencies for each
//button.

const int infraredReceiver = A1;

void setup() {
  Serial.begin(9600);
  pinMode(infraredReceiver, INPUT);
}

unsigned long time0 = 0;
unsigned long pressCounter = 0;
unsigned long lastPressTime = 0;

void loop() {
  int infraredValue = digitalRead(infraredReceiver);
//  Serial.println( infraredValue );
  if ( infraredValue == 0 ) 
  {
    pressDetect (micros());
  }
}

int oneCounter = 0;
int zeroCounter = 0;

void pressDetect( unsigned long t ) {
  //once button is pressed, it will start sending 0s
  unsigned long difference = t - time0;
  if ( difference > 9000 )
  {
    oneCounter++;
    if (zeroCounter > 0)
    { Serial.print("Zeros: ");
      Serial.println(zeroCounter); 
    }
    zeroCounter = 0;
  }
  else if  (difference > 50 && difference < 1000)
  {
    zeroCounter++;
    if (oneCounter > 0)
    { Serial.print("Ones: ");
      Serial.println(oneCounter); 
    }
    oneCounter = 0;
  }
  time0 = t;
}


