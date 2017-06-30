

#include <Servo.h>

Servo servo1;            // create servo object to control a servo
Servo servo2;            // create servo object to control a servo
Servo servo3;            // create servo object to control a servo

const byte servo1Pin = 3;
const byte servo2Pin = 9;
const byte servo3Pin = 10;
#define trigPin1 13
#define echoPin1 12
#define trigPin2 4
#define echoPin2 2
#define trigPin3 7
#define echoPin3 8

unsigned long time = 0;
long duration1, distance1;
long duration2, distance2;
long duration3, distance3;

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

void loop() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 / 2 / 29.1;        // in cm
  if (distance1 < 0) {distance1 = 0;} 
  if (distance1 > 220) {distance1 = 220;} 
  distance1 = map(distance1,0,220,0,180);
  servo1.write(distance1);

  
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 / 2 / 29.1;        // in cm
  if (distance2 < 0) {distance2 = 0;} 
  if (distance2 > 220) {distance2 = 220;} 
  distance2 = map(distance2,0,220,0,180);
  servo2.write(distance2);
  
  
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 / 2 / 29.1;        // in cm
  if (distance3 < 0) {distance3 = 0;} 
  if (distance3 > 220) {distance3 = 220;} 
  distance3 = map(distance3,0,220,0,180);
  servo3.write(distance3);

  delay(100);
}

