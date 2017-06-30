

#include <Servo.h>
#include "Ultrasonic.h"
Servo servo1;            // create servo object to control a servo
Servo servo2;            // create servo object to control a servo
Servo servo3;            // create servo object to control a servo

const byte servo1Pin = 9;
const byte servo2Pin = 10;
Ultrasonic ultrasonic1(12,13);
Ultrasonic ultrasonic2(4,2);

unsigned long time = 0;
long distance1, distance2;

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
}

void loop() {
  distance1 = ultrasonic1.Ranging(CM);
  if (distance1 < 0) {distance1 = 0;} 
  if (distance1 > 600) {distance1 = 600;} 
  distance1 = map(distance1,0,600,0,180);

  distance2 = ultrasonic2.Ranging(CM);
  if (distance2 < 0) {distance2 = 0;} 
  if (distance2 > 600) {distance2 = 600;} 
  distance2 = map(distance2,0,600,0,180);

  servo1.write(distance1);
  servo2.write(distance2);

  delay(100000);
}

