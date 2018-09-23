const int blinker = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(blinker, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(blinker, HIGH);
  delay(1000);
  digitalWrite(blinker, LOW);
  delay(1000);
}
