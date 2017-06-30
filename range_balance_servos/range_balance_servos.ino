

#include <Servo.h>
#include "Ultrasonic.h"
Servo servo1;            // create servo object to control a servo

const byte servo1Pin = 9;
const byte ledPin = 13;
Ultrasonic ultrasonic1(7,4);
Ultrasonic ultrasonic2(12,8);
volatile float angle;
volatile float smoothed = 90.0;

unsigned long time = 0;
long distance1, distance2;

void setup() {
  servo1.attach(servo1Pin);
}

void loop() {
  distance1 = ultrasonic1.Ranging(CM);
  distance2 = ultrasonic2.Ranging(CM);
  angle = 90 - distance1 + distance2;
  angle = max(angle,0);
  angle = min(angle,180);
  smoothed = (smoothed*20 + angle)/21;
  servo1.write(smoothed);
  digitalWrite(ledPin, HIGH);  // turn LED on:
  delay(10);
  digitalWrite(ledPin, LOW);   // turn LED off:
}

