const int analogInPin = A0;

int sensorValue = 0;
int maxSensorValue = 1024;
int 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(analogInPin);
  
  Serial.print("sensor = ");
  Serial.println(sensorValue);
}
