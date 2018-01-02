int delay1 = 10;
int increment = 100;

void setup() {
  // put your setup code here, to run once: 
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
} 

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  delay(delay1);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  delay(delay1);

  delay1 = delay1 + increment;
  if (delay1 > 1000) {
    delay1 = 10;
  }
}
