
#include <Servo.h>

Servo servoLeft;            // create servo object to control a servo
Servo servoRight;            // create servo object to control a servo

const int sensorPin = A0;
const byte servoLeftPin = 9;
const byte servoRightPin = 10;
volatile int smoothed = 0;

void setup() {
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
  pinMode(sensorPin, INPUT);
}

void loop() {
  smoothed = (smoothed*2 + analogRead(sensorPin)/5)/3;
  servoLeft.write(smoothed);
  servoRight.write(180-smoothed);
  delay(10);
}


