#include <Servo.h>
Servo myservo;

const int x_pin = A0;

void setup () {
  analogReference(EXTERNAL);
  Serial.begin(9600);
  myservo.attach(3);
}

void loop(){
  
  int x;
  
  // read pins and obtain  accelerometer input
  x = analogRead(x_pin);
  
  myservo.write(map(x, 448,576,0,180));
  delay(500);
}