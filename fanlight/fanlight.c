#define fan_control A0
#define fan_pin 10
#define light_control 9
#define light_pin 11


int fan_setting = 0;
int light_setting = 0;


void fan();
void light();

void setup() {
  pinMode(light_pin, OUTPUT);
  pinMode(fan_pin, OUTPUT);
  pinMode(fan_control, INPUT PULLUP);
  pinMode(light_control, INPUT PULLUP);
}

void loop() {
  if (digitalRead(fan_control) == LOW) {
    fan_setting++;
    if (fan_setting == 3) {
      fan_setting = 0;
    }
    fan();
  }
  if (digitalRead(light_control) == LOW) {
    light_setting++;
    if (light_setting == 3) {
      light_setting = 0;
    }
    light();
  }
  delay(1000);
}

void fan() {
  if (fan_setting == 0) {
    analogWrite(fan_pin, 0);
  }
  else if(fan_setting == 1) {
    analogWrite(fan_pin, 127);
  }
  else if(fan_setting == 2) {
    analogWrite(fan_pin, 255);
  }
}

void light() {
  if (light_setting == 0) {
    analogWrite(light_pin, 0);
  }
  else if(light_setting == 1) {
    analogWrite(light_pin, 127);
  }
  else if(light_setting == 2) {
    analogWrite(light_pin, 255);
  }
}
