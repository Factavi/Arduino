/*
 * This will integrate LadyAda's IRcommander code and the Vizio
 * specific IR codes I learned with it (see ircodes.h) into the 
 * snap rover drivin' code.
 */


// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!
//uint8_t IRpin = 2;
// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
/*
 * A change from last snap-rover, the IR pin will be digital 2
 * instead of Analog A1. Also, the technique of using digitalRead 
 * is apparently too slow for IR scanning.
 */
#define IRpin_PIN      PIND
#define IRpin          2

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 10000
#define NUMPULSES 30

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20 

// What percent we will allow in variation to match the same code
#define FUZZINESS 20

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[NUMPULSES][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing

#include "ircodes.h"

/*
 * Begin snaprover_infrared code 
 */

//disc-launcher pin
    const int discLauncherDriver = 11;

//motor IC chip-related pins
  //side L
    const int leftEnableDriver = 9;  //enableDriver12EN
    const int driverInput1A = 3;  
    const int driverInput2A = 8;  
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

//Creates a toggle for step mode
boolean StepMode = false;


//initializers for the roverCommands
void roverSTOP();
void roverFORWARD();
void roverRIGHT();
void roverLEFT();
void roverREVERSE();


 

void setup(void) {
  Serial.begin(9600);
//  Serial.println("Ready to decode IR!");

  pinMode(driverInput1A, OUTPUT);
  pinMode(driverInput2A, OUTPUT);  
  pinMode(driverInput3A, OUTPUT);
  pinMode(driverInput4A, OUTPUT);
  pinMode(discLauncherDriver, OUTPUT);

  digitalWrite(leftEnableDriver, HIGH);
  digitalWrite(rightEnableDriver, HIGH);
  digitalWrite(discLauncherDriver, HIGH);
}

void loop(void) {
  int numberpulses;
  numberpulses = listenForIR();
/*
 * To discover new buttons on the remote, uncomment
 * printpulses(); below.
 */
// printpulses();

  if (IRcompare(numberpulses, VizioPowerSignal,sizeof(VizioPowerSignal)/4)) {
    Serial.println("STOP");
    roverSTOP();  
  }
  if (IRcompare(numberpulses, VizioUpSignal,sizeof(VizioUpSignal)/4)) {
    Serial.println("FORWARD");
    roverFORWARD();
    if (StepMode)
    {      
      delay(500);
      roverSTOP();
      Serial.println("STEP MODE STOPPED ME");
    }
  }
  if (IRcompare(numberpulses, VizioDownSignal,sizeof(VizioDownSignal)/4)) {
    Serial.println("DOWN");
    roverREVERSE();
    if (StepMode)
    {      
      delay(500);
      roverSTOP();
      Serial.println("STEP MODE STOPPED ME");
    }
  }
  if (IRcompare(numberpulses, VizioLeftSignal,sizeof(VizioLeftSignal)/4)) {
    Serial.println("LEFT");
    roverLEFT();
    if (StepMode)
    {      
      delay(500);
      roverSTOP();
      Serial.println("STEP MODE STOPPED ME");
    }
  }
  if (IRcompare(numberpulses, VizioRightSignal,sizeof(VizioRightSignal)/4)) {
    Serial.println("RIGHT");
    roverRIGHT();
    if (StepMode)
    {      
      delay(500);
      roverSTOP();
      Serial.println("STEP MODE STOPPED ME");
    }    
  }
  if (IRcompare(numberpulses, VizioCenterSignal,sizeof(VizioCenterSignal)/4)) {
    Serial.println("SHOOT");
    disclauncherSHOOT();
  }
  if (IRcompare(numberpulses, VizioInfoSignal,sizeof(VizioInfoSignal)/4)) {
    Serial.println("STOP SHOOTING");
    disclauncherSTOP();
  }
  if (IRcompare(numberpulses, VizioHDMISignal,sizeof(VizioHDMISignal)/4)) {
    if (StepMode)
    {      
      StepMode = false;
      Serial.println("DISENGAGE STEP MODE");
    }
    else if (!StepMode )
    {
      StepMode = true;      
      Serial.println("ENGAGE STEP MODE");
    }
  }
      
  moveVehicle();  
}

//KGO: added size of compare sample. Only compare the minimum of the two
boolean IRcompare(int numpulses, int Signal[], int refsize) {
  int count = min(numpulses,refsize);

  if ( count <= 10 ) {  //
    return false;       // this got rid of a bug that read false signals
  }                     // 
  
  for (int i=0; i< count-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;
    
#ifdef DEBUG    
    Serial.print(oncode); // the ON signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 0]); // the ON signal we want 
#endif   
    
    // check to make sure the error is less than FUZZINESS percent
    if ( abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) {
#ifdef DEBUG
      Serial.print(" (ok)");
#endif
    } else {
#ifdef DEBUG
      Serial.print(" (x)");
#endif
      // we didn't match perfectly, return a false match
      return false;
    }
    
    
#ifdef DEBUG
    Serial.print("  \t"); // tab
    Serial.print(offcode); // the OFF signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 1]); // the OFF signal we want 
#endif    
    
    if ( abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) {
#ifdef DEBUG
      Serial.print(" (ok)");
#endif
    } else {
#ifdef DEBUG
      Serial.print(" (x)");
#endif
      // we didn't match perfectly, return a false match
      return false;
    }
    
#ifdef DEBUG
    Serial.println();
#endif
  }
  // Everything matched!
  return true;
}

int listenForIR(void) {
  currentpulse = 0;
  
  while (1) {
    uint16_t highpulse, lowpulse;  // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length
  
//  while (digitalRead(IRpin)) { // this is too slow!
    while (IRpin_PIN & (1 << IRpin)) {
       // pin is still HIGH

       // count off another few microseconds
       highpulse++;
       delayMicroseconds(RESOLUTION);

       // If the pulse is too long, we 'timed out' - either nothing
       // was received or the code is finished, so print what
       // we've grabbed so far, and then reset
       
       // KGO: Added check for end of receive buffer
       if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    // we didn't time out so lets stash the reading
    pulses[currentpulse][0] = highpulse;
  
    // same as above
    while (! (IRpin_PIN & _BV(IRpin))) {
       // pin is still LOW
       lowpulse++;
       delayMicroseconds(RESOLUTION);
        // KGO: Added check for end of receive buffer
        if (((lowpulse >= MAXPULSE)  && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    pulses[currentpulse][1] = lowpulse;

    // we read one high-low pulse successfully, continue!
    currentpulse++;
  }
}
void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  for (uint8_t i = 0; i < currentpulse; i++) {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.println(" usec");
  }
  
  // print it in a 'array' format
  Serial.println("int IRsignal[] = {");
  Serial.println("// ON, OFF (in 10's of microseconds)");
  for (uint8_t i = 0; i < currentpulse-1; i++) {
    Serial.print("\t"); // tab
    Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
    Serial.print(", ");
    Serial.print(pulses[i+1][0] * RESOLUTION / 10, DEC);
    Serial.println(",");
  }
  Serial.print("\t"); // tab
  Serial.print(pulses[currentpulse-1][1] * RESOLUTION / 10, DEC);
  Serial.print(", 0};");
}

void disclauncherSTOP()
{
  digitalWrite(discLauncherDriver, HIGH);
}

void disclauncherSHOOT()
{
  digitalWrite(discLauncherDriver, LOW);
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



