int switchState = 0;

int switched = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);

  Serial.begin(9600);
}
void loop() {
  switchState = digitalRead(2);    //this checks if the button is pressed or not
  if (switchState == LOW) { //the button is not pressed
    digitalWrite(3, HIGH); //green LED  
    digitalWrite(4, LOW); // red LED
    digitalWrite(5, LOW); // red LED
    
    if (switched == 0) {
      
      Serial.print("ready...\n");
      
      Serial.print("switched variable = ");
      Serial.print(switched);
      Serial.print(". \n");
      Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      switched = 1;
    }
  }
  else {  // the button is pressed
     if (switched == 1) {
           Serial.print("LAUNCH\n");
           Serial.print("switched variable = ");
           Serial.print(switched);
           Serial.print(". \n");
           Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
           switched = 0;
     }
     digitalWrite(3, LOW);  
     digitalWrite(4, LOW);     
     digitalWrite(5, HIGH);

     delay(50); //wait for a quarter second
     digitalWrite(4, HIGH);     
     digitalWrite(5, LOW);
     delay(50); //wait for a quarter second
  }
}//go back to the beginning  of the loop
