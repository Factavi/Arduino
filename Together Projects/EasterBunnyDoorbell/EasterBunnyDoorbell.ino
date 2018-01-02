int sensorPin = A0;    // select the input pin for the potentiometer
int triggerPin = 4;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int counter = 0;
int sensorvalueLast = 700;
int comparator = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(triggerPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(triggerPin, HIGH);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // write the value to serial
  Serial.println(sensorValue);
  Serial.println(counter);
  comparator = sensorvalueLast - sensorValue;
  sensorvalueLast = sensorValue;
  if (comparator > 100)
  {
  counter++;
  }
  if (counter > 0)
{
    digitalWrite(triggerPin, LOW); 
    counter = 0;
  }
  else
  {
    digitalWrite(triggerPin, HIGH);
  }
  // stop the program for for <sensorValue> milliseconds:
  delay(300);
}
