#include <Servo.h>
Servo myServo;
unsigned long MOVING_TIME = 5000; // moving time is 3 seconds
unsigned long moveStartTime;
unsigned long progress = 0;
int startAngle = 0;
int stopAngle = 0;

void pandown(){
  for(int pos = 180; pos>=90; pos-=1){
    myServo.write(pos);
    delay(56);
  }
}

void panup(){
  startAngle = 90;
  stopAngle = 180;
  unsigned long progress = millis() - moveStartTime;
  if (progress <= MOVING_TIME) {
  long angle = map(progress, 0, MOVING_TIME, startAngle, stopAngle);
  myServo.write(angle);
  Serial.print(angle);
  }
}

void setup() {
  myServo.attach(7);
  moveStartTime = millis();
  }

void loop() {
  for(int pos = 180; pos>=90; pos-=1){
    myServo.write(pos);
    delay(56);
  }
}
