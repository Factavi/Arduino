int delay1 = 5000;
int red = 11;
int yellow = 10;
int green = 9;
void setup() {
  // put your setup code here, to run once:
pinMode(red,OUTPUT); 
pinMode(yellow,OUTPUT);
pinMode(green,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(green,HIGH);
Serial.print("GO!\n");
delay(delay1);

digitalWrite(green,LOW);
digitalWrite(yellow,HIGH);
Serial.print("SLOW!\n");
delay(delay1/2);

digitalWrite(yellow,LOW);
digitalWrite(red,HIGH);
Serial.print("STOP!\n");
delay(delay1);

digitalWrite(red,LOW);
}
