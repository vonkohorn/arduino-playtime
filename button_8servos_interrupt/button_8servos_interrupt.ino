

#include <Servo.h>

Servo servo1;            // create servo object to control a servo
Servo servo2;            // create servo object to control a servo
Servo servo3;            // create servo object to control a servo

const byte servo1Pin = 53;
const byte servo2Pin = 51;
const byte servo3Pin = 49;
const byte buttonPin = 2;
const byte ledPin = 13;

unsigned long time = 0;
volatile byte state = LOW;

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, RISING);  // HIGH means the button is pressed
}

void loop() {
  if (state == HIGH) {
    digitalWrite(ledPin, HIGH);   // turn LED on:
    forward(); 
    delay(1000);
    reverse();
    delay(1000);
    turnRight();
    delay(1000);
    turnLeft();
    delay(1000);
    state = LOW;
  } else {
    stopRobot();
    blink();
  }
}

void buttonPress() {
  state = HIGH;
}

void blink() {
  if( millis() - time > 2000 ) {
    time = millis();
  }
  if( millis() - time < 50 ) {
    digitalWrite(ledPin, HIGH);  // turn LED on:
  } else {
    digitalWrite(ledPin, LOW);   // turn LED off:
  }
}

// Motion routines for forward, reverse, turns, and stop
void forward() {
  servo1.write(0);
  servo2.write(180);
  servo3.write(0);
}

void reverse() {
  servo1.write(180);
  servo2.write(0);
  servo3.write(180);
}

void turnRight() {
  servo1.write(180);
  servo2.write(180);
  servo3.write(180);
}
void turnLeft() {
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
}

void stopRobot() {
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
}

